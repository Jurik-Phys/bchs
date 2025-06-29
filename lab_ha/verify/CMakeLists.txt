cmake_minimum_required(VERSION 3.20)

project(lab_ha_verify)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/../../libTeX/lib
                    ${PROJECT_SOURCE_DIR}/../../libTeX/platform/qt/
                    ${PROJECT_SOURCE_DIR}/../../libTeX/example/qt/
                    ${CMAKE_BINARY_DIR}/libTeX/lib)

# MicroTeX setup
option(HAVE_LOG "Enable or disable MicroTeX logs" OFF)
set(BUILD_STATIC "If build for static library" ON)
set(BUILD_EXAMPLE_QT OFF)
set(QT ON)

# Copy FiraMath font to build directory
set(SOURCE_FONTS_DIR ${PROJECT_SOURCE_DIR}/../../libTeX/res/firamath)
file(COPY ${SOURCE_FONTS_DIR}/FiraMath-Regular.clm2
          ${SOURCE_FONTS_DIR}/FiraMath-Regular.otf DESTINATION ${CMAKE_BINARY_DIR})

qt_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/res/resources.qrc)

if(WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_SOURCE_DIR}/res/icon.rc")
    set(WIN_FLAG "WIN32")
endif()

set(SOURCE_EXE main.cpp)

add_subdirectory(src)
add_subdirectory(${PROJECT_SOURCE_DIR}/../../libTeX ${CMAKE_BINARY_DIR}/libTeX)

add_executable(lab_ha_verify ${WIN_FLAG} ${SOURCE_EXE} ${RESOURCES} ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(lab_ha_verify PRIVATE src-lib Qt6::Widgets microtex microtex-qt)
