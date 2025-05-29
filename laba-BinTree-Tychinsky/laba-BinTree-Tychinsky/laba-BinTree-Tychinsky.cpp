#include <iostream>
#include "BinTree.h"

int main() {
    setlocale(LC_ALL , "ru");
    srand(time(0));

    std::vector<int> v;
    std::cout << "\nvector: ";
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
        std::cout << i << " ";
    }

    BinaryTree tree(v);
    std::cout << "\n\nTree: \n";
    tree.printHorizontal();
    
    std::vector<int> a = tree.getVector();
    for (int g : a) std::cout << g << " ";

    return 0;
}