cmake_minimum_required(VERSION 3.19)
project(tglib LANGUAGES CXX)

add_library(tglib_graphs INTERFACE)
add_library(${PROJECT_NAME}::graphs ALIAS tglib_graphs)
target_sources(tglib_graphs PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES graphs.hpp)

add_library(tglib_tables INTERFACE)
add_library(${PROJECT_NAME}::tables ALIAS tglib_tables)
target_sources(tglib_tables PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES tables.hpp)