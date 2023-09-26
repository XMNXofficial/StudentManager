#include  "ui/student_list.hpp"
#include<imgui.h>
#include<imgui_internal.h>
#include"extern/extern.hpp"
#include"boost/uuid/uuid.hpp"
#include"boost/uuid/uuid_generators.hpp"
#include"boost/uuid/uuid_io.hpp"


void show_gui1()//学生扣分明细
{
}

void ui_list()//学生列表
{

	ImGui::Text("查询:");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(220);
	ImGui::InputText("##InputText_查询学生:", buffer_StudentSelect, 1024);
	if (ImGui::IsItemEdited())
	{
		std::string search = buffer_StudentSelect;
		MainAPP.students = MainAPP.DataBase->Student_Get_Lists(search, search, false);
	}
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
		if (MainAPP.DataBase != nullptr)
		{
			if (MainAPP.DataBase->isInitOK())
			{

				for (int i1 = 0; i1 < MainAPP.students.size(); i1++)
				{
					auto& student = MainAPP.students[i1];
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					std::string temp(student.student_name + "-" + student.student_school_ID);
					if (ImGui::Selectable(temp.c_str(), i1 == select_student_list_index ? true : false))
					{
						select_student_list_index = i1;
						if (select_student_list_index != -1)
						{
							MainAPP.accomplishment = MainAPP.DataBase->Accomplishment_Get(MainAPP.students[select_student_list_index].student_school_ID);
							strcpy(buffer_input_name, MainAPP.students[i1].student_name.c_str());
							strcpy(buffer_input_grade, MainAPP.students[i1].student_school_grade.c_str());
							strcpy(buffer_input_schoolID, MainAPP.students[i1].student_school_ID.c_str());
							strcpy(buffer_input_major, MainAPP.students[i1].student_school_major.c_str());
						}

					}

				}
			}
		}
		ImGui::EndTable();
	}
}

