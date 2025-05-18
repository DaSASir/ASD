#include <iostream>
#include <fstream>
#include <string>
#include "FileSorting.h"

//требуемые функции
bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {



    return false;
}

bool isFileContainsSortedArray(const std::string& fileName) {


    return false;
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

