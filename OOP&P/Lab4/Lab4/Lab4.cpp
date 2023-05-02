#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

using namespace std;

class Material {
	public: 
		virtual float CalculatePrice() = 0;
		virtual ~Material() {
		}
		virtual void Wr2File(ofstream &file) = 0;
		virtual void Print() = 0;
};

class Tile :public Material {
	string brand;
	int height;
	int width;
	float price;
	int amount;

public:
	//Виртуальные функии
	float CalculatePrice() {
		return price * amount;
	}
	void Wr2File(ofstream& file) {
		file << "Tile:" << brand << "," << height << "," << width << "," << price << "," << amount << endl;
	}
	void Print() {
		cout << "Бренд: " << brand << "\nВысота: " << height << "\nШирина: " << width << "\nЦена за еденицу: " << price << "\nКоличество: " << amount << "\nЦена за всё: " << CalculatePrice();
		cout << endl << endl;
	}

	//Конструкторы
	Tile() {
		brand = "Unknon";
		height = 0;
		width = 0;
		price = 0;
		amount = 0;
	}
	Tile(string _brand, int _h, int _w, float _price, int _amount) {
		brand = _brand;
		height = _h;
		width = _w;
		price = _price;
		amount = _amount;
	}
	Tile(const Tile& other) {
		brand = other.brand;
		height = other.height;
		width = other.width;
		price = other.price;
		amount = other.amount;
	}

	//Другие функции
	void SetBrand(string _brand) {
		brand = _brand;
	}
	string GetBrand() {
		return brand;
	}

	void SetHeight(int _h) {
		height = _h;
	}
	int GetHeight() {
		return height;
	}

	void SetWidth(int _w) {
		width = _w;
	}
	int GetWidth() {
		return height;
	}

	void SetPrice(float _price) {
		price = _price;
	}
	float GetPrice() {
		return price;
	}

	void SetAmount(int _amount) {
		amount = _amount;
	}
	int GetAmount() {
		return amount;
	}

};

class Brick :public Material {
	string brand;
	int height;
	float price;
	int amount;

public:
	//Виртуальные функии
	float CalculatePrice() {
		return price * amount;
	}
	void Wr2File(ofstream& file) {
		file << "Brick:" << brand << "," << height << "," << price << "," << amount << endl;
	}
	void Print() {
		cout << "Бренд: " << brand << "\nВысота: " << height << "\nЦена за еденицу: " << price << "\nКоличество: " << amount << "\nЦена за всё: " << CalculatePrice();
		cout << endl << endl;
	}

	//Конструкторы
	Brick() {
		brand = "Unknon";
		height = 0;
		price = 0;
		amount = 0;
	}
	Brick(string _brand, int _h, float _price, int _amount) {
		brand = _brand;
		height = _h;
		price = _price;
		amount = _amount;
	}
	Brick(const Brick& other) {
		brand = other.brand;
		height = other.height;
		price = other.price;
		amount = other.amount;
	}

	//Другие функции
	void SetBrand(string _brand) {
		brand = _brand;
	}
	string GetBrand() {
		return brand;
	}

	void SetHeight(int _h) {
		height = _h;
	}
	int GetHeight() {
		return height;
	}

	void SetPrice(float _price) {
		price = _price;
	}
	float GetPrice() {
		return price;
	}

	void SetAmount(int _amount) {
		amount = _amount;
	}
	int GetAmount() {
		return amount;
	}
};

class Cement :public Material {
	string mark;
	int weight;
	float price_100kg;

public:
	//Виртуальные функии
	float CalculatePrice() {
		return weight * price_100kg / 100;
	}
	void Wr2File(ofstream& file) {
		file << "Cement:" << mark << "," << weight << "," << price_100kg << endl;
	}
	void Print() {
		cout << "Марка: " << mark << "\nВес: " << weight << "\nЦена за 100kg: " << price_100kg << "\nЦена за всё: " << CalculatePrice();
		cout << endl << endl;
	}

	//Конструкторы
	Cement() {
		mark = "Unknown";
		weight = 0;
		price_100kg = 0;
	}
	Cement(string _mark, int _weight, float _price100) {
		mark = _mark;
		weight = _weight;
		price_100kg = _price100;
	}
	Cement(const Cement& other) {
		mark = other.mark;
		weight = other.weight;
		price_100kg = other.price_100kg;
	}

	//Другие функции
	void SetMark(string _mark) {
		mark = _mark;
	}
	string GetMark() {
		return mark;
	}

	void SetWeight(int _w) {
		weight = _w;
	}
	int GetWeight() {
		return weight;
	}

	void SetPrice(float _price) {
		price_100kg = _price;
	}
	float GetPrice() {
		return price_100kg;
	}
};

class Glue : public Material {
	string mark;
	int volume;
	float price_100l;

public: 
	//Виртуальные функии
	float CalculatePrice() {
		return volume * price_100l / 100;
	}
	void Wr2File(ofstream& file) {
		file << "Glue:" << mark << "," << volume << "," << price_100l << endl;
	}
	void Print() {
		cout << "Марка: " << mark << "\nОбъем: " << volume << "\nЦена за 100 литров: " << price_100l << "\nЦена за всё: " << CalculatePrice();
		cout << endl << endl;
	}

	//Конструкторы
	Glue() {
		mark = "Unknown";
		volume = 0;
		price_100l = 0;
	}
	Glue(string _mark, int _volume, float _price100) {
		mark = _mark;
		volume = _volume;
		price_100l = _price100;
	}

	//Другие функции
	void SetMark(string _mark) {
		mark = _mark;
	}
	string GetMark() {
		return mark;
	}

	void SetVolume(int _v) {
		volume = _v;
	}
	int GetVolume() {
		return volume;
	}

