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

double GasExplosionCalc::getInitTg(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_avgT;
    }
    else {
        res = m_avgT;
    }
    return res;
}

void GasExplosionCalc::setFirstValueInitTg(double val){
    if (m_calcIterationCounter == 1) {
        m_init_avgT = val;
    }
}

double GasExplosionCalc::getTheoryOxygenRequire(QString stage){
    double res;
    if (stage == "first"){
        res = 123.0;
    }
    else {
        res = m_theoryOxygenRequire;
    }

    return res;
}

double GasExplosionCalc::getAirFlowRatio(){
    return m_airFlowRatio;
}

double GasExplosionCalc::getVolCO2AtAirFlowRatioEqualOne(){
    return m_volCO2AtAirFlowRatioEqualOne;
}

double GasExplosionCalc::getVolH2OAtAirFlowRatioEqualOne(){
    return m_volH2OAtAirFlowRatioEqualOne;
}

double GasExplosionCalc::getMinusLgKp(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_minusLgKp;
    }
    else {
        res = m_minusLgKp;
    }
    return res;
}

void GasExplosionCalc::setFirstValueMinusLgKp(double val){
    if (m_calcIterationCounter == 1) {
        m_init_minusLgKp = val;
    }
}

double GasExplosionCalc::getKp(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_kp;
    }
    else {
        res = m_kp;
    }
    return res;
}

void GasExplosionCalc::setFirstValueKp(double val){
    if (m_calcIterationCounter == 1) {
        m_init_kp = val;
    }
}

double GasExplosionCalc::getB1(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_bOne;
    }
    else {
        res = m_bOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueB1(double val){
    if (m_calcIterationCounter == 1){
        m_init_bOne = val;
    }
}

double GasExplosionCalc::getB2(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_bTwo;
    }
    else {
        res = m_bTwo;
    }
    return res;
}

void GasExplosionCalc::setFirstValueB2(double val){
    if (m_calcIterationCounter == 1){
        m_init_bTwo = val;
    }
}

double GasExplosionCalc::getVolCO2AtAirFlowRatioLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_volCO2AtAirFlowRatioLessOne;
    }
    else {
        res = m_volCO2AtAirFlowRatioLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueVolCO2AtAirFlowRatioLessOne(double val){
    if (m_calcIterationCounter == 1){
        m_init_volCO2AtAirFlowRatioLessOne = val;
    }
}

double GasExplosionCalc::getVolH2OAtAirFlowRatioLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_volH2OAtAirFlowRatioLessOne;
    }
    else {
        res = m_volH2OAtAirFlowRatioLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueVolH2OAtAirFlowRatioLessOne(double val){
    if (m_calcIterationCounter == 1){
        m_init_volH2OAtAirFlowRatioLessOne = val;
    }
}

double GasExplosionCalc::getVolH2AtAirFlowRatioLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_volH2AtAirFlowRatioLessOne;
    }
    else {
        res = m_volH2AtAirFlowRatioLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueVolH2AtAirFlowRatioLessOne(double val){
    if (m_calcIterationCounter == 1){
        m_init_volH2AtAirFlowRatioLessOne = val;
    }
}

double GasExplosionCalc::getVolN2AtAirFlowRatioLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_volN2AtAirFlowRatioLessOne;
    }
    else {
        res = m_volN2AtAirFlowRatioLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueVolN2AtAirFlowRatioLessOne(double val){
    if (m_calcIterationCounter == 1){
        m_init_volN2AtAirFlowRatioLessOne = val;
    }
}

double GasExplosionCalc::getVolCOAtAirFlowRatioLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_volCOAtAirFlowRatioLessOne;
    }
    else {
        res = m_volCOAtAirFlowRatioLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueVolCOAtAirFlowRatioLessOne(double val){
    if (m_calcIterationCounter == 1){
        m_init_volCOAtAirFlowRatioLessOne = val;
    }
}

double GasExplosionCalc::getVolSumAtAirFlowRatioLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_volSumAtAirFlowRatioLessOne;
    }
    else {
        res = m_volSumAtAirFlowRatioLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValueVolSumAtAirFlowRatioLessOne(double val){
    if (m_calcIterationCounter == 1){
        m_init_volSumAtAirFlowRatioLessOne = val;
    }
}

double GasExplosionCalc::getPressureCO2AtAirFlowRationLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_pressureCO2AtAirFlowRationLessOne;
    }
    else {
        res = m_pressureCO2AtAirFlowRationLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValuePressureCO2AtAirFlowRationLessOne(double v){
    if (m_calcIterationCounter == 1){
        m_init_pressureCO2AtAirFlowRationLessOne = v;
    }
}

double GasExplosionCalc::getPressureCOAtAirFlowRationLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_pressureCOAtAirFlowRationLessOne;
    }
    else {
        res = m_pressureCOAtAirFlowRationLessOne;
    }
   return res;
}

