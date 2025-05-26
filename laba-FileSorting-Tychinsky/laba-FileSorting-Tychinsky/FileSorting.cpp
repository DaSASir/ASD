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
        file << std::rand() % (maxNumberValue * 2 + 1) - maxNumberValue << " ";

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

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue, const int sortType) {
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue))
        return -1;

    switch (sortType) {
    case 1:
        mergersDirectAndNatural(fileName, 0);
        break;
    case 2:
        mergersDirectAndNatural(fileName, 1);
        break;
    case 3:
        mergeMultiway(fileName, 5);
        break;
    }

    if (!isFileContainsSortedArray(fileName))
        return -2;

    return 1;
}

//прямое и естественное слияния
void mergersDirectAndNatural(const std::string& fileName, const bool sortType) {
    if (sortType) mergeMultiway(fileName, 2);
    else {
        int p = 1;
        splitFiles(fileName);

        while (true) {
            std::ifstream check("file1.txt");
            if (!check.is_open()) {
                std::cerr << "mergersDirectAndNatural: Error - check fail is not openning" << std::endl;
                return;
            }

            int value;
            if (!(check >> value)) break;
            check.close();

            mergeFiles(p);
            p *= 2;
        }

        std::remove(fileName.c_str());
        if (std::rename("file0.txt", fileName.c_str()) != 0)
            std::cerr << "mergersDirectAndNatural: Error - problems in rename" << std::endl;
    }
}

void splitFiles(const std::string& fileName) {
    std::ifstream fileMain(fileName);
    std::ofstream fileDop1("file0.txt"), fileDop2("file1.txt");
    if (!fileMain.is_open() || !fileDop1.is_open() || !fileDop2.is_open()) {
        std::cerr << "splitFiles: Error - fails is not openning" << std::endl;
        return;
    }

    int value;
    int index = 0;
    while (fileMain >> value)
        (index++ % 2 == 0 ? fileDop1 : fileDop2) << value << " ";

    fileMain.close();
    fileDop1.close();
    fileDop2.close();
}

