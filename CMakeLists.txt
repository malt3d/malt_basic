cmake_minimum_required(VERSION 3.2)
project(malt)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../malt_cmake/")
set(CMAKE_CXX_STANDARD 14)

find_package(GLM REQUIRED)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

include(Malt)

set(HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/malt_basic")
set(HEADER_FILES
        ${HEADER_PATH}/basic_module.hpp
        ${HEADER_PATH}/input.hpp
        ${HEADER_PATH}/components/transform.hpp
        ${HEADER_PATH}/components/fps_control.hpp
        ${HEADER_PATH}/components/rotate_comp.hpp
        )

set(SOURCE_FILES components/transform.cpp basic_module.cpp components/fps_control.cpp components/rotate_comp.cpp)
add_library(malt_basic ${MALT_LIB_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

malt_def_module(malt_basic)

malt_add_module(malt_basic malt_core)

target_compile_definitions(malt_basic PUBLIC GLM_ENABLE_EXPERIMENTAL=1)
target_include_directories(malt_basic PUBLIC ${GLM_INCLUDE_DIRS})

malt_install(malt_basic ${HEADER_PATH})

add_executable(tests test/test_transform.cpp)
target_link_libraries(tests PUBLIC malt_basic)

enable_testing()
add_test(NAME malt_basic_tests COMMAND tests)