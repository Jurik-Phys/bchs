cmake_minimum_required(VERSION 3.20)

project(formula-draw-demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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

add_executable(formula-draw-demo ${SOURCE_EXE})

target_link_libraries(formula-draw-demo PRIVATE src-lib Qt6::Widgets microtex microtex-qt)
