/*
   Must implement these operations:
   1- add (done Linked list)
   2- edit (done Hash map)
   3- delete (done Linked list)
   4- print (done)
   5- search (done Binary Search Tree)
   6- exit (done)

   2 data structures (from the course) == linked list and binary search tree
   1 data structure (outside the course) == hash map and vectors

   read and write to a file (done by csv file)

   avoid globals (done)
*/

#include "warehouse.h"
#include "warehouse_ls.h"
#include "warehouse_hash.h"
#include "warehouse_bst.h"
#include "Helper.h"
#include <iostream>

using namespace std;

int main() {

    int choice;
    do {
        clearScreen();
        displayMenu();
        choice = get_UI_choice();

        switch (choice) {
            case ADD: {
               Warehouse_LS ls_warehouse;
               ls_warehouse.loadFromCSV("ProductsData_clean.csv");

               Product newProduct;
               newProduct.id = ls_warehouse.getMaxId() + 1; // ID is auto-assigned

               cout << "Enter Product Name: ";
               getline(cin, newProduct.name);

               cout << "Enter Product Price: ";
               cin >> newProduct.price;
               fixInput(newProduct.price);

               cout << "Enter Product Quantity: ";
               cin >> newProduct.qty;
               fixInput(newProduct.qty);

               if (!confirm())
                  break;

               ls_warehouse.addProduct(newProduct);
               ls_warehouse.saveToCSV("ProductsData_clean.csv");
               break;
            }

            case EDIT: {
               Warehouse_Hash hash_warehouse;
               hash_warehouse.loadFromCSV("ProductsData_clean.csv");

               int edit_ID;
               cout << "Enter the ID of the product to edit: ";
               cin >> edit_ID;
               fixInput(edit_ID);

               if (!confirm())
                  break;

               Product* product = hash_warehouse.findProduct(edit_ID);

               if (product) {
                  string newName;
                  double newPrice;
                  int newQty;

                  cout << "Enter new Product Name (current: " << product->name << "): ";
                  getline(cin, newName);

                  cout << "Enter new Product Price (current: " << product->price << "): ";
                  cin >> newPrice;
                  fixInput(newPrice);

                  cout << "Enter new Product Quantity (current: " << product->qty << "): ";
                  cin >> newQty;
                  fixInput(newQty);

                  hash_warehouse.editProduct(edit_ID, newName, newPrice, newQty);
                  hash_warehouse.saveToCSV("ProductsData_clean.csv");
               } else {
                  cout << "Product with ID " << edit_ID << " not found." << endl;
               }
               break;
            }

            case DELETE: {
               Warehouse_LS ls_warehouse;
               ls_warehouse.loadFromCSV("ProductsData_clean.csv");

               int delete_ID;
               cout << "Enter the ID of the product to delete: ";
               cin >> delete_ID;
               fixInput(delete_ID);

               if (!confirm()) {
                  break; 
               }

               ls_warehouse.removeProduct(delete_ID);
               ls_warehouse.saveToCSV("ProductsData_clean.csv");
               break;
            }

            case PRINT: {
               Warehouse w;
               w.loadFromCSV("ProductsData_clean.csv");
               w.showAll();
               break;
            }

            case SEARCH: {
               int searchChoice;
               enum SEARCH {
                  ID = 1,
                  NAME,
                  PRICE,
                  QTY,
                  BACK = -1
               };

               cout << "Search by:" << endl
               << SEARCH::ID << ". ID" << endl
               << SEARCH::NAME << ". Name" << endl
               << SEARCH::PRICE << ". Price" << endl
               << SEARCH::QTY << ". Quantity" << endl
               << SEARCH::BACK << ". Back" << endl
               << "Enter your choice: ";
               cin >> searchChoice;
               fixInput(searchChoice);

               switch (searchChoice) {
                  case ID: {
                     Warehouse_Hash hash_warehouse;
                     hash_warehouse.loadFromCSV("ProductsData_clean.csv");
                     int id;
                     cout << "Enter Product ID to find: ";
                     cin >> id;
                     fixInput(id);

                     Product* found = hash_warehouse.findProduct(id);
                     if (found) {
                        cout << "Product Found:" << endl
                        << "ID: " << found->id << ", Name: " << found->name 
                        << ", Price: " << found->price << ", Qty: " << found->qty << endl;
                     } else {
                        cout << "Product doesn't exist." << endl;
                     }
                     break;
                  }
                  
                  case NAME: {
                     Warehouse_BST bst_warehouse;
                     bst_warehouse.loadFromCSV("ProductsData_clean.csv");
                     string name;
                     cout << "Enter product name to search for: ";
                     getline(cin, name);

                     vector<Product> results = bst_warehouse.searchByName(name);
                     if (!results.empty()) {
                        cout << "Found " << results.size() << " matching products:" << endl;
                        for (auto p : results) {
                           cout << "ID: " << p.id << ", Name: " << p.name 
                           << ", Price: " << p.price << ", Qty: " << p.qty << endl;
                        }
                     } else {
                        cout << "No products found with this name." << endl;
                     }
                     break;
                  }

                  case PRICE: {
                     Warehouse_BST bst_warehouse;
                     bst_warehouse.loadFromCSV("ProductsData_clean.csv");
                     double price;
                     cout << "Enter product price to search for: ";
                     cin >> price;
                     fixInput(price);

                     vector<Product> results = bst_warehouse.searchByPrice(price);
                     if (!results.empty()) {
                        cout << "Found " << results.size() << " matching products:" << endl;
                        for (auto p : results) {
                           cout << "ID: " << p.id << ", Name: " << p.name 
                           << ", Price: " << p.price << ", Qty: " << p.qty << endl;
                        }
                     } else {
                        cout << "No products found at this price." << endl;
                     }
                     break;
                  }

                  case QTY: {
                     Warehouse_BST bst_warehouse;
                     bst_warehouse.loadFromCSV("ProductsData_clean.csv");
                     int qty;
                     cout << "Enter product quantity to search for: ";
                     cin >> qty;
                     fixInput(qty);

                     vector<Product> results = bst_warehouse.searchByQty(qty);
                     if (!results.empty()) {
                        cout << "Found " << results.size() << " matching products:" << endl;
                        for (auto p : results) {
                           cout << "ID: " << p.id << ", Name: " << p.name 
                           << ", Price: " << p.price << ", Qty: " << p.qty << endl;
                        }
                     } else {
                        cout << "No products found with that quantity." << endl;
                     }
                     break;
                  }

                  case BACK: {
                     back();
                     break;
                  }

                  default: {
                     cout << "Invalid choice!" << endl;
                     break;
                  }
               }

            }

            case EXIT: {
               break;
            }

            default: {
               cout << "Invalid choice!" << endl;
               break;
            }
         }
        pause();
    } while (choice != EXIT);

    return 0;
}
