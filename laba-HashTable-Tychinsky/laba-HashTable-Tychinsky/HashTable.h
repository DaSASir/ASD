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

	struct Node {
		Node(Node* next = nullptr) : m_next(next) {};
		Node(const T& value, Node* next = nullptr)
			: m_data(value), m_next(next) {};

		T m_data;
		Node* m_next = nullptr;
	};

public:
	HashTable(const HashFunction function = hash1, const CollisionsMethod method = open, const int size = 0);
	HashTable(const HashTable& other);
	~HashTable();

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

private://Метод открытой адресации
	std::vector<T> m_openTable;
	std::vector<bool> m_openActive;

	void addOpenMethod(const T key);
	bool removeOpenMethod(const T key);
	bool hasOpenMethod(const T key) const;

private://Метод внутренних цепочек
	std::vector<Node*> m_insideTable;

	void addInsideMethod(const T key);
	bool removeInsideMethod(const T key);
	bool hasInsideMethod(const T key) const;

private://Метод внешних цепочек
	std::vector<std::list<T>> m_outsideTable;

	void addOutsideMethod(const T key);
	bool removeOutsideMethod(const T key);
	bool hasOutsideMethod(const T key) const;

private:
	int m_size;
	int m_countValues = 0;

	HashFunction m_function;
	CollisionsMethod m_method;
};

template<typename T>
HashTable<T>::HashTable(HashFunction function, CollisionsMethod method, const int size)
	: m_function(function), m_method(method) {
	setSize((size > 0) ? size : 0);
}

template<typename T>
HashTable<T>::HashTable(const HashTable& other)
	: m_method(other.m_method), m_function(other.m_function) {
	setSize(other.m_size);

	switch (m_method) {
	case CollisionsMethod::open:
		m_openActive = other.m_openActive;
		m_openTable = other.m_openTable;
		break;

	case CollisionsMethod::inside:
		for (int i = 0; i < m_size; i++) {
			Node* nodeOrig = other.m_insideTable[i];
			Node* nodeFirst = nullptr;
			Node* nodeLast = nullptr;

			while (nodeOrig) {
				Node* nodeNew = new Node(nodeOrig->m_data);

				if (!nodeFirst)
					nodeFirst = nodeNew;
				else 
					nodeLast->m_next = nodeNew;

				nodeLast = nodeNew;
				nodeOrig = nodeOrig->m_next;
			}

			m_insideTable[i] = nodeFirst;
		}
		break;

	case CollisionsMethod::outside:
		m_outsideTable = other.m_outsideTable;
		break;
	}
}

template<typename T>
HashTable<T>::~HashTable() {
	if (m_method == CollisionsMethod::inside) {
		for (int i = 0; i < m_size; i++) {
			Node* node = m_insideTable[i];
			while (node) {
				Node* next = node->m_next;
				delete node;
				node = next;
			}
		}
	}
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
	if (removed) m_countValues--;
}

