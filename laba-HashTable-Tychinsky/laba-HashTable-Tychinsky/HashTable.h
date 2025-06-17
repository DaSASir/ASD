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

template<typename T>
class HashTable {
public:
	HashTable(const HashFunction function = hash1, const int size = 0);
	HashTable(const HashTable& other);
	~HashTable() = default;

	void add(const T key);
	void remove(const T key);
	bool hasKey(const T key) const;

	void swap(HashTable& other);

	void print() const;
	
	void setSize(const int size);

	HashTable& operator = (const HashTable& other);
	T& operator [](int index);

public:
	//hash-functions
	int hash(const T key, const int i) const;

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

private://Метод внешних цепочек
	std::vector<std::list<T>> m_outsideTable;
	bool removeOutsideMethod(const T key);

private:
	int m_size;
	int m_countValues = 0;

	HashFunction m_function;
};

template<typename T>
HashTable<T>::HashTable(HashFunction function, const int size)
	: m_function(function), m_method(method) {
	setSize((size > 0) ? size : 0);
}

template<typename T>
HashTable<T>::HashTable(const HashTable& other)
	: m_method(other.m_method), m_function(other.m_function) {
	setSize(other.m_size);
	m_outsideTable = other.m_outsideTable;
}

template<typename T>
void HashTable<T>::setSize(const int size) {
	m_size = size;
	m_outsideTable = std::vector<std::list<T>>(m_size);
}

template<typename T>
void HashTable<T>::add(const T key) {
	if (hasOutsideMethod(key)) return;
	if (m_countValues >= m_size) return;

	int index = hash(key, 0);
	std::cout << index << " ";

	m_outsideTable[index].push_back(key);
	m_countValues++;
}

template<typename T>
void HashTable<T>::remove(const T key) {
	if (removeOutsideMethod(key))
		m_countValues--;
}

template<typename T>
bool HashTable<T>::hasKey(const T key) const {
	int index = hash(key, 0);
	std::list<T> it = m_outsideTable[index];
	return std::find(it.begin(), it.end(), key) != it.end();
}

template<typename T>
void HashTable<T>::print() const {
	std::cout << "\nSize of Hash-Table = " << m_size;
	std::cout << "\nCount of elements in Hash-Table = " << m_countValues;
	std::cout << "\n---------------------\n";
	for (int i = 0; i < m_size; i++) {
		std::cout << "[" << i << "]: ";
		if (!m_outsideTable[i].empty()) {
			int j = 0;
			for (T element : m_outsideTable[i]) {
				std::cout << element;
				if (++j != m_outsideTable[i].size())
					std::cout << " -> ";
			}
		}
		else std::cout << "\0";
		std::cout << "\n";
	}
	std::cout << "---------------------\n";
}

template<typename T>
int HashTable<T>::hash(const T key, const int i) const {
	int index = 0;

	switch (m_function) {
	case HashFunction::hash1:
		index = hashFunction1(key, i);
		break;

	case HashFunction::hash2:
		index = hashFunction2(key, i);
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

template<typename T>
bool HashTable<T>::removeOutsideMethod(const T key) {
	if (!hasKey(key)) return false;
	int index = hash(key, 0);
	m_outsideTable[index].remove(key);
	return true;
}

template<typename T>
void HashTable<T>::swap(HashTable<T>& other) {
	std::swap(m_size, other.m_size);
	std::swap(m_method, other.m_method);
	std::swap(m_function, other.m_function);

	std::swap(m_outsideTable, other.m_outsideTable);
}

template<typename T>
HashTable<T>& HashTable<T>::operator = (const HashTable& other) {
	HashTable<T> back(other);
	return back;
}

template<typename T>
T& HashTable<T>::operator [](int index) {
	if (index < 0) index = 0;
	else if (index >= m_size) index = m_size - 1;

	if (!m_outsideTable[index].empty())
		return m_outsideTable[index].front();
}