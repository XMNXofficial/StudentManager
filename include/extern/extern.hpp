#pragma once
#include<vector>
#include"data/rules.hpp"
#include"data/student_data.hpp"
#include"core/data_base.hpp"
#include"StudentManager.hpp"

//operate
extern char buffer_input_grade[1024];
extern char buffer_input_name[1024];
extern char buffer_input_schoolID[1024];
extern char buffer_input_major[1024];
extern char buffer_reason[1024];
extern char buffer_StudentSelect[1024];
extern int buffer_isIncreaseSource;
extern int buffer_isCustomThing;
extern int select_rules_1;
extern int select_rules_2;
extern rules school_rule;//备注:在这里只是告诉编译器有个class的全局变量,它不会被初始化和构造.它会在extern.cpp中被构造和初始化
//list
extern int select_student_list_index;//学生列表
extern StudentManager MainAPP;