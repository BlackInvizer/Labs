#include <iostream>
#include <windows.h>

#include "Platform.h"

using namespace std;



int main() {
	Platform platform("D:\\University\\OOP&P\\Blogs.txt"); // файл, куда записываются данные (взят из Platform.h в атрибуте доступа public)
	platform.Run(); //метод, который запускает меню (взят из Platform.h в атрибуте доступа public)
}