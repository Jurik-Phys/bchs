// Begin texBuilder.h

#ifndef TEXBUILDER_H
#define TEXBUILDER_H 1

#include "labSolver.h"
#include "labDataInput.h"


class TeXBuilder {

    public:
        TeXBuilder();
        ~TeXBuilder();

        void init(LabSolver*);
        QString getInitDataTeX(QString str = "Ручной ввод данных");
        QString getStage01_BurstEnergyTeX();
        QString getStage02_TNTEquivalentTeX();
        QString getStage03_WaveBurstPressureTeX();
        QString getStage04_AirFlowSpeedTeX();
        QString getStage05_WaveBurstSpeedTeX();
        QString getStage06_StandoffTimeTeX();
        QString getStage07_FinalizeSolutionTeX();
        QString getResultsTeX();

    private:
        LabSolver* m_labSolver;
        QString getNumericString(double, QString fmt = "short");

        InputData m_iData; // Входящие данные для расчёта;
        OutData   m_oData; // Результаты расчёта
        RawData   m_rData; // Промежуточные расчётные данные
};

#endif
// End texBuilder.h
