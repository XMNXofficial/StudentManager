#include"ui/accomplishment.hpp"
#include<imgui.h>
#include<imgui_internal.h>
#include"extern/extern.hpp"

void ui_accomplishment()
{
	if (select_student_list_index == -1)
	{
		ImGui::Text("当前选中学生:%s", "当前未选中!");
	}
	else
	{
		ImGui::Text("当前选中学生:%s-%s", MainAPP.students[select_student_list_index].student_name.c_str(), MainAPP.students[select_student_list_index].student_school_ID.c_str());

	}
	if (ImGui::BeginTable("##Table_accomplishment_detail", 4))
	{
		ImGui::TableSetupColumn("事件");
		ImGui::TableSetupColumn("评分");
		ImGui::TableSetupColumn("条款");
		ImGui::TableSetupColumn("录入用户");
		ImGui::TableHeadersRow();
		auto temp_accomplishment_all = MainAPP.students[select_student_list_index].accomplishments;//所有素养
		for (int i1 = 0; i1 < temp_accomplishment_all.size(); i1++)
		{
			auto temp_accomplishment_one = temp_accomplishment_all[i1];//单个素养
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("%s", temp_accomplishment_one.behavior.c_str());//事件
			ImGui::TableNextColumn();
			ImGui::Text("%s%.2f", temp_accomplishment_one.isIncrease ? "+" : "-", temp_accomplishment_one.scoure);//评分
			ImGui::TableNextColumn();
			ImGui::Text("%s", temp_accomplishment_one.belong.c_str());
			ImGui::TableNextColumn();
			ImGui::Text("%s", temp_accomplishment_one.accomplishment_operator.c_str());
		}
		ImGui::EndTable();
	}
}