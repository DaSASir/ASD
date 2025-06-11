#include <iostream>
#include <string.h>
#include "HashTable.h"

const int sizeV = 10;

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0));


    std::vector<int> nums;
    for (int i = 0; i < sizeV; i++)
        nums.push_back(rand() % (sizeV * 2 - 1) - sizeV);

    std::cout << "Vector: ";
    for (int e : nums) std::cout << e << " ";
    std::cout << std::endl;




    HashTable<int> table(HashFunction::hash2, CollisionsMethod::outside, 5);

    for (int i = 0; i < sizeV; i++)
        table.add(nums[i]);

    std::cout << "\nHash-Table:";
    table.print();


    table.remove(nums[0]);

    std::cout << "\nHash-Table:";
    table.print();



    


    return 0;
}