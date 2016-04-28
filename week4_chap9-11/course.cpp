#include "common.h"
#include "course.h"


ostream &operator<<(ostream &os, const Course &course)
{
	os << course.Id() << course.Name() << " teached by " << course.Teacher() << endl;
	return os; 
}

//CourseManager
CourseManager::CourseManager(const Course curarray[], unsigned int size)
{
	for(int i; i < size; i++)
	{
		m_CourseCap.push_back(curarray[i]);
	}
}

CourseManager::CourseManager(CourseCapType &curcap)
{
	for (auto c : curcap)
	{
		m_CourseCap.push_back(c);
	}
}

CourseManager::CourseManager(CourseManager &curmg)
{
	for (auto c : curmg.m_CourseCap)
	{
		m_CourseCap.push_back(c);
	}
}

bool CourseManager::CourseExisted(const string &name, const string &teacher) const
{
	for (auto c : m_CourseCap)
	{
		if (c.Name() == name && c.Teacher() == teacher)
			return true;
	}

	return false;
}

bool CourseManager::CourseExisted(unsigned id) const
{
	if (m_IdSet.find(id) != m_IdSet.end())
		return true;
	else
		return false;
}

bool CourseManager::CourseExisted(const Course &coursein) const
{
	for (auto c : m_CourseCap)
	{
		if (c.Id() == coursein.Id() && c.Name() == coursein.Name() && 
				c.Teacher() == coursein.Teacher() )
			return true;
	}
	return false;
}

bool CourseManager::AddCourse(const string &name, const string &teacher)
{
	Course newCourse(GetNewId(), name, teacher);
	m_CourseCap.push_back(newCourse);
	m_IdSet.insert(newCourse.Id());
}
bool CourseManager::AddCourse(const Course &course)
{
	if (!CourseExisted(course) && !CourseExisted(course.Id()))
	{
		m_CourseCap.push_back(course);
		m_IdSet.insert(course.Id());
		return true;
	}

	return false;
}

bool CourseManager::DeleteCourse(const string &name)
{
	bool erase_once = false;
	for (auto begin = m_CourseCap.begin(); begin != m_CourseCap.end(); begin++)
	{
		if (*begin.Name() == name)
		{
			erase_once = true;
			m_IdSet.erase(*begin.Id());
			begin = m_CourseCap.erase(begin);

		}
	}

	return erase_once;
}

bool CourseManager::DeleteCourse(unsigned id)
{
	bool erase_once = false;
	for (auto begin = m_CourseCap.begin(); begin != m_CourseCap.end(); begin++)
	{
		if (*begin.Id() == id)
		{
			erase_once = true;
			m_IdSet.erase(*begin.Id());
			begin = m_CourseCap.erase(begin);
		}
	}

	return erase_once;
}

bool CourseManager::DeleteTeacher(const string &teacher)
{
	bool erase_once = false;
	for (auto begin = m_CourseCap.begin(); begin != m_CourseCap.end(); begin++)
	{
		if (*begin.Name() == name)
		{
			erase_once = true;
			m_IdSet.erase(*begin.Id());
			begin = m_CourseCap.erase(begin);
		}
	}

	return erase_once;
}

bool CourseManager::EditCourse(unsigned id, const string &name, const string &teacher)
{
	if (!CourseExisted(id))
		return false;

	for (auto begin = m_CourseCap.begin(); begin != m_CourseCap.end(); begin++) 
	{
		if (*begin.Id() == id)
			break;
	}

	if (begin == m_CourseCap.end())
		return false;

	*begin.SetName(name);
	*begin.SetTeacher(teacher);

	return true;
}

bool CourseManager::GetFistCourseByName(const string &name, Course &CourseOut, bool forward = true)const
{
	auto compare_f = [](const Course &course, const string name)->bool
					{
						if (course.Name() == name) 
							return true; 
						else 
							return false;
					}

	return FindFirstIf(name, compare_f, CourseOut, forward);
}

bool CourseManager::GetFistCourseByPartName(const string &part_name, Course &CourseOut, bool forward = true)const
{
	auto compare_f = [](const Course &course, const string part_name)->bool
					{
						if (course.Name().find(part_name) != string::npos) 
							return true; 
						else 
							return false;
					}

	return FindFirstIf(part_name, compare_f, CourseOut, forward);
}

