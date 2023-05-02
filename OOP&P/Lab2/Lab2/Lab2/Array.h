#pragma once

#include<iostream>

using namespace std;

class Array {
	int* data;
	int size;

	friend ostream& operator<<(std::ostream& stream, const Array& i);
	friend istream& operator>>(std::istream& stream, Array& i);

public:
	Array(); // Конструктор без парамеров
	Array(int _size); //Конструктор с парамететрамии
	Array(const Array& other); //Конструктор копирования
	~Array();// Деструктор


	void SetSize(int _size);
	int GetSize();


	Array& operator++();
	Array& operator--();
	int& operator[](int index);
};

ostream& operator<<(std::ostream& stream, const Array& i);
istream& operator>>(std::istream& stream, Array& i);

