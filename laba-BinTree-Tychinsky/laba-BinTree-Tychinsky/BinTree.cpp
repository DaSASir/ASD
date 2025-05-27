#include "BinTree.h"
#include <iostream>

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
}

void BinaryTree::clearAfter(const Node* root) {
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
	return height_(m_root); 
}

int BinaryTree::height_(Node* root) const {
	if (!root) return 0;
	int result = 1;
	result += (height_(root->leftChild()) == 1 || height_(root->rightChild()) == 1) ? 1 : 0;
	return result;
}

int BinaryTree::countOfNodes() const { 
	return countOfNodes_(m_root); 
}

int BinaryTree::countOfNodes_(Node* root) const {
	if (!root) return 0;
	int result = 1;
	result += countOfNodes_(m_root->leftChild());
	result += countOfNodes_(m_root->rightChild());
	return result;
}

std::vector<int> BinaryTree::getVector() const {
	std::vector<int> keys;
	getVector_(m_root, keys);
	return keys;
}

void BinaryTree::getVector_(Node* root, std::vector<int>& keys) const {
	if (!root) return;
	getVector_(root->leftChild(), keys);
	keys.push_back(root->key());
	getVector_(root->rightChild(), keys);
}

int BinaryTree::min() const {
	int min = 0;
	if (m_root) {
		min = m_root->key();
		min_(m_root->leftChild(), min);
		min_(m_root->rightChild(), min);
	}
	return min;
}

void BinaryTree::min_(Node* root, int& value) const {
	if (!root) return;

	if (root->key() < value)
		value = root->key();

	min_(m_root->leftChild(), value);
	min_(m_root->rightChild(), value);
}

int BinaryTree::max() const {
	int max = 0;
	if (m_root) {
		max = m_root->key();
		max_(m_root->leftChild(), max);
		max_(m_root->rightChild(), max);
	}
	return max;
}

void BinaryTree::max_(Node* root, int& value) const {
	if (!root) return;

	if (root->key() > value)
		value = root->key();

	min_(m_root->leftChild(), value);
	min_(m_root->rightChild(), value);
}

BinaryTree::Node* BinaryTree::add(const int key) {
	if (m_root) 
		return add_(m_root, key);
	else 
		return m_root = new Node(key);
}

BinaryTree::Node* BinaryTree::add_(Node* root, int key) {
	if (!root) 
		root = new Node(key);
	else if (rand() % 2) 
		root->setLeftChild(add_(root->leftChild(), key));
	else 
		root->setRightChild(add_(root->rightChild(), key));
	return root;
}

bool BinaryTree::remove(const int key) {
	Node* nodeKey = nlrSearch(m_root, key);
	if (nodeKey->key() == key) {
		clearAfter(nodeKey);
		return true;
	}
	return false;
}

BinaryTree::Node* BinaryTree::find(const int key) const {
	return nlrSearch(m_root, key);
}

BinaryTree::Node* BinaryTree::nlrSearch(Node* root, int key) const {
	if (!root || root->key() == key) 
		return root;

	Node* subTreeSearchResult = nlrSearch(root->leftChild(), key);
	if (!subTreeSearchResult) 
		subTreeSearchResult = nlrSearch(root->rightChild(), key);

	return subTreeSearchResult;
}

bool BinaryTree::isBalanced() const { 
	return isBalanced_(m_root); 
}

bool BinaryTree::isBalanced_(Node* root) const {
	if (!root) return true;
	int left = isBalanced_(root->leftChild());
	int right = isBalanced_(root->rightChild());
	return (((left - right) <= 1) || ((right - left) <= 1)) && isBalanced_(root->leftChild()) && isBalanced_(root->rightChild());
}

int BinaryTree::level(int key) const {
	return level_(m_root, key, 0);
}

int BinaryTree::level_(Node* node, int key, int level) const {
	if (!node) return -1;
	if (node->key() == key) 
		return level;

	int indexKey = level_(node->leftChild(), key, level + 1);
	if (indexKey == -1)
		indexKey = level_(node->rightChild(), key, level + 1);
	else
		return indexKey;
}

void BinaryTree::printHorizontal() const { 
	printHorizontal_(m_root, 1, 5); 
}

void BinaryTree::printHorizontal_(Node* root, int marginLeft, int levelSpacing) const {
	if (!root) return;

	printHorizontal_(root->rightChild(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
	printHorizontal_(root->leftChild(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::printByLevels() const{
	printByLevels_(m_root);
}

void BinaryTree::printByLevels_(Node* root, int space, int gap) const {
	if (!root) return;

	space += gap;

	printByLevels_(root->rightChild(), space);

	std::cout << std::endl;
	for (int i = gap; i < space; i++)
		std::cout << " ";
	std::cout << root->key() << "\n";

	printByLevels_(root->leftChild(), space);
}

void BinaryTree::lrnPrint() const {
	lrnPrint_(m_root);
}

void BinaryTree::lrnPrint_(Node* root) const {
	if (!root) return;
	
	lrnPrint_(root->leftChild());
	lrnPrint_(root->rightChild());
	std::cout << root->key() << ' ';
}

BinaryTree::Node* BinaryTree::copy(Node* root) const {
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
	return TemplateIterator< const int>(nullptr);
}
