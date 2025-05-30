#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "BinTreeSearch.h"

std::vector<int> create(const int size, const int maxV) {
	std::vector<int> back;
	for (int i = 0; i < size; i++) 
		back.push_back(std::rand() % (2 * maxV + 1) - maxV);

	return back;
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));

	std::vector<int> vector = create(10, 10);
	std::cout << "\nVector: ";
	for (int i : vector) std::cout << i << " ";
	std::cout << "\n\n\n";

	BinaryTreeSearch tree(vector);

	std::cout << "MinValue: " << tree.min();


	return 0;
}