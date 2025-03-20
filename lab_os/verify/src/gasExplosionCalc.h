// Begin gasExplosionCalc.h
#ifndef GASEXPLOSIONCALC_H
#define GASEXPLOSIONCALC_H 1

#include <QDebug>
#include <cmath>

class GasExplosionCalc {

    public:
        GasExplosionCalc();
        ~GasExplosionCalc();

        // 1. Число атомов углерода в углеводородном газе, ед.
        void setCarbonAtomCount(double&);
        double getCarbonAtomCount();

        // 2. Число атомов водорода в углеводородном газе, ед.
        void setHydrogenAtomCount(double&);
        double getHydrogenAtomCount();

        // 3. Теплота сгорания углеводородного газа, МДж/м^3
        void setGasHeatOfCombustion(double&);
        double getGasHeatOfCombustion();

        // 4. Верхний концентрационный предел воспламенения
        //    углеводородного газа, %
        void setUpperFlammabilityLimit(double&);
        double getUpperFlammabilityLimit();

        // 5. Плотность углеводородного газа при нормальных условиях, кг/м^3
        void setGasDensity(double&);
        double getGasDensity();

        // 6. Нормальная скорость распространения пламени, м/c
        void setNormalFlameSpeed(double&);
        double getNormalFlameSpeed();

        // 7. Масса углеводородного газа, образовавшего огневой шар, т
        void setGasMass(double&);
        double getGasMass();

        // 8. Расстояние от зоны горения до приёмника
        //    инфракрасного излучения, м
        void setDistanceToReceiver(double&);
        double getDistanceToReceiver();

        // 9. Время действия излучения на сетчатку глаза человека, с
        void setEyeRadiationTime(double&);
        double getEyeRadiationTime();

        // Средняя температура зоны горения в первом приближении, град. Цельсия
        double getInitTg(QString stage = "last");
        void   setFirstValueInitTg(double val);

        // Средняя температура зоны горения после уточнения
        double getInitAccurateTg(QString = "last");
        void   setFirstValueInitAccurateTg(double val);

        void getResult();

        double getTheoryOxygenRequire(QString stage = "last");
        double getAirFlowRatio();
        double getVolCO2AtAirFlowRatioEqualOne();
        double getVolH2OAtAirFlowRatioEqualOne();
        double getVolCO2AtAirFlowRatioLessOne(QString stage = "last");
        double getVolCOAtAirFlowRatioLessOne(QString stage = "last");
        double getVolH2OAtAirFlowRatioLessOne(QString stage = "last");
        double getVolH2AtAirFlowRatioLessOne(QString stage = "last");
        double getVolN2AtAirFlowRatioLessOne(QString stage = "last");
        double getVolSumAtAirFlowRatioLessOne(QString stage = "last");
        void setFirstValueVolCO2AtAirFlowRatioLessOne(double);
        void setFirstValueVolCOAtAirFlowRatioLessOne(double);
        void setFirstValueVolH2OAtAirFlowRatioLessOne(double);
        void setFirstValueVolH2AtAirFlowRatioLessOne(double);
        void setFirstValueVolN2AtAirFlowRatioLessOne(double);
        void setFirstValueVolSumAtAirFlowRatioLessOne(double);
        double getMinusLgKp(QString stage = "last");
        void   setFirstValueMinusLgKp(double);
        double getKp(QString stage = "last");
        void   setFirstValueKp(double);
        double getB1(QString stage = "last");
        void   setFirstValueB1(double);
        double getB2(QString stage = "last");
        void   setFirstValueB2(double);
        double getPressureCO2AtAirFlowRationLessOne(QString stage = "last");
        double getPressureCOAtAirFlowRationLessOne(QString stage = "last");
        double getPressureH2OAtAirFlowRationLessOne(QString stage = "last");
        double getPressureH2AtAirFlowRationLessOne(QString stage = "last");
        double getPressureN2AtAirFlowRationLessOne(QString stage = "last");
        double getEnthalpy(QString stage = "last");
        void   setFirstValueEnthalpy(double);
        double getGasHeatLoss(QString stage = "last");
        double getAaccuracyCalcAvgT();
        void   setFirstValueGasHeatLoss(double);
        void   setFirstValuePressureCO2AtAirFlowRationLessOne(double);
        void   setFirstValuePressureCOAtAirFlowRationLessOne(double);
        void   setFirstValuePressureH2OAtAirFlowRationLessOne(double);
        void   setFirstValuePressureH2AtAirFlowRationLessOne(double);
        void   setFirstValuePressureN2AtAirFlowRationLessOne(double);
        int    getCalcIterationCounter();
        double getFireBallRadius();
        double getEffPath();
        double getRayDecreaseFactor();
        double getFireBallBlackness();
        double getFireBallSquare();
        double getFireBallEnergyPower();

