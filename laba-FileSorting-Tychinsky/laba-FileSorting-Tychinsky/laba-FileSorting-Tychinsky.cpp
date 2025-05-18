#include <iostream>
#include <fstream>
#include <string>
#include "FileSorting.h"

std::string fileName = "MainFile.txt";

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    createFileWithRandomNumbers(fileName, 10, 50);

    std::cout << "First File:";
    std::ifstream test(fileName);
    int v;
    while (test >> v) 
        std::cout << v << " ";
    test.close();

    mergersDirectAndNatural(fileName);

    std::cout << "\nSorted File:";
    std::ifstream test1(fileName);
    int v1;
    while (test1 >> v1)
        std::cout << v1 << " ";
    test1.close();


    return 0;


    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }
    }

    return 0;
}