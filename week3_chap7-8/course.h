#ifndef COURSE_H
#define COURSE_H
#include "common.h"

class Course
{
	public:
	friend istream &read(istream &is, Course &course);
	friend ostream &operator<<(ostream &os, const Course &course);
	
	public:
	Course(const string &name):Name(name){Id = GenerateId();}
	Course(istream &is){read(is, *this);}
	Course(const Course &course) { Name = course.Name; Id = course.Id; }
	
	unsigned int GetId(void) const {return Id;}
	bool SetId(unsigned int id) {Id = id;}
	string GetName(void) const {return this->Name;}
	string SetName(const string &name) {Name = name;}
	ostream &Print(ostream &os) const { os << *this; return os;}
	static unsigned int GenerateId(void);
	
	private:
	unsigned int Id;
    string   Name;
};

//unsigned int GenerateId(void);
ostream &operator<<(ostream &os, const Course &course);
istream &read(istream &is, Course &course);

class CourseManager
{
	public:
	CourseManager(void) = default;
	CourseManager(const Course curarray[], unsigned int size);
	CourseManager(vector<Course> &vect);
	CourseManager(CourseManager &curmg);
	
	unsigned int GetNum(void) const {return CourseList.size();}
	bool IsInList(const string &name) const;
	bool IsInList(unsigned int id) const;
	bool IsInList(const Course &cur) const;
	bool AddCourse(const string &name);
	bool AddCourse(const Course &cur);
	bool DeleteLastCourse(void);
	bool DeleteCourse(const string &name);
	bool DeleteCourse(unsigned int id);
	bool PrintAll(void) const {return PrintAll(cout);}
	bool PrintAll(ostream &fs) const;
	bool PrintCourse(const string &name) const;
	bool PrintCourse(unsigned int id) const;
	bool ShowMaxLenCourse(void) const;

	private:
	vector<Course> CourseList;
};

class CmdManager
{
	public:
	CmdManager(string LogFileName = "./log.txt");
	~CmdManager();
	bool Run(void);	

	private:
	ostream &PrintHelpInfo(void);
	bool Process(unsigned int cmd);
	bool IsValidCmd(unsigned int cmd);
	bool RecordCmd(unsigned int cmd, bool Rslt);
	
	const unsigned int MinCmd = 0;
	const unsigned int MaxCmd = 8;

	ofstream LogHandle;
	bool ExitFlag = false;

	CourseManager CourseAdmin;
};




#endif
