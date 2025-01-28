// Begin gasExplosionCalc.cpp

#include "gasExplosionCalc.h"

GasExplosionCalc::GasExplosionCalc(){
}

GasExplosionCalc::~GasExplosionCalc(){
}

// 1. "Число атомов углерода в углеводородном газе, ед."
void GasExplosionCalc::setCarbonAtomCount(double& carbonAtomCount){
    m_carbonAtomCount = carbonAtomCount;
}
double GasExplosionCalc::getCarbonAtomCount(){
    return m_carbonAtomCount;
}


// 2. "Число атомов водорода в углеводородном газе, ед." <<
void GasExplosionCalc::setHydrogenAtomCount(double& hydrogenAtomCount){
    m_hydrogenAtomCount = hydrogenAtomCount;
}
double GasExplosionCalc::getHydrogenAtomCount(){
    return m_hydrogenAtomCount;
}


// 3. "Теплота сгорания углеводородного газа, МДж/м^3" <<
void GasExplosionCalc::setGasHeatOfCombustion(double& gasHeatOfCombustion){
    m_gasHeatOfCombustion = gasHeatOfCombustion;
}
double GasExplosionCalc::getGasHeatOfCombustion(){
    return m_gasHeatOfCombustion;
}


// 4. "Верхний концентрационный предел воспламенения углеводородного газа, %" <<
void GasExplosionCalc::setUpperFlammabilityLimit(double & uppFlammabilityLimit){
    m_uppFlammabilityLimit = uppFlammabilityLimit;
}
double GasExplosionCalc::getUpperFlammabilityLimit(){
    return m_uppFlammabilityLimit;
}


// 5. "Плотность углеводородного газа при нормальных условиях, кг/м^3" <<
void GasExplosionCalc::setGasDensity(double & gasDensity){
    m_gasDensity = gasDensity;
}
double GasExplosionCalc::getGasDensity(){
    return m_gasDensity;
}


// 6. "Нормальная скорость распространения пламени, м/c" <<
void GasExplosionCalc::setNormalFlameSpeed(double& normalFlameSpeed){
    m_normalFlameSpeed = normalFlameSpeed;
}
double GasExplosionCalc::getNormalFlameSpeed(){
    return m_normalFlameSpeed;
}


// 7. "Масса углеводородного газа, образовавшего огневой шар, т" <<
void GasExplosionCalc::setGasMass(double& gasMass){
    m_gasMass = gasMass;
}
double GasExplosionCalc::getGasMass(){
    return m_gasMass;
}


// 8. "Расстояние от зоны горения до приёмника инфракрасного излучения, м" <<
void GasExplosionCalc::setDistanceToReceiver(double& distanceToReceiver){
    m_distanceToReceiver = distanceToReceiver;
}
double GasExplosionCalc::getDistanceToReceiver(){
    return m_distanceToReceiver;
}


// 9. "Время действия излучения на сетчатку глаза человека, с";
void GasExplosionCalc::setEyeRadiationTime(double& eyeRadiationTime){
    m_eyeRadiationTime = eyeRadiationTime;
}
double GasExplosionCalc::getEyeRadiationTime(){
    return m_eyeRadiationTime;
}

double GasExplosionCalc::getInitTg(){
    return m_avgT;
}

double GasExplosionCalc::getTheoryOxygenRequire(){
    return m_theoryOxygenRequire;
}

double GasExplosionCalc::getAirFlowRatio(){
    return m_airFlowRatio;
}

void GasExplosionCalc::getResult(){
    qDebug() << "[II] Calculation run now!";

    runStep01();
    runStep02();
    runStep03();
}

void GasExplosionCalc::runStep01(){
    // 1. Задаётся средняя температура зоны горения
    //    в первом приближении, град. Цельсия
    m_avgT = 1400.0;
}

void GasExplosionCalc::runStep02(){
    // 2. По значению предельной концентрации газа в богатой смеси
    //    определяется коэффициент расхода воздуха для первой стадии горения

    // Удельное теоретическое количество кислорода
    // при полном горении углеводородного газа CxHy
    m_theoryOxygenRequire = m_carbonAtomCount + m_hydrogenAtomCount/4.0;
    qDebug() << "[II] O_1 =" << m_theoryOxygenRequire;

    // определяется коэффициент расхода воздуха m_airFlowRatio
    m_airFlowRatio = ((100.0 - m_uppFlammabilityLimit) * 0.2415) /
                    (m_uppFlammabilityLimit*m_theoryOxygenRequire);
    qDebug() << "[II] n =" << m_airFlowRatio;
}

