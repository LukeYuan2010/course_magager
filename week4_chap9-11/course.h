#ifndef COURSE_H
#define COURSE_H

#include "common.h"

#include <algorithm>
#include <list>
#include <set>

using std::set;
using std::list;

class Course
{
	public:
	friend ostream &operator<<(ostream &os, const Course &course);
	
	public:
	//a course must have a unique id, name and teacher can be edited later
	Course() = default;
	Course(unsigned id):m_Id(id) {}
	Course(unsigned id, const string &name, const string &teacher):m_Id(id), m_Name(name), m_Teacher(teacher) {}
	Course(const Course &course) { m_Name = course.m_Name; m_Id = course.m_Id; m_Teacher = course.m_Teacher;}
	
	//get
	unsigned int Id(void) const {return m_Id;}
	string Name(void) const {return this->m_Name;}
	string Teacher(void) const {return this->m_Teacher;}
	//set
	string SetName(const string &name) {return m_Name = name;}
	string SetTeacher(const string &teacher) {return m_Teacher = teacher;}
	//show
	ostream &Print(ostream &os) const { os << *this; return os;}

	private:
	unsigned int m_Id;	//a course must have a unique id, and can't change it 
    string	m_Name;		//course's name can be empty and changed
    string	m_Teacher;	//course's teacher can be changed and repeated
};

//unsigned int GenerateId(void);
ostream &operator<<(ostream &os, const Course &course);

class CourseManager
{
	public:
	using CourseCapType=list<Course>;

	CourseManager(void) = default;
	CourseManager(const Course curarray[], unsigned int size);
	CourseManager(CourseCapType &curcap);
	CourseManager(CourseManager &curmg);
	
	unsigned int Size(void) const {return m_CourseCap.size();}

	bool CourseExisted(const string &name, const string &teacher) const;
	bool CourseExisted(unsigned id) const;
	bool CourseExisted(const Course &coursein) const;

	bool AddCourse(const string &name, const string &teacher);
	bool AddCourse(const Course &course);

	bool DeleteCourse(const string &name);
	bool DeleteCourse(unsigned id);
	bool DeleteTeacher(const string &teacher);

	bool EditCourse(unsigned id, const string &name, const string &teacher);


	bool GetFistCourseByName(const string &name, Course &CourseOut, bool forward = true)const;
	bool GetFistCourseByPartName(const string &part_name, Course &CourseOut, bool forward = true)const;
	bool GetFistCourseByTeacher(const string &teacher, Course &CourseOut, bool forward = true)const;
	bool GetCourseById(unsigned id, Course &CourseOut)const;

	unsigned StatisticTeacher(void);
	unsigned StatisticForTeacher(const string &teacher);
	unsigned StatisticCourse(void);

	bool SortByName(void);
	bool SortByTeacher(void);
	bool SortById(void);

	bool IsEqual(unsigned firstId, unsigned secondId);

	bool ReplaceTeacher(const string &old_teacher, const string &new_teacher);
	
	bool PrintAll(void) const;
	bool PrintCourse(unsigned int id) const;
	bool ShowMaxLenCourse(void) const;

	private:
	using compare_str_type=bool (*)(const Course &, const string &);
	bool FindFirstIf(const string &str, compare_str_type f, Course &CourseOut, bool forward = true)const;
	int GetNewId(void);
	set<unsigned> m_IdSet;
	CourseCapType m_CourseCap;
};

class CmdManager
{
	public:
	CmdManager(string LogFileName = "./log.txt");
	~CmdManager();
	bool Run(void);	

	private:
	bool PrintHelpInfo(void);
	bool Process(unsigned int cmd);
	bool IsValidCmd(unsigned int cmd);
	bool RecordCmd(unsigned int cmd, bool Rslt);
	
	const unsigned int m_MinCmd = 0;
	const unsigned int m_MaxCmd = 11;

	ofstream m_LogHandle;
	bool m_ExitFlag = false;

	CourseManager m_CourseAdmin;
};




#endif