template<typename T>
bool HashTable<T>::hasKey(const T key) const {
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
void HashTable<T>::print() const {
	std::cout << "\nSize of Hash-Table = " << m_size;
	std::cout << "\nCount of elements in Hash-Table = " << m_countValues;
	std::cout << "\n---------------------\n";
	switch (m_method) {
	case CollisionsMethod::open:
		for (int i = 0; i < m_size; i++) {
			std::cout << "[" << i << "]: ";
			if (m_openActive[i]) 
				std::cout << m_openTable[i];
			else std::cout << '\0';
			std::cout << "\n";
		}
		break;

	case CollisionsMethod::inside:
		for (int i = 0; i < m_size; i++) {
			std::cout << "[" << i << "]: ";
			Node* node = m_insideTable[i];
			while (node) {
				std::cout << node->m_data;
				if(node->m_next)
					std::cout<< " -> ";
				node = node->m_next;
			}
			if(!node) std::cout << '\0';
			std::cout << "\n";
		}
		break;

	case CollisionsMethod::outside:
		for (int i = 0; i < m_size; i++) {
			std::cout << "[" << i << "]: ";
			if (!m_outsideTable[i].empty()) {
				int j = 0;
				for (T element : m_outsideTable[i]) {
					std::cout << element;
					if(++j != m_outsideTable[i].size())
						std::cout << " -> ";
				}
			}
			else std::cout << "\0";
			std::cout << "\n";
		}
		break;
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
void HashTable<T>::addOpenMethod(const T key) {
	if (hasOpenMethod(key)) return;
	if (m_countValues >= m_size) return;

	for (int i = 0; i < m_size; i++) {
		int index = hash(key, i);
		if (!m_openActive[index]) {
			m_openTable[index] = key;
			m_openActive[index] = true;
			m_countValues++;
			break;
		}
	}
}

template<typename T>
bool HashTable<T>::removeOpenMethod(const T key) {
	for (int i = 0; i < m_size; i++) {
		int index = hash(key, i);
		if (m_openActive[index] && m_openTable[index] == key) {
			m_openActive[index] = false;
			return true;
		}
	}
	return false;
}

template<typename T>
bool HashTable<T>::hasOpenMethod(const T key) const {
	for (int i = 0; i < m_size; i++) {
		int index = hash(key, i);
		if (m_openActive[index] && m_openTable[index] == key)
			return true;
	}
	return false;
}

template<typename T>
void HashTable<T>::addInsideMethod(const T key) {
	if (hasInsideMethod(key)) return;
	if (m_countValues >= m_size) return;

	int index = hash(key, 0);
	std::cout << index << " ";

	if (!m_insideTable[index]) {
		m_insideTable[index] = new Node(key, nullptr);
	}
	else {
		Node* node = m_insideTable[index];

		while (node->m_next)
			node = node->m_next;

		node->m_next = new Node(key, nullptr);

		for (int i = 1; i < m_size; i++) {
			index = hash(key, i);
			if (!m_insideTable[index]) {
				m_insideTable[index] = new Node(key, nullptr);
				break;
			}
		}
	}
	m_countValues++;
}

template<typename T>
bool HashTable<T>::removeInsideMethod(const T key) {
	if (!hasInsideMethod(key)) return false;

	int index = hash(key, 0);
	Node* node = m_insideTable[index];
	Node* prev = nullptr;
	while (node) {
		if (node->m_data == key) {
			if (prev) 
				prev->m_next = node->m_next;
			else 
				m_insideTable[index] = node->m_next;

			for (int i = 0; i < m_size; i++) {
				if (m_insideTable[i]->m_data == key) {
					m_insideTable[i] = m_insideTable[i]->m_next;
					break;
				}
			}

			delete node;
			return true;
		}
		prev = node;
		node = node->m_next;
	}

	return false;
}

template<typename T>
bool HashTable<T>::hasInsideMethod(const T key) const {
	int index = hash(key, 0);
	Node* node = m_insideTable[index];
	while (node) {
		if (node->m_data == key)
			return true;
		node = node->m_next;
	}
	return false;
}

template<typename T>
void HashTable<T>::addOutsideMethod(const T key) {
	if (hasOutsideMethod(key)) return;
	if (m_countValues >= m_size) return;

	int index = hash(key, 0);
	std::cout << index << " ";

	m_outsideTable[index].push_back(key);
	m_countValues++;
}

template<typename T>
bool HashTable<T>::removeOutsideMethod(const T key) {
	if (!hasOutsideMethod(key)) return false;

	int index = hash(key, 0);
	m_outsideTable[index].remove(key);
	return true;
}

template<typename T>
bool HashTable<T>::hasOutsideMethod(const T key) const {
	int index = hash(key, 0);
	std::list<T> it = m_outsideTable[index];
	return std::find(it.begin(), it.end(), key) != it.end();
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
HashTable<T>& HashTable<T>::operator = (const HashTable& other) {
	HashTable<T> back(other);
	return back;
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
		if (m_insideTable[index])
			return m_insideTable[index]->m_data;

	case CollisionsMethod::outside:
		if (!m_outsideTable[index].empty())
			return m_outsideTable[index].front();
	}
}