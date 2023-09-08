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
	ImGui::SetNextItemWidth(220);
	ImGui::InputText("##InputText_查询学生:", buffer_StudentSelect, 1024);
	ImGui::SameLine();
	if (ImGui::Button("重置"))
	{
		buffer_StudentSelect[0] = 0;
	}
	if (ImGui::BeginTable("##Table_学生列表", 1, ImGuiTableFlags_Borders))
	{
		//表头
		ImGui::TableSetupColumn("学生姓名-学号");
		ImGui::TableHeadersRow();
		for (int i1 = 0; i1 < students.students.size(); i1++)
		{
			auto& student = students.students[i1];
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			std::string temp(student.name + "-" + student.school_id);
			if (ImGui::Selectable(temp.c_str(), i1 == select_student_list_index ? true : false))
			{
				select_student_list_index = i1;
			}
		}

		ImGui::EndTable();
	}
}
