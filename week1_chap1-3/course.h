#ifndef COURSE_H
#define COURSE_H
#include "common.h"
struct course 
{
    unsigned int id;
    string   name;
};

using CourseV=vector<struct course>;


void show_help_info(void);
void show_all_course(CourseV &CourseVec);
void show_course_num(CourseV &CourseVec);
void show_max_course(CourseV &CourseVec);
void delet_last_course(CourseV &CourseVec);

#endif
