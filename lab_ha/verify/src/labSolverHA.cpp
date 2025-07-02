// Begin labSolverHA.cpp

#include "labSolverHA.h"

LabSolverHA::LabSolverHA(){
}

LabSolverHA::~LabSolverHA(){
}

void LabSolverHA::setInputData(const InputDataHA& iData){
    m_iData = iData;
}

void LabSolverHA::getSolve(){
    InputDataHA& iData = m_iData;
    qDebug() << "[II] Start LabSolverHA...";
    qDebug() << "[II] Input data values:";
    qDebug() << "     toxicGasMolarMass:     " << iData.toxicGasMolarMass;
    qDebug() << "     toxicGasAdiabaticIndex:" << iData.toxicGasAdiabaticIndex;
    qDebug() << "     pipelineDiameter:      " << iData.pipelineDiameter;
    qDebug() << "     pipelineGasPressure:   " << iData.pipelineGasPressure;
    qDebug() << "     toxicGasTemperature:   " << iData.toxicGasTemperature;
    qDebug() << "     airTemperature:        " << iData.airTemperature;
    qDebug() << "     airSpeed:              " << iData.airSpeed;
    qDebug() << "     airPasquillClass:      " << iData.airPasquillClass;
    qDebug() << "     groundRoughness:       " << iData.groundRoughness;
    qDebug() << "     toxicGasEmissionHeight:" << iData.toxicGasEmissionHeight;
    qDebug() << "     xDistance:             " << iData.xDistance;
    qDebug() << "     yDistance:             " << iData.yDistance;
    qDebug() << "     toxicGasEmissionTime:  " << iData.toxicGasEmissionTime;
    qDebug() << "     exposureTime:          " << iData.exposureTime;
    qDebug() << "     toxicDoseThreshold:    " << iData.toxicDoseThreshold;
    qDebug() << "     // Shared data //";
    qDebug() << "     airPressure:           " << iData.airPressure;
    qDebug() << "     toxicGasMolarVolume:   " << iData.toxicGasMolarVolume;
    qDebug() << "     uniGasConstR:          " << iData.uniGasConstR;
    qDebug() << "     gAcceleration:         " << iData.gAcceleration;
    qDebug() << "     normalTemperature:     " << iData.normalTemperature;
    qDebug() << "     valueC3:               " << iData.valC3;
    qDebug() << "     valueA1:               " << iData.valA1;
    qDebug() << "     valueB1:               " << iData.valB1;
    qDebug() << "     valueA2:               " << iData.valA2;
    qDebug() << "     valueB2:               " << iData.valB2;
    qDebug() << "     valSigmaZMax:          " << iData.valSigmaZMax;
    qDebug() << "     valueZ0:               " << iData.valZ0;
    qDebug() << "     valueC1:               " << iData.valC1;
    qDebug() << "     valueD1:               " << iData.valD1;
    qDebug() << "     valueC2:               " << iData.valC2;
    qDebug() << "     valueD2:               " << iData.valD2;

    solveStage01_toxicGasMaxFlowPressure();
    solveStage02_toxicGasFlowRate();
    solveStage03_toxicGasFlowSpeedAndHeight();
    solveStage04_toxicGasFlowSigmaY();
    solveStage05_toxicGasFlowSigmaZ();
    solveStage06_toxicGasDilutionFactor();
    solveStage07_toxicGasConcentration();
    solveStage08_receivedToxicDose();
    solveStage09_toxicZone();
}

void LabSolverHA::solveStage01_toxicGasMaxFlowPressure(){
    // 1. Расчет критического давления (Р_ист^крит) при истечении газа
    //    через отверстие, равное диаметру трубопровода, кПа
    qDebug() << "[II] Start Solve stage 01";

    double& toxicGasAdiabaticIndex = m_iData.toxicGasAdiabaticIndex;
    double& airPressure = m_iData.airPressure;
    double& toxicGasMaxFlowPressure = m_rData.toxicGasMaxFlowPressure;


    toxicGasMaxFlowPressure = airPressure /
        (pow(2.0/(toxicGasAdiabaticIndex + 1.0),
                        toxicGasAdiabaticIndex/(toxicGasAdiabaticIndex - 1.0)));
    qDebug() << "     toxicGasMaxFlowPressure:" << toxicGasMaxFlowPressure;
}

