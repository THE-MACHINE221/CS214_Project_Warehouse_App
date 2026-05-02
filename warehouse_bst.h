#ifndef WAREHOUSE_BST_H
#define WAREHOUSE_BST_H

#include "product.h"
#include <string>
#include <vector>

using namespace std;

struct BSTNode {
    Product data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Product p) : data(p), left(NULL), right(NULL) {}
};

class Warehouse_BST {
private:
    BSTNode* root;

    void insert(BSTNode*& node, Product p);
    void destroy(BSTNode* node);
    void searchByName(BSTNode* node, const string& name, vector<Product>& results);
    void searchByPrice(BSTNode* node, double price, vector<Product>& results);
    void searchByQty(BSTNode* node, int qty, vector<Product>& results);
    void inorderTraversal(BSTNode* node, vector<Product>& products);

public:
    Warehouse_BST();
    ~Warehouse_BST();

    void addProduct(Product p);
    void loadFromCSV(string filename);
    vector<Product> searchByName(const string& name);
    vector<Product> searchByPrice(double price);
    vector<Product> searchByQty(int qty);
};

#endif
