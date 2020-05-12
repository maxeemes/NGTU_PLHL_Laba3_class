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
	Student(string _fio, string _group, int _subjCount, SubjectMark *_subjectMarks);
	Student(string _description);
	Student(const Student &ref);
	~Student();
	bool AddSubjectMark(string _subjectName, string _subjectMark);
	string GetFio() const;
	string GetGroup() const;
	int GetSubjectMarkCount() const;
	SubjectMark *GetAllSubjects(int &count);
	SubjectMark GetSubjectMark(int number) const;
	SubjectMark GetSubjectMark(string _subjectName) const;
	bool SetFio(string _fio);
	bool SetGroup(string _group);
	bool SetAllSubjectMarks(int _subjCount, SubjectMark *_subjectMarks);
	bool SetSubjectMark(SubjectMark _subjectMark, int number);
	bool SetSubjectMark(SubjectMark _subjectMark);
	void Print() const;
	string ToString() const;

	static string GetListName();
	static void SetListName(string _listName);
	/****************************************/
	Student &operator=(const Student &ref);
	Student &operator+=(SubjectMark _subjectMark);
	operator float() const;
	operator bool() const;
	Student &operator!();
private:
	string fio;
	string group;
	int subjCount;
	SubjectMark *subjectsMarks;
	bool InitStudentsFromString(string students);
	bool AddSubjects(string subjects);

	static string listName;
};


#endif