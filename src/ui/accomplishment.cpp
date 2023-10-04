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
		ImGui::Text("当前选中学生:%s-%s\t(右键可以编辑/删除!)", MainAPP.students[select_student_list_index].student_name.c_str(), MainAPP.students[select_student_list_index].student_school_ID.c_str());
	}
	//ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
	//| ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
	//	| ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
	//	| ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
	//	| ImGuiTableFlags_SizingFixedFit
	if (ImGui::BeginTable("##Table_accomplishment_detail", 4, ImGuiTableFlags_Resizable))
	{
		ImGui::TableSetupColumn("事件", ImGuiTableColumnFlags_WidthStretch, 150);
		ImGui::TableSetupColumn("评分", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableSetupColumn("条款", ImGuiTableColumnFlags_WidthStretch, 50);
		//ImGui::TableSetupColumn("录入用户", ImGuiTableColumnFlags_WidthStretch, 50);
		ImGui::TableHeadersRow();


		auto temp_accomplishment_all = MainAPP.accomplishment;//所有素养
		static bool isShowEditWindow = false;
		static bool isShowDeleteWindow = false;

		for (int i1 = 0; i1 < temp_accomplishment_all.size(); i1++)
		{
			auto temp_accomplishment_one = temp_accomplishment_all[i1];//单个素养
			ImGui::TableNextRow();
			ImGuiSelectableFlags selectable_flags = 1 ? ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap : ImGuiSelectableFlags_None;

			ImGui::TableSetColumnIndex(0);
			if (ImGui::Selectable(std::string("##" + temp_accomplishment_one.UUID).c_str(), select_accomplishment_list_index == i1 ? true : false, selectable_flags, ImVec2(0, 0)))
			{
				select_accomplishment_list_index = i1;//设置所选id
			}
			if (ImGui::BeginPopupContextItem(0, 1))
			{
				select_accomplishment_list_index = i1;//设置所选id
				if (ImGui::MenuItem("修改素养信息##MenuItem_accomplishment_list_edit_修改素养信息"))
				{
					//在contextitem中,不能显示popup modal,因此这里使用bool申请显示,在外部进行处理(循环外部)
					isShowEditWindow = true;
				}

				if (ImGui::MenuItem("删除素养信息##MenuItem_accomplishment_list_delete_删除素养信息"))
				{
					//在contextitem中,不能显示popup modal,因此这里使用bool申请显示,在外部进行处理(循环外部)
					isShowDeleteWindow = true;
				}
				ImGui::EndPopup();
			}

			ImGui::SameLine(0.0f);
			ImGui::Text("%s", temp_accomplishment_one.behavior.c_str());//事件

			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%.1f", temp_accomplishment_one.score);//评分


			ImGui::TableSetColumnIndex(2);
			ImGui::PushStyleColor(
				ImGuiCol_Text,
				(temp_accomplishment_one.score > 0) ?
				(ImVec4(0.151f, 1.000f, 0.000f, 1.000f)) :
				(ImVec4(1.000f, 0.000f, 0.000f, 1.000f))
			);//加分:绿色,扣分:红色
			ImGui::Text("%s", temp_accomplishment_one.belong.c_str());
			ImGui::PopStyleColor(1);

			//ImGui::TableSetColumnIndex(3);
			//ImGui::Text("%s", temp_accomplishment_one.operator_login_ID.c_str());

		}

		//在循环外面处理弹窗
		//为什么呢:因为popup context item内部,不能popup modal.
		if (isShowEditWindow)
		{
			//重置缓冲区为与当前选中的素养信息一样,这样子方便用户修改
			strcpy(buffer_input_editAccomplishment_newBehavior, MainAPP.accomplishment[select_accomplishment_list_index].behavior.c_str());
			strcpy(buffer_input_editAccomplishment_newBelong, MainAPP.accomplishment[select_accomplishment_list_index].belong.c_str());
			buffer_input_editAccomplishment_newScore = MainAPP.accomplishment[select_accomplishment_list_index].score;
			buffer_select_editAccomplishment_newIsIncrease = MainAPP.accomplishment[select_accomplishment_list_index].score > 0;//大于0真,小于等于0假
			ImGui::OpenPopup("修改素养信息##Popup_window_修改素养信息");
			isShowEditWindow = false;
		}
		if (isShowDeleteWindow)
		{
			ImGui::OpenPopup("删除素养信息##Popup_window_删除素养信息");
			isShowDeleteWindow = false;
		}
		//弹出Popup修改素养信息窗口
		{
			if (ImGui::BeginPopupModal("修改素养信息##Popup_window_修改素养信息", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				//ImGui::Text("UUID:%s", temp_accomplishment_one.UUID.c_str());
				ImGui::Text("您正在编辑素养信息:");
				ImGui::Separator();
				ImGui::Text("学生信息:");
				ImGui::Text("学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
				ImGui::Text("学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
				ImGui::Separator();


				//显示性质
				ImGui::Text("性质:");
				//显示旧的性质
				ImGui::Text("旧的:");
				ImGui::SameLine();
				ImGui::PushStyleColor(
					ImGuiCol_Text,
					(MainAPP.accomplishment[select_accomplishment_list_index].score > 0) ?
					(ImVec4(0.151f, 1.000f, 0.000f, 1.000f)) :
					(ImVec4(1.000f, 0.000f, 0.000f, 1.000f))
				);//加分:绿色,减分:红色
				ImGui::Text("%s", (MainAPP.accomplishment[select_accomplishment_list_index].score > 0) ? ("加分") : ("减分"));
				ImGui::PopStyleColor(1);
				//显示新的性质
				ImGui::Text("新的:");
				ImGui::SameLine();
				ImGui::PushStyleColor(
					ImGuiCol_Text,
					(buffer_select_editAccomplishment_newIsIncrease) ?
					(ImVec4(0.151f, 1.000f, 0.000f, 1.000f)) :
					(ImVec4(1.000f, 0.000f, 0.000f, 1.000f))
				);//加分:绿色,减分:红色
				ImGui::Text("%s", (buffer_select_editAccomplishment_newIsIncrease) ? ("加分") : ("减分"));
				ImGui::PopStyleColor(1);
				//性质控制
				ImGui::SameLine();
				if (ImGui::SmallButton("加分模式##button_EditAccomplishment_increaseSource"))
				{
					buffer_select_editAccomplishment_newIsIncrease = true;
				}
				ImGui::SameLine();
				if (ImGui::SmallButton("扣分模式##button_EditAccomplishment_decreaseSource"))
				{
					buffer_select_editAccomplishment_newIsIncrease = false;
				}
				ImGui::Separator();


				//显示事件
				ImGui::Text("事件:");
				//旧的
				ImGui::Text("旧的:");
				ImGui::SameLine();
				ImGui::Text("%s", MainAPP.accomplishment[select_accomplishment_list_index].behavior.c_str());
				//新的
				ImGui::Text("新的:");
				ImGui::SameLine();
				ImGui::SetNextItemWidth(400);
				ImGui::InputText("##inputText_EditAccomplishment_newBehavior", buffer_input_editAccomplishment_newBehavior, sizeof(buffer_input_editAccomplishment_newBehavior));
				ImGui::Separator();

				//控制分数
				ImGui::Text("分数:");
				//旧的
				ImGui::Text("旧的:");
				ImGui::SameLine();
				ImGui::PushStyleColor(
					ImGuiCol_Text,
					(MainAPP.accomplishment[select_accomplishment_list_index].score > 0) ?
					(ImVec4(0.151f, 1.000f, 0.000f, 1.000f)) :
					(ImVec4(1.000f, 0.000f, 0.000f, 1.000f))
				);//加分:绿色,扣分:红色
				ImGui::Text(
					"%s%.1f分",
					(MainAPP.accomplishment[select_accomplishment_list_index].score > 0) ? ("加") : ("减"),//显示字符:加/减
					(buffer_isIncreaseSource ? 1.0 : -1.0) * MainAPP.accomplishment[select_accomplishment_list_index].score//取分数绝对值
				);
				ImGui::PopStyleColor();
				//新的
				ImGui::Text("新的");
				ImGui::SameLine();
				ImGui::PushStyleColor(
					ImGuiCol_Text,
					(buffer_select_editAccomplishment_newIsIncrease) ?
					(ImVec4(0.151f, 1.000f, 0.000f, 1.000f)) :
					(ImVec4(1.000f, 0.000f, 0.000f, 1.000f))
				);//加分:绿色,扣分:红色
				ImGui::SetNextItemWidth(400);
				ImGui::SliderFloat(
					"##SlidetFloat_EditAccomplishment_increase_or_decrease",
					&buffer_input_editAccomplishment_newScore,
					0.0f, 25.0f,
					(buffer_select_editAccomplishment_newIsIncrease) ? ("当前:+%.1f分") : ("当前:-%.1f分")
				);

				ImGui::PopStyleColor(1);

				if (ImGui::Button("取消选择次素养记录", ImVec2(-1, 0)))
				{
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("我已再次确认,修改当前素养记录", ImVec2(-1, 0)))
				{
					MainAPP.DataBase->Accomplishment_edit(
						MainAPP.accomplishment[select_accomplishment_list_index].UUID,
						buffer_input_editAccomplishment_newBehavior,
						(buffer_select_editAccomplishment_newIsIncrease) ? ("加分") : ("减分"),
						(buffer_select_editAccomplishment_newIsIncrease ? 1.0 : -1.0) * buffer_input_editAccomplishment_newScore
					);
					MainAPP.accomplishment = MainAPP.DataBase->Accomplishment_Get(MainAPP.students[select_student_list_index].student_school_ID);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		//弹出Popup修改素养信息窗口
		{
			if (ImGui::BeginPopupModal("删除素养信息##Popup_window_删除素养信息", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				//ImGui::Text("UUID:%s", temp_accomplishment_one.UUID.c_str());
				ImGui::Text("您真的要删除这个素养记录吗:");
				ImGui::Separator();
				ImGui::Text("学生信息:");
				ImGui::Text("学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
				ImGui::Text("学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
				ImGui::Separator();
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 1.000f, 0.000f, 1.000f));
				ImGui::Text("性质:%s", MainAPP.accomplishment[select_accomplishment_list_index].score > 0.0f ? "加分" : "减分");
				ImGui::Text("分数:%s%.1f分",
					MainAPP.accomplishment[select_accomplishment_list_index].score > 0.0f ? "加" : "减",
					MainAPP.accomplishment[select_accomplishment_list_index].score > 0.0f ? MainAPP.accomplishment[select_accomplishment_list_index].score : MainAPP.accomplishment[select_accomplishment_list_index].score * -1.0
				);
				ImGui::Text("行为:%s", MainAPP.accomplishment[select_accomplishment_list_index].behavior.c_str());
				ImGui::PopStyleColor();
				if (ImGui::Button("取消选择次素养记录", ImVec2(-1, 0)))
				{
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("我已再次确认,确定删除当前素养记录"))
				{
					MainAPP.DataBase->Accomplishment_delete(
						MainAPP.students[select_student_list_index].student_school_ID,
						MainAPP.accomplishment[select_accomplishment_list_index].UUID
					);
					MainAPP.accomplishment = MainAPP.DataBase->Accomplishment_Get(MainAPP.students[select_student_list_index].student_school_ID);
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		ImGui::EndTable();
	}
}


//if (0/*ImGui::BeginPopupContextItem()*/)//跟着上面的selecttable,当右键的时候便会激活
//{
//	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(255, 0, 0, 240));//push窗口颜色
//
//	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
//	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
//
//	ImGui::Begin("请确认:##delete_accomplishment", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
//	select_accomplishment_list_index = i1;//设置所选id
//	//ImGui::Text("UUID:%s", temp_accomplishment_one.UUID.c_str());
//	ImGui::Text("您真的要删除这个素养记录吗:");
//	ImGui::Separator();
//	ImGui::Text("学生信息:");
//	ImGui::Text("学生姓名:%s", MainAPP.students[select_student_list_index].student_name.c_str());
//	ImGui::Text("学生学号:%s", MainAPP.students[select_student_list_index].student_school_ID.c_str());
//	ImGui::Separator();
//	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.000f, 1.000f, 0.000f, 1.000f));
//	ImGui::Text("性质:%s", MainAPP.accomplishment[select_accomplishment_list_index].score > 0.0f ? "加分" : "减分");
//	ImGui::Text("分数:%s%.1f分",
//		MainAPP.accomplishment[select_accomplishment_list_index].score > 0.0f ? "加" : "减",
//		MainAPP.accomplishment[select_accomplishment_list_index].score > 0.0f ? MainAPP.accomplishment[select_accomplishment_list_index].score : MainAPP.accomplishment[select_accomplishment_list_index].score * -1.0
//	);
//	ImGui::Text("行为:%s", MainAPP.accomplishment[select_accomplishment_list_index].behavior.c_str());
//	ImGui::PopStyleColor();
//	if (ImGui::Button("取消选择次素养记录", ImVec2(-1, 0)))
//	{
//		ImGui::CloseCurrentPopup();
//
//	}
//	if (ImGui::Button("我已再次确认,确定删除当前素养记录"))
//	{
//		MainAPP.DataBase->Accomplishment_delete(
//			MainAPP.students[select_student_list_index].student_school_ID,
//			MainAPP.accomplishment[select_accomplishment_list_index].UUID
//		);
//		MainAPP.accomplishment = MainAPP.DataBase->Accomplishment_Get(MainAPP.students[select_student_list_index].student_school_ID);
//		ImGui::CloseCurrentPopup();
//	}
//
//	ImGui::End();
//	ImGui::PopStyleColor(1);
//	ImGui::EndPopup();
//}