void GasExplosionCalc::runStep03(){
    // 3. Проводится расчёт неполного горения
    //    и рассчитывается состав продуктов горения

    // Удельное количество (V) продуктов горения (ПГ) при n=1;
    m_volCO2AtAirFlowRatioEqualOne = m_carbonAtomCount;
    m_volH2OAtAirFlowRatioEqualOne = m_hydrogenAtomCount/2.0;
    qDebug() << "[II] VolCO2AtN=1" << m_volCO2AtAirFlowRatioEqualOne;
    qDebug() << "[II] VolH2OAtN=1" << m_volH2OAtAirFlowRatioEqualOne;

    // n < 1

    // Логарифм константы равновесия
    m_lgKp = -1.0*(2059.0/(m_avgT + 273.0) \
            - 1.5904*log10(m_avgT + 273.0) + \
            0.001817*(m_avgT + 273.0) \
            - 0.565*pow(10.0, -6.0)*pow(m_avgT + 273.0, 2.0) + \
            8.24*pow(10.0, -11.0)*pow(m_avgT + 273.0, 3.0) + 1.5313);
    qDebug() << "[II] lgKp =" << m_lgKp;

    // Значение константы равновесия

    m_kp = pow(10, m_lgKp);
    qDebug() << "[II] Kp =" << m_kp;

    m_bTwo = m_volH2OAtAirFlowRatioEqualOne
            - (m_kp - 2.0)*m_volCO2AtAirFlowRatioEqualOne +
            2.0*m_theoryOxygenRequire*(1.0 - m_airFlowRatio)*(m_kp - 1.0);
    qDebug() << "[II] bTwo =" << m_bTwo;

    m_bOne = -1.0*m_bTwo + \
        sqrt(pow(m_bTwo, 2.0) + 4.0*(m_kp - 1.0)*m_volCO2AtAirFlowRatioEqualOne*
            (m_volCO2AtAirFlowRatioEqualOne + m_volH2OAtAirFlowRatioEqualOne
            - 2.0*m_theoryOxygenRequire*(1.0 - m_airFlowRatio)));
    qDebug() << "[II] bOne = " << m_bOne;

    m_volCO2AtAirFlowRatioLessOne = m_bOne/(2.0*(m_kp - 1.0));
    m_volCOAtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioEqualOne
                                    - m_volCO2AtAirFlowRatioLessOne;
    m_volH2OAtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioEqualOne +
                m_volH2OAtAirFlowRatioEqualOne - m_volCO2AtAirFlowRatioLessOne
                - 2.0*(1.0 - m_airFlowRatio)*m_theoryOxygenRequire;
    m_volH2AtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioLessOne
                - m_volCO2AtAirFlowRatioEqualOne +
                2.0*(1.0 - m_airFlowRatio)*m_theoryOxygenRequire;
    m_volN2AtAirFlowRatioLessOne = 3.76*m_airFlowRatio*m_theoryOxygenRequire;
    m_volSumAtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioLessOne +
                                    m_volH2OAtAirFlowRatioLessOne +
                                    m_volCOAtAirFlowRatioLessOne +
                                    m_volN2AtAirFlowRatioLessOne +
                                    m_volH2AtAirFlowRatioLessOne;
    qDebug() << "[II] VolCO2AtAirFlowRatioLessOne =" <<
                                                m_volCO2AtAirFlowRatioLessOne;
    qDebug() << "[II] VolCOAtAirFlowRatioLessOne  =" <<
                                                m_volCOAtAirFlowRatioLessOne;
    qDebug() << "[II] VolH2OAtAirFlowRatioLessOne =" <<
                                                m_volH2OAtAirFlowRatioLessOne;
    qDebug() << "[II] VolH2AtAirFlowRatioLessOne  =" <<
                                                m_volH2AtAirFlowRatioLessOne;
    qDebug() << "[II] VolN2AtAirFlowRatioLessOne  =" <<
                                                m_volN2AtAirFlowRatioLessOne;
    qDebug() << "[II] VolSumAtAirFlowRatioLessOne =" <<
                                                m_volSumAtAirFlowRatioLessOne;

    m_pressureCO2AtAirFlowRationLessOne =
                m_volCO2AtAirFlowRatioLessOne / m_volSumAtAirFlowRatioLessOne;
    m_pressureCOAtAirFlowRationLessOne  =
                m_volCOAtAirFlowRatioLessOne  / m_volSumAtAirFlowRatioLessOne;
    m_pressureH2OAtAirFlowRationLessOne =
                m_volH2OAtAirFlowRatioLessOne / m_volSumAtAirFlowRatioLessOne;
    m_pressureH2AtAirFlowRationLessOne  =
                m_volH2AtAirFlowRatioLessOne  / m_volSumAtAirFlowRatioLessOne;
    m_pressureN2AtAirFlowRationLessOne  =
                m_volN2AtAirFlowRatioLessOne  / m_volSumAtAirFlowRatioLessOne;

    qDebug() << "[II] PressureCO2AtAirFlowRationLessOne =" <<
                                            m_pressureCO2AtAirFlowRationLessOne;
    qDebug() << "[II] PressureCOAtAirFlowRationLessOne  =" <<
                                            m_pressureCOAtAirFlowRationLessOne;
    qDebug() << "[II] PressureH2OAtAirFlowRationLessOne =" <<
                                            m_pressureH2OAtAirFlowRationLessOne;
    qDebug() << "[II] PressureH2AtAirFlowRationLessOne  =" <<
                                            m_pressureH2AtAirFlowRationLessOne;
    qDebug() << "[II] PressureN2AtAirFlowRationLessOne  =" <<
                                            m_pressureN2AtAirFlowRationLessOne;
}

// End gasExplosionCalc.cpp
