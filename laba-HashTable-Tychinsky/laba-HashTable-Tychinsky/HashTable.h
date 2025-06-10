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
	T& operator [](int index);

public:
	//hash-functions
	int hash(const T key) const;

	//hi(K) = (h(i - 1)(K) + c × i + d × i^2) mod N
	int hashFunction1(const T key, const int i) const;

	//hi(K) = [h(i - 1)(K) × a × N] mod N
	int hashFunction2(const T key, const int i) const;

	//hi(K) = ((K mod N) + i × (1 + K mod (N – 2))) mod N
	int hashFunction3(const T key, const int i) const;

	//a = –(1 – √5) ÷ 2
	//c и d определяются как остаток от деления вашего номера в списке группы на 5 и 7 соответственно
	double a = (-(1 - sqrt(5))) / 2;
	int c = myNumber % 5;
	int d = myNumber % 7;

private://Метод открытой адресации
	std::vector<T> m_openTable;
	std::vector<bool> m_openActive;

	void addOpenMethod(const T key);
	bool removeOpenMethod(const T key);
	bool hasOpenMethod(const T key) const;

private://Метод внутренних цепочек
	std::vector<Node*> m_insideTable;

	void addInsideMethod(const T key);
	bool removeInsideMethod(const T key) const;
	bool hasInsideMethod(const T key) const;

private://Метод внешних цепочек
	std::vector<std::list<T>> m_outsideTable;

	void addOutsideMethod(const T key);
	bool removeOutsideMethod(const T key) const;
	bool hasOutsideMethod(const T key) const;

private:
	int m_size;
	int m_countValues = 0;

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
	setSize((size > 0) ? size : 0);
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
	bool removed = false;
	switch (m_method) {
	case CollisionsMethod::open:
		removed = removeOpenMethod(key);
		break;

	case CollisionsMethod::inside:
		removed = removeInsideMethod(key);
		break;

	case CollisionsMethod::outside:
		removed = removeOutsideMethod(key);
		break;
	}
	if(removed) m_countValues--;
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
	std::cout << "\nSize of Hash-Table = " << m_size;
	std::cout << "\nCount of elements in Hash-Table = " << m_countValues;
	std::cout << "\n---------------------\n";
	switch (m_method) {
	case CollisionsMethod::open:
		for (int i = 0; i < m_size; i++) {
			if (m_openActive[i])
				std::cout << m_openTable[i] << " ";
			else
				std::cout << "_" << " ";
		}
		break;

	case CollisionsMethod::inside:
		for (int i = 0; i < m_size; i++) {
			Node* it = m_insideTable[i];
			while (it != nullptr) {
				std::cout << it->m_data << " ";
				it = it->m_next;
			}
			std::cout << std::endl;
		}
		break;

	case CollisionsMethod::outside:
		break;
	}
	std::cout << "\n---------------------\n";
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
		m_insideTable = std::vector<Node*>(m_size, nullptr);
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
T& HashTable<T>::operator [](int index) {
	if (index < 0) index = 0;
	else if (index >= m_size) index = m_size - 1;

	switch (m_method) {
	case CollisionsMethod::open:
		if (m_openActive[index])
			return m_openTable[index];

	case CollisionsMethod::inside:
		break;

	case CollisionsMethod::outside:
		break;
	}
}

//фарш-функции
template<typename T>
int HashTable<T>::hash(const T key) const {
	int index = 0;
	int i = m_countValues;

	switch (m_function) {
	case HashFunction::hash1:
		index = hashFunction1(key, i);
		break;

	case HashFunction::hash2:
		index =  hashFunction2(key, i);
		break;

	case HashFunction::hash3:
		index = hashFunction3(key, i);
		break;
	}

	if (index < 0) index *= -1;
	return index;
}

template<typename T>
int HashTable<T>::hashFunction1(const T key, const int i) const {
	if (i == 0) return (key % m_size);
	return (hashFunction1(key, i - 1) + (c * i) + (d * i * i)) % m_size;
}

template<typename T>
int HashTable<T>::hashFunction2(const T key, const int i) const {
	if (i == 0) return (key % m_size);
	return (hashFunction2(key, i - 1) * a * m_size) / m_size;
}

template<typename T>
int HashTable<T>::hashFunction3(const T key, const int i) const {
	if (i == 0) return (key % m_size);
	return ((key % m_size) + i * (1 + (key % (m_size - 2)))) % m_size;
}

//Метод открытой адресации
template<typename T>
void HashTable<T>::addOpenMethod(const T key) {
	if (hasOpenMethod(key)) return;
	if (m_countValues == m_size) {
		m_openTable.push_back(NULL);
		m_openActive.push_back(false);
		m_size++;
	}

	int index = hash(key);

	bool pushed = false;
	for (index; index < m_size; index++) {
		if (!m_openActive[index]) {
			m_openTable[index] = key;
			m_openActive[index] = true;
			m_countValues++;
			pushed = true;
			break;
		}
	}

	if (!pushed) {
		m_openTable.push_back(key);
		m_openActive.push_back(true);
		m_size++;
		m_countValues++;
	}
}

template<typename T>
bool HashTable<T>::removeOpenMethod(const T key) {
	if (!hasOpenMethod(key)) return false;

	int index = 0;
	for(index; index < m_size; index++)
		if (m_openTable[index] == key && m_openActive[index]) {
			m_openActive[index] = false;
			return true;
		}

	return false;
}

template<typename T>
bool HashTable<T>::hasOpenMethod(const T key) const {
	for (int i = 0; i < m_size; i++)
		if (m_openTable[i] == key && m_openActive[i])
			return true;

	return false;
}

//Метод внутренних цепочек
template<typename T>
void HashTable<T>::addInsideMethod(const T key) {
	if (hasInsideMethod(key)) return;

	int index = hash(key);
	std::cout << index << " ";

	if (m_insideTable[index] == nullptr) {
		m_insideTable[index] = new Node(key, nullptr);
	}
	else {
		Node* it = m_insideTable[index];
		while (it != nullptr) 
			it = it->m_next;
		it = new Node(key, nullptr);
		m_insideTable[index] = it;
	}
	m_countValues++;
}

template<typename T>
bool HashTable<T>::removeInsideMethod(const T key) const{
	return 0;
}

template<typename T>
bool HashTable<T>::hasInsideMethod(const T key) const {
	for (int i = 0; i < m_size; i++) {

	}

	return 0;
}
	
//Метод внешних цепочек
template<typename T>
void HashTable<T>::addOutsideMethod(const T key) {

}

template<typename T>
bool HashTable<T>::removeOutsideMethod(const T key) const{
	return 0;
}

template<typename T>
bool HashTable<T>::hasOutsideMethod(const T key) const {
	return 0;
}
