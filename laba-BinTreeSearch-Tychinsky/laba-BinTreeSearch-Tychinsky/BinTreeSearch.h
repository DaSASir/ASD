#pragma once
#include "../../laba-BinTree-Tychinsky/laba-BinTree-Tychinsky/BinTree.h"
#include <iostream>
#include <vector>
#include <stack>

class BinaryTreeSearch :public BinaryTree {
public:
	template<typename T>
	class TemplateIterator;
	using Iterator = TemplateIterator<int>;
	using ConstIterator = TemplateIterator<const int>;

public:
	BinaryTreeSearch();
	BinaryTreeSearch(const std::vector<int>& vector);
	BinaryTreeSearch(const BinaryTreeSearch& other);
	BinaryTreeSearch(BinaryTreeSearch&& other) noexcept;
	~BinaryTreeSearch() override = default;

	int min() const;
	int max() const;

	using BinaryTree::add;
	bool remove(const int key);

	Node* find(const int key) const;
	int level(const int key) const;
	std::vector<int> getVector() const;

	BinaryTreeSearch& operator = (const BinaryTreeSearch& other);
	BinaryTreeSearch& operator = (BinaryTreeSearch&& other) noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	int min(Node* root) const;
	int max(Node* root) const;

	Node* add(Node* root, const int key);
	void remove(Node* node, Node* node2);
	Node* findReplacementNode(Node* root) const;

	Node* find(Node* root, const int key) const;
	int level(const Node* root, const int key, const int level_) const;
};

template <typename T>
class BinaryTreeSearch::TemplateIterator {
public:
	TemplateIterator(Node* cell) : m_cell(cell) {
		if (m_cell)
			while (m_cell->leftChild()) {
				unprocessedNodes.push_back(m_cell);
				m_cell = m_cell->leftChild();
			}
	}

	T& operator*() {
		return m_cell->key();
	}

	const T& operator*() const {
		return m_cell->key();
	}

	TemplateIterator operator++() {
		if (!m_cell) return *this;

		if (m_cell->rightChild()) {
			m_cell = m_cell->rightChild();
			while (m_cell->leftChild()) {
				unprocessedNodes.push_back(m_cell);
				m_cell = m_cell->leftChild();
			}
		}
		else if (!unprocessedNodes.empty()) {
			m_cell = unprocessedNodes.back();
			unprocessedNodes.pop_back();
		}
		else m_cell = nullptr;

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

	Node* get() {
		return m_cell;
	}

protected:
	Node* m_cell = nullptr;
	std::list<Node*> unprocessedNodes; //LNR
};