cmake_minimum_required(VERSION 3.5)
project(malt)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../malt_cmake/")
set(CMAKE_CXX_STANDARD 14)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
endif()

include(Malt)

set(HEADER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/malt_basic")
set(HEADER_FILES
        ${HEADER_PATH}/basic_module.hpp
        ${HEADER_PATH}/input.hpp
        ${HEADER_PATH}/time.hpp
        ${HEADER_PATH}/components/transform.hpp
        ${HEADER_PATH}/components/fps_control.hpp
        )

set(SOURCE_FILES components/transform.cpp basic_module.cpp components/fps_control.cpp)
add_library(malt_basic SHARED ${SOURCE_FILES})

target_link_libraries(malt_basic PUBLIC malt_core)
malt_def_module(malt_basic)

malt_add_module(malt_basic malt_core)

target_compile_definitions(malt_basic PUBLIC GLM_ENABLE_EXPERIMENTAL=1)

malt_install(malt_basic ${HEADER_PATH})