void LabSolverHA::solveStage02_toxicGasFlowRate(){
    // 2.  Определение секундного количества истекающего в атмосферу газа.
    qDebug() << "[II] Start Solve stage 02";

    double& toxicGasAdiabaticIndex = m_iData.toxicGasAdiabaticIndex;
    double& absPipelineGasPressure = m_rData.absPipelineGasPressure;
    double& airPressure = m_iData.airPressure;
    double& pipelineGasPressure = m_iData.pipelineGasPressure;
    double& toxicGasPipelineDensity = m_rData.toxicGasPipelineDensity;
    double& toxicGasMaxFlowDensity = m_rData.toxicGasMaxFlowDensity;
    double& toxicGasMolarMass = m_iData.toxicGasMolarMass;
    double& toxicGasMolarVolume = m_iData.toxicGasMolarVolume;
    double& toxicGasStdDensity  = m_rData.toxicGasStdDensity;
    double& normalTemperature = m_iData.normalTemperature;
    double& toxicGasTemperature = m_iData.toxicGasTemperature;
    double& toxicGasMaxFlowPressure = m_rData.toxicGasMaxFlowPressure;
    double& pipelineSquare = m_rData.pipelineSquare;
    double& PI = m_iData.PI;
    double& pipelineDiameter = m_iData.pipelineDiameter;
    double& toxicGasFlowRateS = m_rData.toxicGasFlowRateS;
    double& toxicGasFlowRateH = m_rData.toxicGasFlowRateH;

    absPipelineGasPressure = pipelineGasPressure + airPressure;

    toxicGasStdDensity = toxicGasMolarMass / toxicGasMolarVolume;

    toxicGasPipelineDensity = toxicGasStdDensity *
                                (absPipelineGasPressure / airPressure) *
                                (normalTemperature / toxicGasTemperature);

    toxicGasMaxFlowDensity = toxicGasStdDensity *
                                (toxicGasMaxFlowPressure / airPressure) *
                                    (normalTemperature / toxicGasTemperature);

    pipelineSquare = PI * pow(pipelineDiameter, 2.0) / 4.0;

    if (absPipelineGasPressure <= toxicGasMaxFlowPressure){
        toxicGasFlowRateS = pipelineSquare *
            pow((2.0 * toxicGasAdiabaticIndex / (toxicGasAdiabaticIndex - 1.))*
            absPipelineGasPressure * 1000. * toxicGasPipelineDensity *
            (pow(airPressure/absPipelineGasPressure, 2./toxicGasAdiabaticIndex)-
                 pow(airPressure/absPipelineGasPressure,
                     (toxicGasAdiabaticIndex + 1)/toxicGasAdiabaticIndex)), .5);
    }
    else {
        toxicGasFlowRateS = pipelineSquare *
            pow((2.0 * toxicGasAdiabaticIndex / (toxicGasAdiabaticIndex + 1.))*
                toxicGasMaxFlowPressure * 1000. * toxicGasMaxFlowDensity *
                pow(2./(toxicGasAdiabaticIndex + 1),
                    (2./toxicGasAdiabaticIndex -1. )), .5);
    }

    toxicGasFlowRateH = toxicGasFlowRateS * 3600.0;

    qDebug() << "     absPipelineGasPressure: " << absPipelineGasPressure;
    qDebug() << "     toxicGasStdDensity:     " << toxicGasStdDensity;
    qDebug() << "     toxicGasPipelineDensity:" << toxicGasPipelineDensity;
    qDebug() << "     toxicGasMaxFlowDensity: " << toxicGasMaxFlowDensity;
    qDebug() << "     pipelineSquare:         " << pipelineSquare;
    qDebug() << "     toxicGasFlowRateS:      " << toxicGasFlowRateS;
    qDebug() << "     toxicGasFlowRateH:      " << toxicGasFlowRateH;

}

