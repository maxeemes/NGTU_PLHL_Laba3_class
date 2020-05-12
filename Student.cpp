#include "Student.h"
#include "ConsoleTextStyle.h"

string Student::listName = "studentsMarks";

Student::Student() :fio(""), group(""), subjCount(0)
{
	subjectsMarks = 0;
	AddConsoleTextColor("Создан студент без информации");
}

Student::Student(string _fio, string _group) :fio(_fio), group(_group), subjCount(0)
{
	subjectsMarks = 0;
	AddConsoleTextColor("Студент " + fio + " добавлен без оценок");
}

Student::Student(string _fio, string _group, int _subjCount, SubjectMark * _subjectMarks) :fio(_fio), group(_group), subjCount(_subjCount)
{
	subjectsMarks = new SubjectMark[subjCount];
	for (int i = 0; i < subjCount; i++) {
		subjectsMarks[i] = _subjectMarks[i];
	}
	AddConsoleTextColor("Студент " + fio + " добавлен");
}

Student::Student(string _description)
{
	if (InitStudentsFromString(_description)) {
		AddConsoleTextColor("Студент " + fio + " добавлен из строки");
	}
	else {
		AddConsoleTextColor("Ошибка добавления студента из строки: " + _description);
	}
}

Student::Student(const Student & ref) :fio(ref.fio), group(ref.group), subjCount(ref.subjCount)
{
	if (subjCount) {
		subjectsMarks = new SubjectMark[subjCount];
		for (int i = 0; i < subjCount; i++) {
			subjectsMarks[i] = ref.subjectsMarks[i];
		}
	}
	else
		subjectsMarks = 0;
	AddConsoleTextColor("Студент " + fio + " скопирован");
}

Student::~Student()
{
	delete[] subjectsMarks;
	AddConsoleTextColor("Студент " + fio + " удален");
}
