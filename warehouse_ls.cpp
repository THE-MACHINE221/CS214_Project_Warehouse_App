#include "warehouse_ls.h"
#include "rapidcsv.h"
#include <iostream>
#include <fstream>
using namespace std;

Warehouse_LS::Warehouse_LS() {
    head = NULL;
}

Warehouse_LS::~Warehouse_LS() {
    ProductNode* temp = head;
    while (temp != NULL) {
        ProductNode* q = temp;
        temp = temp->next;
        delete q;
    }
    head = NULL;
}

void Warehouse_LS::addProduct(Product p) {
    // Add at the beginning for best time complexity.
    ProductNode* q = new ProductNode(p);
    q->next = head;
    head = q;
}

void Warehouse_LS::removeProduct(int ID) { // Remove by ID.
    ProductNode* current = head;
    ProductNode* prev = NULL;

    while (current != NULL && current->data.id != ID) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "Product with ID " << ID << " not found." << endl;
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    cout << "Product with ID " << ID << " removed." << endl;
}

void Warehouse_LS::loadFromCSV(string filename) {
    // Deconstruct the previous list if any:
    while (head != NULL) {
        ProductNode* temp = head;
        head = head->next;
        delete temp;
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
    cout << "Loaded " << doc.GetRowCount() << " products from " << filename << endl;
}

void Warehouse_LS::saveToCSV(string filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return;
    }

    file << "product_id,product_name,price,qty\n";

    ProductNode* current = head;
    int count = 0;
    while (current != NULL) {
        file << current->data.id << ","
             << "\"" << current->data.name << "\","
             << current->data.price << ","
             << current->data.qty << "\n";
        current = current->next;
        count++;
    }

    cout << "Saved " << count << " products to " << filename << endl;
}

int Warehouse_LS::getMaxId() {
    if (head == NULL) {
        return 0; // start IDs from 1 (in main getMaxId() + 1), that's why return 0 not 1.
    }

    int maxId = 0;
    ProductNode* current = head;
    while (current != NULL) {
        if (current->data.id > maxId) {
            maxId = current->data.id;
        }
        current = current->next;
    }
    return maxId;
}
