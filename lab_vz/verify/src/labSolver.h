// Begin labSolver.h
#ifndef LABSOLVER_H
#define LABSOLVER_H 1

#include <QDebug>
#include "labDataTypes.h"

class LabSolver {
    public:
        LabSolver();
        ~LabSolver();

        // Запуск расчёта (получить решение)
        void getSolve();

        void setInputData(const InputData&);
        InputData getInputData();
        OutData getOutData();
        RawData getRawData();

    private:
        InputData m_iData; // Входящие данные для расчёта;
        OutData   m_oData; // Результаты расчёта
        RawData   m_rData; // Промежуточные расчётные данные

        void solveStage01();
        void solveStage02();
        void solveStage03();
        void solveStage04();
        void solveStage05();
        void solveStage06();
        void solveStage07();
        void solveSaveOut();
};

#endif
// End labSolver.h
