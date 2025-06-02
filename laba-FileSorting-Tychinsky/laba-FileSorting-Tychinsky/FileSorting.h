#pragma once

//требуемые функции
bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string& fileName);
int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue, const int sortTyp);

//прямое и естественное слияния
void mergersDirectAndNatural(const std::string& fileName, const bool sortType = false);
void splitFiles(const std::string& fileName);
void mergeFiles(const int p);

//многопутевое слияние
void mergeMultiway(const std::string& fileName, const int COUNT_FILES);
void splitMultiway(const std::string& fileName, const int COUNT_FILES);
void mergeMultiway(const std::string& from, const std::string& to, const int COUNT_FILES);