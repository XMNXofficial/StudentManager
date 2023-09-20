cmake_minimum_required (VERSION 3.8)

#创建lib
add_library(StudentManager_extern
"extern.cpp"
)

#经过实验,我居然发现不用包含目录也可以
#引用imgui文件夹
target_link_directories(StudentManager_extern PUBLIC ${CMAKE_SOURCE_DIR}/externalLib/hello_imgui/external/)

#链接imgui库
target_link_libraries(StudentManager_extern PUBLIC imgui)