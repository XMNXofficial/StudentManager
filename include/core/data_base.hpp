#pragma once
#include"sqlite3.h"
#include<string>

class data_base
{
	//备注:初始化类后,需要调用isInitOK()来确认初始化结果.
private:
	std::string Name_DataBase = "StudentManager.db";
	sqlite3* db = nullptr;//数据库
	int result_code = 0;
	bool initOK = false;
	void free_data_base();//释放sqlite3
public:
	data_base();
	~data_base();
	inline bool isInitOK() { return initOK; }

	//添加管理员
	bool Operator_add(
		std::string OperatorName,
		std::string Operator_login_ID,
		std::string Operator_login_Password
	);
	//删除管理员
	bool Operator_delete(std::string login_ID);

	bool Student_add(
		std::string Student_name,//姓名
		std::string School_ID,//学号
		std::string School_grade,//年级
		std::string School_major//专业
	);

	bool Student_delete(
		std::string School_ID
	);

	//添加素养记录,每个素养会生成一个位独立UUID
	bool Accomplishment_add(
		std::string School_ID,
		std::string behavior,
		std::string belong,
		std::string Operator_login_ID,
		float scoure
	);
	bool Accomplishment_delete(
		std::string School_ID,
		std::string Accomplishment_UUID
	);

};

//CREATE TABLE
//IF
//NOT EXISTS operator ( operator TEXT, login_ID TEXT, login_Password TEXT );
//CREATE TABLE
//IF
//NOT EXISTS accomplishment(behavior TEXT, belong TEXT, operator TEXT, scoure REAL, school_ID TEXT);
//CREATE TABLE
//IF
//NOT EXISTS student(name TEXT, school_ID TEXT, school_grade TEXT, school_major TEXT);