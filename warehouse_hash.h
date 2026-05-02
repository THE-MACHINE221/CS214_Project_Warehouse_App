#ifndef WAREHOUSE_HASH_H
#define WAREHOUSE_HASH_H

#include "product.h"
#include <string>
#include <vector>
#include <list>

using namespace std;
class Warehouse_Hash {
private:
    static const int TABLE_SIZE = 100;
    list<Product> table[TABLE_SIZE];

    int hashFunction(int productId) {
        return productId % TABLE_SIZE;
    }

public:
    Product* findProduct(int productId);
    void editProduct(int productId, string newName, double newPrice, int newQty);
    void addProduct(Product p);
    void loadFromCSV(string filename);
    void saveToCSV(string filename);
};

#endif
