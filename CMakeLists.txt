cmake_minimum_required(VERSION 3.5)
project(malt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES components/transform.cpp components/transform.hpp basic_module.cpp basic_module.hpp)
add_library(malt_basic SHARED ${SOURCE_FILES})

set_target_properties(malt_basic PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(malt_basic PUBLIC "../")
target_link_libraries(malt_basic malt_core)