void mergeFiles(const int p) {
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

    std::vector<int> segmentNumbers(2);
    std::vector<bool> segmentActive(2, false);
    bool haveActive = false;

    int indexOutFile = 0;
    while (true) {
        std::vector<int> segmentCounts(2, 0);
        haveActive = false;

        for (int i = 0; i < 2; ++i)
            if (fileRead[i] >> segmentNumbers[i]) {
                segmentCounts[i]++;
                segmentActive[i] = true;
                haveActive = true;
            }

        if (!haveActive) break;

        while (segmentActive[0] && segmentActive[1]) {
            if (segmentNumbers[0] <= segmentNumbers[1]) {
                fileWrite[indexOutFile] << segmentNumbers[0] << " ";
                segmentActive[0] = (segmentCounts[0] < p) && (fileRead[0] >> segmentNumbers[0]);
                if(segmentActive[0])
                    segmentCounts[0]++;
            }
            else {
                fileWrite[indexOutFile] << segmentNumbers[1] << " ";
                segmentActive[1] = (segmentCounts[1] < p) && (fileRead[1] >> segmentNumbers[1]);
                if (segmentActive[1])
                    segmentCounts[1]++;
            }
        }
        
        for(int i = 0; i < 2; ++i)
            while (segmentActive[i]) {
                fileWrite[indexOutFile] << segmentNumbers[i] << " ";
                segmentActive[i] = (segmentCounts[i] < p) && (fileRead[i] >> segmentNumbers[i]);
                if (segmentActive[i])
                    segmentCounts[i]++;
            }

        indexOutFile = (indexOutFile + 1) % 2;
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

//многопутевое слияние
void mergeMultiway(const std::string& fileName, const int COUNT_FILES) {
    const std::string prefix_f = "f_";
    const std::string prefix_g = "g_";

    bool fromFtoG = true;

    splitMultiway(fileName, 5);
    while (true) {
        std::ifstream checkFile((fromFtoG ? prefix_f : prefix_g) + "file1.txt");
        if (!checkFile.is_open()) {
            std::cerr << "mergeMultiway: Error - checkFile file is not openning" << std::endl;
            return;
        }

        int value;
        if (!(checkFile >> value)) break;
        checkFile.close();

        if (fromFtoG)
            mergeMultiway(prefix_f, prefix_g, 5);
        else
            mergeMultiway(prefix_g, prefix_f, 5);

        fromFtoG = !fromFtoG;
    }

    std::remove(fileName.c_str());
    if (std::rename(((fromFtoG ? prefix_f : prefix_g) + "file0.txt").c_str(), fileName.c_str()) != 0)
        std::cerr << "mergeMultiway: Error - problems in rename" << std::endl;
}

void splitMultiway(const std::string& fileName, const int COUNT_FILES) {
    std::ifstream fileMain(fileName);
    if (!fileMain.is_open()) {
        std::cerr << "splitMultiway: Error - fileMain fail is not openning" << std::endl;
        return;
    }
    std::vector<std::ofstream> fileAdditional(COUNT_FILES);
    for (int i = 0; i < COUNT_FILES; ++i) {
        fileAdditional[i].open("f_file" + std::to_string(i) + ".txt");
        if (!fileAdditional[i].is_open()) {
            std::cerr << "splitMultiway: Error - fileAdditional fails is not openning" << std::endl;
            for (int j = 0; j < i; ++j)
                fileAdditional[j].close();
            return;
        }
    }

    int value1, value2;
    int index = 0;
    fileMain >> value1;
    while (fileMain >> value2) {
        fileAdditional[index] << value1 << " ";
        if (value1 > value2)
            index = (index + 1) % COUNT_FILES;
        value1 = value2;
    }
    fileAdditional[index] << value1 << " ";

    for (int i = 0; i < COUNT_FILES; ++i)
        fileAdditional[i].close();
    fileMain.close();
}

void mergeMultiway(const std::string& from, const std::string& to, const int COUNT_FILES) {
    std::vector<std::ifstream> file_f(COUNT_FILES);
    std::vector<std::ofstream> file_g(COUNT_FILES);
    for (int i = 0; i < COUNT_FILES; ++i) {
        file_f[i].open(from + "file" + std::to_string(i) + ".txt");
        file_g[i].open(to + "file" + std::to_string(i) + ".txt");

        if (!file_f[i].is_open() || !file_g[i].is_open()) {
            std::cerr << "mergeMultiway: Error - fails is not openning" << std::endl;
            for (int j = 0; j < i; ++j) {
                file_f[j].close();
                file_g[j].close();
            }
            return;
        }
    }

    std::vector<int> segmentNumbers(COUNT_FILES);
    std::vector<bool> segmentActive(COUNT_FILES, false);
    int lastElement = INT32_MIN;
    int minValue = INT32_MAX;

    for (int i = 0; i < COUNT_FILES; ++i)
        segmentActive[i] = (bool)(file_f[i] >> segmentNumbers[i]);

    int indexFileG = 0;
    while (true) {
        int minIndex = -1;

        for (int i = 0; i < COUNT_FILES; ++i)
            if (segmentActive[i] && segmentNumbers[i] < minValue) {
                minIndex = i;
                minValue = segmentNumbers[i];
            }

        if (minIndex == -1) break;

        if (lastElement > minValue)
            indexFileG = (indexFileG + 1) % COUNT_FILES;

        file_g[indexFileG] << minValue << " ";
        lastElement = minValue;

        segmentActive[minIndex] = (bool)(file_f[minIndex] >> segmentNumbers[minIndex]);
    }

    for (int i = 0; i < COUNT_FILES; ++i) {
        file_f[i].close();
        file_g[i].close();
    }
}