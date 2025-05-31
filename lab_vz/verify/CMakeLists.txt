cmake_minimum_required(VERSION 3.20)

project(lab_vz_verify)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE_EXE main.cpp)

add_subdirectory(src)

add_executable(lab_vz_verify ${SOURCE_EXE})

target_link_libraries(lab_vz_verify PRIVATE src-lib Qt6::Widgets)
