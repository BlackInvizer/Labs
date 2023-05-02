#pragma once

#include "Shop.h"

using namespace std;

class Platform {
	int amount;
	Shop** all_shops;


	int ShowMenu();
	
	void AddShop();
	void ViewAllShops();
	void ViewShop(Shop*);
	void ViewShopByCity();

	Shop* InputShop();
	PetStore* InputPetStore();
	HomeApplicanceStore* InputHomeAppStore();
	

	void SetAmount(int _amount);
	int GetAmount();
	

public:
	void RunPlatform();
	Platform();
	~Platform();
};
