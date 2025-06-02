#include "BinTree.h"
#include <iostream>
#include <queue>

//Node functions 
BinaryTree::Node::Node(int key, Node* leftChild, Node* rightChild)
	:m_key(key), m_leftChild(leftChild), m_rightChild(rightChild) {}

int BinaryTree::Node::key() const {
	return m_key;
}
void BinaryTree::Node::setKey(const int& newKey) {
	m_key = newKey;
}

BinaryTree::Node* BinaryTree::Node::leftChild() const {
	return m_leftChild;
}
BinaryTree::Node* BinaryTree::Node::rightChild() const {
	return m_rightChild;
}

void BinaryTree::Node::setLeftChild(Node* newLeftChild) {
	m_leftChild = newLeftChild;
}
void BinaryTree::Node::setRightChild(Node* newRightChild) {
	m_rightChild = newRightChild;
}

//Binary Tree
BinaryTree::BinaryTree(const std::vector<int>& vector) {
	for (int a : vector) add(a);
}
BinaryTree::BinaryTree(const BinaryTree& other) {
	m_root = copy(other.m_root);
}

BinaryTree::BinaryTree(BinaryTree&& other) noexcept {
	std::swap(m_root, other.m_root);
}

BinaryTree::~BinaryTree() {
	clear();
}

void BinaryTree::clear() {
	clearAfter(m_root);
	m_root = nullptr;
}

void BinaryTree::clearAfter(Node* root) {
	if (root) {
		clearAfter(root->leftChild());
		clearAfter(root->rightChild());
		delete root;
	}
}

bool BinaryTree::isEmpty() const {
	return (!m_root);
}

BinaryTree::Node* BinaryTree::root() const {
	return m_root;
}

int BinaryTree::height() const {
	return height(m_root);
}

int BinaryTree::height(const Node* root) const {
	if (!root) return 0;
	bool condition = (height(root->leftChild()) > height(root->rightChild()));
	return (condition ? height(root->leftChild()) : height(root->rightChild())) + 1;
}

int BinaryTree::countOfNodes() const {
	if (!m_root) return 0;

	int result = 0;
	for (auto it = begin(); it != end(); it++)
		++result;

	return result;
}

std::vector<int> BinaryTree::getVector() const {
	std::vector<int> keys;
	getVector(m_root, keys);
	return keys;
}

void BinaryTree::getVector(const Node* root, std::vector<int>& keys) const {
	if (!root) return;
	getVector(root->leftChild(), keys);
	keys.push_back(root->key());
	getVector(root->rightChild(), keys);
}

int BinaryTree::min() const {
	int min = 0;
	for (auto it = begin(); it != end(); it++)
		if (min > *it)
			min = *it;

	return min;
}

int BinaryTree::max() const {
	int max = 0;
	for (auto it = begin(); it != end(); it++)
		if (max < *it)
			max = *it;

	return max;
}

BinaryTree::Node* BinaryTree::add(const int key) {
	if (m_root)
		return add(m_root, key);
	else
		return m_root = new Node(key);
}

BinaryTree::Node* BinaryTree::add(Node* root, int key) {
	if (!root)
		root = new Node(key);
	else if (rand() % 2)
		root->setLeftChild(add(root->leftChild(), key));
	else
		root->setRightChild(add(root->rightChild(), key));

	return root;
}

bool BinaryTree::remove(const int key) {
	Node* node = find(key);
	if (!node) return false;

	if (!node->leftChild() && !node->rightChild()) {
		Node* nodeParent = findParent(node);

		if (nodeParent->leftChild() == node)
			nodeParent->setLeftChild(nullptr);
		else
			nodeParent->setRightChild(nullptr);

		delete node;
	}
	else {
		Node* replacementNode = findReplacementNode(node);
		Node* nodeParent = findParent(replacementNode);

		node->setKey(replacementNode->key());

		if (nodeParent->leftChild() == replacementNode)
			nodeParent->setLeftChild(nullptr);
		else
			nodeParent->setRightChild(nullptr);

		delete replacementNode;
	}

	return true;
}