void GasExplosionCalc::setFirstValuePressureCOAtAirFlowRationLessOne(double v){
    if (m_calcIterationCounter == 1){
        m_init_pressureCOAtAirFlowRationLessOne = v;
    }
}

double GasExplosionCalc::getPressureH2OAtAirFlowRationLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_pressureH2OAtAirFlowRationLessOne;
    }
    else {
        res = m_pressureH2OAtAirFlowRationLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValuePressureH2OAtAirFlowRationLessOne(double v){
    if (m_calcIterationCounter == 1){
        m_init_pressureH2OAtAirFlowRationLessOne = v;
    }
}

double GasExplosionCalc::getPressureH2AtAirFlowRationLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_pressureH2AtAirFlowRationLessOne;
    }
    else {
        res = m_pressureH2AtAirFlowRationLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValuePressureH2AtAirFlowRationLessOne(double v){
    if (m_calcIterationCounter == 1){
        m_init_pressureH2AtAirFlowRationLessOne = v;
    }
}

double GasExplosionCalc::getPressureN2AtAirFlowRationLessOne(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_pressureN2AtAirFlowRationLessOne;
    }
    else {
        res = m_pressureN2AtAirFlowRationLessOne;
    }
    return res;
}

void GasExplosionCalc::setFirstValuePressureN2AtAirFlowRationLessOne(double v){
    if (m_calcIterationCounter == 1){
        m_init_pressureN2AtAirFlowRationLessOne = v;
    }
}

void GasExplosionCalc::getResult(){
    qDebug() << "[II] Calculation run now!";
    m_calcIterationCounter = 0;

    runStage01();
    runStage02();
    runStage03();
    runStage04();
}

void GasExplosionCalc::runStage01(double initT){
    // Увеличение счётчика итераций расчёта
    m_calcIterationCounter++;
    qDebug() << "[II] ***************************";
    qDebug() << "[II] >> Iteration counter: " << m_calcIterationCounter << "<<";
    qDebug() << "[II] ***************************";

    // 1. Задаётся средняя температура зоны горения
    //    в первом приближении, град. Цельсия
    m_avgT = initT;
    setFirstValueInitTg(m_avgT);
}

void GasExplosionCalc::runStage02(){
    // 2. По значению предельной концентрации газа в богатой смеси
    //    определяется коэффициент расхода воздуха для первой стадии горения

    // Величины расчётного этапа №2 не зависят от начальной температуры.
    // Расчёт производится при первой итерации, в остальных случаях пропуск
    if (m_calcIterationCounter == 1){
        // Удельное теоретическое количество кислорода
        // при полном горении углеводородного газа CxHy
        m_theoryOxygenRequire = m_carbonAtomCount + m_hydrogenAtomCount/4.0;
        qDebug() << "[II] O_1 =" << m_theoryOxygenRequire;

        // определяется коэффициент расхода воздуха m_airFlowRatio
        m_airFlowRatio = ((100.0 - m_uppFlammabilityLimit) * 0.2415) /
                    (m_uppFlammabilityLimit*m_theoryOxygenRequire);
        qDebug() << "[II] n =" << m_airFlowRatio;
    }
}

