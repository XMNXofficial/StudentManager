#pragma once
#include"sqlite3.h"
#include <vector>
#include <string>
#include <codecvt>
#include <locale>
struct data_accomplishment
{
	std::string behavior;//素养行为
	std::string belong;//奖惩所属条例
	double score = 0.0f;//分数加减
	std::string UUID;//素养的独立ID
};

struct data_operator
{
	std::string operator_name;//操作人员姓名
	std::string operator_login_ID;//操作人员账户ID
	std::string operator_password;//操作人员密码
};

struct data_student
{
	std::string student_name;//姓名
	std::string student_school_ID;//学号
	std::string student_school_grade;//班级
	std::string student_school_major;//专业
};

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

	//添加学生
	bool Student_add(
		std::string Student_name,//姓名
		std::string School_ID,//学号
		std::string School_grade,//年级
		std::string School_major//专业
	);

	bool Student_edit(
		std::string School_ID,
		std::string new_Student_name,//姓名
		std::string new_School_ID,//学号
		std::string new_School_grade,//年级
		std::string new_School_major//专业
	);

	//删除学生
	bool Student_delete(
		std::string School_ID
	);

	//添加素养记录,每个素养会生成一个位独立UUID
	bool Accomplishment_add(
		std::string School_ID,
		std::string behavior,
		std::string belong,
		float score
	);

	//编辑素养记录,以学生ID以及素养UUID作为参数
	bool Accomplishment_edit(
		std::string UUID,
		std::string new_behavior,
		std::string new_belong,
		float new_score
	);

	//删除素养记录
	bool Accomplishment_delete(
		std::string School_ID,
		std::string Accomplishment_UUID
	);

	//返回学生列表,参数空白则返回全部学生
	//支持全字匹配,默认关闭
	std::vector<data_student>Student_Get_Lists(
		std::string student_name = "",
		std::string student_school_ID = "",
		bool isExactMatch = false,//是否开启全字匹配
		bool* result = nullptr//返回查询是否成功
	);

	//根据学号取某个学生的信息
	data_student Student_Get_Data(std::string student_school_ID);

	//操作者登录
	bool Operator_Login(
		std::string Operator_login_ID,
		std::string Operator_login_password
	);

	//返回操作员用户列表,参数空白则返回全部操作者
	//支持全字匹配,默认关闭
	std::vector<data_operator> Operator_Get_Lists(
		std::string operator_name = "",
		std::string operator_login_ID = "",
		bool isExactMatch = false//是否开启全字匹配
	);

	//根据学号取某个学生的所有素养信息
	std::vector<data_accomplishment>Accomplishment_Get(std::string student_school_I, bool* result = nullptr);
	
	//获取最后执行结果
	int Get_ResultCode();
};

//CREATE TABLE
//IF
//NOT EXISTS operator ( operator TEXT, login_ID TEXT, login_Password TEXT );
//CREATE TABLE
//IF
// 
//NOT EXISTS accomplishment(behavior TEXT, belong TEXT, operator TEXT, score REAL, school_ID TEXT);
//CREATE TABLE
//IF
//NOT EXISTS student(name TEXT, school_ID TEXT, school_grade TEXT, school_major TEXT);