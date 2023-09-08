cmake_minimum_required (VERSION 3.8)

add_library(StudentManager_core
"data_base.cpp"
)

#链接sqlite
	target_include_directories(StudentManager_core PUBLIC ${CMAKE_SOURCE_DIR}/externalLib/sqlite/include/)
	target_link_libraries(StudentManager_core PUBLIC sqlite)
