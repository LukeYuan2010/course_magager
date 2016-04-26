#include "common.h"
#include "course.h"

unsigned int Course::GenerateId(void)
{
	static unsigned int Id = 0;
	return Id++; 
}

ostream &operator<<(ostream &os, const Course &course)
{
	os << course.Name << " " << course.Id;
	return os; 
}

istream &read(istream &is, Course &course)
{
	is >> course.Name >> course.Id;
	return is;
}

//CourseManager
CourseManager::CourseManager(const Course curarray[], unsigned int size)
{
	for(int i; i < size; i++)
	{
		CourseList.push_back(curarray[i]);
	}
}

CourseManager::CourseManager(vector<Course> &vect)
{
	for (auto c : vect)
	{
		CourseList.push_back(c);
	}
}

CourseManager::CourseManager(CourseManager &curmg)
{
	for (auto c : curmg.CourseList)
	{
		CourseList.push_back(c);
	}
}

bool CourseManager::IsInList(const string &name) const
{
	for (auto c : CourseList)
	{
		if (name == c.GetName())
			return true;
	}

	return false;
}

bool CourseManager::IsInList(unsigned int id) const
{
	for (auto c : CourseList)
	{
		if (id == c.GetId())
			return true;
	}

	return false;
}

bool CourseManager::IsInList(const Course &cur) const
{
	for (auto c : CourseList)
	{
		if (cur.GetName() == c.GetName() || cur.GetId() == c.GetId())
			return true;
	}

	return false;
}

bool CourseManager::AddCourse(const string &name)
{
	if (!IsInList(name))
	{
		CourseList.push_back(Course(name));
		return true;
	}

	return false;
}

bool CourseManager::AddCourse(const Course &cur)
{
	if (!IsInList(cur))
	{
		CourseList.push_back(cur);
		return true;
	}

	return false;
}

bool CourseManager::DeleteLastCourse(void)
{
	if (!CourseList.empty())
	{
		CourseList.erase(--(CourseList.end()));
		return true;
	}

	return false;
}

bool CourseManager::DeleteCourse(const string &name)
{
	for (auto b = CourseList.begin(); b != CourseList.end(); b++)
	{
		if (b->GetName() == name)
		{
			CourseList.erase(b);
			return true;
		}
	}

	return false;
}

bool CourseManager::DeleteCourse(unsigned int id)
{
	for (auto b = CourseList.begin(); b != CourseList.end(); b++)
	{
		if (b->GetId() == id)
		{
			CourseList.erase(b);
			return true;
		}
	}

	return false;
}

bool CourseManager::PrintAll(ostream &fs) const
{
	if (CourseList.empty())
		return false;

	for (auto c : CourseList)
	{
		fs << c << endl;
	}
	return true;
}

bool CourseManager::PrintCourse(const string &name) const
{
	if (CourseList.empty())
		return false;

	for (auto c : CourseList)
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
	if (CourseList.empty())
		return false;

	for (auto c : CourseList)
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
	if (CourseList.empty())
		return false;
	
	unsigned max_length = 0;
    for (auto c : CourseList)
    {
        if (c.GetName().size() > max_length)
           max_length = c.GetName().size();
    }
         
    //cout << "max_length = " << max_length << ", course name is:" << endl;
    for (auto c : CourseList)
    {
        if (c.GetName().size() == max_length)
        {
           cout <<  c.GetName() << endl;
        }
    }

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

