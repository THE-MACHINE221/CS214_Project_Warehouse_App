#include "warehouse_hash.h"
#include "rapidcsv.h"
#include <iostream>
#include <fstream>

Product* Warehouse_Hash::findProduct(int productId) {
    int index = hashFunction(productId);
    list<Product>& chain = table[index];

    for (auto it = chain.begin(); it != chain.end(); it++) {
        if (it->id == productId) {
            return &(*it);
        }
    }
    return NULL;
}

void Warehouse_Hash::editProduct(int productId, string newName, double newPrice, int newQty) {
    Product* productToEdit = findProduct(productId);

    if (productToEdit != NULL) {
        productToEdit->name = newName;
        productToEdit->price = newPrice;
        productToEdit->qty = newQty;
        cout << "Product with ID " << productId << " has been updated." << endl;
    } else {
        cout << "Could not edit. Product with ID " << productId << " not found." << endl;
    }
}

void Warehouse_Hash::addProduct(Product p) {
    int index = hashFunction(p.id);
    table[index].push_back(p);
}

void Warehouse_Hash::loadFromCSV(string filename) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i].clear();
    }

    rapidcsv::Document doc(filename);

    for (size_t i = 0; i < doc.GetRowCount(); i++) {
        Product p;
        p.id = doc.GetCell<int>("product_id", i);
        p.name = doc.GetCell<string>("product_name", i);
        p.price = doc.GetCell<double>("price", i);
        p.qty = doc.GetCell<int>("qty", i);
        addProduct(p);
    }
    cout << "Loaded " << doc.GetRowCount() << " products into hash table from " << filename << endl;
}

void Warehouse_Hash::saveToCSV(string filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    file << "product_id,product_name,price,qty\n";

    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (auto product : table[i]) {
            file << product.id << ","
            << "\"" << product.name << "\","
            << product.price << ","
            << product.qty << "\n";
            count++;
        }
    }

    cout << "Saved " << count << " products to " << filename << endl;
}
