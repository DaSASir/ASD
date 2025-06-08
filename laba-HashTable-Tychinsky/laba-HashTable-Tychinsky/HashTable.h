#pragma once
#include <vector>
#include <list>

class HashTable {




public:
	HashTable(const int size = 0);
	HashTable(const HashTable& other);
	~HashTable();

	void add(const int key);
	void remove(const int key);
	bool hasElement(const int key);

	void swap(HashTable& other);

	void print();
	
	void setSize(const int size);

	HashTable& operator = (const HashTable& other);
	HashTable& operator [](const int index);

private:
	//hash-functions

	//hi(K) = (h(i - 1)(K)+c × i + d × i2) mod N

	//hi(K) = [hi-1(K) × a × N] mod N; a = – (1 – √5) ÷ 2

	//hi(K) = ((K mod N) + i × (1+ K mod (N – 2))) mod N



private:
	int m_size;

	//Метод открытой адресации

	//Метод внутренних цепочек

	//Метод внешних цепочек
	std::vector<std::list<int>> m_table;




};
