cmake_minimum_required (VERSION 3.8)

#创建lib
add_library(StudentManager_ui
	"operate.cpp"
	"student_list.cpp"
	"accomplishment.cpp"
	"DevelopWindow.cpp"
)

#引用imgui文件夹
target_link_directories(StudentManager_ui PUBLIC ${CMAKE_SOURCE_DIR}/externalLib/hello_imgui/external/)

#链接imgui库
target_link_libraries(StudentManager_ui PUBLIC imgui)