void LabSolverHA::solveStage03_toxicGasFlowSpeedAndHeight(){
    // 3.  Расчет скорости истечения газа из трубопровода
    //     и начальной высоты подъема частиц газа в воздухе.
    qDebug() << "[II] Start Solve stage 03";

    double& toxicGasConstR = m_rData.toxicGasConstR;
    double& toxicGasMolarMass = m_iData.toxicGasMolarMass;
    double& uniGasConstR = m_iData.uniGasConstR;
    double& absPipelineGasPressure = m_rData.absPipelineGasPressure;
    double& toxicGasMaxFlowPressure = m_rData.toxicGasMaxFlowPressure;
    double& pipelineSquare = m_rData.pipelineSquare;
    double& toxicGasPipelineDensity = m_rData.toxicGasPipelineDensity;
    double& toxicGasMaxFlowDensity = m_rData.toxicGasMaxFlowDensity;
    double& toxicGasFlowSpeed = m_rData.toxicGasFlowSpeed;
    double& toxicGasFlowVolumeSpeed = m_rData.toxicGasFlowVolumeSpeed;
    double& toxicGasFlowRateS = m_rData.toxicGasFlowRateS;
    double& toxicGasAdiabaticIndex = m_iData.toxicGasAdiabaticIndex;
    double& toxicGasTemperature = m_iData.toxicGasTemperature;
    double& toxicGasEmissionDeltaHeight = m_rData.toxicGasEmissionDeltaHeight;
    double& airTemperature = m_iData.airTemperature;
    double& airSpeed = m_iData.airSpeed;
    double& gAcceleration = m_iData.gAcceleration;
    double& toxicGasEmissionEffectiveHeight = m_rData.
                                                toxicGasEmissionEffectiveHeight;
    double& toxicGasEmissionHeight = m_iData.toxicGasEmissionHeight;

    toxicGasConstR = uniGasConstR / toxicGasMolarMass;

    if (absPipelineGasPressure <= toxicGasMaxFlowPressure){
        toxicGasFlowSpeed = toxicGasFlowRateS /
                (toxicGasPipelineDensity * pipelineSquare);
        toxicGasFlowVolumeSpeed = toxicGasFlowRateS / toxicGasPipelineDensity;
    }
    else {
        toxicGasFlowSpeed = pow( (2 * toxicGasAdiabaticIndex /
                        (toxicGasAdiabaticIndex + 1.)) * toxicGasConstR *
                                                    toxicGasTemperature, .5);
        toxicGasFlowVolumeSpeed = toxicGasFlowRateS / toxicGasMaxFlowDensity;
    }

    toxicGasEmissionDeltaHeight = 1.6*gAcceleration*toxicGasFlowVolumeSpeed *
        (toxicGasTemperature - airTemperature) /
            (airTemperature * pow(airSpeed, 3.));

    toxicGasEmissionEffectiveHeight = toxicGasEmissionDeltaHeight +
                                                        toxicGasEmissionHeight;

    qDebug() << "     toxicGasFlowSpeed:  " << toxicGasFlowSpeed;
    qDebug() << "     tGasFlowVolumeSpeed:" << toxicGasFlowVolumeSpeed;
    qDebug() << "     tGasEmissionEHeight:" << toxicGasEmissionEffectiveHeight;
}

double LabSolverHA::getSigmaY(const double& xDistance){
    double& valC3 = m_iData.valC3;
    return valC3 * xDistance * pow( 1. + 0.0001 * xDistance, .5);
}

void LabSolverHA::solveStage04_toxicGasFlowSigmaY(){
    // 4. Определение стандартного отклонения (\sigma_Y) распределения
    //    примеси в облаке выброса в направлении оси Y, м.
    qDebug() << "[II] Start Solve stage 04";

    double& xDistance = m_iData.xDistance;
    double& toxicGasFlowSigmaY = m_rData.toxicGasFlowSigmaY;

    toxicGasFlowSigmaY = getSigmaY(xDistance);

    qDebug() << "      toxicGasFlowSigmaY:" << toxicGasFlowSigmaY;
}

