#ifndef COURSE_H
#define COURSE_H
#include "common.h"
struct course 
{
    unsigned int id;
    string   name;
};

using CourseV=vector<struct course>;


inline void show_help_info(void)
{
     cout << "usage:\12" << 
          "input 0: show help info(that's me)\12" \
          "input 1: show all course\12" \
          "input 2: show all the course's num\12" \
          "input 3: show the max lenth course\12" \
          "input 4: delet the last course\12" \
          "input 5: exit!" << endl;
}
void show_all_course(CourseV &CourseVec);
inline void show_course_num(CourseV &CourseVec)
{
     cout << "we have " << CourseVec.size() << " courses" <<endl;
}
void show_max_course(CourseV &CourseVec);
void delet_last_course(CourseV &CourseVec);

#endif
