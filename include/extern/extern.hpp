#pragma once
#include"data/rules.hpp"
extern char buffer_grade[1024];
extern char buffer_name[1024];
extern char buffer_EnterUser[1024];
extern char buffer_remark[1024];
extern char buffer_reason[1024];
extern char buffer_StudentSelect[1024];
extern int buffer_isIncreaseSource;
extern int buffer_isCustomThing;
extern int select_rules_1;
extern int select_rules_2;
extern rules school_rule;//备注:在这里只是告诉编译器有个class的全局变量,它不会被初始化和构造.它会在extern.cpp中被构造和初始化
