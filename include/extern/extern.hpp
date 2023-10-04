#pragma once
#include<vector>
#include"data/rules.hpp"
#include"core/data_base.hpp"
#include"StudentManager.hpp"

//MainAPP
extern StudentManager MainAPP;

//operate-add-student新建学生信息
extern char buffer_input_addStudent_grade[1024];//新建学生年级
extern char buffer_input_addStudent_name[1024];//新建学生姓名
extern char buffer_input_addStudent_schoolID[1024];//新建学生id
extern char buffer_input_addStudent_major[1024];//新建学生专业
//operate-edit-student编辑学生信息
extern char buffer_input_editStudent_grade[1024];//录入学生年级
extern char buffer_input_editStudent_name[1024];//录入学生姓名
extern char buffer_input_editStudent_schoolID[1024];//录入学生id
extern char buffer_input_editStudent_major[1024];//录入学生专业
//operate-add-accomplishment新建素养信息
extern char buffer_input_accomplishment_reason[1024];//扣分原因(素养行为behavior)
extern bool buffer_isIncreaseSource;//true:加分,false:扣分
extern bool buffer_isCustomThing; //是否自定义事件	true:自定义,false:系统内置
extern float buffer_accomplishment_increase_or_decrease_source;//加分/减分的分值
extern int select_rule_list_index;//系统内置规则 的选择索引
//AccomplishmentList-edit素养信息列表_编辑素养信息
extern char buffer_input_editAccomplishment_newBehavior[1024];//新的素养行为
extern char buffer_input_editAccomplishment_newBelong[1024];//所属规则
extern float buffer_input_editAccomplishment_newScore;//新的分数
extern bool buffer_select_editAccomplishment_newIsIncrease;//是否加分

//list学生列表
extern int select_student_list_index;//学生列表 -1代表未选中
extern char buffer_StudentSelect[1024];//学生搜索输入缓冲区
//accomplishment-list-all素养列表
extern int select_accomplishment_list_index;
