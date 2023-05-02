#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Stack {
	int info;
	Stack* next;
};

Stack** CreateHashTable(int m) { // Создает пустую хеш-таблицу
	Stack** hash = new Stack * [m];
	for (int i = 0; i < m; i++) hash[i] = NULL;
	return hash;
}

void Add(int info, int m, Stack** hash) { //Добавляет новый элемент в хеш-таблицу     info-значение, которое надо добавить,  m-Размер хеш-таблицы,  hash-Указатель на массив списков
	Stack* list = new Stack; //Создается список для хранения значений из массива по некому индексу

	list->info = info; //Записываем значение в новый список
	int index = info % m; //Определяется индекс , по которому необходимо положить значение из массива 

	if (hash[index] == NULL) { // Если по этому индексу еще не лежит значений
		hash[index] = list; //Присваиваем список индексу хеш-таблицы с заданным первым значением
		list->next = NULL; //Указатель на следующий элемент устанавливается в NULL
	}
	else { // Если по этому индексу уже находятся значения
		list->next = hash[index]; // Записываем в следующее звено списка значение из предыдущего звена 
		hash[index] = list; // Добавляем новый элемент в начало цепочки
	}
}

Stack* Search(int info, int m, Stack** hash) { //info- искомый элемент
	int index = abs(info % m); //Вычисляется индекс, где может находится искомый элемент
	Stack* list = hash[index]; //Записываем в list список, который хранится в хеш-таблице по данному индексу

	while (list != NULL){ // проверяем все элементы в списке
		if (list->info == info) return list; //Если значения совпали, то возвращаем звено, иначе переходим на следующее
		list = list->next;
	}
	return NULL; //Если такое значение не найдено, то возвращаем NULL
}

void View(int m, Stack** hash) { // Вывод хеш-таблицы
	Stack* list;
	cout << "\n\n\n\t\t\t\t\t\t    Hash table   \n\n";
	cout << "\t\t+-------+---------+---------+---------+---------+---------+---------+---------+\n";
	cout << "\t\t| Index | Value 1 | Value 2 | Value 3 | Value 4 | Value 5 | Value 6 | Value 7 |";
	for (int index = 0; index < m; index++) {
		cout << "\n\t\t+-------+---------------------------------------------------------------------+\n";
		cout << "\t\t|   " << index << "   |";
		
		list = hash[index];
		while (list != NULL) {
			cout <<"  " << list->info<<" ->";
			list = list->next;
		}
		cout << "  NULL   " << "|";
		
	}
	cout << "\n\t\t+-------+---------------------------------------------------------------------+\n";
}


void Delete(int m, Stack** hash) {
	Stack* list;
	Stack* current;

	for (int index = 0; index < m; index++) {
		list = hash[index];
		while (list != NULL) {
			current = list; //Сохраняет указатель на текущий элемент списка
			list = list->next;//  Переходит к следующему элементу списка
			delete current; //Удаляет текущий элемент списка
		}
		hash[index] = NULL;
	}
	delete[] hash; //Освобождает память, занимаемую массивом списков 
}

int main() {
	int n = 7;
	int array[7];
	srand(time(NULL));

	int m = 10;
	int index;

	Stack** hash;
	hash = CreateHashTable(m);

	for (index = 0; index < n; index++) {
		array[index] = rand() % (89000 - 47000 + 1) + 47000; //Заполнение массива случайными числами
		Add(array[index], m, hash);
	}

	cout << "\t\t\t\t\t\t   Value table   \n\n";
	cout << "\t\t\t\t\t\t+-------+-------+\n";
	cout << "\t\t\t\t\t\t| Index | Value |\n";
	for (index = 0; index < n; index++) {
		cout << "\t\t\t\t\t\t+-------+-------+\n";
		cout <<"\t\t\t\t\t\t|   " << index + 1 << "   | " << array[index] << " |" << endl;
	}
	cout << "\t\t\t\t\t\t+-------+-------+\n";

	View(m, hash);

	int searchNumber;
	Stack* pos;
	cout << "\n\n\nEnter value you want to find: ";
	cin >> searchNumber;

	while (searchNumber != -1) {
		pos = Search(searchNumber, m, hash);

		if (pos == NULL) cout << "There are no element in array" << endl;
		else cout <<"The element with value [" << pos->info <<"] found" << endl;
		cout << "\n\n\nEnter value you want to find: ";
		cin >> searchNumber;
	}
	Delete(m, hash);
}