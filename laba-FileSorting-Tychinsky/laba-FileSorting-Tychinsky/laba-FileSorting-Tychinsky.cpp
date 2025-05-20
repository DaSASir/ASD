#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "FileSorting.h"

std::string fileName = "MainFile.txt";

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    const int numbersCount = 100000;
    const int maxNumberValue = 100000;

    std::clock_t start = clock();
    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue, 2)) {
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
    std::clock_t stop = clock();
    double timeChecker = double(stop - start) / double(CLOCKS_PER_SEC);
    std::cout << "\nTime of programm working: " << timeChecker << "sec\n";

    return 0;
}