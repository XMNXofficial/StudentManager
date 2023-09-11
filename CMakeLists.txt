cmake_minimum_required (VERSION 3.8)

#解决奇数个数中文在msvc上无法编译utf-8不带bom的代码文件
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#开启MSVC热重载
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#项目
project ("StudentManager")

#添加第三方模块
	#添加imgui
		add_subdirectory (externalLib/hello_imgui)
		list(APPEND CMAKE_MODULE_PATH ${HELLOIMGUI_CMAKE_PATH})
		include(hello_imgui_add_app)
	#添加sqlite
		add_subdirectory(externalLib/sqlite)
	#添加spdlog
		add_subdirectory(externalLib/spdlog)

#项目模块化
add_subdirectory(src)

#目标
hello_imgui_add_app (StudentManager "StudentManager.cpp" "StudentManager.hpp")

#自己的模块
	#项目头文件
		target_include_directories(StudentManager PUBLIC include)
	#项目模块
		target_link_libraries(StudentManager PUBLIC StudentManager_data)#data模块
		target_link_libraries(StudentManager PUBLIC StudentManager_ui)#ui模块
		target_link_libraries(StudentManager PUBLIC StudentManager_extern)#ui模块
		target_link_libraries(StudentManager PUBLIC StudentManager_core)#core模块(sqlite调用)

#调用模块
	#链接sqlite
		target_include_directories(StudentManager PUBLIC externalLib/sqlite/include)
		target_link_libraries(StudentManager PUBLIC sqlite)#sqlite模块
	#链接spdlog
		target_include_directories(StudentManager PUBLIC externalLib/spdlog/include)
		target_link_libraries(StudentManager PUBLIC spdlog)#spdlog模块

#开启C++20标准
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StudentManager PROPERTY CXX_STANDARD 20)
endif()

