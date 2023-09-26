#include"ui/operate.hpp"
#include<imgui.h>
#include<imgui_internal.h>
#include"extern/extern.hpp"

void ui_operate()//扣分/加分面板
{
	if (ImGui::BeginTabBar("##TabBar_contral"))
	{
		if (ImGui::BeginTabItem("当前学生##TabItem_student_score"))
		{
			ImGui::BeginGroup();
			static float item_length = 350;
			if (select_student_list_index == -1)
			{
				ImGui::Text("当前选中学生:%s", "当前未选中!");
			}
			else
			{
				ImGui::Text("当前选中学生:%s-%s", MainAPP.students[select_student_list_index].student_name.c_str(), MainAPP.students[select_student_list_index].student_school_ID.c_str());
			}


			ImGui::Text("修改姓名:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##修改姓名:", buffer_input_name, 1024);
			ImGui::Text("修改班级:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##修改年级:", buffer_input_grade, 1024);
			ImGui::Text("修改学号:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##修改学号:", buffer_input_schoolID, 1024);
			ImGui::Text("修改专业:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##修改专业:", buffer_input_major, 1024);
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical | ImGuiSeparatorFlags_SpanAllColumns);
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("新增加减分项:");
			ImGui::Text("性质:");	ImGui::SameLine();	ImGui::RadioButton("加分##性质", &buffer_isIncreaseSource, 1);	ImGui::SameLine();	ImGui::RadioButton("扣分##性质", &buffer_isIncreaseSource, 0);



			ImGui::Text("条款:");	ImGui::SameLine();
			ImGui::SetNextItemWidth(item_length);
			if (ImGui::BeginCombo("##条款combo", school_rule.SchoolRule[select_rules_1].belong.c_str()))
			{
				for (int n = 0; n < school_rule.SchoolRule.size(); n++)
				{
					const bool is_selected = (select_rules_1 == n);
					if (ImGui::Selectable(school_rule.SchoolRule[n].belong.c_str(), is_selected))
					{
						if (select_rules_1 != n)//如果选中项目有改变,否则无需变化
						{
							select_rules_1 = n;//备注:当条款被点击后,需要重置详细信息选中
							select_rules_2 = 0;//重置详细信息选中
						}
					}
					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();//如果当前选项是被选中的那个,则设置焦点
					}
				}
				ImGui::EndCombo();
			}
			ImGui::Text("选择:");
			ImGui::SameLine();
			int temp_backup_buffer_isCustomThing = buffer_isCustomThing;
			if (ImGui::RadioButton("自定义", &buffer_isCustomThing, 1))
			{
				if (temp_backup_buffer_isCustomThing != buffer_isCustomThing)
				{
					buffer_reason[0] = 0;//重置input输入框缓冲区
				}
			}
			ImGui::SameLine();
			if (ImGui::RadioButton("系统内置", &buffer_isCustomThing, 0))
			{
				if (temp_backup_buffer_isCustomThing != buffer_isCustomThing)
				{
					select_rules_2 = 0;//重置详细信息选中
				}
			}

			if (buffer_isCustomThing == 1)
			{
				ImGui::Text("事件:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##事件原因", buffer_reason, 1024);
			}
			else if (buffer_isCustomThing == 0)
			{
				ImGui::Text("内置:");
				ImGui::SameLine();
				ImGui::SetNextItemWidth(item_length);
				if (ImGui::BeginCombo("##详细combo", school_rule.SchoolRule[select_rules_1].items[select_rules_2].thing.c_str()))
				{
					for (int n = 0; n < school_rule.SchoolRule[select_rules_1].items.size(); n++)
					{
						const bool is_selected = (select_rules_2 == n);
						if (ImGui::Selectable(school_rule.SchoolRule[select_rules_1].items[n].thing.c_str(), is_selected))
						{
							if (select_rules_2 != n)//如果选中项目有改变,否则无需变化
							{
								select_rules_2 = n;
							}
						}
						if (is_selected)
						{
							ImGui::SetItemDefaultFocus();//如果当前选项是被选中的那个,则设置焦点
						}
					}
					ImGui::EndCombo();
				}
			}
			ImGui::EndGroup();
			if (ImGui::Button("我已确认无误,添加记录", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
			{
				ImGui::OpenPopup("请再次确认!");
			}
			//pop弹出窗口
			{
				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

				if (ImGui::BeginPopupModal("请再次确认!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("以下是信息改动:");
					ImGui::Text("学生学号:%s", "202266667777");
					ImGui::Text("原姓名:%s", "夕木柠昔");
					ImGui::Text("新姓名:%s", "夕木柠昔");
					ImGui::Text("原班级:%s", "物流2003");
					ImGui::Text("新班级:%s", "物流2003");
					ImGui::Text("性质:%s", (buffer_isIncreaseSource == 1) ? "加分" : "扣分");
					ImGui::Text("根据条款:%s", school_rule.SchoolRule[select_rules_1].belong.c_str());
					ImGui::Text("%s事件:%s", (buffer_isIncreaseSource == 1) ? "加分" : "扣分", (buffer_isCustomThing == 1) ? buffer_reason : school_rule.SchoolRule[select_rules_1].items[select_rules_2].thing.c_str());
					if (ImGui::Button("我已再次确认信息无误,确定录入"))
					{
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}


			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("数据导出##TabItem_student_score"))
		{
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}