	void SetPrice(float _price) {
		price_100l = _price;
	}
	float GetPrice() {
		return price_100l;
	}

};

// Функции работы с платформой

class Platform {
	string file;



	int ShowMenu(int level) {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);

		if (level == 0) {
			cout << "[1] > Добавить материал" << endl;
			cout << "[2] > Просмотреть все материалы" << endl;
			cout << "[4] > Выход\n" << endl;
		}
		else {
			cout << "[1] > Плитка" << endl;
			cout << "[2] > Кирпич" << endl;
			cout << "[3] > Цемент" << endl;
			cout << "[4] > Клей" << endl;
			cout << "[5] > Назад\n" << endl;
		}

		cout << "Ваш выбор : ";

		int choice;

		cin >> choice;
		cout << endl;

		return choice;
	}

	void AddMaterial() {
		Material* new_material = NULL;

		
		int c = ShowMenu(1);

		switch (c) {
		case 1: {
			string brand;
			int height;
			int width;
			float price;
			int _amount;

			cout << "\nВведите бренд плитки: ";
			cin >> brand;
			cout << "\nВведите высоту плитки: ";
			cin >> height;
			cout << "\nВведите ширину плитки: ";
			cin >> width;
			cout << "\nВведите цену плитки: ";
			cin >> price;
			cout << "\nВведите количество плитки: ";
			cin >> _amount;

			new_material = new Tile(brand, height, width, price, _amount);

			AppendMaterial(new_material);
		}  break;

		case 2: {
			string brand;
			int height;
			float price;
			int _amount;

			cout << "\nВведите бренд кирпичей: ";
			cin >> brand;
			cout << "\nВведите высоту кирпича: ";
			cin >> height;
			cout << "\nВведите цену кирпича: ";
			cin >> price;
			cout << "\nВведите количество кирпичей: ";
			cin >> _amount;

			new_material = new Brick(brand, height, price, _amount);

			AppendMaterial(new_material);
		} break;

		case 3: {
			string mark;
			int weight;
			float price_100kg;

			cout << "\nВведите марку цемента: ";
			cin >> mark;
			cout << "\nВведите вес цемента: ";
			cin >> weight;
			cout << "\nВведите цену цемента за 100кг: ";
			cin >> price_100kg;

			new_material = new Cement(mark, weight, price_100kg);

			AppendMaterial(new_material);
		} break;

		case 4: {
			string mark;
			int volume;
			float price_100l;

			cout << "\nВведите марку клея: ";
			cin >> mark;
			cout << "\nВведите объем клея: ";
			cin >> volume;
			cout << "\nВведите цену клея за 100л: ";
			cin >> price_100l;

			new_material = new Glue(mark, volume, price_100l);
			
			AppendMaterial(new_material);
		} break;
		case 5:
		default: return;
		}
		

		delete new_material;

	}

	Material** RdAllMaterials(int& amount) {
		ifstream F(file);
		if (!F.is_open()) {
			cout << "Error: Cannot open file!" << endl;
			return nullptr;
		}
		F >> amount;

		Material** all_m = new Material* [amount];
		string FL;

		string line;


		for (int i = 0; i < amount; i++) {
			getline(F, FL, '\n');
			getline(F, line, ':');
			if (line == "Tile") {
				string brand;
				int height, width, amount;
				float price;
				getline(F, brand, ',');
				F >> height;
				F.ignore();
				F >> width;
				F.ignore();
				F >> price;
				F.ignore();
				F >> amount;
				all_m[i] = new Tile(brand, height, width, price, amount);
			}
			else if (line == "Brick") {
				string brand;
				int height, amount;
				float price;
				getline(F, brand, ',');
				F >> height;
				F.ignore();
				F >> price;
				F.ignore();
				F >> amount;
				all_m[i] = new Brick(brand, height, price, amount);

			}
			else if (line == "Cement") {
				string mark;
				int weight;
				float price_100kg;

				getline(F, mark, ',');
				F >> weight;
				F.ignore();
				F >> price_100kg;
				all_m[i] = new Cement(mark, weight, price_100kg);
			}
			else if (line == "Glue") {
				string mark;
				int volume;
				float price_100l;

				getline(F, mark, ',');
				F >> volume;
				F.ignore();
				F >> price_100l;
				all_m[i] = new Glue(mark, volume, price_100l);

			}
		}
		F.close();
		return all_m;
	}

	void ViewAllMaterials() {
		ifstream F(file);
		if (!F.is_open()) {
			cout << "Error: Cannot open file!" << endl;
			return;
		}

		int amount;

		Material** allMaterials = RdAllMaterials(amount);
		for (int i = 0; i < amount; i++) {
			allMaterials[i]->Print();
		}

		F.close();

		for (int i = 0; i < amount; i++) {
			delete allMaterials[i];
		}
		delete[] allMaterials;
	}

	void AppendMaterial(Material* last_mat) {
		int amount;
		Material** all = RdAllMaterials(amount);
		amount++;
		ofstream File(file);

		File << amount << endl;

		for (int i = 0; i < amount - 1 ; i++) {
			all[i]->Wr2File(File);
		}
		last_mat->Wr2File(File);

		File.close();

		for (int i = 0; i < amount - 1; i++) {
			delete all[i];
		}
		delete[] all;
	}

public:
	Platform(string _file) {
		file = _file;
	}

	void RunPlatform() {
		do {
			int c = ShowMenu(0);
			switch (c) {
			case 1: AddMaterial(); break;
			case 2: ViewAllMaterials(); break;
			case 3:
			default: return;
			}
		} while (true);
	}
};



int main()
{
	Platform platform("E:\\A_Univer\\OOP&P\\Lab4\\Materials.txt");
	platform.RunPlatform();
}
