cmake_minimum_required(VERSION 3.20)

project(lab_os_verify)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(HAVE_LOG "Enable or disable MicroTeX logs" OFF)
set(BUILD_EXAMPLE_QT OFF)
set(QT ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR}/src              \\
                    ${CMAKE_SOURCE_DIR}/ext/MicroTeX     \\
                    ${CMAKE_SOURCE_DIR}/ext/MicroTeX/lib \\
                    ${CMAKE_BINARY_DIR}/ext/MicroTeX/lib)

set(SOURCE_EXE main.cpp)

add_subdirectory(src)
add_subdirectory(ext/MicroTeX)

add_executable(lab_os_verify ${SOURCE_EXE})

target_link_libraries(lab_os_verify PRIVATE src-lib Qt6::Widgets microtex microtex-qt)
