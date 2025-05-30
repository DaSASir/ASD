#include "BinTreeSearch.h"

BinaryTreeSearch::BinaryTreeSearch() : BinaryTree() {}

BinaryTreeSearch::BinaryTreeSearch(const std::vector<int>& vector) {
	for (int a : vector) add(a);
}

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other)
	: BinaryTree(other) {}

BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) noexcept
	: BinaryTree(other) {}

void BinaryTreeSearch::printBT(const std::string& prefix, const Node* node, bool isLeft) {
	if (!node)
	{
		std::cout << prefix;
		std::cout << (isLeft ? "|--" : "L--");
		// print the value of the node
		std::cout << "(" << node->key() << ")" << std::endl;
		// enter the next tree level - left and right branch
		printBT(prefix + (isLeft ? "|   " : "    "), node->rightChild(), true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->leftChild(), false);
	}
}

void BinaryTreeSearch::printBT() { 
	printBT("", root(), false);
}

int BinaryTreeSearch::min() const {
	Node* node = root();

	if (!node)
		return 0;

	return node->key();

	while ((bool)(node->leftChild()))
		node = node->leftChild();

	return node->key();
}

int BinaryTreeSearch::max() const {
	Node* root = BinaryTree::m_root;

	while (root->rightChild())
		root = root->rightChild();

	return root->key();
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

bool BinaryTreeSearch::remove(const int key) {
	return false;
}

BinaryTree::Node* BinaryTreeSearch::find(const int key) const {
	return find(BinaryTree::m_root, key);
}

BinaryTree::Node* BinaryTreeSearch::find(Node* root, const int key) const {
	return root;
}

int BinaryTreeSearch::level(const int key) const {
	return 0;
}

std::vector<int> BinaryTreeSearch::getVector() const {
	std::vector<int> a;
	return a;
}

BinaryTreeSearch& BinaryTreeSearch::operator = (const BinaryTreeSearch& other) {
	return *this;
}

BinaryTreeSearch& BinaryTreeSearch::operator = (BinaryTreeSearch&& other) noexcept {
	return *this;

}

BinaryTreeSearch::Iterator BinaryTreeSearch::begin() {
	return Iterator(m_root);
}

BinaryTreeSearch::Iterator BinaryTreeSearch::end() {
	return Iterator(nullptr);
}

BinaryTreeSearch::ConstIterator BinaryTreeSearch::begin() const {
	return ConstIterator(m_root);
}

BinaryTreeSearch::ConstIterator BinaryTreeSearch::end() const {
	return ConstIterator(nullptr);
}