BinaryTree::Node* BinaryTree::findParent(const Node* root) const {
	for (auto it = begin(); it != end(); it++)
		if (it.cell()->leftChild() == root || it.cell()->rightChild() == root)
			return it.cell();

	return nullptr;
}

BinaryTree::Node* BinaryTree::findReplacementNode(Node* root) const {
	if (!root) return nullptr;

	Node* result = nullptr;

	if ((rand() % 2 && root->leftChild()) || !root->rightChild())
		result = findReplacementNode(root->leftChild());
	else
		result = findReplacementNode(root->rightChild());

	if (!result && !root->leftChild() && !root->rightChild())
		return root;

	return result;
}

BinaryTree::Node* BinaryTree::find(const int key) const {
	return nlrSearch(m_root, key);
}

BinaryTree::Node* BinaryTree::nlrSearch(Node* root, const  int key) const {
	if (!root || root->key() == key)
		return root;

	Node* subTreeSearchResult = nlrSearch(root->leftChild(), key);
	if (!subTreeSearchResult)
		subTreeSearchResult = nlrSearch(root->rightChild(), key);

	return subTreeSearchResult;
}

bool BinaryTree::isBalanced() const {
	return isBalanced(m_root);
}

bool BinaryTree::isBalanced(const Node* root) const {
	if (!root) return true;
	int left = height(root->leftChild());
	int right = height(root->rightChild());
	bool balanceChilds = ((left - right) <= 1) && ((right - left) <= 1);
	return balanceChilds && isBalanced(root->leftChild()) && isBalanced(root->rightChild());
}

int BinaryTree::level(const int key) const {
	return level(m_root, key, 0);
}

int BinaryTree::level(const Node* node, const  int key, const  int level_) const {
	if (!node) return -1;
	if (node->key() == key)
		return level_;

	int indexKey = level(node->leftChild(), key, level_ + 1);
	if (indexKey == -1)
		indexKey = level(node->rightChild(), key, level_ + 1);
	else
		return indexKey;
}

void BinaryTree::printHorizontal() const {
	printHorizontal(m_root, 1, 5);
}

void BinaryTree::printHorizontal(const Node* root, const int marginLeft, const int levelSpacing) const {
	if (!root) return;

	printHorizontal(root->rightChild(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
	printHorizontal(root->leftChild(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::printByLevels() const {
	int current = -1;
	for (auto it = begin(); it != end(); it++) {
		if (current != level(*it)) {
			current = level(*it);
			std::cout << std::endl << "Level " << current << ": ";
		}
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void BinaryTree::lrnPrint() const {
	lrnPrint(m_root);
}

void BinaryTree::lrnPrint(const Node* root) const {
	if (!root) return;

	lrnPrint(root->leftChild());
	lrnPrint(root->rightChild());
	std::cout << root->key() << ' ';
}

BinaryTree::Node* BinaryTree::copy(const Node* root) const {
	if (!root) return nullptr;
	return new Node(root->key(), copy(root->leftChild()), copy(root->rightChild()));
}

BinaryTree& BinaryTree::operator = (const BinaryTree& other) {
	if (this != &other) {
		clear();
		m_root = copy(other.m_root);
	}
	return *this;
}

BinaryTree& BinaryTree::operator = (BinaryTree&& other) noexcept {
	if (this != &other)
		std::swap(m_root, other.m_root);
	return *this;
}

BinaryTree::Iterator BinaryTree::begin() {
	return TemplateIterator<int>(m_root);
}
BinaryTree::Iterator BinaryTree::end() {
	return TemplateIterator<int>(nullptr);
}
BinaryTree::ConstIterator BinaryTree::begin() const {
	return TemplateIterator<const int>(m_root);
}
BinaryTree::ConstIterator BinaryTree::end() const {
	return TemplateIterator<const int>(nullptr);
}