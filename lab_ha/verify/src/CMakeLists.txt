cmake_minimum_required(VERSION 3.20)

set(SOURCE_LIB ${PROJECT_SOURCE_DIR}/../../libTeX/example/qt/qt_texwidget.cpp
                haLabMain.cpp)

add_library(src-lib STATIC ${SOURCE_LIB})

target_link_libraries(src-lib PRIVATE Qt6::Widgets)
