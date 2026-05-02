#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector> // اول متطلب (data structere not coverd in the course)
#include <string>
#include "product.h"
using namespace std;

class Warehouse {
public:
    vector<Product> items;
    //هنا نعرف اي ميثود مثل اغلى ثلاث منتجات ولاتنسى ان المنتجات جوا فيكتور ف التعامل معهم بسيط
    void loadFromCSV(string filename);
    void showAll();
    void addProduct(Product p);
};

#endif



// items = [p1 , p2 , p3]

//p1 = p1.id , p1.name , p1.price , p1.qty


//we have to use two of data structere we have studied in the course
// [linked_list , dict , tuple , queue , stack , array , tree ]