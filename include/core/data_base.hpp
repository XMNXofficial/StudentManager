#pragma once
#include"sqlite3.h"
#include<string>

class data_base
{
	//备注:初始化类后,需要调用isInitOK()来确认初始化结果.
private:
	std::string Name_DataBase = "StudentManager.db";
	sqlite3* db = nullptr;
	int result_code = 0;
	bool initOK = false;
	void free_data_base();//释放sqlite3
public:
	data_base();
	~data_base();
	inline bool isInitOK() { return initOK; }
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