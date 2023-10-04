#include"core/data_base.hpp"
#include"extern/extern.hpp"
#include"sqlite3.h"
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/locale.hpp>
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
	CREATE TABLE IF NOT EXISTS accomplishment ( behavior TEXT, belong TEXT, score REAL, school_ID TEXT, UUID TEXT );
	CREATE TABLE IF NOT EXISTS student ( name TEXT, school_ID TEXT UNIQUE , school_grade TEXT, school_major TEXT );
	)";
	//UNIQUE用来约束school_ID唯一
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
	select_student_list_index = -1;
	initOK = false;
	free_data_base();//释放sqlite3
}

void data_base::free_data_base()
{
	std::printf("free:%d", sqlite3_close(db));
	db = nullptr;
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

bool  data_base::Student_edit(
	std::string School_ID,
	std::string new_Student_name,//姓名
	std::string new_School_ID,//学号
	std::string new_School_grade,//年级
	std::string new_School_major//专业
)
{
	// 定义编译后的语句对象
	sqlite3_stmt* stmt = nullptr;

	// 定义要执行的SQL INSERT语句
	std::string Student_edit_SQLite = R"(
	UPDATE
		"main"."student" 
	SET
		"name" = ? , "school_ID" = ? , "school_grade" = ? , "school_major" = ?
	WHERE
		"school_ID" = ? ;
    )";

	// 编译参数化语句
	result_code = sqlite3_prepare_v2(db, Student_edit_SQLite.c_str(), (int)Student_edit_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//编译出错
	{
		sqlite3_finalize(stmt);//释放资源
		return false;
	}

	// 绑定参数
	int idx = 1;
	sqlite3_bind_text(stmt, idx++, new_Student_name.c_str(), (int)new_Student_name.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, new_School_ID.c_str(), (int)new_School_ID.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, new_School_grade.c_str(), (int)new_School_grade.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, new_School_major.c_str(), (int)new_School_major.length(), SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, idx++, School_ID.c_str(), (int)School_ID.length(), SQLITE_TRANSIENT);


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
	float scoure
)
{
	sqlite3_stmt* stmt = nullptr;//查询语句参数化的缓冲区
	std::string Accomplishment_add_SQLite = R"(
	INSERT INTO 
	"main"."accomplishment" 
	( "behavior", "belong", "score", "school_ID", "UUID" )
	VALUES ( ?, ?, ?, ?, ? );
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

bool data_base::Accomplishment_edit(
	std::string UUID,
	std::string new_behavior,
	std::string new_belong,
	float new_score
)
{
	sqlite3_stmt* stmt = nullptr;//查询语句参数化的缓冲区
	std::string Accomplishment_edit_SQLite = R"(
	UPDATE
		"main"."accomplishment" 
	SET
		"behavior" = ? , "belong" = ? , "score" = ? 
	WHERE
		"UUID" = ?;
	)";

	//编译参数化语句
	result_code = sqlite3_prepare_v2(db, Accomplishment_edit_SQLite.c_str(), (int)Accomplishment_edit_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)//判断是否编译成功
	{
		sqlite3_finalize(stmt);
		return false;
	}

	//绑定参数
	int idx = 1;
	sqlite3_bind_text(stmt, idx++, new_behavior.c_str(), (int)new_behavior.length(), SQLITE_TRANSIENT);//素养行为
	sqlite3_bind_text(stmt, idx++, new_belong.c_str(), (int)new_belong.length(), SQLITE_TRANSIENT);//所属条款
	sqlite3_bind_double(stmt, idx++, new_score);//分数
	sqlite3_bind_text(stmt, idx++, UUID.c_str(), (int)UUID.length(), SQLITE_TRANSIENT); //UUID

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

std::string utf8_to_gbk(const std::string& utf8Str) {
	std::string gbkStr = boost::locale::conv::between(utf8Str, "GBK", "UTF-8");
	return gbkStr;
}

std::vector<data_student> data_base::Student_Get_Lists(
	std::string student_name,
	std::string student_school_ID,
	bool isExactMatch, //是否开启全字匹配
	bool* result
)
{
	sqlite3_stmt* stmt = nullptr;
	char* error_message = nullptr;//用于存储错误消息的地址
	std::string Student_Get_Lists_SQLite = R"(
	SELECT name, school_ID ,school_grade ,school_major 
	FROM "main"."student"
	WHERE
	name LIKE ? OR school_ID LIKE ?;
	)";
	std::vector<data_student> students;

	result_code = sqlite3_prepare_v2(db, Student_Get_Lists_SQLite.c_str(), (int)Student_Get_Lists_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)
	{
		sqlite3_finalize(stmt);
		if (result != nullptr)
		{
			*result = false;
		}
		return {};
	}

	std::string pattern_student_name = student_name;
	std::string pattern_student_school_ID = student_school_ID;
	if (isExactMatch)
	{
		//开启全字匹配
		pattern_student_name += "%";
		pattern_student_school_ID += "%";
	}
	else
	{
		//关闭全字匹配
		pattern_student_name = "%" + pattern_student_name + "%";
		pattern_student_school_ID = "%" + pattern_student_school_ID + "%";
	}

	sqlite3_bind_text(stmt, 1, pattern_student_name.c_str(), (int)pattern_student_name.length(), SQLITE_TRANSIENT);//踩坑:原来绑定字符串参数,不需要加单引号!
	sqlite3_bind_text(stmt, 2, pattern_student_school_ID.c_str(), (int)pattern_student_school_ID.length(), SQLITE_TRANSIENT);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		// 从查询结果中提取数据并添加到 students 向量中
		std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		std::string schoolID(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		std::string grade = (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
		std::string major(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		data_student student;
		student.student_name = name;
		student.student_school_ID = schoolID;
		student.student_school_grade = grade;
		student.student_school_major = major;

		students.push_back(student);
	}

	sqlite3_finalize(stmt);
	if (result != nullptr)
	{
		*result = true;
	}
	return students;
}

std::vector<data_accomplishment> data_base::Accomplishment_Get(std::string student_school_ID, bool* result)
{
	std::vector<data_accomplishment> accomplishments = {};
	sqlite3_stmt* stmt = nullptr;
	std::string Accomplishment_Get_SQLite = R"(
	SELECT
		behavior,belong,score,UUID
	FROM
		'main'.'accomplishment'
	WHERE
		school_ID LIKE ?;
	)";
	result_code = sqlite3_prepare_v2(db, Accomplishment_Get_SQLite.c_str(), (int)Accomplishment_Get_SQLite.length(), &stmt, nullptr);
	if (result_code != SQLITE_OK)
	{
		if (result != nullptr)
		{
			*result = false;
		}
		return {};
	}

	sqlite3_bind_text(stmt, 1, student_school_ID.c_str(), student_school_ID.length(), SQLITE_TRANSIENT);

	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::string behavior(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		std::string belong(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		double score = sqlite3_column_double(stmt, 2);
		std::string UUID(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
		data_accomplishment accomplishment;
		accomplishment.behavior = behavior;
		accomplishment.belong = belong;
		accomplishment.score = score;
		accomplishment.UUID = UUID;
		accomplishments.push_back(accomplishment);
	}
	sqlite3_finalize(stmt);
	if (result != nullptr)
	{
		*result = true;
	}
	return accomplishments;
}

//获取最后执行结果
int data_base::Get_ResultCode()
{
	return result_code;
}