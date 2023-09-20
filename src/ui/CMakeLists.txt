cmake_minimum_required (VERSION 3.8)

#创建lib
add_library(StudentManager_ui
	"operate.cpp"
	"student_list.cpp"
	"accomplishment.cpp"
	"DevelopWindow.cpp"
)

#经过实验,我居然发现不用包含目录也可以
#引用imgui文件夹
target_link_directories(StudentManager_ui PUBLIC ${CMAKE_SOURCE_DIR}/externalLib/hello_imgui/external/)

#链接imgui库
target_link_libraries(StudentManager_ui PUBLIC imgui)


#链接boost
	#添加BOOST库
		find_package(Boost REQUIRED COMPONENTS locale)#备注:环境变量BOOST_ROOT
		# 如果 Boost 库已找到，则进行链接
		if (${Boost_FOUND})#搜索成功
			target_include_directories(StudentManager_ui PUBLIC ${Boost_INCLUDE_DIRS})
			target_link_libraries(StudentManager_ui PUBLIC ${Boost_LIBRARIES})
		else()
			message(FATAL_ERROR "Boost library not found")	# 如果 Boost 库未找到，则给出错误提示
		endif()
		