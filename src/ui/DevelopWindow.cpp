#include<imgui.h>
#include"extern/extern.hpp"
#include"ui/DevelopWindow.hpp"
#include"core/data_base.hpp"
#include<iostream>
#include <format>
#include<boost/locale.hpp>

DevelopWindow::DevelopWindow()
{

}

DevelopWindow::~DevelopWindow()
{

}

std::string utf8_to_gbk_(const std::string& utf8Str) {
	std::string gbkStr = boost::locale::conv::between(utf8Str, "GBK", "UTF-8");
	return gbkStr;
}

void DevelopWindow::gui()
{

	ImGui::SetNextWindowSize({ 800,600 });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(255, 0, 0, 240));//push窗口颜色
	ImGui::Begin("DevelopWindow");
	ImGui::GetIO().ConfigDockingWithShift = true;
	ImGui::Text("数据库状态:%s", MainAPP.DataBase != nullptr ? (MainAPP.DataBase->isInitOK() ? "初始化成功!" : "初始化失败.") : "未连接");

	if (ImGui::Button("断开连接"))
	{
		delete MainAPP.DataBase;
		MainAPP.DataBase = nullptr;
		MainAPP.students = {};
		MainAPP.accomplishment = {};
	}
	ImGui::SameLine();
	if (ImGui::Button("重新连接"))
	{
		MainAPP.DataBase = new data_base;
		MainAPP.students = {};
		MainAPP.accomplishment = {};
	}

	if (ImGui::Button("断开并且重连数据库"))
	{
		delete MainAPP.DataBase;
		MainAPP.DataBase = nullptr;
		MainAPP.DataBase = new data_base;
		MainAPP.students = {};
		MainAPP.accomplishment = {};

	}

	if (ImGui::Button("删除数据库(需要先断开连接)"))
	{
		int result = std::remove("./StudentManager.db");
	}

	ImGui::Separator();
	{
		if (ImGui::Button("插入测试数据"))
		{
			MainAPP.DataBase->Operator_add("陈强", "ChenQiang", "WBIOF974");
			MainAPP.DataBase->Student_add("周豪", "202235010751", "2022", "计算机科学与技术");
			MainAPP.DataBase->Student_add("柠昔", "202235010700", "2022", "计算机科学与技术");
			MainAPP.DataBase->Accomplishment_add("202235010751", "JAVA语言大赛一等奖", "第五条", "ChenQiang", 5.0);
			MainAPP.DataBase->Accomplishment_add("202235010700", "驾驶证", "第四条", "ChenQiang", 3.0);
		}
	}
	{
		static bool buffer_result = false;
		if (ImGui::Button("打印所有学生数据到控制台"))
		{
			auto students = MainAPP.DataBase->Student_Get_Lists("", "", false, &buffer_result);

			for (auto& i : students)
			{
				std::cout << std::format("Name:{}\tSchoolID:{}\tGrade:{}\tMajor:{}", utf8_to_gbk_(i.student_name), utf8_to_gbk_(i.student_school_ID), utf8_to_gbk_(i.student_school_grade), utf8_to_gbk_(i.student_school_major)) << std::endl;

			}
		}
		ImGui::SameLine();
		ImGui::Text("执行结果:%s", buffer_result ? "成功" : "失败");
	}

	//测试成功!及时搜索
	//{
	//	static char buffer_input_test[1024] = { 0 };
	//	static bool buffer_result = false;//存储返回结果
	//	ImGui::InputText("##InputText_test:", buffer_input_test, 1024);
	//	if (ImGui::IsItemEdited())
	//	{
	//		auto students = DataBase.Student_Get_Lists(&buffer_result, std::string(buffer_input_test));
	//		for (auto& i : students)
	//		{
	//			std::cout << std::format("Name:{}\tSchoolID:{}\tGrade:{}\tMajor:{}", utf8_to_gbk_(i.student_name), utf8_to_gbk_(i.student_school_ID), utf8_to_gbk_(i.student_school_grade), utf8_to_gbk_(i.student_school_major)) << std::endl;

	//		}
	//	}
	//}

	ImGui::End();
	ImGui::PopStyleColor();//push窗口颜色
}