#include "BinTreeSearch.h"

BinaryTreeSearch::BinaryTreeSearch() : BinaryTree() {}

BinaryTreeSearch::BinaryTreeSearch(const std::vector<int>& vector) {
	for (int a : vector) add(a);
}

//BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other)
//	: BinaryTree(other) {}
//
//BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) noexcept
//	: BinaryTree(other) {}


int BinaryTreeSearch::min() const {
	Node* node = root();

	if (!node)
		return 0;

	return node->key();




	/*while ((bool)(node->leftChild()))
		node = node->leftChild();

	return node->key();*/
}

//int BinaryTreeSearch::max() const {
//	return 0;
//}

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
//
//bool BinaryTreeSearch::remove(const int key) {
//	return false;
//}
//
//BinaryTree::Node* BinaryTreeSearch::find(const int key) const {
//	return root();
//}
//
//BinaryTree::Node* BinaryTreeSearch::find(Node* root, const int key) const {
//	return root;
//}
//
//int BinaryTreeSearch::level(const int key) const {
//	return 0;
//}
//
//std::vector<int> BinaryTreeSearch::getVector() const {
//	std::vector<int> a;
//	return a;
//}
//
//BinaryTreeSearch& BinaryTreeSearch::operator = (const BinaryTreeSearch& other) {
//	return *this;
//}
//
//BinaryTreeSearch& BinaryTreeSearch::operator = (BinaryTreeSearch&& other) noexcept {
//	return *this;
//
//}
//
//BinaryTreeSearch::Iterator BinaryTreeSearch::begin() {
//	return Iterator(m_root);
//}
//
//BinaryTreeSearch::Iterator BinaryTreeSearch::end() {
//	return Iterator(nullptr);
//}
//
//BinaryTreeSearch::ConstIterator BinaryTreeSearch::begin() const {
//	return ConstIterator(m_root);
//}
//
//BinaryTreeSearch::ConstIterator BinaryTreeSearch::end() const {
//	return ConstIterator(nullptr);
//}