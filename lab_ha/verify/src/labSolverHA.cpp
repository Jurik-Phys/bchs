// Begin labSolverHA.cpp

#include "labSolverHA.h"

labSolverHA::labSolverHA(){
}

labSolverHA::~labSolverHA(){
}

void labSolverHA::getSolve(){
    InputDataHA iData = labDataVariants[0];
    qDebug() << "[II] Start labSolverHA...";
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
    qDebug() << "     molarVolume:           " << iData.molarVolume;
    qDebug() << "     uniGasConstR:          " << iData.uniGasConstR;
    qDebug() << "     gAcceleration:         " << iData.gAcceleration;
    qDebug() << "     normalTemperature:     " << iData.normalTemperature;
    qDebug() << "     valueC3:               " << iData.getC3();
    qDebug() << "     valueA1:               " << iData.getA1();
    qDebug() << "     valueB1:               " << iData.getB1();
    qDebug() << "     valueA2:               " << iData.getA2();
    qDebug() << "     valueB2:               " << iData.getB2();
    qDebug() << "     valueSigmaMaxZ:        " << iData.getSigmaMaxZ();
    qDebug() << "     valueZ0:               " << iData.getZ0();
    qDebug() << "     valueC1:               " << iData.getC1();
    qDebug() << "     valueD1:               " << iData.getD1();
    qDebug() << "     valueC2:               " << iData.getC2();
    qDebug() << "     valueD2:               " << iData.getD2();
}

// End labSolverHA.cpp
