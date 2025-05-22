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
BinaryTree::BinaryTree(const BinaryTree& other) {
	if (other.root()) 
		m_root = new Node(
			other.m_root->key(), 
			other.m_root->leftChild(), 
			other.m_root->rightChild());
}
BinaryTree::BinaryTree(BinaryTree&& other) noexcept {
	std::swap(m_root, other.m_root);
}
BinaryTree::~BinaryTree() { clear(); }

BinaryTree::Node* BinaryTree::root() const {
	return m_root;
}

void BinaryTree::clear() {clearAfter(m_root);}

void BinaryTree::clearAfter(const Node* root) {
	if (root) {
		clearAfter(root->leftChild());
		clearAfter(root->rightChild());
		delete root;
	}
}

bool BinaryTree::isEmpty() const {
	return m_root;
}

void BinaryTree::add(const int key) {

}

int BinaryTree::height() const {
	return 0;
}
int BinaryTree::countOfNodes() const {
	return 0;
}

int BinaryTree::min() const {
	return 0;
}
int BinaryTree::max() const {
	return 0;
}
