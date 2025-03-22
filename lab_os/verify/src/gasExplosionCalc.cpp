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

double GasExplosionCalc::getInitAccurateTg(QString stage){
    double res;
    if (stage == "first") {
        res = m_init_accurate_avgT;
    }
    else {
        res = m_avgT;
    }
    return res;
}

void GasExplosionCalc::setFirstValueInitAccurateTg(double val){
    if (m_calcIterationCounter == 1) {
        m_init_accurate_avgT = val;
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

double GasExplosionCalc::getEnthalpy(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_enthalpy;
    }
    else {
        res = m_enthalpy;
    }
    return res;
}

void GasExplosionCalc::setFirstValueEnthalpy(double val){
    if (m_calcIterationCounter == 1){
        m_init_enthalpy = val;
    }
}

double GasExplosionCalc::getGasHeatLoss(QString stage){
    double res;
    if (stage == "first"){
        res = m_init_gasHeatLoss;
    }
    else {
        res = m_gasHeatLoss;
    }
    return res;
}

void GasExplosionCalc::setFirstValueGasHeatLoss(double value){
    if (m_calcIterationCounter == 1){
        m_init_gasHeatLoss = value;
    }
}

int GasExplosionCalc::getCalcIterationCounter(){
    return m_calcIterationCounter;
}

double GasExplosionCalc::getAaccuracyCalcAvgT(){
    return m_accuracyCalcAvgT;
}

double GasExplosionCalc::getFireBallRadius(){
    return m_fireBallRadius;
}

double GasExplosionCalc::getEffPath(){
    return m_effPath;
}
double GasExplosionCalc::getRayDecreaseFactor(){
    return m_rayDecreaseFactor;
}

double GasExplosionCalc::getFireBallBlackness(){
    return m_fireBallBlackness;
}

double GasExplosionCalc::getFireBallArea(){
    return m_fireBallArea;
}

double GasExplosionCalc::getFireBallEnergyPower(){
    return m_fireBallEnergyPower;
}

double GasExplosionCalc::getRaySpreadSphereArea(){
    return m_raySpreadSphereArea;
}

double GasExplosionCalc::getQDensity(){
    return m_qDensity;
}

double GasExplosionCalc::getEyeEnDensity(){
    return m_eyeEnDensity;
}

double GasExplosionCalc::getEyeFocus(){
    return m_eyeFocus;
}

double GasExplosionCalc::getFireBallEyeSize(){
    return m_fireBallEyeSize;
}

double GasExplosionCalc::getSmokeKinematicViscosity(){
    return m_smokeKinematicViscosity;
}

double GasExplosionCalc::getRe(){
    return m_Re;
}

double GasExplosionCalc::getTurboFlameSpeed(){
    return m_turboFlameSpeed;
}

double GasExplosionCalc::getAvgFlameSpeed(){
    return m_avgFlameSpeed;
}

double GasExplosionCalc::getFireTime(){
    return m_fireTime;
}

double GasExplosionCalc::getPI(){
    return m_PI;
}

double GasExplosionCalc::getSigma(){
    return m_Sigma;
}

void GasExplosionCalc::getResult(){
    qDebug() << "[II] Calculation run now!";
    m_calcIterationCounter = 0;

    runStage01();
    runStage02();
    runStage03();
    runStage04();
    runStage05();
    runStage06();
    runStage07();
    runStage08();
    runStage09();
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
    qDebug() << "\n[**] > Stage 04 <";

    double newAvgT = m_avgT;
    double oldAvgT = 0;
    double deltaQ = 0;

    do {
        double m_enthalpy = (1.465*m_pressureN2AtAirFlowRationLessOne
                           + 1.516*m_pressureCOAtAirFlowRationLessOne
                           + 1.424*m_pressureH2AtAirFlowRationLessOne
                           + 2.449*m_pressureCO2AtAirFlowRationLessOne
                           + 2.001*m_pressureH2OAtAirFlowRationLessOne)*2200.0;
        setFirstValueEnthalpy(m_enthalpy);
        qDebug() << "[II] Enthalpy (I) = " << m_enthalpy;

        // Теплота химического недожёга продуктов неполного горения, МДж/м^3
        m_gasHeatLoss = (12.65*m_pressureCOAtAirFlowRationLessOne
                          + 10.77*m_pressureH2AtAirFlowRationLessOne)*
                                                  m_volSumAtAirFlowRatioLessOne;
        setFirstValueGasHeatLoss(m_gasHeatLoss);
        qDebug() << "[II] qHeatLoss = " << m_gasHeatLoss;

        oldAvgT = newAvgT;
        deltaQ = m_gasHeatOfCombustion - m_gasHeatLoss;
        if (oldAvgT >= 950){
            newAvgT = ((deltaQ*1000.0)/(m_volSumAtAirFlowRatioLessOne*m_enthalpy)
                                                                  + 0.075)*2050;
            setFirstValueInitAccurateTg(newAvgT);
            qDebug() << "[II] T > 950; T' =" << newAvgT;
        }
        else{
            // Опечатка в методических указаниях(?)
            // newAvgT=(m_enthalpy+0.3*(deltaQ*1000.0)/m_volSumAtAirFlowRatioLessOne)/
            //     ((2695*deltaQ*1000)/(m_volSumAtAirFlowRatioLessOne));
            newAvgT=((2695*deltaQ*1000)/(m_volSumAtAirFlowRatioLessOne))/
                (m_enthalpy+0.3*(deltaQ*1000.0)/m_volSumAtAirFlowRatioLessOne);
                setFirstValueInitAccurateTg(newAvgT);
                qDebug() << "[II] T < 950; T' =" << newAvgT;
        }

        // Обновление параметров сжигания газа
        runStage01(newAvgT);
        runStage02();
        runStage03();
    }

    while (fabs(newAvgT - oldAvgT) > m_accuracyCalcAvgT );
    qDebug() << "[II] Update m_avgT: " << m_avgT << ", N = " <<
                                                        m_calcIterationCounter;
}

void GasExplosionCalc::runStage05(){
    // 5. С учётом плотности и массы углеводородного газа, находившегося
    //    в резервуаре, определяются размеры газовоздушного облака.
    qDebug() << "\n[**] > Stage 05 <";

    double num = (3.0/(4*m_PI)) *
                 (m_gasMass*1000.0*m_volSumAtAirFlowRatioLessOne/m_gasDensity) *
                 ((m_avgT + 273.0)/273.0);
    m_fireBallRadius =  pow(num, 1.0/3.0);

    qDebug() << "[II] Fire ball radius: " << m_fireBallRadius;
}

void GasExplosionCalc::runStage06(){
    // 6. По температуре и размеру зоны горения, по количеству излучающих газов
    //    рассчитывается степень черноты (ε) горящего облака.
    qDebug() << "\n[**] > Stage 06 <";

    m_effPath = 1.3 * m_fireBallRadius;
    qDebug() << "[II] effPath:" << m_effPath;

    m_rayDecreaseFactor = (
            (0.8 + 1.6*m_pressureH2OAtAirFlowRationLessOne)/
                (pow((m_pressureH2OAtAirFlowRationLessOne +
                           m_pressureCO2AtAirFlowRationLessOne)*m_effPath,0.5))
            )*(1 - 0.38*(m_avgT + 273.0)/1000.0);
    qDebug() << "[II] m_rayDecreaseFactor:" << m_rayDecreaseFactor;

    m_fireBallBlackness = 1 - exp(-1.0 * m_rayDecreaseFactor * m_effPath *
                                (m_pressureH2OAtAirFlowRationLessOne +
                                       m_pressureCO2AtAirFlowRationLessOne));
    qDebug() << "[II] m_fireBallBlackness:" << m_fireBallBlackness;
}

void GasExplosionCalc::runStage07(){
    // 7. По степени черноты, температуре и величине внешней поверхности зоны
    //    горения определяется интегральный поток собственного излучения
    //    огненного шара.
    qDebug() << "\n[**] > Stage 07 <";

    m_fireBallArea = 4.0 * m_PI * pow(m_fireBallRadius, 2.0);
    qDebug() << "[II] m_fireBallArea:" << m_fireBallArea;

    m_fireBallEnergyPower = m_Sigma * m_fireBallBlackness *
                                    pow(m_avgT + 273.0, 4.0) * m_fireBallArea;

    qDebug() << "[II] m_fireBallEnergyPower:" << m_fireBallEnergyPower;
}

void GasExplosionCalc::runStage08(){
    // 8. По величине интегрального потока собственного излучения
    //    и по расстоянию от центра зоны горения до приёмника вычисляется
    //    величина плотности потока энерги (q) инфракрасного излучения
    qDebug() << "\n[**] > Stage 08 <";

    m_raySpreadSphereArea = 4.0 * m_PI *
                              pow(m_fireBallRadius + m_distanceToReceiver, 2.0);

    qDebug() << "[II] m_raySpreadSphereArea:" << m_raySpreadSphereArea;

    m_qDensity = m_Sigma * m_fireBallBlackness *
                                            pow(m_avgT + 273.0, 4.0) *
                                                    pow(m_fireBallRadius, 2.0)/
                              pow(m_fireBallRadius + m_distanceToReceiver, 2.0);

    qDebug() << "[II] m_qDensity:" << m_qDensity;
}

void GasExplosionCalc::runStage09(){
    // 9. Определяются значения параметров воздействия.
    qDebug() << "\n[**] > Stage 09 <";

    m_eyeEnDensity = m_qDensity * m_eyeRadiationTime;
    qDebug() << "[II] m_eyeEnDensity:" << m_eyeEnDensity;

    // Фокусное расстояние глаза человека (среднее значение)
    m_eyeFocus = 17.0;
    m_fireBallEyeSize = m_eyeFocus * 2.0 * m_fireBallRadius /
                                                           m_distanceToReceiver;

    qDebug() << "[II] m_fireBallEyeSize:" << m_fireBallEyeSize;

    m_smokeKinematicViscosity = 12.2E-6;

    m_Re = 2.0 * m_fireBallRadius * m_normalFlameSpeed /
                                                      m_smokeKinematicViscosity;

    qDebug() << "[II] m_Re:" << m_Re;

    m_turboFlameSpeed = 0.18 * pow(m_normalFlameSpeed, 0.26) * pow(m_Re, 0.24);

    qDebug() << "[II] m_turboFlameSpeed:" << m_turboFlameSpeed;

    m_avgFlameSpeed = (m_normalFlameSpeed + m_turboFlameSpeed)/2.0;

    qDebug() << "[II] m_avgFlameSpeed:" << m_avgFlameSpeed;

    m_fireTime = 2.0 * m_fireBallRadius / m_avgFlameSpeed;

    qDebug() << "[II] m_fireTime:" << m_fireTime;
}

// End gasExplosionCalc.cpp