double LabSolverHA::getSigmaZ(const double& xDistance){
    double sigmaZ;
    double& valZ0 = m_iData.valZ0;
    double& valA1 = m_iData.valA1;
    double& valB1 = m_iData.valB1;
    double& valA2 = m_iData.valA2;
    double& valB2 = m_iData.valB2;
    double& valC1 = m_iData.valC1;
    double& valC2 = m_iData.valC2;
    double& valD1 = m_iData.valD1;
    double& valD2 = m_iData.valD2;
    double& valSigmaZMax = m_iData.valSigmaZMax;

    if (valZ0 > 10){
        sigmaZ = (valA1 * pow(xDistance, valB1)/
            (1. + valA2 * pow(xDistance, valB2))) *
                        log(valC1 * pow(xDistance, valD1) *
                                        (1. + valC2 * pow(xDistance, valD2)));
    }
    else {
        sigmaZ = (valA1 * pow(xDistance, valB1)/
            (1. + valA2 * pow(xDistance, valB2))) *
                        log(valC1 * pow(xDistance, valD1) /
                                        (1. + valC2 * pow(xDistance, valD2)));
    }

    if (sigmaZ > valSigmaZMax){
        sigmaZ  = valSigmaZMax;
        qDebug() << "            valSigmaZMax:" << valSigmaZMax;
    }

    return sigmaZ;
}

void LabSolverHA::solveStage05_toxicGasFlowSigmaZ(){
    // 5.  Расчет стандартного отклонения (\sigma_Z) распределения
    //     примеси в облаке выброса в направлении оси Z, м.
    qDebug() << "[II] Start Solve stage 05";

    double& xDistance = m_iData.xDistance;
    double& toxicGasFlowSigmaZ = m_rData.toxicGasFlowSigmaZ;

    toxicGasFlowSigmaZ = getSigmaZ(xDistance);
}

double LabSolverHA::getDilutionFactor(const double& x, const double& y){
    double dilutionFactor;

    double& PI = m_iData.PI;
    double& airSpeed = m_iData.airSpeed;
    double& toxicGasEmissionEffectiveHeight = m_rData.
                                                toxicGasEmissionEffectiveHeight;
    double  toxicGasFlowSigmaY = getSigmaY(x);
    double  toxicGasFlowSigmaZ = getSigmaZ(x);

    dilutionFactor = (1.0/(PI*toxicGasFlowSigmaY*toxicGasFlowSigmaZ*airSpeed))*
        exp((-1. * pow(y, 2.) / (2. * pow(toxicGasFlowSigmaY, 2. ))) -
                                (pow(toxicGasEmissionEffectiveHeight, 2.) /
                                            (2.*pow(toxicGasFlowSigmaZ, 2.))));

    return dilutionFactor;
}

void LabSolverHA::solveStage06_toxicGasDilutionFactor(){
    // 6. Фактор разбавления в облаке для концентраций на уровне земли, с/м^3.
    qDebug() << "[II] Start Solve stage 06";

    double& yDistance = m_iData.yDistance;
    double& xDistance = m_iData.xDistance;
    double& toxicGasDilutionFactor = m_rData.toxicGasDilutionFactor;

    toxicGasDilutionFactor = getDilutionFactor(xDistance, yDistance);
    qDebug() << "  toxicGasDilutionFactor:" << toxicGasDilutionFactor;
}

double LabSolverHA::getToxicGasConcentration(const double& x, const double& y){
    double& toxicGasFlowRateS = m_rData.toxicGasFlowRateS;
    return toxicGasFlowRateS * getDilutionFactor(x, y);
}

void LabSolverHA::solveStage07_toxicGasConcentration(){
    // 7.  Расчет концентрации газа в точке с координатами
    //     {xDistance, yDistance, z = 0}.
    qDebug() << "[II] Start Solve stage 07";

    double& xDistance = m_iData.xDistance;
    double& yDistance = m_iData.yDistance;
    double& toxicGasConcentrationAtPoint = m_rData.toxicGasConcentrationAtPoint;

    toxicGasConcentrationAtPoint=getToxicGasConcentration(xDistance,yDistance);

    qDebug() << "toxicGasConcentrationAtPoint:" << toxicGasConcentrationAtPoint;
}

double LabSolverHA::getReceivedToxicDose(const double& x, const double& y){
    double& exposureTime = m_iData.exposureTime;
    return exposureTime * 60 * getToxicGasConcentration(x, y) * 1.0E6;
}

