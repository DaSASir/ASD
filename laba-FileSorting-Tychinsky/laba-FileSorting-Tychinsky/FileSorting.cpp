#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <limits>
#include "FileSorting.h"

//требуемые функции
bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
    if (numbersCount <= 0)
        return false;

    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "createFileWithRandomNumbers: Error - fail is not openning" << std::endl;
        return false;
    }

    for (int i = 0; i < numbersCount; ++i)
        file << std::rand() % (maxNumberValue*2 + 1) - maxNumberValue << " ";

    file.close();
    return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "isFileContainsSortedArray: Error - fail is not openning" << std::endl;
        return false;
    }

    int value1, value2;
    file >> value1;
    while (file >> value2) {
        if (value1 > value2)
            return false;

        value1 = value2;
    }

    file.close();
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
void mergersDirectAndNatural(const std::string& fileName, const bool sortType) {
    int p = 1;
    splitFiles(sortType, fileName);

    while (true) {
        std::ifstream check("file1.txt");
        if (!check.is_open()) {
            std::cerr << "mergersDirectAndNatural: Error - check fail is not openning" << std::endl;
            return;
        }
        int value;
        if (!(check >> value)) break;
        check.close();

        sortType ? mergeFiles(sortType) : mergeFiles(sortType, p);
        p *= 2;
    }

    std::ofstream fileMain(fileName);
    std::ifstream fileDop("file0.txt");
    if (!fileMain.is_open() || !fileDop.is_open()) {
        std::cerr << "mergersDirectAndNatural: Error - Main or Dop fail is not openning" << std::endl;
        return;
    }
    int value;
    while (fileDop >> value) 
        fileMain << value << " ";
    fileMain.close();
    fileDop.close();
}

void splitFiles(const bool sortType, const std::string& fileName) {
    std::ifstream fileMain(fileName);
    std::ofstream fileDop1("file0.txt"), fileDop2("file1.txt");
    if (!fileMain.is_open() || !fileDop1.is_open() || !fileDop2.is_open()) {
        std::cerr << "splitFiles: Error - fails is not openning" << std::endl;
        return;
    }

    int value1, value2;
    int index = 0;
    switch (sortType) {
    case false:
        while (fileMain >> value1)
            (index++ % 2 == 0 ? fileDop1 : fileDop2) << value1 << " ";
        break;

    case true:
        fileMain >> value1;
        while (fileMain >> value2) {
            (index % 2 == 0 ? fileDop1 : fileDop2) << value1 << " ";
            if (value1 > value2) {
                (index % 2 == 0 ? fileDop1 : fileDop2) << std::numeric_limits<int>::max() << " ";
                index++;
            }
            value1 = value2;
        }
        (index % 2 == 0 ? fileDop1 : fileDop2) << value1 << " ";
        break;
    }

    fileMain.close();
    fileDop1.close();
    fileDop2.close();
}

void mergeFiles(const bool sortType, const int p) {
    std::ifstream fileRead[2];
    std::ofstream fileWrite[2] = {
        std::ofstream("file2.txt"),
        std::ofstream("file3.txt")
    };

    for (int i = 0; i < 2; ++i) {
        fileRead[i].open("file" + std::to_string(i) + ".txt");
        if (!fileRead[i].is_open() || !fileWrite[i].is_open()) {
            std::cerr << "mergeFiles: Error - fails is not openning" << std::endl;
            for (auto& file : fileRead) file.close();
            for (auto& file : fileWrite) file.close();
            return;
        }
    }
    
    int indexOutFiles = 0;
    bool haveValue = true;

    while (haveValue) {
        haveValue = false;
        bool isLastStep = true;
        std::vector<int> block1, block2;
        int val;

        for (int i = 0; i < p && fileRead[0] >> val; ++i) {
            if (val == std::numeric_limits<int>::max()) break;
            block1.push_back(val);
            haveValue = true;
        }

        for (int i = 0; i < p && fileRead[1] >> val; ++i) {
            if (val == std::numeric_limits<int>::max()) break;
            block2.push_back(val);
            haveValue = true;
            isLastStep = false;
        }

        if (!block1.empty() || !block2.empty()) {
            int i = 0, j = 0;

            while (i < block1.size() && j < block2.size()) {
                if (block1[i] < block2[j])
                    fileWrite[indexOutFiles] << block1[i++] << " ";
                else
                    fileWrite[indexOutFiles] << block2[j++] << " ";
            }

            while (i < block1.size())
                fileWrite[indexOutFiles] << block1[i++] << " ";
            while (j < block2.size())
                fileWrite[indexOutFiles] << block2[j++] << " ";

            if(sortType && isLastStep)
                fileWrite[indexOutFiles] << std::numeric_limits<int>::max() << " ";

            indexOutFiles = (indexOutFiles + 1) % 2;
        }
    }

    for (auto& file : fileRead) file.close();
    for (auto& file : fileWrite) file.close();

    std::remove("file0.txt");
    std::remove("file1.txt");

    if (std::rename("file2.txt", "file0.txt") != 0)
        std::cerr << "mergeFiles: Error - problems in rename" << std::endl;
    if (std::rename("file3.txt", "file1.txt") != 0)
        std::cerr << "mergeFiles: Error - problems in rename" << std::endl;
}
