#include<imgui.h>
#include"extern/extern.hpp"
#include"ui/DevelopWindow.hpp"
#include"core/data_base.hpp"
DevelopWindow::DevelopWindow()
{

}

DevelopWindow::~DevelopWindow()
{

}

void DevelopWindow::gui()
{
	ImGui::SetNextWindowSize({ 400,300 });
	ImGui::Begin("DevelopWindow");
	ImGui::Text("数据库状态:%s", DataBase.isInitOK() ? "初始化成功!" : "初始化失败.");
	if (ImGui::Button("断开数据库"))
	{
		DataBase.~data_base();
	}
	if (ImGui::Button("重连数据库"))
	{
		DataBase = data_base();
	}
	ImGui::End();
}