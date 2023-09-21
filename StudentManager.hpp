#pragma once
#include <core/data_base.hpp>


class StudentManager
{
private:
	void CreateDockingParams(void* ptr);//HelloImGui::DockingParams*
public:
	data_base* DataBase;
	std::vector<data_student>students = {};
	std::vector<data_accomplishment>accomplishment = {};
	void RunGUI();
	StudentManager();
	~StudentManager();
};