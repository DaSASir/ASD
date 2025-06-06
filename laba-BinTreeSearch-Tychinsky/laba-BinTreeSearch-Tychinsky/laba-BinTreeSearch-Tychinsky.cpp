#include <iostream>
#include <vector>
#include "BinTreeSearch.h"

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));

	SearchTreeTester tester(true);
	tester.test(100);

	return 0;
}