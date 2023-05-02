#include<windows.h>


#include "Array.h"

Array::Array() {
	data = nullptr;
	size = 0;
}

Array::Array(int _size) {
	SetSize(_size);
	data = new int[size];
}

Array::Array(const Array& other) {
	size = other.size;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

Array::~Array() {
	if (data != nullptr ) delete[] data;
	//cout << "Destructor\n";
}


void Array::SetSize(int _size) {
	size = _size;
}

int Array::GetSize() {
	return size;
}


Array& Array::operator++() {
	int* newData = new int[size + 1];

	for (int i = 0; i < size; i++) {	// копируем старые элементы в новый массив
		newData[i] = data[i];
	}

	newData[size] = 0;	// добавляем новый элемент в конец массива

	if (data != nullptr) delete[] data;

	data = newData;
	size++;

	return *this;

}

Array& Array::operator--() {

	if (size == 0) {
		return *this;
	}
	int* newData = nullptr;

	if (size > 1) {
		newData = new int[size - 1];
	}
	

	for (int i = 0; i < size - 1; i++) {
		newData[i] = data[i];
	}

	if (data != nullptr) delete[] data;

	data = newData;
	size--;

	return *this;
}

int& Array:: operator[](int index) {
	
	if (index < 0 || index >= size) {
		throw out_of_range("Обращение к несуществующему элементу\n");
	}

	return data[index];
}

ostream& operator<<(std::ostream& stream, const Array& arr)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	stream << "Вы создали массив: " << endl;
	stream << "{";
	for (int i = 0; i < arr.size; i++) {
		stream << arr.data[i];
		if (i != arr.size - 1) {
			stream << ", ";
		}
	}
	stream << "}";
	return stream;
}

istream& operator>>(std::istream& stream, Array& arr) {
	
	for (int i = 0; i < arr.size; i++) {
		cout << "Введите [" << i + 1 << "]" << " элемент: ";
		stream >> arr.data[i];
	}

	return stream;
}

