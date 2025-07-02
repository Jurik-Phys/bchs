// Begin labSolverHA.h

#ifndef LABSOLVERHA_H
#define LABSOLVERHA_H 1

#include <QDebug>
#include "labDataInputHA.h"

class LabSolverHA {
    public:
        LabSolverHA();
        ~LabSolverHA();

        void setInputData(const InputDataHA&);

        void getSolve();
    private:
        InputDataHA m_iData;
        RawDataHA   m_rData;
        OutDataHA   m_oData;

        void solveStage01_toxicGasMaxFlowPressure();
        void solveStage02_toxicGasFlowRate();
        void solveStage03_toxicGasFlowSpeedAndHeight();
        void solveStage04_toxicGasFlowSigmaY();
        void solveStage05_toxicGasFlowSigmaZ();
        void solveStage06_toxicGasDilutionFactor();
        void solveStage07_toxicGasConcentration();
        void solveStage08_receivedToxicDose();
        void solveStage09_toxicZone();

        double getSigmaY(const double&);
        double getSigmaZ(const double&);
        double getDilutionFactor(const double&, const double&);
        double getToxicGasConcentration(const double&, const double&);
        double getReceivedToxicDose(const double&, const double&);
        double getToxicZoneHalfWidth(const double&, const double&);
};

#endif

// End labSolverHA.h
