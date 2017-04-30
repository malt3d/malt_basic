cmake_minimum_required(VERSION 3.5)
project(malt)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES components/transform.cpp components/transform.hpp basic_module.cpp basic_module.hpp input.hpp time.hpp)
add_library(malt_basic SHARED ${SOURCE_FILES})
add_executable(transform_test test/test_transform.cpp)

set_target_properties(malt_basic PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(malt_basic PUBLIC "../")
target_link_libraries(malt_basic malt_core)

target_link_libraries(transform_test malt_basic)

target_compile_definitions(malt_basic PUBLIC GLM_ENABLE_EXPERIMENTAL=1)