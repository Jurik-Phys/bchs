// Begin appWindowHA.cpp

#include "appWindowHA.h"

QAppWindowHA::QAppWindowHA(QWidget *parent) : QWidget(parent){
    this->resize(m_appWindowWidth, m_appWindowHeight);
    this->setWindowTitle("Лабораторная работа «Техногенная химическая авария». "
                                                          "Проверочный расчёт");
    m_labSolverHA = new LabSolverHA();

    m_labSolverHA->setInputData(labDataVariants[0]);
    m_labSolverHA->getSolve();
}

QAppWindowHA::~QAppWindowHA(){}

// End appWindowHA.cpp
