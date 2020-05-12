#include "ConsoleTextStyle.h"
#include <iostream>
#include <windows.h>

//�����: 7 - �����(�����������), 10 - �������, 12 - �������, 14 - ������, 224 - ������ �� ������ ����
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
