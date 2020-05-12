#include "Student.h"
#include "ConsoleTextStyle.h"

string Student::listName = "studentsMarks";

Student::Student() :fio(""), group(""), subjCount(0)
{
	subjectsMarks = 0;
	AddConsoleTextColor("������ ������� ��� ����������");
}

Student::Student(string _fio, string _group) :fio(_fio), group(_group), subjCount(0)
{
	subjectsMarks = 0;
	AddConsoleTextColor("������� " + fio + " �������� ��� ������");
}

Student::Student(string _fio, string _group, int _subjCount, SubjectMark * _subjectMarks) :fio(_fio), group(_group), subjCount(_subjCount)
{
	subjectsMarks = new SubjectMark[subjCount];
	for (int i = 0; i < subjCount; i++) {
		subjectsMarks[i] = _subjectMarks[i];
	}
	AddConsoleTextColor("������� " + fio + " ��������");
}

Student::Student(string _description)
{
	if (InitStudentsFromString(_description)) {
		AddConsoleTextColor("������� " + fio + " �������� �� ������");
	}
	else {
		AddConsoleTextColor("������ ���������� �������� �� ������: " + _description);
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
	AddConsoleTextColor("������� " + fio + " ����������");
}

Student::~Student()
{
	delete[] subjectsMarks;
	AddConsoleTextColor("������� " + fio + " ������");
}
