#pragma once

#include <string>

using namespace std;

class Shop {
	string Name;
	string Adress;
	string City;
	unsigned int Phone;
	string Type;
protected:
	Shop(string _name, string _adress, string _city, unsigned int _phone, string _type);
public:
	Shop();
	Shop(string _name, string _adress, string _city, unsigned int _phone);
	Shop(const Shop& _shop);

	void SetName(string _name);
	string GetName();
	void SetAdress(string _adress);
	string GetAdress();
	void SetCity(string _city);
	string GetCity();
	void SetPhone(unsigned int _phone);
	unsigned int GetPhone();
	string GetType();

};


class PetStore : public Shop {
	string PetsType;

public:
	PetStore();
	PetStore(string _name, string _adress, string _city, unsigned int _phone, string _petsType);

	void SetPetsType(string _petsType);
	string GetPetsType();
};


class HomeApplicanceStore : public Shop {
	string ProductType;

public :
	HomeApplicanceStore();
	HomeApplicanceStore(string _name, string _adress, string _city, unsigned int _phone, string _productType);

	void SetProductType(string _productType);
	string GetProductType();
};