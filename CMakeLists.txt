cmake_minimum_required(VERSION 3.21)
project(tglib LANGUAGES CXX)

# leave compiler options up to parent project, as these libs are header-only

# create header-only interface target for graphs.hpp
add_library(tglib_graphs INTERFACE)
add_library(${PROJECT_NAME}::graphs ALIAS tglib_graphs)
target_sources(tglib_graphs PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES graphs.hpp)

# create header-only interface target for tables.hpp
add_library(tglib_tables INTERFACE)
add_library(${PROJECT_NAME}::tables ALIAS tglib_tables)
target_sources(tglib_tables PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES tables.hpp)

# compile example binaries as executables
if (PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    add_executable(tglib_graphs_example "${CMAKE_CURRENT_SOURCE_DIR}/graphs.cpp")
    target_link_libraries(tglib_graphs_example PRIVATE tglib::graphs)
    add_executable(tglib_tables_example "${CMAKE_CURRENT_SOURCE_DIR}/tables.cpp")
    target_link_libraries(tglib_tables_example PRIVATE tglib::tables)
endif()