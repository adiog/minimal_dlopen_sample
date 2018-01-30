cmake_minimum_required(VERSION 3.9)
project(CommonData)

set(CMAKE_CXX_STANDARD 11)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(CommonData main.cc)
target_link_libraries(CommonData dl)

add_library(qm1 SHARED qm1.cc)
add_library(qm2 SHARED qm2.cc)

add_library(qm-cont-load SHARED qm.cc)
add_custom_command(TARGET qm-cont-load POST_BUILD COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/qm_reload.sh)