void GasExplosionCalc::runStage03(){
    // 3. Проводится расчёт неполного горения
    //    и рассчитывается состав продуктов горения

    // При n = 1 уельное количество (V) продуктов горения
    // не зависит от температуры горения. Расчёт только при первой итерации
    if (m_calcIterationCounter == 1){
        // Удельное количество (V) продуктов горения (ПГ) при n=1;
        m_volCO2AtAirFlowRatioEqualOne = m_carbonAtomCount;
        m_volH2OAtAirFlowRatioEqualOne = m_hydrogenAtomCount/2.0;
        qDebug() << "[II] VolCO2AtN=1" << m_volCO2AtAirFlowRatioEqualOne;
        qDebug() << "[II] VolH2OAtN=1" << m_volH2OAtAirFlowRatioEqualOne;
    }
    // n < 1

    // Логарифм константы равновесия
    m_minusLgKp = 1.0*(2059.0/(m_avgT + 273.0)
            - 1.5904*log10(m_avgT + 273.0)
            + 0.001817*(m_avgT + 273.0)
            - 0.565*pow(10.0, -6.0)*pow(m_avgT + 273.0, 2.0)
            + 8.24*pow(10.0, -11.0)*pow(m_avgT + 273.0, 3.0) + 1.5313);
    setFirstValueMinusLgKp(m_minusLgKp);
    qDebug() << "[II] -lgKp =" << m_minusLgKp;

    // Значение константы равновесия

    m_kp = pow(10, -1*m_minusLgKp);
    setFirstValueKp(m_kp);
    qDebug() << "[II] Kp =" << m_kp;

    m_bTwo = m_volH2OAtAirFlowRatioEqualOne
            - (m_kp - 2.0)*m_volCO2AtAirFlowRatioEqualOne +
            2.0*m_theoryOxygenRequire*(1.0 - m_airFlowRatio)*(m_kp - 1.0);
    setFirstValueB2(m_bTwo);
    qDebug() << "[II] bTwo =" << m_bTwo;

    m_bOne = -1.0*m_bTwo +
        sqrt(pow(m_bTwo, 2.0) + 4.0*(m_kp - 1.0)*m_volCO2AtAirFlowRatioEqualOne*
            (m_volCO2AtAirFlowRatioEqualOne + m_volH2OAtAirFlowRatioEqualOne
            - 2.0*m_theoryOxygenRequire*(1.0 - m_airFlowRatio)));
    setFirstValueB1(m_bOne);
    qDebug() << "[II] bOne = " << m_bOne;

    m_volCO2AtAirFlowRatioLessOne = m_bOne/(2.0*(m_kp - 1.0));
    setFirstValueVolCO2AtAirFlowRatioLessOne(m_volCO2AtAirFlowRatioLessOne);

    m_volCOAtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioEqualOne
                                    - m_volCO2AtAirFlowRatioLessOne;
    setFirstValueVolCOAtAirFlowRatioLessOne(m_volCOAtAirFlowRatioLessOne);

    m_volH2OAtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioEqualOne +
                m_volH2OAtAirFlowRatioEqualOne - m_volCO2AtAirFlowRatioLessOne
                - 2.0*(1.0 - m_airFlowRatio)*m_theoryOxygenRequire;
    setFirstValueVolH2OAtAirFlowRatioLessOne(m_volH2OAtAirFlowRatioLessOne);

    m_volH2AtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioLessOne
                - m_volCO2AtAirFlowRatioEqualOne +
                2.0*(1.0 - m_airFlowRatio)*m_theoryOxygenRequire;
    setFirstValueVolH2AtAirFlowRatioLessOne(m_volH2AtAirFlowRatioLessOne);

    // Не зависит от температуры, не будет пересчитываться на каждом этапе
    if (m_calcIterationCounter == 1){
        m_volN2AtAirFlowRatioLessOne =3.76*m_airFlowRatio*m_theoryOxygenRequire;
        setFirstValueVolN2AtAirFlowRatioLessOne(m_volN2AtAirFlowRatioLessOne);
    }
    m_volSumAtAirFlowRatioLessOne = m_volCO2AtAirFlowRatioLessOne +
                                    m_volH2OAtAirFlowRatioLessOne +
                                    m_volCOAtAirFlowRatioLessOne +
                                    m_volN2AtAirFlowRatioLessOne +
                                    m_volH2AtAirFlowRatioLessOne;
    setFirstValueVolSumAtAirFlowRatioLessOne(m_volSumAtAirFlowRatioLessOne);
    qDebug() << "[II] VolCO2AtAirFlowRatioLessOne =" <<
                                                m_volCO2AtAirFlowRatioLessOne;
    qDebug() << "[II] VolCOAtAirFlowRatioLessOne  =" <<
                                                m_volCOAtAirFlowRatioLessOne;
    qDebug() << "[II] VolH2OAtAirFlowRatioLessOne =" <<
                                                m_volH2OAtAirFlowRatioLessOne;
    qDebug() << "[II] VolH2AtAirFlowRatioLessOne  =" <<
                                                m_volH2AtAirFlowRatioLessOne;
    // Не зависит от температуры, не будет логироваться
    // на каждом этапе т.к., нет пересчёта
    if (m_calcIterationCounter == 1){
        qDebug() << "[II] VolN2AtAirFlowRatioLessOne  =" <<
                                                m_volN2AtAirFlowRatioLessOne;
    }
    qDebug() << "[II] VolSumAtAirFlowRatioLessOne =" <<
                                                m_volSumAtAirFlowRatioLessOne;

    m_pressureCO2AtAirFlowRationLessOne =
                m_volCO2AtAirFlowRatioLessOne / m_volSumAtAirFlowRatioLessOne;
    setFirstValuePressureCO2AtAirFlowRationLessOne(
                                           m_pressureCO2AtAirFlowRationLessOne);
    m_pressureCOAtAirFlowRationLessOne  =
                m_volCOAtAirFlowRatioLessOne  / m_volSumAtAirFlowRatioLessOne;
    setFirstValuePressureCOAtAirFlowRationLessOne(
                                            m_pressureCOAtAirFlowRationLessOne);
    m_pressureH2OAtAirFlowRationLessOne =
                m_volH2OAtAirFlowRatioLessOne / m_volSumAtAirFlowRatioLessOne;
    setFirstValuePressureH2OAtAirFlowRationLessOne(
                                           m_pressureH2OAtAirFlowRationLessOne);
    m_pressureH2AtAirFlowRationLessOne  =
                m_volH2AtAirFlowRatioLessOne  / m_volSumAtAirFlowRatioLessOne;
    setFirstValuePressureH2AtAirFlowRationLessOne(
                                            m_pressureH2AtAirFlowRationLessOne);
    m_pressureN2AtAirFlowRationLessOne  =
                m_volN2AtAirFlowRatioLessOne  / m_volSumAtAirFlowRatioLessOne;
    setFirstValuePressureN2AtAirFlowRationLessOne(
                                            m_pressureN2AtAirFlowRationLessOne);

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

void GasExplosionCalc::runStage04(){
    // 4. По уровнению теплового баланса уточняется значение температуры
    //    и при необходимости осуществляется возврат к п.1 (runStage01);

    int counterT = 0;
    double newAvgT = m_avgT;
    double oldAvgT = 0;
    double deltaQ = 0;

    do {
        double m_enthalpy = (1.465*m_pressureN2AtAirFlowRationLessOne
                           + 1.516*m_pressureCOAtAirFlowRationLessOne
                           + 1.424*m_pressureH2AtAirFlowRationLessOne
                           + 2.449*m_pressureCO2AtAirFlowRationLessOne
                           + 2.001*m_pressureH2OAtAirFlowRationLessOne)*2200.0;
        qDebug() << "[II] Enthalpy (I) = " << m_enthalpy;

        // Теплота химического недожёга продуктов неполного горения, МДж/м^3
        double gasHeatLoss = (12.65*m_pressureCOAtAirFlowRationLessOne
                          + 10.77*m_pressureH2AtAirFlowRationLessOne)*
                                                  m_volSumAtAirFlowRatioLessOne;

        qDebug() << "[II] qHeatLoss = " << gasHeatLoss;

        oldAvgT = newAvgT;
        deltaQ = m_gasHeatOfCombustion - gasHeatLoss;
        if (oldAvgT >= 950){
            newAvgT = ((deltaQ*1000.0)/(m_volSumAtAirFlowRatioLessOne*m_enthalpy)
                                                                  + 0.075)*2050;
            qDebug() << "[II] T > 950; T' =" << newAvgT;
        }
        else{
            // newAvgT=(m_enthalpy+0.3*(deltaQ*1000.0)/m_volSumAtAirFlowRatioLessOne)/
            //     ((2695*deltaQ*1000)/(m_volSumAtAirFlowRatioLessOne));
            newAvgT=((2695*deltaQ*1000)/(m_volSumAtAirFlowRatioLessOne))/
                (m_enthalpy+0.3*(deltaQ*1000.0)/m_volSumAtAirFlowRatioLessOne);
                qDebug() << "[II] T < 950; T' =" << newAvgT;
        }

        // Обновление параметров сжигания газа
        runStage01(newAvgT);
        runStage02();
        runStage03();
        counterT++;
    }

    while (fabs(newAvgT - oldAvgT) > m_accuracyCalcAvgT );
    qDebug() << "[II] Update m_avgT: " << m_avgT << ", N = " << counterT;
}

// End gasExplosionCalc.cpp
