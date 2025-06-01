#include <iostream>
#include <vector>
#include "BinTreeSearch.h"

std::vector<int> create(const int size, const int maxV) {
	std::vector<int> back;
	for (int i = 0; i < size; i++)
		back.push_back(rand() % (2 * maxV + 1) - maxV);
	return back;
}

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));

	std::vector<int> v = create(10, 10);
	std::cout << "\nVector: ";
	for (int a : v) std::cout << a << " ";
	std::cout << "\n\n";

	BinaryTreeSearch tree(v);

	tree.printHorizontal();

	std::cout << (tree.isEmpty() ? "empty\n" : "not empty\n");

	std::cout << "choose element: ";
	int element;
	std::cin >> element;
	tree.remove(element);
	tree.printHorizontal();




	std::cout << "\nVector: ";
	std::vector<int> gg = tree.getVector();
	for (int i : gg) std::cout << i << " ";



	return 0;
}