bool CourseManager::GetFistCourseByTeacher(const string &teacher, Course &CourseOut, bool forward = true)const
{
	auto compare_f = [](const Course &course, const string teacher)->bool
					{
						if (course.Teacher() == teacher) 
							return true; 
						else 
							return false;
					}
	return FindFirstIf(name, compare_f, CourseOut, forward);
}

bool CourseManager::FindFirstIf(const string &str, compare_str_type f, Course &CourseOut, bool forward = true)const
{
	if (forward)
	{
		auto it = m_CourseCap.begin();
		for ( ; it != m_CourseCap.end(); ++it)
		{
			if (f(*it, str)) 
			{
				CourseOut == *it;
				return true;
			}
		}
	}
	else
	{
		auto it = m_CourseCap.rbegin();
		for ( ; it != m_CourseCap.rend(); ++it)
		{
			if (f(*it, str)) 
			{
				CourseOut == *it;
				return true;
			}
		}
	}

	return false;
}

bool CourseManager::GetCourseById(unsigned id, Course &CourseOut)const
{
	auto it = m_CourseCap.begin();
	for ( ; it != m_CourseCap.end(); ++it)
	{
		if (*it.Id() == id) 
		{
			CourseOut == *it;
			return true;
		}
	}

	return false;
}

unsigned CourseManager::StatisticTeacher(void)
{
	set<string> TeacherSet;
	for (auto begin = m_CourseCap.begin() ; begin != m_CourseCap.end(); ++begin)
	{
		TeacherSet.insert(*begin.Teacher());
	}

	return TeacherSet.size();
}

unsigned CourseManager::StatisticForTeacher(const string &teacher)
{
	auto f = [teacher](const Course &course)->bool
			{
				if (course.Teacher() == teacher)
					return true;
				else
					return false;
			}

	return count_if(m_CourseCap.begin(), m_CourseCap.end(), f);
}

unsigned CourseManager::StatisticCourse(void)
{
	return m_CourseCap.size();
}

bool CourseManager::SortByName(void)
{
	auto f = [](const Course &first; const Course &second)->bool{return first.Name() < second.Name();}
	sort_stable(m_CourseCap.begin(), m_CourseCap.end(), f);

	return true;
}

bool CourseManager::SortByTeacher(void)
{
	auto f = [](const Course &first; const Course &second)->bool{return first.Teacher() < second.Teacher();}
	sort_stable(m_CourseCap.begin(), m_CourseCap.end(), f);

	return true;
}

bool CourseManager::SortById(void)
{
	auto f = [](const Course &first; const Course &second)->bool{return first.Id() < second.Id();}
	sort_stable(m_CourseCap.begin(), m_CourseCap.end(), f);

	return true;
}

bool CourseManager::IsEqual(unsigned firstId, unsigned secondId)
{
	Course course1, course2;
	if (GetCourseById(firstId, course1) && GetCourseById(secondId, course2))
	{
		return (course1 == course2);
	}

	return false;
}


bool CourseManager::ReplaceTeacher(const string &old_teacher, const string &new_teacher)
{
	for (auto &c : m_CourseCap)
	{
		if (c.Teacher() == old_teacher)
			c.SetTeacher(new_teacher);
	}

	return true;
}

bool CourseManager::PrintAll(ostream &fs) const
{
	if (m_CourseCap.empty())
		return false;

	fs << "there " << m_CourseCap.size() > 1 ? " are " : " is " 
	<< m_CourseCap.size() << "course" << m_CourseCap.size() > 1 ? "s" : "" << endl;
	for (auto c : m_CourseCap)
	{
		fs << c;
	}
	return true;
}

bool CourseManager::PrintCourse(const string &name) const
{
	if (m_CourseCap.empty())
		return false;

	for (auto c : m_CourseCap)
	{
		if (c.Name() == name)
		{
			cout << c;
		}
	}

	return true;
}

bool CourseManager::PrintCourse(unsigned int id) const
{
	if (m_CourseCap.empty())
		return false;

	for (auto c : m_CourseCap)
	{
		if (c.Id() == id)
		{
			cout << c;
		}
	}

	return false;
}

