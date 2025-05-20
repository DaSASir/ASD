#pragma once

//требуемые функции
bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string& fileName);
int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue);

//прямое и естественное слияния
void mergersDirectAndNatural(const std::string& fileName, const bool sortType = false);
void splitFiles(const bool sortType, const std::string& fileName);
void mergeFiles(const bool sortType, const int p = INT16_MAX);

//многопутевое слияние
void mergeMultiway(const std::string& fileName);
void splitMultiway(const std::string& fileName);
void mergeMultiway(const std::string& from, const std::string& to);