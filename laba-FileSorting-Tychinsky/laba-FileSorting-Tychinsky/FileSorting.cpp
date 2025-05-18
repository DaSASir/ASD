#include <iostream>
#include <fstream>
#include <string>
#include "FileSorting.h"

//требуемые функции
bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    if (numbersCount <= 0)
        return false;

    std::ofstream file(fileName);
    if (!file.is_open())
        return false;

    for (int i = 0; i < numbersCount; ++i)
        file << rand() % (maxNumberValue - 0 + 1) + maxNumberValue << " ";

    return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        return false;

    int value1, value2;
    file >> value1;
    while (file >> value2) {
        if (value1 > value2)
            return false;

        value1 = value2;
    }

    return true;
}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) 
        return -1;

    //sortFile(fileName); //Вызов вашей функции сортировки

    if (!isFileContainsSortedArray(fileName)) 
        return -2;

    return 1;
}

//файловые сортировки

