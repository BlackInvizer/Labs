#include "Platform.h"

#include<iostream>
#include <string>
#include<Windows.h>

using namespace std;

int inputInt(int leftRange, int rightRange)
{
    int var;
    while (1)
        if (scanf_s("%d", &var) < 1)
        {
            std::cout << "������ �����. ���������� �����\n";
            rewind(stdin);
        }
        else
        {
            if ((var < leftRange) || (var > rightRange))
                std::cout << "�������� ������� �� �������. ���������� �����\n";
            else
                return var;
        }
}





int Platform::ShowMenu(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    cout << "[1] > �������� �������" << endl;
    cout << "[2] > ����������� ��� ��������" << endl;
    cout << "[3] > ����� ��� �������� � ������" << endl;
    cout << "[4] > �����\n" << endl;
    cout << "��� ����� : ";

    int choice;

    choice = inputInt(1,4);
    cout << endl;

    return choice;
}

void Platform::AddShop(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int total;

    cout << "��������� ��������� : " << amount << endl << endl;

    cout << "������ ���������� ���������, ������� �� ������ �������� (�� 1 �� 10): ";
    total = inputInt(1, 10);
    
    Shop** newAll_shops = new Shop*[amount + total];

    for (int i = 0; i < amount; i++) {
        newAll_shops[i] = all_shops[i];
    }

    if (all_shops != nullptr) delete[] all_shops;
    all_shops = newAll_shops;

    for (int i = amount; i < amount + total; i++) {
        cout << "������� �������, ������� �������� ��������: \n";
        cout << "[1] > ������� ��� ���������� \n";
        cout << "[2] > ���������� \n";
        cout << "[3] > ������� ������� ������� \n\n";
        cout << "��� �����: \n";

        int choice;
        choice = inputInt(1, 3);

        switch (choice) {
        case 2: 
            all_shops[i] = InputPetStore();
            break;

        case 3:
            all_shops[i] = InputHomeAppStore();
            break;

        case 1:
        default:
            all_shops[i] = InputShop();
            break;
        }
    }

    SetAmount(amount + total);
    
}

void Platform::ViewAllShops(){

    for (int i = 0; i < amount; i++) {
        ViewShop(all_shops[i]);
    }
}

void Platform::ViewShop(Shop* shop) {
    cout << "�������� : " << shop->GetName() << endl;
    cout << "����� : " << shop->GetAdress() << endl;
    cout << "����� : " << shop->GetCity() << endl;
    cout << "������� : +" << shop->GetPhone() << endl;
    if (shop->GetType() == "PetStore") {
        cout << "��� ��������: " << ((PetStore*)shop)->GetPetsType() << endl << endl;
    }
    else if (shop->GetType() == "HomeApplicanceStore") {
        cout << "��� ������: " << ((HomeApplicanceStore*)shop)->GetProductType() << endl << endl;
    }
    cout << endl;
}

void Platform::ViewShopByCity(){
    cout << "������� �����, � ������� �� ������ ����� ��������: ";
    string city;
    cin >> city;
    cout << endl;

    for (int i = 0; i < amount; i++) {
        if(city == all_shops[i]->GetCity()) ViewShop(all_shops[i]);
    }
}



Shop* Platform::InputShop(){
    string name;
    cout << "������� �������� ��������: ";
    cin >> name;
    
    string adress;
    cout << "������� ����� ��������: ";
    cin >> adress;

    string city;
    cout << "������� �����, ��� ������� ��������� : ";
    cin >> city;

    unsigned int number;
    cout << "������� ������� ��������: ";
    number = inputInt(1, 9999999);
    cout << endl;

    Shop* shop = new Shop(name, adress, city, number);

    return shop;
}

PetStore* Platform::InputPetStore() {
    string name;
    cout << "������� �������� ��������: ";
    cin >> name;

    string adress;
    cout << "������� ����� ��������: ";
    cin >> adress;

    string city;
    cout << "������� �����, ��� ������� ��������� : ";
    cin >> city;

    unsigned int number;
    cout << "������� ������� ��������: ";
    number = inputInt(1, 9999999);

    string pets_type;
    cout << "������� ��� ����������� �������� : ";
    cin >> pets_type;
    cout << endl;

    PetStore* pet_store = new PetStore(name, adress, city, number , pets_type);

    return pet_store;
}

HomeApplicanceStore* Platform::InputHomeAppStore() {
    string name;
    cout << "������� �������� ��������: ";
    cin >> name;

    string adress;
    cout << "������� ����� ��������: ";
    cin >> adress;

    string city;
    cout << "������� �����, ��� ������� ��������� : ";
    cin >> city;

    unsigned int number;
    cout << "������� ������� ��������: ";
    number = inputInt(1, 9999999);

    string products_type;
    cout << "������� ��� ������������ ������ : ";
    cin >> products_type;
    cout << endl;

    HomeApplicanceStore* home_app_store = new HomeApplicanceStore(name, adress, city, number, products_type);

    return home_app_store;
}



void Platform::SetAmount(int _amount) {
    amount = _amount;
}

int Platform::GetAmount() {
    return amount;
}

void Platform::RunPlatform(){
    do {
        int c = ShowMenu();
        switch (c) {
        case 1: AddShop(); break;
        case 2: ViewAllShops(); break;
        case 3: ViewShopByCity();  break;
        case 4: 
        default: return;
        }
    } while (true);
}

Platform::Platform(){
    all_shops = nullptr;
    amount = 0;
}

Platform::~Platform(){
    if (all_shops == nullptr) return;
    for (int i = 0; i < amount; i++) {
        delete all_shops[i];
    }
    delete[] all_shops;
}
