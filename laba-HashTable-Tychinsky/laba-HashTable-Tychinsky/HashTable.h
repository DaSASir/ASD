#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>

static const int myNumber = 17;

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
	int hash(const T key) const;

	//hi(K) = (h(i - 1)(K) + c × i + d × i^2) mod N
	int hashFunction1(const T key) const;

	//hi(K) = [h(i - 1)(K) × a × N] mod N
	int hashFunction2(const T key) const;

	//hi(K) = ((K mod N) + i × (1 + K mod (N – 2))) mod N
	int hashFunction3(const T key) const;

	//a = –(1 – √5) ÷ 2
	//c и d определяются как остаток от деления вашего номера в списке группы на 5 и 7 соответственно
	int a = (-(1 - sqrt(5))) / 2;
	int c = myNumber % 5;
	int d = myNumber % 7;

private://Метод открытой адресации
	std::vector<T> m_openTable;
	std::vector<bool> m_openActive;

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
	int m_countValues = 0;
	int m_lastIndex = 0;

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
	: m_function(function), m_method(method) {
	setSize(size);
}

template<typename T>
HashTable<T>::HashTable(const HashTable& other) {
	*this = other;
}

template<typename T>
HashTable<T>::~HashTable() {
	switch (m_method) {
	case CollisionsMethod::open:
		break;

	case CollisionsMethod::inside:
		for (int i = 0; i < m_size; i++)
			delete m_insideTable[i];
		break;

	case CollisionsMethod::outside:
		break;
	}
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
	std::swap(m_size, other.m_size);
	std::swap(m_method, other.m_method);
	std::swap(m_function, other.m_function);

	switch (m_method) {
	case CollisionsMethod::open:
		std::swap(m_openTable, other.m_openTable);
		std::swap(m_openActive, other.m_openActive);
		break;

	case CollisionsMethod::inside:
		std::swap(m_insideTable, other.m_insideTable);
		break;

	case CollisionsMethod::outside:
		std::swap(m_outsideTable, other.m_outsideTable);
		break;
	}
}

template<typename T>
void HashTable<T>::print() const {
	std::cout << "Hash-Table: \n";
	std::cout << "---------------------\n";
	switch (m_method) {
	case CollisionsMethod::open:
		for (int i = 0; i < m_size; i++) {
			if (!m_openActive[i]) 
				std::cout << "none" << std::endl;
			else
				std::cout << m_openTable[i] << std::endl;
		}

		break;

	case CollisionsMethod::inside:

		break;

	case CollisionsMethod::outside:

		break;
	}
	std::cout << "---------------------\n";
}

template<typename T>
void HashTable<T>::setSize(const int size) {
	m_size = size;

	switch (m_method) {
	case CollisionsMethod::open:
		m_openTable = std::vector<T>(m_size);
		m_openActive = std::vector<bool>(m_size, false);
		break;

	case CollisionsMethod::inside:
		m_insideTable = std::vector<Node*>(m_size);
		break;

	case CollisionsMethod::outside:
		m_outsideTable = std::vector<std::list<T>>(m_size);
		break;
	}
}

template<typename T>
HashTable<T>& HashTable<T>::operator = (const HashTable& other) {
	HashTable<T> buffer(other);
	return buffer;
}

template<typename T>
T& HashTable<T>::operator [](const int index) {
	if (index < 0) index = 0;
	else if (index >= m_size) index = m_size - 1;

	switch (m_method) {
	case CollisionsMethod::open:
		break;

	case CollisionsMethod::inside:
		break;

	case CollisionsMethod::outside:
		break;
	}
	return 0;
}

//фарш-функции
template<typename T>
int HashTable<T>::hash(const T key) const {
	int index = 0;
	switch (m_function) {
	case HashFunction::hash1:
		index = hashFunction1(key);
		break;

	case HashFunction::hash2:
		index =  hashFunction2(key);
		break;

	case HashFunction::hash3:
		index = hashFunction3(key);
		break;
	}

	if (index < 0) index *= -1;
	return index;
}

template<typename T>
int HashTable<T>::hashFunction1(const T key) const {
	if (m_countValues == 0) return (key % m_size);
	return (m_lastIndex + (c * m_countValues) + (d * m_countValues * m_countValues)) % m_size;
}

template<typename T>
int HashTable<T>::hashFunction2(const T key) const {
	if (m_countValues == 0) return (key % m_size);
	return (m_lastIndex * a * m_size) / m_size;
}

template<typename T>
int HashTable<T>::hashFunction3(const T key) const {
	if (m_countValues == 0) return (key % m_size);
	return ((key % m_size) + m_countValues * (1 + (key % (m_size - 2)))) % m_size;
}

//Метод открытой адресации
template<typename T>
void HashTable<T>::addOpenMethod(const T key) {
	if (m_countValues == m_size) return;

	int index = hash(key);
	if (m_openActive[index] == false) {
		m_openTable[index] = key;
		m_openActive[index] = true;
	}
	else {
		for (int i = 0; i < m_size; i++) {
			if (m_openActive[i] == false) {
				m_openTable[i] = key;
				m_openActive[i] = true;
			}
		}
	}

	m_countValues++;
	m_lastIndex = index;
}

template<typename T>
void HashTable<T>::removeOpenMethod(const T key) {
	
}

template<typename T>
bool HashTable<T>::hasOpenMethod(const T key) const {
	return 0;
}

//Метод внутренних цепочек
template<typename T>
void HashTable<T>::addInsideMethod(const T key) {

}

template<typename T>
void HashTable<T>::removeInsideMethod(const T key) {

}

template<typename T>
bool HashTable<T>::hasInsideMethod(const T key) const {
	return 0;
}
	
//Метод внешних цепочек
template<typename T>
void HashTable<T>::addOutsideMethod(const T key) {

}

template<typename T>
void HashTable<T>::removeOutsideMethod(const T key) {

}

template<typename T>
bool HashTable<T>::hasOutsideMethod(const T key) const {
	return 0;
}