void LabSolverHA::solveStage08_receivedToxicDose(){
    // 8.   Определение токсической дозы при известном времени ингаляции
    //      зараженного воздуха (D), мг∙мин/м^3.
    qDebug() << "[II] Start Solve stage 08";

    double& xDistance = m_iData.xDistance;
    double& yDistance = m_iData.yDistance;
    double& receivedToxicDose = m_rData.receivedToxicDose;

    receivedToxicDose = getReceivedToxicDose(xDistance, yDistance);

    qDebug() << "       receivedToxicDose:" << receivedToxicDose;
}

double LabSolverHA::getToxicZoneHalfWidth(const double& x,
                                              const double& toxicDoseThreshold){
    double tZoneHalfWidth;
    double& exposureTime = m_iData.exposureTime;
    double& airSpeed = m_iData.airSpeed;
    double& toxicGasFlowRateS = m_rData.toxicGasFlowRateS;
    double& toxicGasEmissionEffectiveHeight = m_rData.
                                                toxicGasEmissionEffectiveHeight;

    double sigmaY = getSigmaY(x);
    double sigmaZ = getSigmaZ(x);
    double& PI = m_iData.PI;

    tZoneHalfWidth = pow( 2. * pow(sigmaY, 2.) *
            (-1.*(log( toxicDoseThreshold * PI * sigmaY * sigmaZ * airSpeed /
                (toxicGasFlowRateS * exposureTime * 60 * 1E6))) -
                                (pow(toxicGasEmissionEffectiveHeight, 2.) /
                                                (2. * pow(sigmaZ, 2.)))), .5);
    return tZoneHalfWidth;
}

void LabSolverHA::solveStage09_toxicZone(){
    // 9.  Расчет зоны заражения, в которой значение токсической дозы
    //     выше пороговой.
    qDebug() << "[II] Start Solve stage 09";

    double& toxicDoseThresholdExample = m_iData.toxicDoseThresholdExample;
    double& toxicDoseThreshold = m_iData.toxicDoseThreshold;
    double& xDistance = m_iData.xDistance;
    double& yDistance = m_iData.yDistance;
    double& toxicZoneHalfWidthExample = m_rData.toxicZoneHalfWidthExample;

    toxicZoneHalfWidthExample = getToxicZoneHalfWidth(xDistance,
                                                    toxicDoseThresholdExample);

    qDebug() << "toxicZoneHalfWidthExample:" << toxicZoneHalfWidthExample;

    // 9A. Поиск безопасного расстояния для выбранного времени ингаляции
    double x = 0.0;
    double tempReceivedToxicDose = toxicDoseThreshold; // getReceivedToxicDose(xDistance, yDistance);
    double tempToxicZoneHalfWidth;

    while(tempReceivedToxicDose >= toxicDoseThreshold){
        x += 10;
        tempReceivedToxicDose = getReceivedToxicDose(x, yDistance);
    }

    // 9B. Расчёт полуширины зоны заражения
    std::vector<double>& xDistanceArray = m_rData.xDistanceArray;
    std::vector<double>& toxicZoneHalfWidthArray = m_rData.
                                                        toxicZoneHalfWidthArray;

    int nCell = 15;
    int dX = int(x/nCell) + 1;
    for (int n = 0; n < nCell + 1; ++n){
        if (n != 0){
            tempReceivedToxicDose = getReceivedToxicDose(n*dX, yDistance);
            if (tempReceivedToxicDose > toxicDoseThreshold) {
                tempToxicZoneHalfWidth = getToxicZoneHalfWidth(n*dX,
                        toxicDoseThreshold);
            }
            else {
                tempToxicZoneHalfWidth = 0;
            }
        }
        else {
            tempToxicZoneHalfWidth = 0;
        }
        xDistanceArray.push_back(n*dX);
        toxicZoneHalfWidthArray.push_back(tempToxicZoneHalfWidth);
    }

    for (int i = 0; i < xDistanceArray.size(); ++i){
        qDebug() << "  N =" << i << "X =" << xDistanceArray[i];
        qDebug() << "  tempToxicZoneHalfWidth:" << toxicZoneHalfWidthArray[i];
    }
}

// End labSolverHA.cpp
