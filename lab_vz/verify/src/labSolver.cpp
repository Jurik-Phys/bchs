// Begin labSolver.cpp

#include "labSolver.h"

LabSolver::LabSolver(){
}

LabSolver::~LabSolver(){
}

void LabSolver::setInputData(const InputData& i) {
    m_iData = i;
}

InputData LabSolver::getInputData(){
    return m_iData;
}

OutData LabSolver::getOutData(){
    return m_oData;
}

RawData LabSolver::getRawData(){
    return m_rData;
}

void LabSolver::getSolve(){
    qDebug() << "[II] Start solver...";
    qDebug() << "[II] Input data:";
    qDebug() << "     gasTankDiameter:"   << m_iData.gasTankDiameter;
    qDebug() << "     gasTankLength:"     << m_iData.gasTankLength;
    qDebug() << "     gasAdiabaticIndex:" << m_iData.gasAdiabaticIndex;
    qDebug() << "     tankBurstPressure:" << m_iData.tankBurstPressure;
    qDebug() << "     ntpTankGasDensity:" << m_iData.ntpTankGasDensity;
    qDebug() << "     airTemperature:"    << m_iData.airTemperature;
    qDebug() << "     releaseFraction:"   << m_iData.releaseFraction;
    qDebug() << "     standoffDistance:"  << m_iData.standoffDistance;
    qDebug() << "     airPressure:"       << m_iData.airPressure;

    solveStage01();
    solveStage02();
    solveStage03();
    solveStage04();
    solveStage05();
    solveStage06();
    solveStage07();
    solveSaveOut();
}

void LabSolver::solveStage01(){
    qDebug() << "[II] >> Solve stage 01 <<";
    double& absTankBurstPressure = m_rData.absTankBurstPressure;
    double& tankBurstPressure = m_iData.tankBurstPressure;
    double& airPressure = m_iData.airPressure;
    double& gasTankDiameter = m_iData.gasTankDiameter;
    double& gasTankLength = m_iData.gasTankLength;
    double& tankVolume = m_rData.tankVolume;
    double& burstEnergy = m_rData.burstEnergy;
    double& gasAdiabaticIndex = m_iData.gasAdiabaticIndex;

    absTankBurstPressure = tankBurstPressure + airPressure;
    tankVolume = M_PI*pow(gasTankDiameter/2.0, 2.0) * gasTankLength;
    burstEnergy = ((absTankBurstPressure-airPressure)/(gasAdiabaticIndex - 1.0))
                                                                   * tankVolume;
    qDebug() << "     P_1:" << m_rData.absTankBurstPressure;
    qDebug() << "     V_г:" << m_rData.tankVolume;
    qDebug() << "     E_п:" << m_rData.burstEnergy;
}

void LabSolver::solveStage02(){
    qDebug() << "[II] >> Solve stage 02 <<";

    m_rData.tntEquivalent = m_rData.burstEnergy/m_iData.tntSpecificEnergy;
    qDebug() << "     W_тнт:" << m_rData.tntEquivalent;
}

void LabSolver::solveStage03(){
    qDebug() << "[II] >> Solve stage 03 <<";
    double& dynParamX0 = m_rData.dynParamX0;
    double& releaseFraction = m_iData.releaseFraction;
    double& airPressure = m_iData.airPressure;
    double& burstEnergy = m_rData.burstEnergy;
    double& rsDistance = m_rData.rsDistance;
    double& standoffDistance = m_iData.standoffDistance;
    double& waveBurstPressure = m_rData.waveBurstPressure;

    dynParamX0 = pow(releaseFraction*burstEnergy/airPressure, 1.0/3.0);
    rsDistance = standoffDistance / dynParamX0;

    if (0 < rsDistance <= 2){
        waveBurstPressure = airPressure
          / (0.6 * (-1.0 + pow((1.0 + 29.847755*pow(rsDistance,3.0)),1.0/2.0)));

    }
    else {
        double sqrtArg;
        sqrtArg = 1.0 + 70.0 * pow(rsDistance, 2.)*(log(rsDistance/2.0) + 1.0 );
        waveBurstPressure = airPressure
          / (0.6*(-1. + pow(sqrtArg, 1./2.)));
    }

    qDebug() << "     X_0:" << m_rData.dynParamX0;
    qDebug() << "     R_s:" << m_rData.rsDistance;
    qDebug() << "     p_s:" << m_rData.waveBurstPressure;
}

