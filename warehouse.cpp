#include "Warehouse.h"
#include "rapidcsv.h" //من قيت هب //https://github.com/d99kris/rapidcsv

#include <iostream>
using namespace std;

void Warehouse::loadFromCSV(string filename) {
    rapidcsv::Document doc(filename);
    items.clear();
    //قراءة الملف عن طريق مكتبة لقيتها ب قيت هب ف صار بس الي علي اسندهم لل ستركت
    for (size_t i = 0; i < doc.GetRowCount(); i++) {
        Product p;
        p.id = doc.GetCell<int>("product_id", i);
        p.name = doc.GetCell<string>("product_name", i);
        p.price = doc.GetCell<double>("price", i);
        p.qty = doc.GetCell<int>("qty", i);
        items.push_back(p); //بعد مايخزن كل شي بال ستركت يحطه اخر شي
    }
}

//يطبعهم بطريقه ماهي واضحه بس مفهومه لنا عشان نكمل الشغل (برجع له بعدين ) 

void Warehouse::showAll() {
    for (Product& p : items)
        cout <<p.id << " " << p.name << " " << p.price << " " << p.qty << endl;
}

// نسوي بوش للمنتج عشان يصير اخر الفيكتور
void Warehouse::addProduct(Product p) {
    items.push_back(p);
}

//we have to use two of data structere we have studied in the course
// [linked_list , dict , tuple , queue , stack , array , tree ]