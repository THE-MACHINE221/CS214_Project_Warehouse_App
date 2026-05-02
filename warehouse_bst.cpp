#include "warehouse_bst.h"
#include "rapidcsv.h"
#include <iostream>
#include <fstream>

Warehouse_BST::Warehouse_BST() : root(NULL) {}

Warehouse_BST::~Warehouse_BST() {
    destroy(root);
}

void Warehouse_BST::insert(BSTNode*& node, Product p) {
    if (node == NULL) {
        node = new BSTNode(p);
    } else if (p.id < node->data.id) {
        insert(node->left, p);
    } else {
        insert(node->right, p);
    }
}

void Warehouse_BST::destroy(BSTNode* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

void Warehouse_BST::addProduct(Product p) {
    insert(root, p);
}

void Warehouse_BST::loadFromCSV(string filename) {
    destroy(root);
    root = NULL;
    rapidcsv::Document doc(filename);

    for (size_t i = 0; i < doc.GetRowCount(); i++) {
        Product p;
        p.id = doc.GetCell<int>("product_id", i);
        p.name = doc.GetCell<string>("product_name", i);
        p.price = doc.GetCell<double>("price", i);
        p.qty = doc.GetCell<int>("qty", i);
        addProduct(p);
    }
    cout << "Loaded " << doc.GetRowCount() << " products into BST from " << filename << endl;
}

void Warehouse_BST::searchByName(BSTNode* node, const string& name, vector<Product>& results) {
    if (node) {
        searchByName(node->left, name, results);
        if (node->data.name.find(name) != string::npos) {
            results.push_back(node->data);
        }
        searchByName(node->right, name, results);
    }
}

void Warehouse_BST::searchByPrice(BSTNode* node, double price, vector<Product>& results) {
    if (node) {
        searchByPrice(node->left, price, results);
        if (node->data.price == price) {
            results.push_back(node->data);
        }
        searchByPrice(node->right, price, results);
    }
}

void Warehouse_BST::searchByQty(BSTNode* node, int qty, vector<Product>& results) {
    if (node) {
        searchByQty(node->left, qty, results);
        if (node->data.qty == qty) {
            results.push_back(node->data);
        }
        searchByQty(node->right, qty, results);
    }
}

void Warehouse_BST::inorderTraversal(BSTNode* node, vector<Product>& products) {
    if (node) {
        inorderTraversal(node->left, products);
        products.push_back(node->data);
        inorderTraversal(node->right, products);
    }
}

vector<Product> Warehouse_BST::searchByName(const string& name) {
    vector<Product> results;
    searchByName(root, name, results);
    return results;
}

vector<Product> Warehouse_BST::searchByPrice(double price) {
    vector<Product> results;
    searchByPrice(root, price, results);
    return results;
}

vector<Product> Warehouse_BST::searchByQty(int qty) {
    vector<Product> results;
    searchByQty(root, qty, results);
    return results;
}
