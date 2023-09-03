cmake_minimum_required (VERSION 3.8)

#开启MSVC热重载
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#项目
project ("StudentManager")

#目标
add_executable (StudentManager "StudentManager.cpp" "StudentManager.h")

#开启C++20标准
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StudentManager PROPERTY CXX_STANDARD 20)
endif()

