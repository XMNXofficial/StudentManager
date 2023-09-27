#pragma once
#include <core/data_base.hpp>
#include <data/rules.hpp>

class StudentManager
{
private:
	void CreateDockingParams(void* ptr);//HelloImGui::DockingParams*
public:
	data_base* DataBase;
	rules school_rule;//初始化
	std::vector<data_student>students = {};
	std::vector<data_accomplishment>accomplishment = {};
	void RunGUI();
	StudentManager();
	~StudentManager();
};