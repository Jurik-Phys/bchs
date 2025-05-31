// Begin appWindow.cpp

#include "appWindow.h"

QAppWindow::QAppWindow(QWidget *parent) : QWidget(parent){
    this->resize(m_appWindowWidth, m_appWindowHeight);
    this->setWindowTitle("Лабораторная работа «Техногенный взрыв». "
                                                        "Проверочный расчёт");

    InputData m_data = {
        // 1. Диаметр цилиндрического резервуара со сжатым газом, м.
        .gasTankDiameter = 0.205,
        // 2. Длина цилиндрического резервуара со сжатым газом, м.
        .gasTankLength = 1.39,
        // 3. Показатель адиабаты сжатого газа в резервуаре.
        .gasAdiabaticIndex = 1.3,
        // 4. Избыточное давление сжатого газа в резервуаре при взрыве, кПа
        .tankBurstPressure = 23000.0,
        // 5. Плотность газа при нормальных условиях, кг/м^3.
        .ntpTankGasDensity = 1.43,
        // 6. Температура воздуха, град. Цельсия.
        .airTemperature = 20.0,
        // 7. Коэффициент перехода.
        .releaseFraction = 0.9,
        // 8. Расстояние от центра взрывной системы до приёмника уд. волны, м.
        .standoffDistance = 3.0,
        // 9. Атмосферное давление.
        .airPressure = 101.3,
        // 10. Показатель адиабаты воздуха.
        .airAdiabaticIndex = 1.4,
        // 11. Плотность воздуха, кг/м^3.
        .airDensity = 1.293,
        // 12. Удельная энергия взрывчатого разложения тротилла, кДж/кг
        .tntSpecificEnergy = 4180.0,
        // 13. Энергетический параметр (alpha) взрыва
        .alpha = 0.852793,
        // 14. Итерационная глубина при расчёте безразмерного времени
        .tauItCount = 500,
        // 15. Масса тела человека, кг.
        .humanMass = 70.
    };

    m_labSolver = new LabSolver();

    m_labSolver->setInputData(m_data);
    m_labSolver->getSolve();
}

QAppWindow::~QAppWindow(){
}

// End appWindow.cpp
