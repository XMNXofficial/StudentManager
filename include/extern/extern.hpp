#pragma once
#include<vector>
#include"data/rules.hpp"
#include"core/data_base.hpp"
#include"StudentManager.hpp"

//operate
extern char buffer_input_grade[1024];
extern char buffer_input_name[1024];
extern char buffer_input_schoolID[1024];
extern char buffer_input_major[1024];
extern char buffer_input_accomplishment_reason[1024];
extern char buffer_StudentSelect[1024];
extern bool buffer_isIncreaseSource;
extern bool buffer_isCustomThing;
extern int select_accomplishment_customThing;
extern float buffer_accomplishment_increase_or_decrease_source;

//list
extern int select_student_list_index;//学生列表
extern StudentManager MainAPP;