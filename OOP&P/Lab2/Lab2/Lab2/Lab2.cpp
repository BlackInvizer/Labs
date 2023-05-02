#include <iostream>
#include<windows.h>

#include "Array.h"

using namespace  std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size;
	cout << "Введите размер массива: ";
	cin >> size;
	Array arr(size);

	cin >> arr;
	cout << endl << arr << endl;

	
	do {
		cout << "\nВыберите опцию: " << endl;
		cout << "[1] > Добавить новые элементы в конец массива" << endl;
		cout << "[2] > Удалить последние элементы" << endl;
		cout << "[3] > Завершить программу" << endl;

		int amount = 0;
		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Ведите количество новых элементов, которые вы хотите добавить в конец массива : ";
			cin >> amount;



			for (int i = 0; i < amount; i++) {
				++arr;
			}

			for (int j = arr.GetSize() - amount; j < arr.GetSize(); j++) {
				cin >> arr[j];
			}

			cout << endl << arr << endl;

			break;
		case 2:
			cout << "Ведите количество элементов, которые вы хотите удалить из конца массива: ";
			cin >> amount;

			for (int i = 0; i < amount; i++) {
				--arr;
			}

			cout << endl << arr << endl;
			break;
		case 3:
		default: return 0;
		}

	} while (true);
	
}