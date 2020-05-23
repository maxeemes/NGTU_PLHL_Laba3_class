#include "ConsoleTextStyle.h"
#include <iostream>
#include <windows.h>

OutputTable * CreateOutputTable()
{
	OutputTable * outTable = new OutputTable();
	outTable->content = 0;
	outTable->columnsCount = 0;
	outTable->rowsCount = 0;
	outTable->highLights = 0;
	outTable->highLightsCount = 0;
	outTable->primaryColor = 7;
	outTable->headerColor = 14;
	outTable->highLightsColor = 12;
	return outTable;
}

bool KillOutputTable(OutputTable * outTable)
{
	for (int i = 0; i < outTable->columnsCount; i++) {
		delete[] outTable->content[i];
	}
	delete[] outTable->content;
	delete[] outTable->highLights;
	delete outTable;
	return true;
}

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

bool AddConsoleTable(OutputTable * outTable)
{
	if (outTable->columnsCount <= 0 || outTable->columnsCount >= 29 || outTable->rowsCount <= 0 || outTable->rowsCount >= 9000) {
		AddConsoleTextColor("������ ����������� �������! ���������� ���������� �������!", 12);
		return false;
	}
	//���������� �������� ����������
	//max width 120
	int *columsWidth = new int[outTable->columnsCount];
	const int consoleWidth = 120;
	int columnWidth = 0, sumColumsWidth = 0, spaceForColumnContent = consoleWidth - 1 - outTable->columnsCount;
	//��������� �������
	for (int i = 0; i < outTable->columnsCount; i++) {
		columsWidth[i] = 0;
		for (int j = 0; j < outTable->columnsCount; j++) {
			columnWidth = outTable->content[i][j].length();
			columsWidth[i] = columnWidth > columsWidth[i] ? columnWidth : columsWidth[i];
		}
		if (columsWidth[i] <= 0) {
			delete[] columsWidth;
			AddConsoleTextColor("������ ����������� �������! � ������� ����� " + to_string(i) + " ��� �������� ������!");
			return false;
		}
		sumColumsWidth += columsWidth[i];
	}
	//��������������� �������� ������� ��� ������ �������
	if (sumColumsWidth > spaceForColumnContent) {
		int newColumnWidth = 0;
		for (int i = 0; i < outTable->columnsCount; i++) {
			newColumnWidth = columsWidth[i] * 100 / sumColumsWidth * spaceForColumnContent;
			if (newColumnWidth >= 3) {
				columsWidth[i] = newColumnWidth;
			}
			else if (columsWidth[i] <= newColumnWidth) {
				columsWidth[i] = newColumnWidth;
			}
			else
			{
				spaceForColumnContent -= 3 - newColumnWidth;
				columsWidth[i] = 3;
			}
		}
	}
	//���������� � �����������
	cout.fill('_');
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, outTable->headerColor);
	cout.width(consoleWidth);
	cout << "" << endl;
	//����������� ��������� �������
	for (int i = 0; i < outTable->columnsCount; i++) {
		if (i == 0) {
			cout.width(columsWidth[i] + 2);
			cout << left << "|" + outTable->content[i][0].substr(0, columsWidth[i]) << right << "|";
		}
		else
		{
			cout.width(columsWidth[i] + 1);
			cout << left << outTable->content[i][0].substr(0, columsWidth[i]) << right << "|";
		}
	}
	cout << endl;
	//����������� ���� �������
	SetConsoleTextAttribute(hConsole, outTable->primaryColor);
	for (int j = 1; j < outTable->rowsCount; j++) {
		for (int i = 0; i < outTable->columnsCount; i++) {
			if (i == 0) {
				cout.width();
				cout << "|";
			}
			cout.width(columsWidth[i]);
			if (outTable->highLightsCount > 0) {
				bool isFound = false;
				int h = 0;
				do {
					isFound = outTable->content[i][j] == outTable->highLights[h];
					h++;
				} while (isFound == false && h < outTable->highLightsCount);
				if (isFound) {
					SetConsoleTextAttribute(hConsole, outTable->highLightsColor);
					cout << left << outTable->content[i][j].substr(0, columsWidth[i]);
					SetConsoleTextAttribute(hConsole, outTable->primaryColor);
				}
				else {
					cout << left << outTable->content[i][j].substr(0, columsWidth[i]);
				}
			}
			else {
				cout << left << outTable->content[i][j].substr(0, columsWidth[i]);
			}
			cout.width();
			cout << "|";
		}
		cout << endl;
	}
	return true;
}
