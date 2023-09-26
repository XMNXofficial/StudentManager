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
	//ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
	//| ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
	//	| ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
	//	| ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
	//	| ImGuiTableFlags_SizingFixedFit
	if (ImGui::BeginTable("##Table_accomplishment_detail", 4, ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("事件", ImGuiTableColumnFlags_WidthStretch,100);
		ImGui::TableSetupColumn("评分", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableSetupColumn("条款", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableSetupColumn("录入用户", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableHeadersRow();


		auto temp_accomplishment_all = MainAPP.accomplishment;//所有素养
		static int selecte_accomplishment = 0;
		for (int i1 = 0; i1 < temp_accomplishment_all.size(); i1++)
		{
			auto temp_accomplishment_one = temp_accomplishment_all[i1];//单个素养
			ImGui::TableNextRow();
			ImGuiSelectableFlags selectable_flags = 1 ? ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap : ImGuiSelectableFlags_None;

			ImGui::TableSetColumnIndex(0);
			if (ImGui::Selectable(std::string("##" + temp_accomplishment_one.UUID).c_str(), selecte_accomplishment == i1 ? true : false, selectable_flags, ImVec2(0, 0)))
			{
				selecte_accomplishment = i1;
			}
			if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
			{
				selecte_accomplishment = i1;
				ImGui::Text("This a popup for \"%s\"!", temp_accomplishment_one.UUID.c_str());
				if (ImGui::Button("Close"))
					ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
			}

			ImGui::SameLine(0.0f);
			ImGui::Text("%s", temp_accomplishment_one.behavior.c_str());//事件

			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%s%.2f", temp_accomplishment_one.score >= 0 ? "+" : "-", temp_accomplishment_one.score);//评分


			ImGui::TableSetColumnIndex(2);

			ImGui::Text("%s", temp_accomplishment_one.belong.c_str());

			ImGui::TableSetColumnIndex(3);
			ImGui::Text("%s", temp_accomplishment_one.operator_login_ID.c_str());


		}
		ImGui::EndTable();
	}
}