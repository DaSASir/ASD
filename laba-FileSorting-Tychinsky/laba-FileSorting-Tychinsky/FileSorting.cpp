#include "FileSorting.h"
#include <iostream>
#include <fstream>
#include <string>

void CreateFile(const std::string& fileName, const int minNum, const int maxNum, const int amountNum) {
    std::ofstream file(fileName);
    if (!file.is_open())
        exit(-1);
    for (int i = 0; i < amountNum; i++)
        file << rand() % (maxNum - minNum + 1) + minNum << " ";
    file.close();
}

void Print(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        exit(-1);
    int value;
    while (file >> value)
        std::cout << value << " ";
    file.close();
}