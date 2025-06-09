#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>

enum class HashFunction {
	hash1, hash2, hash3
};

enum class CollisionsMethod {
	open, inside, outside
};

template<typename T>
class HashTable {
	struct Node;
public:
	HashTable(HashFunction function = hash1, CollisionsMethod method = open, const int size = 0);
	HashTable(const HashTable& other);
	~HashTable();

	void add(const T key);
	void remove(const T key);
	bool isThere(const T key) const;

	void swap(HashTable& other);

	void print() const;
	
	void setSize(const int size);

	HashTable& operator = (const HashTable& other);
	T& operator [](const int index);

private:
	//hash-functions
	int hash() const;

	//hi(K) = (h(i - 1)(K) + c × i + d × i^2) mod N
	int hashFunction1() const;

	//hi(K) = [h(i - 1)(K) × a × N] mod N; a = – (1 – √5) ÷ 2
	int hashFunction2() const;

	//hi(K) = ((K mod N) + i × (1 + K mod (N – 2))) mod N
	int hashFunction3() const;

	//a = –(1 – √5) ÷ 2
	//c и d определяются как остаток от деления вашего номера в списке группы на 5 и 7 соответственно
	int a = (-(1 - sqrt(5))) % 2;
	int c, d;

private://Метод открытой адресации
	std::vector<T> m_openTable;

	void addOpenMethod(const T key);
	void removeOpenMethod(const T key);
	bool hasOpenMethod(const T key) const;

private://Метод внутренних цепочек
	std::vector<Node*> m_insideTable;

	void addInsideMethod(const T key);
	void removeInsideMethod(const T key);
	bool hasInsideMethod(const T key) const;

private://Метод внешних цепочек
	std::vector<std::list<T>> m_outsideTable;

	void addOutsideMethod(const T key);
	void removeOutsideMethod(const T key);
	bool hasOutsideMethod(const T key) const;

private:
	int m_size;
	HashFunction m_function;
	CollisionsMethod m_method;
};

template<typename T>
struct HashTable<T>::Node {
	Node(Node* next = nullptr) : m_next(next) {};

	Node(const T& value, Node* next = nullptr)
		: m_data(value), m_next(next) {};

	T m_data;
	Node* m_next;
};

//необходимые функции
template<typename T>
HashTable<T>::HashTable(HashFunction function, CollisionsMethod method, const int size)
	: m_function(function), m_method(method), m_size(size) {};

template<typename T>
HashTable<T>::HashTable(const HashTable& other) {
	*this = other;
}

template<typename T>
HashTable<T>::~HashTable() {

}

template<typename T>
void HashTable<T>::add(const T key) {
	switch (m_method) {
	case CollisionsMethod::open:
		addOpenMethod(key);
		break;

	case CollisionsMethod::inside:
		addInsideMethod(key);
		break;

	case CollisionsMethod::outside:
		addOutsideMethod(key);
		break;
	}
}

template<typename T>
void HashTable<T>::remove(const T key) {
	switch (m_method) {
	case CollisionsMethod::open:
		removeOpenMethod(key);
		break;

	case CollisionsMethod::inside:
		removeInsideMethod(key);
		break;

	case CollisionsMethod::outside:
		removeOutsideMethod(key);
		break;
	}
}

template<typename T>
bool HashTable<T>::isThere(const T key) const {
	switch (m_method) {
	case CollisionsMethod::open:
		return hasOpenMethod(key);

	case CollisionsMethod::inside:
		return hasInsideMethod(key);

	case CollisionsMethod::outside:
		 return hasOutsideMethod(key);
	}
}

template<typename T>
void HashTable<T>::swap(HashTable<T>& other) {

}

template<typename T>
void HashTable<T>::print() const {

}

template<typename T>
void HashTable<T>::setSize(const int size) {
	m_size = size;
}

template<typename T>
HashTable<T>& HashTable<T>::operator = (const HashTable& other) {
	HashTable<T> buffer(other);
	return buffer;
}

template<typename T>
T& HashTable<T>::operator [](const int index) {
	return 0;
}



