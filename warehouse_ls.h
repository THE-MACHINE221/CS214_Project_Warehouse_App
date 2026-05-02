// Linked list for insertion and deletion, since it has the best time complexity for that.

#ifndef WAREHOUSE_LS_H
#define WAREHOUSE_LS_H


#include "product.h"
#include <string>
using namespace std;

struct ProductNode {
    Product data;
    ProductNode* next;

    ProductNode(Product p) : data(p), next(NULL) {}
};

class Warehouse_LS {
private:
    ProductNode* head;

public:
    Warehouse_LS();
    ~Warehouse_LS();

    void addProduct(Product p);
    void removeProduct(int productId);
    void loadFromCSV(string filename);
    void saveToCSV(string filename);
    int getMaxId();
};

#endif
