#include "BinTreeSearch.h"

BinaryTreeSearch::BinaryTreeSearch() : BinaryTree() {}

BinaryTreeSearch::BinaryTreeSearch(const std::vector<int>& vector) {
	for (int a : vector) add(a);
}

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other)
	: BinaryTree(other) {}

BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) noexcept
	: BinaryTree(other) {}

int BinaryTreeSearch::min() const {

	if (!root())
		return 0;

	Node* node = root();

	return node->key();

	/*while (node->leftChild())
		node = node->leftChild();

	return node->key();*/
}

BinaryTree::Node* BinaryTreeSearch::add(const int key) {
	return add(root(), key);
}

BinaryTree::Node* BinaryTreeSearch::add(Node* root, const int key) {
	if (!root)
		root = new Node(key);
	else if (key < root->key())
		root->setLeftChild(add(root->leftChild(), key));
	else
		root->setRightChild(add(root->rightChild(), key));

	return root;
}
