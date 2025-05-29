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
	void clearAfter(Node* root);

	bool isEmpty() const;

	Node* root() const;
	int height() const;
	int countOfNodes() const;

	virtual std::vector<int> getVector() const;

	virtual int min() const;
	virtual int max() const;

	virtual Node* add(const int key);
	virtual bool remove(const int key);

	virtual Node* find(const int key) const;
	virtual int level(const int key) const;

	bool isBalanced() const;

	void printHorizontal() const;
	void printByLevels() const;
	void lrnPrint() const;

	BinaryTree& operator = (const BinaryTree& other);
	BinaryTree& operator = (BinaryTree&& other) noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

protected:
	Node* copy(const Node* root) const;

	Node* findParent(const Node* root) const;
	Node* findReplacementNode(Node* root) const;

	int height(const Node* root) const;
	void getVector(const Node* node, std::vector<int>& keys) const;

	Node* add(Node* root, const  int key);
	Node* nlrSearch(Node* root, const  int key) const;

	bool isBalanced(const Node* root) const;
	int level(const Node* root, const int key, const int level_) const;

	void printHorizontal(const Node* root, const int marginLeft, const int levelSpacing) const;
	void lrnPrint(const Node* root) const;

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
	TemplateIterator(Node* cell) : m_cell(cell) {
		if (m_cell) {
			if (m_cell->leftChild())
				unprocessedNodes.push_back(m_cell->leftChild());
			if (m_cell->rightChild())
				unprocessedNodes.push_back(m_cell->rightChild());
		}
	}

	T& operator*() { 
		return m_cell->key(); 
	}

	const T& operator*() const { 
		return m_cell->key(); 
	}

	TemplateIterator operator++() {
		if (unprocessedNodes.empty()) 
			m_cell = nullptr; 
		else {
			m_cell = unprocessedNodes.front();

			if (m_cell->leftChild())
				unprocessedNodes.push_back(m_cell->leftChild());
			if (m_cell->rightChild())
				unprocessedNodes.push_back(m_cell->rightChild());

			unprocessedNodes.pop_front();
		}
		return *this;
	}

	TemplateIterator operator++(int) {
		TemplateIterator back = *this;
		++(*this);
		return back;
	}

	bool operator==(const TemplateIterator& other) const { 
		return (m_cell == other.m_cell); 
	}

	bool operator!=(const TemplateIterator& other) const { 
		return (m_cell != other.m_cell); 
	}

	Node* cell() { 
		return m_cell; 
	}

protected:
	Node* m_cell = nullptr;
	std::list<Node*> unprocessedNodes; //BFS
};