void LabSolver::solveStage04(){
    qDebug() << "[II] >> Solve stage 04 <<";

    double& airSndSpeed = m_rData.airSndSpeed;
    double& airAdiabaticIndex =  m_iData.airAdiabaticIndex;
    double& airPressure = m_iData.airPressure;
    double& airDensity = m_iData.airDensity;
    double& airFlowSpeed = m_rData.airFlowSpeed;
    double& rsDistance = m_rData.rsDistance;

    airSndSpeed = pow(airAdiabaticIndex * airPressure * 1000. / airDensity, .5);

    if (0 < rsDistance <= 2){
        airFlowSpeed = 0.30507 * airSndSpeed / pow(rsDistance, 1.5);
    }
    else {
        airFlowSpeed = 0.21571 * airSndSpeed
                        / (rsDistance * pow((log(rsDistance/2.0) + 1.0), .5));
    }

    qDebug() << "     C_1:" << m_rData.airSndSpeed;
    qDebug() << "     V_s:" << m_rData.airFlowSpeed;
}

void LabSolver::solveStage05(){
    qDebug() << "[II] >> Solve stage 05 <<";

    double& waveBurstSpeed = m_rData.waveBurstSpeed;
    double& airAdiabaticIndex =  m_iData.airAdiabaticIndex;
    double& airFlowSpeed = m_rData.airFlowSpeed;
    double& airSndSpeed = m_rData.airSndSpeed;


    waveBurstSpeed = 0.25*(airAdiabaticIndex + 1)*airFlowSpeed
    + 0.5 * pow(0.25*pow(airAdiabaticIndex + 1,2.)* pow(airFlowSpeed,2.)
            + 4. * pow(airSndSpeed,2.),0.5);

    qDebug() << "     D:" << m_rData.waveBurstSpeed;
}

void LabSolver::solveStage06(){
    qDebug() << "[II] >> Solve stage 06 <<";

    int& tauItCount = m_iData.tauItCount;
    double& alpha = m_iData.alpha;
    double& tauResult = m_rData.tauResult;
    double& dynParamT0 = m_rData.dynParamT0;
    double& dynParamX0 = m_rData.dynParamX0;
    double& airDensity = m_iData.airDensity;
    double& rsDistance = m_rData.rsDistance;
    double& raDistance = m_rData.raDistance;
    double& deltaR     = m_rData.deltaR;
    double& airPressure = m_iData.airPressure;
    double& standoffTime = m_rData.standoffTime;
    double& airAdiabaticIndex = m_iData.airAdiabaticIndex;
    std::vector<double>& tauArray = m_rData.tauArray;
    tauArray.resize(m_iData.tauItCount + 1);

    dynParamT0 = dynParamX0 * pow(airDensity/(airPressure * 1000.0),0.5);
    raDistance = 0.01/pow(alpha, 0.2);

    tauArray[0] = 0.00001;
    deltaR = (rsDistance - raDistance)/ (double)tauItCount;

    for (int i = 1; i < tauItCount + 1; ++i){
        tauArray[i] = tauArray[i-1]
        + (deltaR * 5. * pow(alpha, .5)*pow(raDistance + deltaR*i, 1.5))
                        /(1. + pow(25. * airAdiabaticIndex * alpha
                                    * pow(raDistance + deltaR * i ,2.),.5));
    }
    tauResult = tauArray[m_iData.tauItCount];

    standoffTime = dynParamT0 * tauResult;

    qDebug() << "     T_0:" << m_rData.dynParamT0;
    qDebug() << "     R_alpha:" << m_rData.raDistance;
    qDebug() << "     tau[1]:" << m_rData.tauArray[1];
    qDebug() << "     tau[2]:" << m_rData.tauArray[2];
    qDebug() << "     tau:" << m_rData.tauResult;
    qDebug() << "     T:" << m_rData.standoffTime;
}

