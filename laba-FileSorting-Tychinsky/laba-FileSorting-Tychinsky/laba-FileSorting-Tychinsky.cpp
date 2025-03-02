#include <iostream>
#include <fstream>
#include <string>
#include "FileSorting.h"

const int fileAmount = 5;

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    using std::cout;

    cout << "MainFile: ";
    CreateFile("MainFile.txt", -100, 100, 10);
    Print("MainFile.txt");
    




    return 0;
}