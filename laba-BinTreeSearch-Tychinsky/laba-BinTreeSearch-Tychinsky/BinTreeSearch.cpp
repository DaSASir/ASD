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
	if (!root()) return 0;

	Node* node = root();
	while (node->leftChild())
		node = node->leftChild();

	return node->key();
}

int BinaryTreeSearch::max() const {
	if (!root()) return 0;

	Node* node = root();
	while (node->rightChild())
		node = node->rightChild();

	return node->key();
}

//BinaryTree::Node* BinaryTreeSearch::add(const int key) {
//	Node* node = root();
//	if (node)
//		return add(node, key);
//	else
//		return node = new Node(key);
//}

BinaryTree::Node* BinaryTreeSearch::add(Node* root, const int key) {
	if (!root)
		root = new Node(key);
	else if (key < root->key())
		root->setLeftChild(add(root->leftChild(), key));
	else
		root->setRightChild(add(root->rightChild(), key));

	return root;
}

BinaryTree::Node* BinaryTreeSearch::find(const int key) const {
	return find(root(), key);
}

BinaryTree::Node* BinaryTreeSearch::find(Node* root, const int key) const {
	if (!root || root->key() == key)
		return root;

	if (key < root->key())
		return find(root->leftChild(), key);
	else
		return find(root->rightChild(), key);
}

int BinaryTreeSearch::level(const int key) const {
	return level(root(), key, 0);
}

int BinaryTreeSearch::level(const Node* node, const int key, const int level_) const {
	if (!node) return -1;
	if (node->key() == key)
		return level_;

	if (key < node->key())
		return level(node->leftChild(), key, level_ + 1);
	else
		return level(node->rightChild(), key, level_ + 1);
}

std::vector<int> BinaryTreeSearch::getVector() const {
	return BinaryTree::getVector();
}

BinaryTreeSearch& BinaryTreeSearch::operator = (const BinaryTreeSearch& other) {
	BinaryTree::operator=(other);
	return *this;
}

BinaryTreeSearch& BinaryTreeSearch::operator = (BinaryTreeSearch&& other) noexcept {
	BinaryTree::operator=(other);
	return *this;
}

BinaryTreeSearch::Iterator BinaryTreeSearch::begin() {
	return TemplateIterator<int>(root());
}

BinaryTreeSearch::Iterator BinaryTreeSearch::end() {
	return TemplateIterator<int>(nullptr);
}

BinaryTreeSearch::ConstIterator BinaryTreeSearch::begin() const {
	return TemplateIterator<const int>(root());
}

BinaryTreeSearch::ConstIterator BinaryTreeSearch::end() const {
	return TemplateIterator<const int>(nullptr);
}

