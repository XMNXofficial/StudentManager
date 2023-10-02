#include<extern/extern.hpp>

//MainAPP
StudentManager MainAPP;

//operate
char buffer_input_grade[1024] = { 0 };//成绩
char buffer_input_name[1024] = { 0 };//姓名
char buffer_input_schoolID[1024] = { 0 };//录入用户
char buffer_input_major[1024] = { 0 };//录入备注
char buffer_input_accomplishment_reason[1024] = { 0 };//扣分原因
char buffer_StudentSelect[1024] = { 0 };
bool buffer_isIncreaseSource = true;//1:加分,0:扣分
bool buffer_isCustomThing = true;//是否自定义事件	true:自定义,false:系统内置
int select_accomplishment_customThing = 0;
extern float buffer_accomplishment_increase_or_decrease_source = 0;
//list
int select_student_list_index = -1;//学生列表 -1代表未选中
//accomplishment列表
int select_accomplishment = 0;
//core
