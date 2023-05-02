#include "Blog.h"
#include <string.h>
#include <time.h>

Blog::Blog() {
	day = 1;
	month = 1;
	year = 2000;
	name[0] = '\0';
	author[0] = '\0';
	theme[0] = '\0';
}

Blog::Blog(int d, int m, int y, char n[128], char a[128], char t[128]){
	SetDate(d, m, y);
	SetName(n);
	SetTheme(t);
	SetAuthor(a);
}

Blog::Blog(const Blog& blog){

	strncpy_s(name, blog.name, 128);
	strncpy_s(author, blog.author, 128);
	strncpy_s(theme, blog.theme, 128);
	day = blog.day;
	month = blog.month;
	year = blog.year;
}

Blog::~Blog(){
	name[0] = '\0';
	author[0] = '\0';
	theme[0] = '\0';
}

void Blog::SetDate(int date_day, int date_month, int date_year) {
	if (date_day < 0 || date_day>31)
		return;// Возвращает значения по умолчанию, если введены неправильные
	if (date_month < 0 || date_month>12)
		return;

	time_t seconds = time(NULL);
	struct tm current_time;
	localtime_s(&current_time, &seconds); // преобразует значение времени из time t в struct tm
	int current_year = current_time.tm_year + 1900; //возвращает год начиная с 1900 года
	if (date_year < 2000 || date_year > current_year)
		return;

	day = date_day;
	month = date_month;
	year = date_year;
}

void Blog::GetDate(int* date_day, int* date_month, int* date_year) {
	*date_day = day;
	*date_month = month;
	*date_year = year;
}

void Blog::SetName(char blog_name[128]) {
	if (blog_name[0] == '\0')
		return;
	strncpy_s(name, blog_name, 128);// копирует из переданного параметра в private переменную name 128 байт

}

const char* Blog::GetName() {
	return name;
}

void Blog::SetAuthor(char blog_author[128]) {
	if (blog_author[0] == '\0')
		return;
	strncpy_s(author, blog_author, 128);
}

const char* Blog::GetAuthor() {
	return author;
}

void Blog::SetTheme(char blog_theme[128]) {
	if (blog_theme[0] == '\0')
		return;
	strncpy_s(theme, blog_theme, 128);
}

const char* Blog::GetTheme() {
	return theme;
}

void Blog::Clone(Blog& blog) {
	strncpy_s(name, blog.name, 128);
	strncpy_s(author, blog.author, 128);
	strncpy_s(theme, blog.theme, 128);
	day = blog.day;
	month = blog.month;
	year = blog.year;
}
