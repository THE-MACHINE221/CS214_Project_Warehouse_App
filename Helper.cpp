#include "Helper.h"
#include <iostream>
#include <limits> // نحتاج المكتبة هذي عشان نمسح البافر

using namespace std;

void pause() {
   cout << "Press Enter to continue...";
   cin.get();
   cout << endl;
}

void back() {
    cout << "Press Enter to go back...";
    cin.get();
    cout << endl;
}

void clearBuffer() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // تمسح البافر كاملًا
}

bool confirm() {
    char choice;
    cout << "Are you sure? (y/n): ";
    cin >> choice;
    clearBuffer();

    switch (choice) {
        case 'y':
            return true;
        case 'Y':
            return true;
        case 'n':
            return false;
        case 'N':
            return false;
        default:
            cout << "Invalid choice!" << endl;
            return confirm();
    }
    return false; // هذا السطر ما راح يتنفذ أبدًا، بس اضفته تفاديًا للوارننق
}

void fixInput(int& in) {
    while (cin.fail()) {
        clearBuffer();
        cout << "Wrong input!" << endl << "Enter a value: ";
        cin >> in;
    }
    clearBuffer(); // امسح البافر حتى لو كان الادخال صحيح
}

void fixInput(double& in) {
    while (cin.fail()) {
        clearBuffer();
        cout << "Wrong input!" << endl << "Enter a value: ";
        cin >> in;
    }
    clearBuffer(); // امسح البافر حتى لو كان الادخال صحيح
}


void clearScreen() {
    cout << "\033[2J\033[H"; // رمزين: الأول يمسح الشاشة، والثاني يؤدي المؤشر فوق يسار
}

void displayMenu() {
    cout << "Warehouse Management System" << endl
    << "===========================" << endl
    << UI::ADD << ". Add Product" << endl
    << UI::EDIT << ". Edit Product" << endl
    << UI::DELETE << ". Delete Product" << endl
    << UI::PRINT << ". Print All Products" << endl
    << UI::SEARCH << ". Search for Product" << endl
    << UI::EXIT << ". Exit" << endl
    << "Enter your choice: ";
}

int get_UI_choice() {
    int choice;
    cin >> choice;
        fixInput(choice);
        
    return choice;
}
