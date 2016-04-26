#include "common.h"
#include "course.h"


ostream &operator<<(ostream &os, const Course &course)
{
	os << course.Name << " " << course.Id;
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
		if (c.m_Name == name && c.Teacher == teacher)
			return true;
	}

	return false;
}

bool CourseManager::CourseExisted(unsigned id) const;
{
	if (m_IdSet.find(id) != m_IdSet.end())
		return true;
	else
		return false;
}

bool CourseManager::CourseExisted(const course &coursein) const
{
	for (auto c : m_CourseCap)
	{
		if (c == coursein)
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

bool CourseManager::GetFistIdByName(const string &name, bool forward = true, Course CourseOut)const
{
	
}

bool CourseManager::GetFistIdByPartName(const string &part_name, bool forward = true, Course CourseOut)const
{

}

bool CourseManager::GetFistIdByTeacher(const string &teacher, bool forward = true, Course CourseOut)const
{

}

bool CourseManager::GetFistIdByTeacher(unsigned id, bool forward = true, Course CourseOut)const
{

}

unsigned CourseManager::StatisticTeacher(void)
{

}
unsigned CourseManager::StatisticForTeacher(const string &teacher)
{

}
unsigned CourseManager::StatisticCourse(void)
{

}

bool CourseManager::SortByName(void)
{

}

bool CourseManager::SortByTeacher(void)
{

}

bool CourseManager::SortById(void)
{

}

bool CourseManager::IsEqual(unsigned firstId, unsigned secondId)
{

}


bool CourseManager::ReplaceTeacher(const string &old_teacher, const string &new_teacher)
{

}

bool CourseManager::PrintAll(ostream &fs) const
{
	if (m_CourseCap.empty())
		return false;

	for (auto c : m_CourseCap)
	{
		fs << c << endl;
	}
	return true;
}

bool CourseManager::PrintCourse(const string &name) const
{
	if (m_CourseCap.empty())
		return false;

	for (auto c : m_CourseCap)
	{
		if (c.GetName() == name)
		{
			cout << c;
			return true;
		}
	}

	return false;
}

bool CourseManager::PrintCourse(unsigned int id) const
{
	if (m_CourseCap.empty())
		return false;

	for (auto c : m_CourseCap)
	{
		if (c.GetId() == id)
		{
			cout << c;
			return true;
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
        if (c.GetName().size() > max_length)
           max_length = c.GetName().size();
    }
         
    //cout << "max_length = " << max_length << ", course name is:" << endl;
    for (auto c : m_CourseCap)
    {
        if (c.GetName().size() == max_length)
        {
           cout <<  c.GetName() << endl;
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
     "input 0: show help info(that's me)\12" \
     "input 1: show all course\12" \
     "input 2: show all the course's num\12" \
     "input 3: show the max lenth course\12" \
     "input 4: delet the last course\12" \
     "input 5: delet a course by name\12" \
     "input 6: delet a course by id\12" \
     "input 7: add a course by name\12" \
     "input 8: exit!" << endl;
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
				return CourseAdmin.PrintAll();
				break;
			case 2:
				cout << "course's num is " << CourseAdmin.GetNum();
				return true;
				break;
			case 3:
				return CourseAdmin.ShowMaxLenCourse();
				break;
			case 4:
				return  CourseAdmin.DeleteLastCourse();
				break;
			case 5:
				{
				string name;
				cout << "input the name will be deleted" << endl;
				cin >> name;
				return CourseAdmin.DeleteCourse(name);
				}
				break;
			case 6:
				{
				unsigned int id;
				cout << "input the id will be deleted" << endl;
				cin >> id;
				return CourseAdmin.DeleteCourse(id);
				}
				break;
			case 7:
				{
				string name;
				cout << "input the name will be added" << endl;
				cin >> name;
				return CourseAdmin.AddCourse(name);
				}
				break;
			case 8:
				ExitFlag = true;
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

