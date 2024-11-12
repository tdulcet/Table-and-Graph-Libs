cmake_minimum_required(VERSION 3.20) # TODO: reevaluate min version
project(tgl LANGUAGES CXX)

add_library(tgl_graphs "${CMAKE_CURRENT_SOURCE_DIR}/graphs.cpp")
add_library(${PROJECT_NAME}::graphs ALIAS tgl_graphs)
target_include_directories(tgl_graphs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(tgl_tables "${CMAKE_CURRENT_SOURCE_DIR}/tables.cpp")
add_library(${PROJECT_NAME}::tables ALIAS tgl_tables)
target_include_directories(tgl_tables PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})