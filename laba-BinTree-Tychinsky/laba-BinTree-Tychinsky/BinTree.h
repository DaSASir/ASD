#pragma once
#include <iostream>
#include <vector>
#include <list>

class BinaryTree {
public:
	class Node;

	template <typename T>
	class TemplateIterator;
	using Iterator = TemplateIterator<int>;
	using ConstIterator = TemplateIterator<const int>;

public:
	BinaryTree() = default;
	BinaryTree(const std::vector<int>& vector);
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other) noexcept;
	~BinaryTree();

	void clear();
	void clearAfter(const Node* root);

	bool isEmpty() const;

	Node* root() const;
	int height() const;
	int countOfNodes() const;
	std::vector<int> getVector() const;

	int min() const;
	int max() const;

	Node* add(const int key);
	bool remove(const int key);
	Node* find(const int key) const;

	bool isBalanced() const;
	int level(int key) const;

	void printHorizontal() const;
	void printByLevels() const;
	void lrnPrint() const;

	BinaryTree& operator = (const BinaryTree& other);
	BinaryTree& operator = (BinaryTree&& other) noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	Node* copy(Node* root) const;

	int height_(Node* root) const;
	int countOfNodes_(Node* root) const;
	void getVector_(Node* node, std::vector<int>& keys) const;

	void min_(Node* root, int& value) const;
	void max_(Node* root, int& value) const;

	Node* add_(Node* root, int key);
	Node* nlrSearch(Node* root, int key) const;

	bool isBalanced_(Node* root) const;
	int level_(Node* root, int key, int level) const;

	void printHorizontal_(Node* root, int marginLeft, int levelSpacing) const;
	void printByLevels_(Node* root, int space = 0, int gap = 4) const;
	void lrnPrint_(Node* root) const;

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

template <typename T>
class BinaryTree::TemplateIterator {
public:
	TemplateIterator(Node* cell) : m_cell(cell) {}

	T& operator*() { return m_cell->key; }
	const T& operator*() const { return m_cell->key; }
	TemplateIterator operator++() {
		//???????????
	}
	TemplateIterator operator++(int) {
		TemplateIterator back = *this;
		++(*this);
		return back;
	}
	bool operator==(const TemplateIterator& other) const { return (m_cell == other.m_cell); }
	bool operator!=(const TemplateIterator& other) const { return (m_cell != other.m_cell); }

	Node* get() { return m_cell; };

protected:
	Node* m_cell = nullptr;
};

