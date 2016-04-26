#include "common.h"
#include "course.h"

void show_all_course(CourseV &CourseVec)
{
     if (0 == CourseVec.size())
     {
         cout << "has none course, so easy!" << endl;
     }
     else
     {
         for (auto c : CourseVec)
         {
             cout << "ID - " << c.id << ", Name - " << c.name << endl;
         }
         cout << "<<<<that's all" << endl;
     }
}

void show_max_course(CourseV &CourseVec)
{
     if (0 == CourseVec.size())
     {
         cout << "has none course, check your course please!" << endl;
     }
     else
     {
         unsigned max_length = 0;
         for (auto c : CourseVec)
         {
             if (c.name.size() > max_length)
                max_length = c.name.size();
         }
         
         cout << "max_length = " << max_length << ", course name is:" << endl;
         for (auto c : CourseVec)
         {
             if (c.name.size() == max_length)
             {
                cout <<  c.name << endl;
             }
         }
     }
}

void delet_last_course(CourseV &CourseVec)
{
     if (0 == CourseVec.size())
     {
         cout << "has none course, check your course please!" << endl;
     }
     else
     {
         auto e = CourseVec.end();
         cout << "befor delete the last course, we have " << CourseVec.size() \
              << " courses" << endl;
         CourseVec.erase(--e);    
         cout << "after delete the last course, we have " << CourseVec.size() \
              << " courses" << endl;
     }
}

int main()
{
    CourseV course_vec = { {0, "Linux" }, {1, "C++"}, {2, "HTML"}, {4, "NodeJS"},
                         {5, "Shell"}, {6, "Python"} };
    show_help_info();
    
    unsigned cmd;
    while(cin >> cmd)
    {        
        bool exit_flag = false;
        try {
            switch (cmd)
            {
                case 0:
                    show_help_info();
                    break;
                case 1:
                    show_all_course(course_vec);
                    break;
                case 2:
                     show_course_num(course_vec);
                     break;
                case 3:
                    show_max_course(course_vec);
                    break;
                case 4:
                    delet_last_course(course_vec);
                    break;
                case 5:
                     exit_flag = true;
                     break;
                default:
                    throw out_of_range("invalid input!");
                    break;
            }
        } catch (out_of_range err) {
            cout << err.what() << "\12 check you input." << endl;
            show_help_info();
        }
        
        
        if (exit_flag)
           break;       
        cout << "======================" << endl;
        cout << "input the next number:" << endl;
    }
    
    cout << "loop is out, bye!" << endl;
    return 0;
}
