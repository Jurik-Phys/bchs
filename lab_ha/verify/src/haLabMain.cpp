// Begin haLabMain.cpp

#include "haLabMain.h"

QHaLabMain::QHaLabMain(QWidget *parent) : QWidget(parent){
    this->resize(m_appWindowWidth, m_appWindowHeight);
    this->setWindowTitle("Лабораторная работа «Техногенная химическая авария». "
                                                          "Проверочный расчёт");
}

QHaLabMain::~QHaLabMain(){}

// End haLabMain.cpp
