#pragma once
#include <vector>
#include <stack>
#include "../../laba-BinTree-Tychinsky/laba-BinTree-Tychinsky/BinTree.h"

class BinaryTreeSearch : public BinaryTree {
public:
	template<typename T>
	class TemplateIterator;
	using Iterator = TemplateIterator<int>;
	using ConstIterator = TemplateIterator<const int>;

public:
	BinaryTreeSearch() = default;
	BinaryTreeSearch(const std::vector<int>& vector);
	//BinaryTreeSearch(const BinaryTreeSearch& other);
	//BinaryTreeSearch(BinaryTreeSearch&& other) noexcept;
	~BinaryTreeSearch() override = default;

	int min() const override;
	/*int max() const override;*/

	Node* add(const int key) override;
	/*bool remove(const int key) override;

	Node* find(const int key) const override;
	int level(const int key) const override;
	std::vector<int> getVector() const override;

	BinaryTreeSearch& operator = (const BinaryTreeSearch& other);
	BinaryTreeSearch& operator = (BinaryTreeSearch&& other) noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;*/

private:
	Node* add(Node* root, const int key) override;
	/*bool remove(Node* root, const int key);

	Node* find(Node* root, const int key) const;

	void printBT(const std::string& prefix, const Node* node, bool isLeft);*/

};

//template <typename T>
//class BinaryTreeSearch::TemplateIterator {
//public:
//	TemplateIterator(Node* cell) : m_cell(cell) {
//		
//	}
//
//	T& operator*() {
//		return m_cell->key();
//	}
//
//	const T& operator*() const {
//		return m_cell->key();
//	}
//
//	TemplateIterator operator++() {
//		
//	}
//
//	TemplateIterator operator++(int) {
//		TemplateIterator back = *this;
//		++(*this);
//		return back;
//	}
//
//	bool operator==(const TemplateIterator& other) const {
//		return (m_cell == other.m_cell);
//	}
//
//	bool operator!=(const TemplateIterator& other) const {
//		return (m_cell != other.m_cell);
//	}
//
//	Node* get() {
//		return m_cell;
//	}
//
//protected:
//	Node* m_cell = nullptr;
//	
//};