bool CourseManager::ShowMaxLenCourse(void) const
{
	if (m_CourseCap.empty())
		return false;
	
	unsigned max_length = 0;
    for (auto c : m_CourseCap)
    {
        if (c.Name().size() > max_length)
           max_length = c.Name().size();
    }
         
    //cout << "max_length = " << max_length << ", course name is:" << endl;
    for (auto c : m_CourseCap)
    {
        if (c.Name().size() == max_length)
        {
           cout <<  c.Name();
        }
    }

}

int CourseManager::GetNewId(void)
{
	for (unsigned id = 0; CourseExisted(id); id++) {};
	//return the first not used id
	return id;
}

//CmdManager
CmdManager::CmdManager(string LogFileName)
{
	LogHandle.open(LogFileName, ofstream::out | ofstream::app);
}
CmdManager::~CmdManager()
{
	LogHandle.close();
}

bool CmdManager::Run(void)
{
	while(!ExitFlag)
	{
		cout << "\12=================" << endl;
		cout << "input a cmd" << endl;
		unsigned cmd = 0;
		cin >> cmd;

		RecordCmd(cmd, Process(cmd));
	}

	return true;
}	

ostream &CmdManager::PrintHelpInfo(void)
{
	cout << "usage:\12" << 
     "input 0: show help info\12" \
     "input 1: show all course\12" \
     "input 2: check if course is existed by name and teacher\12" \
     "input 3: add a new course\12" \
     "input 4: delete a course by id\12" \
     "input 5: get a course by part-name\12" \
     "input 6: Statistic a teacher's Course\12" \
     "input 7: sort by name\12" \
     "input 8: sort by id\12" \
     "input 9: sort by teacher\12" \
     "input 10: replace a teacher\12" \
     "input 11: exit!" << endl;
}

bool CmdManager::Process(unsigned int cmd)
{
	try {
		switch (cmd)
		{
			case 0:
				return PrintHelpInfo();
				break;
			case 1:
				return m_CourseAdmin.PrintAll();
				break;
			case 2:
				{
					cout << "input course's name and teacher" << endl;
					string name, teacher;
					cin >> name >> teacher;
					if (m_CourseAdmin.CourseExisted(name, teacher))
						cout << "find the course" << endl;
					else
						cout << "can't find the course" << endl;
					return true;
				}
				break;
			case 3:
				{
					cout << "input course's name and teacher" << endl;
					string name, teacher;
					cin >> name >> teacher;
					return m_CourseAdmin.AddCourse(name, teacher);
				}
				break;
			case 4:
				{
					count << "input the id will be deleted" << endl;
					unsigned id = 0;
					cin >> id;
					return m_CourseAdmin.DeleteCourse(id);
				}
				break;
			case 5:
				{
					string name;
					cout << "input the name tou want" << endl;
					cin >> name;
					Course course;
					bool result = m_CourseAdmin.GetFistCourseByPartName(name, course)
					if (result)
						cout << course;
					return result;
				}
				break;
			case 6:
				{
					cout << "input course's name teacher" << endl;
					string  teacher;
					cin >> teacher;
					cout << "teacher " << teacher << " have " <<  
							m_CourseAdmin.StatisticForTeacher(teacher) << " course" << endl;
					return true;
				}
				break;
			case 7:
				return m_CourseAdmin.SortByName();
				break;
			case 8:
				return m_CourseAdmin.SortById();
				break;
			case 9:
				return m_CourseAdmin.SortByTeacher();
				break;	
			case 10:
				{
					cout << "input course's old and new teacher" << endl;
					string old_teacher, new_teacher;
					cin >> old_teacher >> new_teacher;
					return m_CourseAdmin.ReplaceTeacher(old_teacher, new_teacher);
				}
				break;
			case 11:
				m_ExitFlag = true;
				return true;
				break;
			default:
				PrintHelpInfo();
				return false;
				break;
		}
		return true;
	} catch (out_of_range err) {
            cout << err.what() << "\12 check you input." << endl;
            PrintHelpInfo();
            return false;
    }
}

bool CmdManager::IsValidCmd(unsigned int cmd)
{
	if (cmd >= MinCmd && cmd <= MaxCmd)
		return true;
	else
		return false;
}

bool CmdManager::RecordCmd(unsigned int cmd, bool Rslt)
{
	if (LogHandle.good())
	{
		LogHandle << "cmd " << cmd << "result " << Rslt << endl;
	}
	else
	{
		return false;
	}

	return true;
}

