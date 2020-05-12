#include "ConsoleTextStyle.h"
#include <iostream>
#include <windows.h>

//÷вета: 7 - белый(стандартный), 10 - зеленый, 12 - красный, 14 - желтый, 224 - черный на желтом фоне
bool AddConsoleTextColor(const string _text, const int color)
{
	if (color == 7) {
		cout << _text << endl;
	}
	else {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		cout << _text << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	return true;
}
