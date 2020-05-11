#include<string>
#ifndef STUDENT_H
#define STUDENT_H

using namespace std;
struct SubjectMark {
	string subject;
	string  mark;
};

class Student {
public:
	Student();
	Student(string _fio, string _group);
	Student(string _fio, string _group, int _subjCount, SubjectMark *_marks);
private:
	string fio;
	string group;
	int subjCount;
	SubjectMark *marks;
	bool InitStudentsFromString(string students);
	bool AddSubjects(string subjects);
};


#endif