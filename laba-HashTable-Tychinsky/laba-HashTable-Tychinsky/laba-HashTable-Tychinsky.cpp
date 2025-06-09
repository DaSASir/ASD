#include <iostream>
#include <string.h>
#include "HashTable.h"

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));

    std::vector<int> nums = { -5, 2, -7, -5, -2 , 2, -8, 6,-1, 6, 7, 5 };
    /*for (int i = 0; i < 12; i++)
        nums.push_back(rand() % (10 * 2 - 1) - 10);*/

    std::cout << "Vector: ";
    for (int e : nums) std::cout << e << " ";
    std::cout << std::endl;


    std::vector<int> num;
    num.push_back(5);
    for (int i = 1; i < 12; i++) {
        num.push_back((num[i - 1] + 2 * i + 3 * i * i) % 12);
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (int e : num) std::cout << e << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    HashTable<int> table(HashFunction::hash1, CollisionsMethod::open, 12);
    for (int i = 0; i < 12; i++)
        table.add(nums[i]);
    table.print();


    return 0;
}