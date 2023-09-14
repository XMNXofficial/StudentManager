#include"core/data_base.hpp"
#include"sqlite3.h"
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

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
	CREATE TABLE IF NOT EXISTS accomplishment ( behavior TEXT, belong TEXT, operator TEXT, scoure REAL, school_ID TEXT, UUID TEXT );
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

bool data_base::Operator_add(
	std::string OperatorName,
	std::string Operator_login_ID,
	std::string Operator_login_Password
)
{
	sqlite3_stmt* stmt = nullptr;
	std::string Operator_add_SQLite = R"(
	INSERT INTO "main"."operator"
	("operator", "login_ID", "login_Password")
	VALUES (?, ?, ?);
    )";

	// 编译参数化语句
	result_code = sqlite3_prepare_v2(db, Operator_add_SQLite.c_str(), (int)Operator_add_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//编译错误
	{
		sqlite3_finalize(stmt);  // 释放资源
		return false;
	}

	// 绑定参数
	int idx = 1;
	sqlite3_bind_text(stmt, idx++, OperatorName.c_str(), (int)OperatorName.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, Operator_login_ID.c_str(), (int)Operator_login_ID.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, Operator_login_Password.c_str(), (int)Operator_login_Password.length(), SQLITE_TRANSIENT);

	// 执行语句
	result_code = sqlite3_step(stmt);
	if (result_code != SQLITE_DONE)//执行出错
	{
		sqlite3_finalize(stmt);//释放资源
		return false;
	}

	// 释放语句对象的资源
	sqlite3_finalize(stmt);

	return true;  // 操作成功
}

bool  data_base::Operator_delete(std::string login_ID)
{
	sqlite3_stmt* stmt = nullptr;
	std::string Operator_delete_SQLite = R"(
	DELETE FROM "main"."operator"
	WHERE "login_ID" = ?;
	)";

	//编译查询语句
	result_code = sqlite3_prepare_v2(db, Operator_delete_SQLite.c_str(), (int)Operator_delete_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//编译失败
	{
		sqlite3_finalize(stmt);
		return false;
	}

	//绑定参数
	sqlite3_bind_text(stmt, 1, login_ID.c_str(), (int)login_ID.length(), SQLITE_TRANSIENT);


	result_code = sqlite3_step(stmt);//执行语句
	if (result_code != SQLITE_DONE)//执行失败
	{
		sqlite3_finalize(stmt);
		return false;
	}

	return true;
}

bool  data_base::Student_add(
	std::string Student_name,//姓名
	std::string School_ID,//学号
	std::string School_grade,//年级
	std::string School_major//专业
)
{
	// 定义编译后的语句对象
	sqlite3_stmt* stmt = nullptr;

	// 定义要执行的SQL INSERT语句
	std::string Student_add_SQLite = R"(
	INSERT INTO "main"."student"
	("name", "school_ID", "school_grade", "school_major")
	VALUES (?, ?, ?, ?);
    )";

	// 编译参数化语句
	result_code = sqlite3_prepare_v2(db, Student_add_SQLite.c_str(), (int)Student_add_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//编译出错
	{
		sqlite3_finalize(stmt);//释放资源
		return false;
	}

	// 绑定参数
	int idx = 1;
	sqlite3_bind_text(stmt, idx++, Student_name.c_str(), (int)Student_name.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, School_ID.c_str(), (int)School_ID.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, School_grade.c_str(), (int)School_grade.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, School_major.c_str(), (int)School_major.length(), SQLITE_TRANSIENT);

	// 执行语句
	result_code = sqlite3_step(stmt);
	if (result_code != SQLITE_DONE)//执行出错
	{
		sqlite3_finalize(stmt);//释放资源
		return false;
	}

	sqlite3_finalize(stmt);//释放资源
	return true;
}

bool data_base::Student_delete(
	std::string School_ID
)
{
	sqlite3_stmt* stmt = nullptr;
	std::string Student_delete_SQLite = R"(
        DELETE FROM "main"."student"
        WHERE "school_ID" = ?;
    )";

	//编译查询语句
	result_code = sqlite3_prepare_v2(db, Student_delete_SQLite.c_str(), (int)Student_delete_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//编译失败
	{
		sqlite3_finalize(stmt);
		return false;
	}

	//绑定参数
	sqlite3_bind_text(stmt, 1, School_ID.c_str(), (int)School_ID.length(), SQLITE_TRANSIENT);

	//执行语句
	result_code = sqlite3_step(stmt);
	if (result_code != SQLITE_DONE)//执行失败
	{
		sqlite3_finalize(stmt);//释放资源
		return false;
	}

	sqlite3_finalize(stmt);//释放资源
	return true;
}

bool data_base::Accomplishment_add(
	std::string School_ID,
	std::string behavior,
	std::string belong,
	std::string Operator_login_ID,
	float scoure
)
{
	sqlite3_stmt* stmt = nullptr;//查询语句参数化的缓冲区
	std::string Accomplishment_add_SQLite = R"(
	INSERT INTO 
	"main"."accomplishment" 
	( "behavior", "belong", "operator", "scoure", "school_ID", "UUID" )
	VALUES ( ?, ?, ?, ?, ?, ? );
	)";

	//uuid
	boost::uuids::random_generator uuid_gen;  // 创建 UUID 生成器对象
	boost::uuids::uuid uuid = uuid_gen();     // 生成随机 UUID
	std::string uuid_str = boost::uuids::to_string(uuid);  // 将 UUID 转换成字符串格式

	//编译参数化语句
	result_code = sqlite3_prepare_v2(db, Accomplishment_add_SQLite.c_str(), (int)Accomplishment_add_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//判断是否编译成功
	{
		sqlite3_finalize(stmt);
		return false;
	}

	//绑定参数
	int idx = 1;
	sqlite3_bind_text(stmt, idx++, behavior.c_str(), (int)behavior.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, belong.c_str(), (int)belong.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, Operator_login_ID.c_str(), (int)Operator_login_ID.length(), SQLITE_TRANSIENT);
	sqlite3_bind_double(stmt, idx++, scoure);
	sqlite3_bind_text(stmt, idx++, School_ID.c_str(), (int)School_ID.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, uuid_str.c_str(), (int)uuid_str.length(), SQLITE_TRANSIENT);  // 填写 "UUID" 字段的值

	result_code = sqlite3_step(stmt);//执行语句
	if (result_code != SQLITE_DONE)//执行失败
	{
		sqlite3_finalize(stmt);
		return false;
	}

	sqlite3_finalize(stmt);
	return true;
}

bool data_base::Accomplishment_delete(
	std::string School_ID,
	std::string Accomplishment_UUID
)
{
	sqlite3_stmt* stmt = nullptr;
	std::string Accomplishment_delete_SQLite = R"(
        DELETE FROM "main"."accomplishment"
        WHERE "UUID" = ? AND "school_ID" = ?;
    )";

	//编译参数化语句
	result_code = sqlite3_prepare_v2(db, Accomplishment_delete_SQLite.c_str(), (int)Accomplishment_delete_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//编译出错
	{
		sqlite3_finalize(stmt);
		return false;
	}

	//绑定参数
	int idx = 1;
	sqlite3_bind_text(stmt, idx++, Accomplishment_UUID.c_str(), (int)Accomplishment_UUID.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, School_ID.c_str(), (int)School_ID.length(), SQLITE_TRANSIENT);

	result_code = sqlite3_step(stmt);//执行语句
	if (result_code != SQLITE_DONE)//执行错误
	{
		sqlite3_finalize(stmt);//释放资源
		return false;
	}

	sqlite3_finalize(stmt);//释放资源
	return true;
}