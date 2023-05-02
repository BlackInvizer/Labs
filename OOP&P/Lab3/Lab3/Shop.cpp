#include "Shop.h"

using namespace std;

Shop::Shop() {
	Name = "Unknown";
	Adress = "Unknown";
	City = "Unknown";
	Phone = 0;
	Type = "Shop";
}

Shop::Shop(string _name, string _adress, string _city, unsigned int _phone){
	SetName(_name);
	SetAdress(_adress);
	SetCity(_city);
	SetPhone(_phone);
	Type = "Shop";
}

Shop::Shop(string _name, string _adress, string _city, unsigned int _phone, string _type){
	SetName(_name);
	SetAdress(_adress);
	SetCity(_city);
	SetPhone(_phone);
	Type = _type;
}

Shop::Shop(const Shop& _shop){
	Name = _shop.Name;
	Adress = _shop.Adress;
	City = _shop.City;
	Phone = _shop.Phone;
	Type = _shop.Type;
}


void Shop::SetName(string _name){
	Name = _name;
}

string Shop::GetName() {
	return Name;
}

void Shop::SetAdress(string _adress) {
	Adress = _adress;
}

string Shop::GetAdress() {
	return Adress;
}

void Shop::SetCity(string _city) {
	City = _city;
}

string Shop::GetCity() {
	return City;
}

void Shop:: SetPhone(unsigned int _phone) {
	Phone = _phone;
}

unsigned int Shop::GetPhone() {
	return Phone;
}

string Shop::GetType(){
	return Type;
}






PetStore::PetStore() {
	PetsType = "Unknown";
}

PetStore::PetStore(string _name, string _adress, string _city, unsigned int _phone, string _petsType)
	: Shop(_name, _adress, _city, _phone, "PetStore")
{
	SetPetsType(_petsType);
}


void PetStore::SetPetsType(string _petsType) {
	PetsType = _petsType;
}

string PetStore::GetPetsType() {
	return PetsType;
}






HomeApplicanceStore::HomeApplicanceStore() 
{
	ProductType = "Unknown";
}

HomeApplicanceStore::HomeApplicanceStore(string _name, string _adress, string _city, unsigned int _phone, string _productType)
	: Shop(_name, _adress, _city, _phone, "HomeApplicanceStore")
{
	SetProductType(_productType);
}

void HomeApplicanceStore::SetProductType(string _productType) {
	ProductType = _productType;
}

string HomeApplicanceStore::GetProductType() {
	return ProductType;
}
