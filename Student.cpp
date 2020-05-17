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

bool Student::AddSubjectMark(string _subjectName, string _subjectMark)
{
	SubjectMark newSubjectMark = { _subjectName, _subjectMark };
	if (*this == newSubjectMark) {
		return false;
	}
	SubjectMark *newSubjectsMarks = new SubjectMark[subjCount+1];
	for (int i = 0; i < subjCount; i++) {
		newSubjectsMarks[i] = subjectsMarks[i];
	}
	newSubjectsMarks[subjCount] = newSubjectMark;
	delete[] subjectsMarks;
	subjCount++;
	subjectsMarks = newSubjectsMarks;
	return true;
}

string Student::GetFio() const
{
	return fio;
}

string Student::GetGroup() const
{
	return group;
}

int Student::GetSubjectMarkCount() const
{
	return subjCount;
}

SubjectMark * Student::GetAllSubjects()
{
	SubjectMark* _subjectsMarks = new SubjectMark[subjCount];
	for (int i = 0; i < subjCount; i++) {
		_subjectsMarks[i] = subjectsMarks[i];
	}
	return _subjectsMarks;
}

SubjectMark Student::GetSubjectMark(int number) const
{
	if (number < subjCount && number >= 0) {
		return subjectsMarks[number];
	}
	return SubjectMark();
}

SubjectMark Student::GetSubjectMark(string _subjectName) const
{
	if (subjCount > 0) {
		for (int i = 0; i < subjCount; i++) {
			if (subjectsMarks[i].subject == _subjectName) {
				return subjectsMarks[i];
			}
		}
	}
	return SubjectMark();
}

bool Student::SetFio(string _fio)
{
	fio = _fio;
	return true;
}

bool Student::SetGroup(string _group)
{
	group = _group;
	return true;
}

bool Student::SetAllSubjectMarks(int _subjCount, SubjectMark * _subjectsMarks)
{
	if (_subjCount > 0) {
		int tmpSubjCount = subjCount;
		SubjectMark * tmpSubjMarks = 0;
		if (tmpSubjCount > 0) {
			tmpSubjMarks = new SubjectMark[tmpSubjCount];
			for (int i = 0; i < tmpSubjCount; i++) {
				tmpSubjMarks[i] = subjectsMarks[i];
			}
			delete[] subjectsMarks;
			subjCount = 0;
		}
		for (int i = 0; i < subjCount; i++) {
			if (AddSubjectMark(_subjectsMarks[i].subject, _subjectsMarks[i].mark) == false) {
				subjCount = tmpSubjCount;
				subjectsMarks = tmpSubjMarks;
				return false;
			}
		}
		if (tmpSubjCount > 0) {
			delete[] tmpSubjMarks;
		}
	}
	else {
		return false;
	}
	return true;
}

bool Student::SetSubjectMark(SubjectMark _subjectMark, int number)
{
	if (number >= 0 && number < subjCount) {
		subjectsMarks[number] = _subjectMark;
		return true;
	}
	return false;
}

bool Student::SetSubjectMark(SubjectMark _subjectMark)
{
	for (int i = 0; i < subjCount; i++) {
		if (subjectsMarks[i].subject.compare(_subjectMark.subject) == 0) {
			subjectsMarks[i].mark = _subjectMark.mark;
			return true;
		}
	}
	return false;
}

void Student::Print() const
{
	OutputTable *studentsMarks = CreateOutputTable();
	studentsMarks->columnsCount = 2;
	studentsMarks->rowsCount = subjCount + 1;
	studentsMarks->content = new string*[subjCount + 1];
	studentsMarks->content[0] = new string[2]{"ПРЕДМЕТ", "ОЦЕНКА"};
	for (int i = 0; i < subjCount; i++) {
		studentsMarks->content[i + 1] = new string[2]{subjectsMarks[i].subject, subjectsMarks[i].mark};
	}
	/*string line = "_";
	
	AddConsoleTextColor()
	cout << left << "Студент: " + student.fio << endl;
	cout << left << "Группа: " + student.group << endl;
	cout << left << "ОЦЕНКИ" << endl;
	cout.fill('_');*/
}
