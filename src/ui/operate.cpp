#include"ui/operate.hpp"
#include<imgui.h>
#include<imgui_internal.h>
#include"extern/extern.hpp"

void ui_operate()//扣分/加分面板
{
	if (ImGui::BeginTabBar("##TabBar_contral"))
	{

		static float item_length = 350;

		if (ImGui::BeginTabItem("学生建档"))
		{
			ImGui::Text("添加学生信息:");

			ImGui::Text("学生姓名:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_新建学生姓名:", buffer_input_addStudent_name, 1024);
			ImGui::Text("年级班级:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_新建学生年级:", buffer_input_addStudent_grade, 1024);
			ImGui::Text("学生学号:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_新建学生学号:", buffer_input_addStudent_schoolID, 1024);
			ImGui::Text("学生专业:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_新建学生专业:", buffer_input_addStudent_major, 1024);
			if (ImGui::Button("我已确认无误,添加记录##button_AddStudent_我已确认无误,添加记录", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
			{
				ImGui::OpenPopup("请再次确认!##Popup_window_AddStudent_请再次确认!");
			}

			static bool isShowConfirmWindow = false;
			static bool isAddOK = false;

			//Popup弹出确认窗口
			{
				if (ImGui::BeginPopupModal("请再次确认!##Popup_window_AddStudent_请再次确认!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (buffer_input_addStudent_grade[0] != 0 &&
						buffer_input_addStudent_major[0] != 0 &&
						buffer_input_addStudent_name[0] != 0 &&
						buffer_input_addStudent_schoolID != 0
						)
					{
						//四个信息都输入了
						ImGui::Text("新建学生:");
						ImGui::Separator();

						//姓名
						ImGui::Text("学生姓名:");
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.000f, 0.750f, 1.000f, 1.000f));
						ImGui::Text("%s", buffer_input_addStudent_name);
						ImGui::PopStyleColor(1);

						//学号
						ImGui::Text("学生学号:");
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.000f, 0.750f, 1.000f, 1.000f));
						ImGui::Text("%s", buffer_input_addStudent_schoolID);
						ImGui::PopStyleColor(1);

						//年级
						ImGui::Text("学生姓名:");
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.000f, 0.750f, 1.000f, 1.000f));
						ImGui::Text("%s", buffer_input_addStudent_grade);
						ImGui::PopStyleColor(1);

						//专业
						ImGui::Text("学生专业:");
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.000f, 0.750f, 1.000f, 1.000f));
						ImGui::Text("%s", buffer_input_addStudent_major);
						ImGui::PopStyleColor(1);


						//确认按钮
						if (ImGui::Button("我已再次确认信息无误,确定录入。##button_AddStudent_confirm"))
						{
							//添加学生
							isAddOK = MainAPP.DataBase->Student_add(
								buffer_input_addStudent_name,
								buffer_input_addStudent_schoolID,
								buffer_input_addStudent_grade,
								buffer_input_addStudent_major
							);
							//弹出执行结果确认窗口
							isShowConfirmWindow = true;
							ImGui::CloseCurrentPopup();
						}

					}
					else
					{
						//有任意信息没有输入
						if (ImGui::Button("我知道了。##button_AddStudent_error"))
						{
							//无需弹出执行结果确认窗口
							isAddOK = false;
							isShowConfirmWindow = false;
							ImGui::CloseCurrentPopup();
						}
					}
					ImGui::EndPopup();
				}
			}

			if (isShowConfirmWindow)
			{
				ImGui::OpenPopup("执行结果:##Popup_window_AddStudent_result_执行结果:");
			}

			//Popup弹出结果窗口
			{
				if (ImGui::BeginPopupModal("执行结果:##Popup_window_AddStudent_result_执行结果:", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (isAddOK)
					{
						//执行成功
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.550f, 1.000f, 0.000f, 1.000f));
						ImGui::Text("执行成功!");
						ImGui::PopStyleColor();

						ImGui::Text("因为你改动了学生信息,系统将重新刷新学生列表。");
						ImGui::Text("如需对当前学生继续改动,请重新选择。");
						if (ImGui::Button("我知道了##Button_AddStudent_confirm_OK_我知道了"))
						{
							ImGui::CloseCurrentPopup();

							//数据有变动,重置学生列表,重新获取学生信息
							MainAPP.students = MainAPP.DataBase->Student_Get_Lists();
							select_student_list_index = -1;
							MainAPP.accomplishment = {};//重置素养列表
							buffer_input_addStudent_schoolID[0] = 0;
							buffer_input_addStudent_name[0] = 0;
							buffer_input_addStudent_major[0] = 0;
							buffer_input_addStudent_grade[0] = 0;

							isShowConfirmWindow = false;
							isAddOK = false;
						}
					}
					else
					{
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
						ImGui::Text("执行失败!");
						ImGui::PopStyleColor();

						ImGui::Text("原因:");
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 1.000f, 0.000f, 1.000f));
						if (MainAPP.DataBase->Get_ResultCode() == 19)
						{
							ImGui::Text("学生学号ID重复了!");
						}
						else
						{
							ImGui::Text("未知原因!错误号:%d", MainAPP.DataBase->Get_ResultCode());
						}
						ImGui::PopStyleColor();
						if (ImGui::Button("我知道了##Button_AddStudent_confirm_ERROR_我知道了"))
						{
							ImGui::CloseCurrentPopup();
							isShowConfirmWindow = false;
							isAddOK = false;
						}
					}

					ImGui::EndPopup();
				}
			}

			ImGui::EndTabItem();
		}

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


			ImGui::Text("修改姓名:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_修改学生姓名:", buffer_input_editStudent_name, 1024);
			ImGui::Text("年级班级:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_修改学生年级:", buffer_input_editStudent_grade, 1024);
			ImGui::Text("修改学号:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_修改学生学号:", buffer_input_editStudent_schoolID, 1024);
			ImGui::Text("修改专业:");	ImGui::SameLine();	ImGui::SetNextItemWidth(item_length);	ImGui::InputText("##input_修改学生专业:", buffer_input_editStudent_major, 1024);
			ImGui::EndGroup();

			ImGui::SameLine();
			ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical | ImGuiSeparatorFlags_SpanAllColumns);
			ImGui::SameLine();

			ImGui::BeginGroup();

			ImGui::EndGroup();

			//如果进入修改,为true;//需要显示结果
			//如果进入修改但是修改失败, 为true;//需要显示结果
			//如果未选中学生,为false;无需显示结果
			static bool isEditing = false;

			//修改成功:true
			//修改失败:false
			static bool isEditOK = false;

			static bool isEditOK_for_resultShow = false;//这个用于备份,因为openpopup只能执行一次,不能放在主循环里,因此判断isEditOK后执行openpopup必须只能执行一次,执行完之后重置isEditOK.而被openpopup的弹窗,是在重置之后才执行,因此需要一个备份

			if (ImGui::Button("我已确认无误,添加记录##button_EditStudent_我已确认无误,添加记录!", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
			{
				ImGui::OpenPopup("请再次确认!##Popup_window_EditStudent_请再次确认!");
			}
			//pop弹出窗口
			{
				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

				//这里备注一份关于popup的个人心得,
				//open是打开,close是关闭,end是暂时结束(close之后,begin返回false.而end之后,begin返回true)
				if (ImGui::BeginPopupModal("请再次确认!##Popup_window_EditStudent_请再次确认!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (select_student_list_index != -1)
					{

						ImGui::Text("以下是信息改动:");
						ImGui::Separator();

						//学号
						if (MainAPP.students[select_student_list_index].student_school_ID == buffer_input_editStudent_schoolID)
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
							ImGui::Text("新学生学号:%s", buffer_input_editStudent_schoolID);
							ImGui::PopStyleColor(1);
						}
						ImGui::Separator();


						//姓名
						if (MainAPP.students[select_student_list_index].student_name == buffer_input_editStudent_name)
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
							ImGui::Text("新学生姓名:%s", buffer_input_editStudent_name);
							ImGui::PopStyleColor(1);

						}
						ImGui::Separator();

						if (MainAPP.students[select_student_list_index].student_school_grade == buffer_input_editStudent_grade)
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
							ImGui::Text("新学生班级:%s", buffer_input_editStudent_grade);
							ImGui::PopStyleColor(1);
						}
						ImGui::Separator();

						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
						if (ImGui::Button("糟糕！我写错了，取消更改。", ImVec2(-1, 0)))
						{
							ImGui::CloseCurrentPopup();
						}
						ImGui::PopStyleColor(1);

						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.367f, 1.000f, 0.000f, 0.784f));
						if (ImGui::Button("我已再次确认信息无误,确定录入。"))
						{
							ImGui::CloseCurrentPopup();
							//为什么要把这两个状态放在这里?因为openpopup并不是直接执行这一部分的代码.
							//可以理解为openpopup是异步的
							isEditOK = MainAPP.DataBase->Student_edit(
								MainAPP.students[select_student_list_index].student_school_ID,
								buffer_input_editStudent_name,
								buffer_input_editStudent_schoolID,
								buffer_input_editStudent_grade,
								buffer_input_editStudent_major
							);
							isEditing = true;
						}
						ImGui::PopStyleColor(1);
					}
					else
					{
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
						ImGui::Text("修改失败!当前未选择学生!");
						ImGui::PopStyleColor(1);
						if (ImGui::Button("我知道了"))
						{
							isEditing = false;
							ImGui::CloseCurrentPopup();
						}
					}
					ImGui::EndPopup();
				}
			}

			if (isEditing)
			{
				ImGui::OpenPopup("录入结果:");
				isEditing = false;
				isEditOK_for_resultShow = isEditOK;
				isEditOK = false;
			}

			//pop弹出窗口,显示结果	
			{
				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));//居中显示

				if (ImGui::BeginPopupModal("录入结果:", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (isEditOK_for_resultShow)
					{
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.151f, 1.000f, 0.000f, 1.000f));
						ImGui::Text("成功");
						ImGui::PopStyleColor(1);
					}
					else
					{
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
						ImGui::Text("失败");
						ImGui::PopStyleColor(1);
					}
					ImGui::Text("因为你改动了学生信息,系统将重新刷新学生列表。");
					ImGui::Text("如需对当前学生继续改动,请重新选择。");
					if (ImGui::Button("我知道了"))
					{
						isEditOK_for_resultShow = false;

						//数据有变动,重置学生列表,重新获取学生信息
						MainAPP.students = MainAPP.DataBase->Student_Get_Lists();
						select_student_list_index = -1;
						MainAPP.accomplishment = {};//重置素养列表
						buffer_input_editStudent_schoolID[0] = 0;
						buffer_input_editStudent_name[0] = 0;
						buffer_input_editStudent_major[0] = 0;
						buffer_input_editStudent_grade[0] = 0;

						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("添加学生素养##TabItem_student_accomplishment_add_or_delete"))
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
			if (ImGui::SmallButton("加分模式##button_AddAccomplishment_increaseSource_yes"))
			{
				if (buffer_isIncreaseSource != true)
				{
					//如果已经是次选项,则不重置索引
					buffer_isIncreaseSource = true;
					select_rule_list_index = 0;//重置默认索引
					if (buffer_isCustomThing)
					{
						buffer_accomplishment_increase_or_decrease_source = 0;//如果是自定义事件,则设为0
					}
					else
					{
						//如果是系统内置事件,则重置为第0个选项的最低分数
						//为什么要这样子?因为imgui的slider控件不会对缓冲区进行初始化,需要我们手动初始化呢
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_increase[select_rule_list_index].minPoint;
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
					select_rule_list_index = 0;//重置默认索引
					if (buffer_isCustomThing)
					{
						buffer_accomplishment_increase_or_decrease_source = 0;//如果是自定义事件,则设为0
					}
					else
					{
						//如果是系统内置事件,则重置为第0个选项的最低分数
						//为什么要这样子?因为imgui的slider控件不会对缓冲区进行初始化,需要我们手动初始化呢
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_decrease[select_rule_list_index].minPoint;
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
					select_rule_list_index = 0;//重置默认索引
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
					select_rule_list_index = 0;//重置默认索引

					//此时是系统内置事件,重置为第0个选项的最低分数
					//为什么要这样子?因为imgui的slider控件不会对缓冲区进行初始化,需要我们手动初始化呢
					if (buffer_isIncreaseSource)
					{
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_increase[select_rule_list_index].minPoint;
					}
					else
					{
						buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_decrease[select_rule_list_index].minPoint;
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
					if (ImGui::BeginCombo("##combo_accomplishment_customthing加分事件", MainAPP.school_rule.rule_increase[select_rule_list_index].thing.c_str()))
					{
						for (int i1 = 0; i1 < MainAPP.school_rule.rule_increase.size(); i1++)
						{
							const bool isSelected = select_rule_list_index == i1;
							if (ImGui::Selectable(MainAPP.school_rule.rule_increase[i1].thing.c_str(), isSelected))
							{
								select_rule_list_index = i1;
								buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_increase[select_rule_list_index].minPoint;//重置分数缓冲区为,当前选中规则的最低分数
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
					if (ImGui::BeginCombo("##combo_accomplishment_customthing减分事件", MainAPP.school_rule.rule_decrease[select_rule_list_index].thing.c_str()))
					{
						for (int i1 = 0; i1 < MainAPP.school_rule.rule_decrease.size(); i1++)
						{
							const bool isSelected = select_rule_list_index == i1;
							if (ImGui::Selectable(MainAPP.school_rule.rule_decrease[i1].thing.c_str(), isSelected))
							{
								select_rule_list_index = i1;
								buffer_accomplishment_increase_or_decrease_source = MainAPP.school_rule.rule_decrease[select_rule_list_index].minPoint;//重置分数缓冲区为,当前选中规则的最低分数
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
					auto temp = MainAPP.school_rule.rule_increase[select_rule_list_index];
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
					auto temp = MainAPP.school_rule.rule_decrease[select_rule_list_index];
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

			if (ImGui::Button("我已确认无误,添加记录##button_accomplishment_add", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
			{
				ImGui::OpenPopup("请再次确认!##accomplishment");
			}
			//pop弹出窗口
			{
				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
				if (ImGui::BeginPopupModal("请再次确认!##accomplishment", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (select_student_list_index != -1 && buffer_accomplishment_increase_or_decrease_source != 0.0f)//如果index是-1或分数为0,则不能 添加学生,这里的异常会在else分支里处理
					{

						if (buffer_isCustomThing == true && buffer_input_accomplishment_reason[0] == 0)
						{
							//如果是自定义事件,而且忘记填写原因
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
							ImGui::Text("修改失败!您还未填写原因!");
							ImGui::PopStyleColor(1);
							if (ImGui::Button("我知道了"))
							{
								ImGui::CloseCurrentPopup();
							}
						}
						else
						{

							ImGui::Text("以下是信息改动:");
							ImGui::Separator();
							ImGui::Text("学生信息:");
							ImGui::Text("学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
							ImGui::Text("学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
							ImGui::Separator();
							ImGui::Text("素养信息添加:");
							if (buffer_isIncreaseSource)
							{
								//加分
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.151f, 1.000f, 0.000f, 1.000f));
								ImGui::Text("性质:加分");
								ImGui::PopStyleColor(1);
							}
							else
							{
								//扣分				
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
								ImGui::Text("性质:减分");
								ImGui::PopStyleColor(1);
							}

							ImGui::Text("行为:");
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.930f, 0.000f, 1.000f));//yellow
							ImGui::SameLine();
							ImGui::Text("%s", buffer_isCustomThing ? buffer_input_accomplishment_reason : (buffer_isIncreaseSource ? MainAPP.school_rule.rule_increase[select_rule_list_index].thing.c_str() : MainAPP.school_rule.rule_decrease[select_rule_list_index].thing.c_str()));
							ImGui::PopStyleColor();

							ImGui::Text("分数:");
							if (buffer_isIncreaseSource)
							{
								//加分
								ImGui::SameLine();
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.151f, 1.000f, 0.000f, 1.000f));
								ImGui::Text("加 %.1f 分", buffer_accomplishment_increase_or_decrease_source);
								ImGui::PopStyleColor(1);
							}
							else
							{
								//扣分
								ImGui::SameLine();
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 1.000f));
								ImGui::Text("扣 %.1f 分", buffer_accomplishment_increase_or_decrease_source);
								ImGui::PopStyleColor(1);
							}


							if (ImGui::Button("我已再次确认信息无误,确定录入"))
							{
								MainAPP.DataBase->Accomplishment_add(
									MainAPP.students[select_student_list_index].student_school_ID,//ID
									buffer_isCustomThing ? (buffer_input_accomplishment_reason) : (buffer_isIncreaseSource ? (MainAPP.school_rule.rule_increase[select_rule_list_index].thing) : (MainAPP.school_rule.rule_decrease[select_rule_list_index].thing)),//行为
									buffer_isIncreaseSource ? "加分" : "减分",//条款
									(buffer_isIncreaseSource ? 1.0 : -1.0) * buffer_accomplishment_increase_or_decrease_source//分数
								);
								MainAPP.accomplishment = MainAPP.DataBase->Accomplishment_Get(MainAPP.students[select_student_list_index].student_school_ID);
								ImGui::CloseCurrentPopup();
							}
						}
					}
					else
					{
						if (select_student_list_index == -1)
						{
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
							ImGui::Text("修改失败!当前未选择学生!");
							ImGui::PopStyleColor(1);
						}
						else if (buffer_accomplishment_increase_or_decrease_source == 0.0f)
						{
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 0.000f, 0.000f, 0.784f));
							ImGui::Text("修改失败!分数不能为0!");
							ImGui::PopStyleColor(1);
						}
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

		if (ImGui::BeginTabItem("数据导出##TabItem_student_score"))
		{
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}