        const double m_PI = 3.141592653589793;
        const double m_Sigma = 5.67E-8;
        double getPI();
        double getSigma();
    private:
        // Initial data from users input //
        double m_avgT, m_init_avgT, m_init_accurate_avgT;
        double m_carbonAtomCount;
        double m_hydrogenAtomCount;
        double m_gasHeatOfCombustion;
        double m_uppFlammabilityLimit;
        double m_gasDensity;
        double m_normalFlameSpeed;
        double m_gasMass;
        double m_distanceToReceiver;
        double m_eyeRadiationTime;

        //// Intermediate values for LaTeX ////
        // Удельное теоретическое количество кислорода при полном горении
        // углеводородного газа CxHy (0_1);
        double m_theoryOxygenRequire; //
        // Коэффициент расхода воздуха для первой стадии горения (n)
        double m_airFlowRatio;
        // Удельное количество продуктов горения при N=1 (CO2, H2O)
        double m_volCO2AtAirFlowRatioEqualOne;
        double m_volH2OAtAirFlowRatioEqualOne;

        // Логарифм константы равновесия "lg(k_p)" и сама константа "k_p";
        double m_minusLgKp, m_init_minusLgKp;
        double m_kp, m_init_kp;

        // Вспомогательные величины
        double m_bOne, m_init_bOne;
        double m_bTwo, m_init_bTwo;

        // Удельное количество продуктов горения
        // при N<1 (CO, CO2, H2O, N2, H2, Sum)
        double m_volCOAtAirFlowRatioLessOne,  m_init_volCOAtAirFlowRatioLessOne;
        double m_volN2AtAirFlowRatioLessOne,  m_init_volN2AtAirFlowRatioLessOne;
        double m_volH2AtAirFlowRatioLessOne,  m_init_volH2AtAirFlowRatioLessOne;
        double m_volCO2AtAirFlowRatioLessOne,
                                             m_init_volCO2AtAirFlowRatioLessOne;
        double m_volH2OAtAirFlowRatioLessOne,
                                             m_init_volH2OAtAirFlowRatioLessOne;
        double m_volSumAtAirFlowRatioLessOne,
                                             m_init_volSumAtAirFlowRatioLessOne;

        // Парциальное давление в продуктах горения //
        double m_pressureCO2AtAirFlowRationLessOne,
                                       m_init_pressureCO2AtAirFlowRationLessOne;
        double m_pressureCOAtAirFlowRationLessOne,
                                        m_init_pressureCOAtAirFlowRationLessOne;
        double m_pressureH2OAtAirFlowRationLessOne,
                                       m_init_pressureH2OAtAirFlowRationLessOne;
        double m_pressureH2AtAirFlowRationLessOne,
                                        m_init_pressureH2AtAirFlowRationLessOne;
        double m_pressureN2AtAirFlowRationLessOne,
                                        m_init_pressureN2AtAirFlowRationLessOne;

        // Энтальпия продуктов сгорания при 2200 град. Цельсия
        double m_enthalpy, m_init_enthalpy;

        double m_gasHeatLoss, m_init_gasHeatLoss;

        // Точность уточнения температуры на 4-ом этапе;
        double m_accuracyCalcAvgT = 0.1;

        // Счётчик итераций на 4-ом этапе
        int m_calcIterationCounter;

        // Средний радиус зоны горения (огневого шара)
        double m_fireBallRadius;

        // Эффективная длина луча в огневом шаре
        double m_effPath;

        // Коэффициент ослабления лучей
        double m_rayDecreaseFactor;

        // Степень черноты огневого шара
        double m_fireBallBlackness;

        // Площадь внешней поверхности огневого шара;
        double m_fireBallSquare;

        // Поток энергии инфракрасного излучения огневого шара
        double m_fireBallEnergyPower;

        void runStage01(double initT = 1400.0);
        void runStage02();
        void runStage03();
        void runStage04();
        void runStage05();
        void runStage06();
        void runStage07();

};




#endif
// End gasExplosionCalc.h
