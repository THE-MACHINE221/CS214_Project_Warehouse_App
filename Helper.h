#ifndef HELPER_H
#define HELPER_H

enum UI {
    ADD = 1,
    EDIT,
    DELETE,
    PRINT,
    SEARCH,
    EXIT = -1
};

void pause();
void back();
void clearBuffer();
bool confirm();
void fixInput(int& in);
void fixInput(double& in);
void clearScreen();

void displayMenu();
int get_UI_choice();

#endif


