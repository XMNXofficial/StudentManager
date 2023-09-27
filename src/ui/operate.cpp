#include"ui/operate.hpp"
#include<imgui.h>
#include<imgui_internal.h>
#include"extern/extern.hpp"

void ui_operate()//扣分/加分面板
{
	if (ImGui::BeginTabBar("##TabBar_contral"))
	{

		static float item_length = 350;
		if (ImGui::BeginTabItem("修改学生信息##TabItem_student_edit_student_information"))
		{
			ImGui::BeginGroup();
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
					if (select_student_list_index != -1)
					{

						ImGui::Text("以下是信息改动:");
						ImGui::Separator();

						//学号
						if (MainAPP.students[select_student_list_index].student_school_ID == buffer_input_schoolID)
						{
							//学号未被修改
							ImGui::Text("学号是否更改:");
							ImGui::SameLine();
							ImGui::Text("未更改");
							ImGui::Text("学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
						}
						else
						{
							//学号被修改
							ImGui::Text("学号是否更改:");
							ImGui::SameLine();
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
							ImGui::Text("已更改");
							ImGui::PopStyleColor(1);
							ImGui::Text("旧学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.818f, 0.306f, 1.000f, 0.784f));
							ImGui::Text("新学生学号:%s", buffer_input_schoolID);
							ImGui::PopStyleColor(1);
						}
						ImGui::Separator();


						//姓名
						if (MainAPP.students[select_student_list_index].student_name == buffer_input_name)
						{
							//姓名未被修改
							ImGui::Text("姓名是否更改:");
							ImGui::SameLine();
							ImGui::Text("未更改");
							ImGui::Text("学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
						}
						else
						{
							//姓名被更改
							ImGui::Text("姓名是否更改:");
							ImGui::SameLine();
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
							ImGui::Text("已更改");
							ImGui::PopStyleColor(1);
							ImGui::Text("旧学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.818f, 0.306f, 1.000f, 0.784f));
							ImGui::Text("新学生姓名:%s", buffer_input_name);
							ImGui::PopStyleColor(1);

						}
						ImGui::Separator();

						if (MainAPP.students[select_student_list_index].student_school_grade == buffer_input_grade)
						{
							//班级未被更改
							ImGui::Text("班级是否更改");
							ImGui::SameLine();
							ImGui::Text("未更改");
							ImGui::Text("学生班级:%s", MainAPP.students[select_student_list_index].student_school_grade.c_str());
						}
						else
						{
							//班级被更改
							ImGui::Text("班级是否更改:");
							ImGui::SameLine();
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
							ImGui::Text("已更改");
							ImGui::PopStyleColor(1);
							ImGui::Text("旧学生班级:%s", MainAPP.students[select_student_list_index].student_school_grade.c_str());
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.818f, 0.306f, 1.000f, 0.784f));
							ImGui::Text("新学生班级:%s", buffer_input_grade);
							ImGui::PopStyleColor(1);
						}
						ImGui::Separator();



						if (ImGui::Button("我已再次确认信息无误,确定录入"))
						{
							ImGui::CloseCurrentPopup();
						}
					}
					else
					{
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
						ImGui::Text("修改失败!当前未选择学生!");
						ImGui::PopStyleColor(1);
						if (ImGui::Button("我知道了"))
						{
							ImGui::CloseCurrentPopup();
						}
					}
					ImGui::EndPopup();
				}
			}


			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("添加/删除学生素养##TabItem_student_accomplishment_add_or_delete"))
		{
			if (select_student_list_index == -1)
			{
				ImGui::Text("当前选中学生:%s", "当前未选中!");
			}
			else
			{
				ImGui::Text("当前选中学生:%s-%s", MainAPP.students[select_student_list_index].student_name.c_str(), MainAPP.students[select_student_list_index].student_school_ID.c_str());
			}

			ImGui::Separator();

			ImGui::Text("性质:");
			//这里加减分项,需要强调处理,所以设置不同颜色
			if (buffer_isIncreaseSource)
			{
				//加分
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.151f, 1.000f, 0.000f, 1.000f));
				ImGui::Text("加分");
				ImGui::PopStyleColor(1);
			}
			else
			{
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
				ImGui::Text("减分");
				ImGui::PopStyleColor(1);
			}

			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.151f, 1.000f, 0.000f, 1.000f));
			if (ImGui::SmallButton("加分模式##button_accomplishment_increaseSource_yes"))
			{
				if (buffer_isIncreaseSource != true)
				{
					//如果已经是次选项,则不重置索引
					buffer_isIncreaseSource = true;
					select_accomplishment_customThing = 0;//重置默认索引
					if (buffer_isCustomThing)
					{
						buffer_accomplishment_increase_or_decrease_source = 0;//如果是自定义事件,则设为0
					}
					else
					{
						//如果是系统内置事件,则重置为第0个选项的最低分数
						//为什么要这样子?因为imgui的slider控件不会对缓冲区进行初始化,需要我们手动初始化呢
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_increase[select_accomplishment_customThing].minPoint;
					}
				}
			}
			ImGui::PopStyleColor(1);

			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
			if (ImGui::SmallButton("减分模式##button_accomplishment_increaseSource_no"))
			{
				if (buffer_isIncreaseSource != false)
				{
					//如果已经是次选项,则不重置索引
					buffer_isIncreaseSource = false;
					select_accomplishment_customThing = 0;//重置默认索引
					if (buffer_isCustomThing)
					{
						buffer_accomplishment_increase_or_decrease_source = 0;//如果是自定义事件,则设为0
					}
					else
					{
						//如果是系统内置事件,则重置为第0个选项的最低分数
						//为什么要这样子?因为imgui的slider控件不会对缓冲区进行初始化,需要我们手动初始化呢
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_decrease[select_accomplishment_customThing].minPoint;
					}
				}
			}
			ImGui::PopStyleColor(1);

			ImGui::Separator();

			ImGui::Text("事件:%s", buffer_isCustomThing ? "自定义事件" : "系统内置事件");
			ImGui::SameLine();
			if (ImGui::SmallButton("自定义事件"))
			{
				if (buffer_isCustomThing != true)
				{
					//如果已经是次选项,则不重置索引
					buffer_isCustomThing = true;
					select_accomplishment_customThing = 0;//重置默认索引
					//此时是自定义事件,分数直接设为0
					buffer_accomplishment_increase_or_decrease_source = 0;

				}
			}
			ImGui::SameLine();
			if (ImGui::SmallButton("系统内置事件"))
			{
				if (buffer_isCustomThing != false)
				{
					//如果已经是次选项,则不重置索引
					buffer_isCustomThing = false;
					select_accomplishment_customThing = 0;//重置默认索引

					//此时是系统内置事件,重置为第0个选项的最低分数
					//为什么要这样子?因为imgui的slider控件不会对缓冲区进行初始化,需要我们手动初始化呢
					if (buffer_isIncreaseSource)
					{
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_increase[select_accomplishment_customThing].minPoint;
					}
					else
					{
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_decrease[select_accomplishment_customThing].minPoint;
					}
				}
			}

			ImGui::AlignTextToFramePadding();
			ImGui::Text("原因:");
			if (buffer_isCustomThing)
			{
				//自定义事件
				ImGui::SameLine();
				ImGui::InputText("##inputText_accomplishment_reason", buffer_input_accomplishment_reason, 1024);
			}
			else
			{
				//使用系统内置事件
				if (buffer_isIncreaseSource)
				{
					//内置加分事件
					ImGui::SameLine();
					if (ImGui::BeginCombo("##combo_accomplishment_customthing加分事件", MainAPP.school_rule.rule_increase[select_accomplishment_customThing].thing.c_str()))
					{
						for (int i1 = 0; i1 < MainAPP.school_rule.rule_increase.size(); i1++)
						{
							const bool isSelected = select_accomplishment_customThing == i1;
							if (ImGui::Selectable(MainAPP.school_rule.rule_increase[i1].thing.c_str(), isSelected))
							{
								select_accomplishment_customThing = i1;
								buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_increase[select_accomplishment_customThing].minPoint;//重置分数缓冲区为,当前选中规则的最低分数
							}
							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();//如果当前选项是被选中的那个,则设置焦点
							}
						}
						ImGui::EndCombo();
					}
				}
				else
				{
					//内置扣分事件
					ImGui::SameLine();
					if (ImGui::BeginCombo("##combo_accomplishment_customthing减分事件", MainAPP.school_rule.rule_decrease[select_accomplishment_customThing].thing.c_str()))
					{
						for (int i1 = 0; i1 < MainAPP.school_rule.rule_decrease.size(); i1++)
						{
							const bool isSelected = select_accomplishment_customThing == i1;
							if (ImGui::Selectable(MainAPP.school_rule.rule_decrease[i1].thing.c_str(), isSelected))
							{
								select_accomplishment_customThing = i1;
								buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_decrease[select_accomplishment_customThing].minPoint;//重置分数缓冲区为,当前选中规则的最低分数
							}
							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();//如果当前选项是被选中的那个,则设置焦点
							}
						}
						ImGui::EndCombo();
					}
				}
			}

			//控制分数
			if (buffer_isIncreaseSource)
			{
				//加分
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.151f, 1.000f, 0.000f, 1.000f));
				ImGui::Text("加分:");
				ImGui::SameLine();
				if (buffer_isCustomThing)
				{
					//自定义事件
					ImGui::SliderFloat("##SlidetInt_accomplishment_increase", &buffer_accomplishment_increase_or_decrease_source, 0.0f, 25.0f, "当前:+%.1f分");

				}
				else
				{
					//系统内置事件
					auto temp = MainAPP.school_rule.rule_increase[select_accomplishment_customThing];
					if (temp.minPoint != temp.maxPoint)
					{
						ImGui::SliderFloat("##SlidetInt_accomplishment_increase", &buffer_accomplishment_increase_or_decrease_source, temp.minPoint, temp.maxPoint, "当前:%.1f分");
					}
					else
					{
						ImGui::Text("固定+%.1f分", temp.minPoint);
					}
				}
				ImGui::PopStyleColor(1);

			}
			else
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
				ImGui::Text("减分:");
				ImGui::SameLine();
				if (buffer_isCustomThing)
				{
					//自定义事件
					ImGui::SliderFloat("##SlidetInt_accomplishment_decrease", &buffer_accomplishment_increase_or_decrease_source, 0.0f, 25.0f, "当前:-%.1f分");
				}
				else
				{
					//系统内置事件
					auto temp = MainAPP.school_rule.rule_decrease[select_accomplishment_customThing];
					if (temp.minPoint != temp.maxPoint)
					{
						ImGui::SliderFloat("##SlidetInt_accomplishment_decrease", &buffer_accomplishment_increase_or_decrease_source, temp.minPoint, temp.maxPoint, "当前:-%.1f分");
					}
					else
					{
						ImGui::Text("固定-%.1f分", temp.minPoint);
					}
				}
				ImGui::PopStyleColor(1);

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
