#include "Student.h"
#include "ConsoleTextStyle.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace std;

const int maxStudentsCount = 1000;
const string defaultFilePeth = "studentsMarks.txt";
int studentsCount = 0;
Student **students = 0;

int mainMenu();
int modeSelectMenu();
void studentsEditSubMenu();
void userAddStudentsFromFile();
void printAllStudents();
void userStudentAdd();
void userStudentEdit();
void userStudentDelete();
void userStudentDeleteAll();
void userSaveStudentsToFile();

bool AddStudent(Student *newStudent);
bool AddStudentsFromFile(string filePath);//TODO: Доделать функцию

string readFilePath();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int selected = 0;
	do {
		selected = mainMenu();
		switch (selected)
		{
		case 1:
			userAddStudentsFromFile();
			break;
		case 2:
			studentsEditSubMenu();
			break;
		case 3:
			userSaveStudentsToFile();
			break;
		default:
			break;
		}
	} while (selected != 4);

	getchar();
	return 0;
}

int mainMenu() {
	AddConsoleTextColor("______МЕНЮ______", 224);
	AddConsoleTextColor("1. Добавить студентов из файла", 14);
	AddConsoleTextColor("2. Просмотр/редактирование информации о студентах", 14);
	AddConsoleTextColor("3. Сохранить студентов в файл", 14);
	AddConsoleTextColor("4. ВЫХОД");
	AddConsoleTextColor("Введите номер действия...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

int modeSelectMenu() {
	AddConsoleTextColor("______Просмотр/редактирование информации о студентах______", 224);
	AddConsoleTextColor("1. Добавить студента", 14);
	AddConsoleTextColor("2. Изменить информацию о студенте", 14);
	AddConsoleTextColor("3. Удалить студента", 14);
	AddConsoleTextColor("4. Удалить всех студентов");
	AddConsoleTextColor("5. Вернуться в главное меню", 14);
	AddConsoleTextColor("Введите номер действия...", 7);
	int selected = 0;
	cin >> selected;
	return selected;
}

void studentsEditSubMenu()
{
	int selectedMode = 0;
	do {
		printAllStudents();
		selectedMode = modeSelectMenu();
		switch (modeSelectMenu())
		{
		case 1:
			userStudentAdd();
			break;
		case 2:
			userStudentEdit();
			break;
		case 3:
			userStudentDelete();
			break;
		case 4:
			userStudentDeleteAll();
			break;
		default:
			break;
		}
	} while (selectedMode != 5);
}

void userAddStudentsFromFile()
{
	AddConsoleTextColor("______Добавление студентов из файла______", 224);
	bool isExit = false;
	bool isSuccess = false;
	do {
		string filePath = readFilePath();
		isSuccess = AddStudentsFromFile(filePath);
		if (isSuccess == false) {
			AddConsoleTextColor("Ошибка! Неверный путь к файлу\nВвести снова?\n0. Да\t1. Нет");
			cin >> isExit;
		}
	} while (isSuccess == false && isExit == false);
}

bool AddStudent(Student * newStudent)
{
	int newStudentsCount = studentsCount + 1;
	if (newStudentsCount <= maxStudentsCount)
	{
		Student **newStudents = new Student *[newStudentsCount];
		newStudents[studentsCount] = newStudent;
		if (studentsCount > 0)
		{
			for (int i = 0; i < studentsCount; i++)
			{
				newStudents[i] = students[i];
			}
			delete[] students;
		}
		studentsCount = newStudentsCount;
		students = newStudents;
		return true;
	}
	return false;
}

bool AddStudentsFromFile(string filePath)
{
	AddConsoleTextColor("Чтение студентов из файла " + filePath + "...");
	ifstream fileStudents(filePath);
	if (fileStudents.is_open()) {

	}
	else {
		AddConsoleTextColor("Ошибка! Файл не найден!", 12);
		fileStudents.close();
	}
	return false;
}

string readFilePath()
{
	string filePath = "";
	AddConsoleTextColor("Введите адрес файла или любой сивол, чтобы выбрать стандартный путь...", 14);
	cin >> filePath;
	filePath = filePath.length() > 1 ? filePath : defaultFilePeth;
	return filePath;
}
