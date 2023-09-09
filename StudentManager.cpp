#include "StudentManager.hpp"
#include <imgui_internal.h>
#include <hello_imgui.h>
#include "ui/operate.hpp"//学生操作面板
#include "ui/student_list.hpp"//学生列表
#include "ui/accomplishment.hpp"//学生素养详细信息
ImFont* gFont = nullptr;

int main()
{
	HelloImGui::RunnerParams p;
	p.appWindowParams.windowTitle = "APP";
	p.appWindowParams.resizable = false; // 禁止更改大小
	p.appWindowParams.windowGeometry.size = { 800, 600 };
	p.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
	p.dockingParams = show_dockinggui();
	p.dockingParams.layoutCondition = HelloImGui::DockingLayoutCondition::ApplicationStart;

	p.callbacks.LoadAdditionalFonts = []()
	{
		ImFontGlyphRangesBuilder a;
		static ImVector<ImWchar>b;
		a.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseFull());
		a.BuildRanges(&b);
		gFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyhbd.ttc", 40.0f, nullptr, b.Data); };
	//p.imGuiWindowParams.tweakedTheme = { ImGuiTheme::ImGuiTheme_ImGuiColorsLight,ImGuiTheme::ImGuiThemeTweaks() };
	p.imGuiWindowParams.showMenuBar = true;
	p.imGuiWindowParams.showMenu_View = false;//不显示默认的view菜单
	p.imGuiWindowParams.showStatusBar = false;
	p.imGuiWindowParams.rememberStatusBarSettings = false;
	p.imGuiWindowParams.rememberTheme = false;
	p.imGuiWindowParams.Enable_MainDockSpace_NoResize = true;
	p.imGuiWindowParams.Enable_MainDockSpace_NoTabBar = true;
	HelloImGui::Run(p);
	
	return 0;
}

HelloImGui::DockingParams show_dockinggui()
{
	HelloImGui::DockingParams d;

	std::vector<HelloImGui::DockingSplit> s;

	//创建dock空间:dock_list 显示学生列表
	HelloImGui::DockingSplit dock_list;
	dock_list.initialDock = "MainDockSpace";
	dock_list.newDock = "dock_list";
	dock_list.direction = ImGuiDir_Right;
	dock_list.ratio = 0.3f;
	dock_list.nodeFlags = ImGuiDockNodeFlags_NoTabBar;
	s.push_back(dock_list);

	//创建dock空间:dock_accomplishment 显示单个学生素养信息
	HelloImGui::DockingSplit dock_accomplishment;
	dock_accomplishment.initialDock = "MainDockSpace";
	dock_accomplishment.newDock = "dock_accomplishment";
	dock_accomplishment.direction = ImGuiDir_Up;
	dock_accomplishment.ratio = 0.56f;
	dock_accomplishment.nodeFlags = ImGuiDockNodeFlags_NoTabBar;

	s.push_back(dock_accomplishment);
	d.dockingSplits = s;

	std::vector<HelloImGui::DockableWindow> w;


	//创建dock窗口:window_accomplishment 单个学生素养详细信息
	HelloImGui::DockableWindow window_accomplishment;
	window_accomplishment.label = "window_accomplishment";//设置窗口标题
	window_accomplishment.dockSpaceName = "dock_accomplishment";//把窗口放在dock空间中
	window_accomplishment.GuiFunction = [] { ui_accomplishment(); };//界面渲染

	//创建dock窗口:window_operate 学生操作面板
	HelloImGui::DockableWindow window_operate;
	window_operate.label = "window_operate";//设置窗口标题
	window_operate.dockSpaceName = "MainDockSpace";//把窗口放在dock空间中,这里放在主空间中
	window_operate.GuiFunction = []{ ui_operate(); };//界面渲染
	window_operate.imGuiWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;//设置窗口属性

	//创建dock窗口:window_list 学生列表
	HelloImGui::DockableWindow window_list;
	window_list.label = "window_list";//设置窗口标题
	window_list.dockSpaceName = "dock_list";//把窗口放在dock空间中
	window_list.GuiFunction = []{ ui_list(); };//界面渲染

	w.push_back(window_accomplishment);
	w.push_back(window_operate);
	w.push_back(window_list);

	d.dockableWindows = w;

	return d;
}
