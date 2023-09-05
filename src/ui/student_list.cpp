#include "ui/student_list.hpp"
#include<imgui.h>
#include<imgui_internal.h>
#include"extern/extern.hpp"
void show_gui1()//学生扣分明细
{
}

void ui_list()//学生列表
{
	ImGui::Text("查询:");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(225);
	ImGui::InputText("##InputText_查询学生:", buffer_StudentSelect, 1024);
	ImGui::SameLine();
	if (ImGui::Button("重置"))
	{
		buffer_StudentSelect[0] = 0;
	}
	if(ImGui::BeginTable("##Table_学生列表", 1))
	{

		ImGui::EndTable();
	}
}
