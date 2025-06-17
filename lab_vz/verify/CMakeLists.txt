cmake_minimum_required(VERSION 3.20)

project(lab_vz_verify)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# MicroTeX setup
option(HAVE_LOG "Enable or disable MicroTeX logs" OFF)
set(BUILD_STATIC "If build for static library" ON)
set(BUILD_EXAMPLE_QT OFF)
set(QT ON)

# Copy FiraMath font to build directory
set(SOURCE_FONTS_DIR ${CMAKE_SOURCE_DIR}/ext/MicroTeX/res/firamath)
set(BUILD_DIR ${CMAKE_BINARY_DIR})
file(COPY ${SOURCE_FONTS_DIR}/FiraMath-Regular.clm2
          ${SOURCE_FONTS_DIR}/FiraMath-Regular.otf DESTINATION ${BUILD_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src
               ${CMAKE_SOURCE_DIR}/ext/MicroTeX/platform/qt/
               ${CMAKE_SOURCE_DIR}/ext/MicroTeX/example/qt/
               ${CMAKE_SOURCE_DIR}/ext/MicroTeX/lib
               ${CMAKE_BINARY_DIR}/ext/MicroTeX/lib)

set(SOURCE_EXE main.cpp)

add_subdirectory(src)
add_subdirectory(ext/MicroTeX)

add_executable(lab_vz_verify ${SOURCE_EXE})

target_link_libraries(lab_vz_verify PRIVATE src-lib Qt6::Widgets microtex microtex-qt)
