cmake_minimum_required (VERSION 3.8)

add_library(StudentManager_core
"data_base.cpp"
)

#链接sqlite
	target_include_directories(StudentManager_core PUBLIC ${CMAKE_SOURCE_DIR}/externalLib/sqlite/include)
	target_link_libraries(StudentManager_core PUBLIC sqlite)

#链接boost
	#添加BOOST库
		find_package(Boost)#备注:环境变量BOOST_ROOT
		# 如果 Boost 库已找到，则进行链接
		if (${Boost_FOUND})#搜索成功
			target_include_directories(StudentManager_core PUBLIC ${Boost_INCLUDE_DIRS})
			target_link_libraries(StudentManager_core ${Boost_LIBRARIES})
		else()
			message(FATAL_ERROR "Boost library not found")	# 如果 Boost 库未找到，则给出错误提示
		endif()