void LabSolver::solveStage07(){
    qDebug() << "[II] >> Solve stage 07 <<";

    double& compressImpulse = m_rData.compressImpulse;
    double& airPressure = m_iData.airPressure;
    double& dynParamX0 = m_rData.dynParamX0;
    double& rsDistance = m_rData.rsDistance;
    double& airSndSpeed = m_rData.airSndSpeed;
    double& airFlowSpeed = m_rData.airFlowSpeed;
    double& compressTau = m_rData.compressTau;
    double& waveBurstPressure = m_rData.waveBurstPressure;
    double& airBurstDensity = m_rData.airBurstDensity;
    double& waveBurstSpeed = m_rData.waveBurstSpeed;
    double& airAdiabaticIndex =  m_iData.airAdiabaticIndex;
    double& airDensity = m_iData.airDensity;
    double& flowSpeedPressure = m_rData.flowSpeedPressure;
    double& relativeWaveBurstPressure = m_rData.relativeWaveBurstPressure;
    double& compressImpulseA = m_rData.compressImpulseA;
    double& compressImpulseB = m_rData.compressImpulseB;
    double& humanMass = m_iData.humanMass;
    double& loud = m_rData.loud;

    compressImpulse = .04444*airPressure * 1000* dynParamX0
                                                    / (airSndSpeed*rsDistance);
    compressTau = 2.*compressImpulse/(waveBurstPressure*1000.);

    airBurstDensity = ((airAdiabaticIndex + 1.) * airDensity)
         /((airAdiabaticIndex - 1.)*(1. + 2.*pow(airSndSpeed, 2.)
                         /(pow(waveBurstSpeed, 2.)*(airAdiabaticIndex - 1.))));

    flowSpeedPressure = 0.5 * airBurstDensity * pow(airFlowSpeed, 2.);

    relativeWaveBurstPressure = waveBurstPressure / airPressure;

    compressImpulseA = compressImpulse
                           / (pow(airPressure*1000., .5)*pow(humanMass, 1./3.));

    compressImpulseB = compressImpulse / pow(humanMass, 1./3.);

    const double p0 = 2.E-5; // Порог слышимости по давлению (константа)
    loud  = 20 * std::log10(waveBurstPressure*1000./p0);

    qDebug() << "     i_s:" << m_rData.compressImpulse;
    qDebug() << "     tau_s:" << m_rData.compressTau;
    qDebug() << "     rho_s:" << m_rData.airBurstDensity;
    qDebug() << "     p_ск:" << m_rData.flowSpeedPressure;
    qDebug() << "     P_отн:" << m_rData.relativeWaveBurstPressure;
    qDebug() << "     i'_s:" << m_rData.compressImpulseA;
    qDebug() << "     i''_s:" << m_rData.compressImpulseB;
    qDebug() << "     L_p:" << m_rData.loud;
}

void LabSolver::solveSaveOut(){
    qDebug() << "[II] >> Output results <<";
    // 1. Избыточное давление (p_s) воздуха на фронте ударной волны, кПа.
    m_oData.waveBurstPressure = m_rData.waveBurstPressure;
    // 2. Удельный положительный импульс фазы сжатия.
    m_oData.compressImpulse = m_rData.compressImpulse;
    // 3. Относит. избыт. давление (P_отн) воздуха на фронте уд. волны, кПа.
    m_oData.relativeWaveBurstPressure =m_rData.relativeWaveBurstPressure;
    // 4. Импульс фазы сжатия (i'_s) приведённый к атм. давл. и массе человека
    m_oData.compressImpulseA =m_rData.compressImpulseA;
    // 5. Импульс фазы сжатия, приведённый к масе тела человека
    m_oData.compressImpulseB =m_rData.compressImpulseB ;
    // 6. Уровень звукового давления у приёмника ударной волны, дБ
    m_oData.loud = m_rData.loud;

    qDebug() << "     waveBurstPressure:" <<      m_oData.waveBurstPressure;
    qDebug() << "     compressImpulse:"   <<      m_oData.compressImpulse;
    qDebug() << "     relativeWaveBurstPressure:" <<
                                            m_oData.relativeWaveBurstPressure;
    qDebug() << "     compressImpulseA:"  <<      m_oData.compressImpulseA;
    qDebug() << "     compressImpulseB:"  <<      m_oData.compressImpulseB;
    qDebug() << "     loud:"              <<      m_oData.loud;
}

double LabSolver::getPI(){
    return m_PI;
}

// End labSolver.cpp
