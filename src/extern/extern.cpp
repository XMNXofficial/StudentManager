#include<extern/extern.hpp>

//缓冲区
char buffer_grade[1024] = { 0 };//成绩
char buffer_name[1024] = { 0 };//姓名
char buffer_EnterUser[1024] = { 0 };//录入用户
char buffer_remark[1024] = { 0 };//录入备注
char buffer_reason[1024] = { 0 };//扣分原因
char buffer_StudentSelect[1024] = { 0 };
int buffer_isIncreaseSource = 0;//1:加分,0:扣分
int buffer_isCustomThing = 0;//是否自定义事件	1:自定义,0:系统内置
int select_rules_1 = 0;//存储条款选中
int select_rules_2 = 0;//存储详细信息选中 备注:当条款被点击后,以及被切换详细信息模式(自定义/系统内置)后,需要重置详细信息选中
rules school_rule;//初始化
student_data::StudentInformation students;//初始化