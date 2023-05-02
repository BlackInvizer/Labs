#pragma once

#include <iostream>

using namespace std;

class Blog {
	char name[128]; 
	char authorShop[128]; 
	char theme[128];
	int day; 
	int month;
	int year;

public:
	Blog();
	Blog(int d, int m, int y, char n[128], char a[128], char t[128]);
	Blog(const Blog& blog);
	~Blog();


	void SetDate(int date_day, int date_month, int date_year); 

	void GetDate(int* date_day, int* date_month, int* date_year);

	void SetName(char blog_name[128]);

	const char* GetName();

	void SetAuthor(char blog_author[128]);

	const char* GetAuthor();

	void SetTheme(char blog_theme[128]);

	const char* GetTheme();

	void Clone(Blog& blog);

};

