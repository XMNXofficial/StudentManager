cmake_minimum_required (VERSION 3.8)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/externalLib/sqlite/include)

add_subdirectory(core)
add_subdirectory(data)
add_subdirectory(ui)
add_subdirectory(extern)