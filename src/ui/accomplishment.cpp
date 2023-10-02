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
		ImGui::TableSetupColumn("事件", ImGuiTableColumnFlags_WidthStretch, 100);
		ImGui::TableSetupColumn("评分", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableSetupColumn("条款", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableSetupColumn("录入用户", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableHeadersRow();


		auto temp_accomplishment_all = MainAPP.accomplishment;//所有素养
		for (int i1 = 0; i1 < temp_accomplishment_all.size(); i1++)
		{
			auto temp_accomplishment_one = temp_accomplishment_all[i1];//单个素养
			ImGui::TableNextRow();
			ImGuiSelectableFlags selectable_flags = 1 ? ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap : ImGuiSelectableFlags_None;

			ImGui::TableSetColumnIndex(0);
			if (ImGui::Selectable(std::string("##" + temp_accomplishment_one.UUID).c_str(), select_accomplishment == i1 ? true : false, selectable_flags, ImVec2(0, 0)))
			{
				select_accomplishment = i1;//设置所选id
			}

			if (ImGui::BeginPopupContextItem())//跟着上面的selecttable,当右键的时候便会激活
			{
				ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(255, 0, 0, 240));//push窗口颜色

				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

				ImGui::Begin("请确认:##delete_accomplishment", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
				select_accomplishment = i1;//设置所选id
				//ImGui::Text("UUID:%s", temp_accomplishment_one.UUID.c_str());
				ImGui::Text("您真的要删除这个素养记录吗:");
				ImGui::Separator();
				ImGui::Text("学生信息:");
				ImGui::Text("学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
				ImGui::Text("学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
				ImGui::Separator();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 1.000f, 0.000f, 1.000f));
				ImGui::Text("性质:%s", MainAPP.accomplishment[select_accomplishment].score > 0.0f ? "加分" : "减分");
				ImGui::Text("分数:%s%.1f分",
					MainAPP.accomplishment[select_accomplishment].score > 0.0f ? "加" : "减",
					MainAPP.accomplishment[select_accomplishment].score > 0.0f ? MainAPP.accomplishment[select_accomplishment].score : MainAPP.accomplishment[select_accomplishment].score * -1.0
				);
				ImGui::Text("行为:%s", MainAPP.accomplishment[select_accomplishment].behavior.c_str());
				ImGui::PopStyleColor();
				if (ImGui::Button("取消选择次素养记录", ImVec2(-1, 0)))
				{
					ImGui::CloseCurrentPopup();

				}
				if (ImGui::Button("我已再次确认,确定删除当前素养记录"))
				{
					MainAPP.DataBase->Accomplishment_delete(
						MainAPP.students[select_student_list_index].student_school_ID,
						MainAPP.accomplishment[select_accomplishment].UUID
					);
					MainAPP.accomplishment = MainAPP.DataBase->Accomplishment_Get(MainAPP.students[select_student_list_index].student_school_ID);
					ImGui::CloseCurrentPopup();
				}

				ImGui::End();
				ImGui::PopStyleColor(1);
				ImGui::EndPopup();
			}

			ImGui::SameLine(0.0f);
			ImGui::Text("%s", temp_accomplishment_one.behavior.c_str());//事件

			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%.1f", temp_accomplishment_one.score);//评分


			ImGui::TableSetColumnIndex(2);

			ImGui::Text("%s", temp_accomplishment_one.belong.c_str());

			ImGui::TableSetColumnIndex(3);
			ImGui::Text("%s", temp_accomplishment_one.operator_login_ID.c_str());


		}
		ImGui::EndTable();
	}
}