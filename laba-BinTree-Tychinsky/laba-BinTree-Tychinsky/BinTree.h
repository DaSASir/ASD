#pragma once

class BinaryTree {
public:
	class Node;

	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other) noexcept;
	~BinaryTree();

	void clear();
	void clearAfter(const Node* root);

	bool isEmpty() const;
	void add(const int key);

	Node* root() const;
	int height() const;
	int countOfNodes() const;

	int min() const;
	int max() const;

private:
	Node* m_root = nullptr;
};

class BinaryTree::Node {
public:
	Node(int key = 0, Node* leftChild = nullptr, Node* rightChild = nullptr);
	~Node() = default;

	int key() const;
	void setKey(const int& newKey);

	Node* leftChild() const;
	Node* rightChild() const;

	void setLeftChild(Node* newLeftChild);
	void setRightChild(Node* newRightChild);

private:
	int m_key;
	Node* m_leftChild;
	Node* m_rightChild;
};

