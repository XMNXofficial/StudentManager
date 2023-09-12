#include"core/data_base.hpp"
#include"sqlite3.h"
#include <iostream>

data_base::data_base()
{
	//备注:initOK变量默认是false,只有所有步骤都初始化完成,才为true.
	result_code = sqlite3_open(Name_DataBase.c_str(), &db);//打开数据库,没有会自动创建
	if (result_code != SQLITE_OK)
	{
		free_data_base();
		return;
	}

	std::string createTableSQLite = R"(
	CREATE TABLE IF NOT EXISTS operator ( operator TEXT, login_ID TEXT, login_Password TEXT );
	CREATE TABLE IF NOT EXISTS accomplishment ( behavior TEXT, belong TEXT, operator TEXT, scoure REAL, school_ID TEXT );
	CREATE TABLE IF NOT EXISTS student ( name TEXT, school_ID TEXT, school_grade TEXT, school_major TEXT );
	)";
	result_code = sqlite3_exec(db, createTableSQLite.c_str(), nullptr, nullptr, nullptr);
	if (result_code != SQLITE_OK)
	{
		free_data_base();
		return;
	}
	initOK = true;

}

data_base::~data_base()
{
	initOK = false;
	free_data_base();//释放sqlite3
}

void data_base::free_data_base()
{
	sqlite3_close(db);
}
