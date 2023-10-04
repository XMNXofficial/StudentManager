#include<extern/extern.hpp>

//MainAPP
StudentManager MainAPP;

//operate-add-student新建学生信息
char buffer_input_addStudent_grade[1024] = { 0 };//录入学生年级
char buffer_input_addStudent_name[1024] = { 0 };//录入学生姓名
char buffer_input_addStudent_schoolID[1024] = { 0 };//录入学生id
char buffer_input_addStudent_major[1024] = { 0 };//录入专业
//operate-edit-student编辑学生信息
char buffer_input_editStudent_grade[1024] = { 0 };//录入学生年级
char buffer_input_editStudent_name[1024] = { 0 };//录入学生姓名
char buffer_input_editStudent_schoolID[1024] = { 0 };//录入学生id
char buffer_input_editStudent_major[1024] = { 0 };//录入专业
//operate-add-accomplishment新建素养信息
char buffer_input_accomplishment_reason[1024] = { 0 };//扣分原因
bool buffer_isIncreaseSource = true;//true:加分,false:扣分
bool buffer_isCustomThing = true;//是否自定义事件	true:自定义,false:系统内置
float buffer_accomplishment_increase_or_decrease_source = 0.0f;//加分/减分的分值
int select_rule_list_index = 0;//系统内置规则 的选择索引
//AccomplishmentList-edit素养信息列表_编辑素养信息
char buffer_input_editAccomplishment_newBehavior[1024] = { 0 };//新的素养行为
char buffer_input_editAccomplishment_newBelong[1024] = { 0 };//所属规则
float buffer_input_editAccomplishment_newScore = 0.0f;//新的分数
bool buffer_select_editAccomplishment_newIsIncrease = true;//是否加分
//list学生列表
int select_student_list_index = -1;//学生列表 -1代表未选中
char buffer_StudentSelect[1024] = { 0 };//学生搜索输入缓冲区
//accomplishment-list-all素养列表
int select_accomplishment_list_index = 0;
