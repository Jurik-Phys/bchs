// Begin gasExplosionCalc.h
#ifndef GASEXPLOSIONCALC_H
#define GASEXPLOSIONCALC_H 1

#include <QDebug>
#include <cmath>

class GasExplosionCalc {

    public:
        GasExplosionCalc();
        ~GasExplosionCalc();

        // 1. "Число атомов углерода в углеводородном газе, ед."
        void setCarbonAtomCount(double&);
        double getCarbonAtomCount();

        // 2. "Число атомов водорода в углеводородном газе, ед." <<
        void setHydrogenAtomCount(double&);
        double getHydrogenAtomCount();

        // 3. "Теплота сгорания углеводородного газа, МДж/м^3" <<
        void setGasHeatOfCombustion(double&);
        double getGasHeatOfCombustion();

        // 4. "Верхний концентрационный предел воспламенения углеводородного газа, %" <<
        void setUpperFlammabilityLimit(double&);
        double getUpperFlammabilityLimit();

        // 5. "Плотность углеводородного газа при нормальных условиях, кг/м^3" <<
        void setGasDensity(double&);
        double getGasDensity();

        // 6. "Нормальная скорость распространения пламени, м/c" <<
        void setNormalFlameSpeed(double&);
        double getNormalFlameSpeed();

        // 7. "Масса углеводородного газа, образовавшего огневой шар, т" <<
        void setGasMass(double&);
        double getGasMass();

        // 8. "Расстояние от зоны горения до приёмника инфракрасного излучения, м" <<
        void setDistanceToReceiver(double&);
        double getDistanceToReceiver();

        // 9. "Время действия излучения на сетчатку глаза человека, с";
        void setEyeRadiationTime(double&);
        double getEyeRadiationTime();

        void getResult();

    private:
        // Initial data from users input //
        double m_avgT;
        double m_carbonAtomCount;
        double m_hydrogenAtomCount;
        double m_gasHeatOfCombustion;
        double m_upperFlammabilityLimit;
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
        double m_lgKp;
        double m_kp;

        // Вспомогательные величины
        double m_bOne;
        double m_bTwo;

        // Удельное количество продуктов горения при N<1 (CO, CO2, H2O, N2, H2, Sum)
        double m_volCOAtAirFlowRatioLessOne;
        double m_volN2AtAirFlowRatioLessOne;
        double m_volH2AtAirFlowRatioLessOne;
        double m_volCO2AtAirFlowRatioLessOne;
        double m_volH2OAtAirFlowRatioLessOne;
        double m_volSumAtAirFlowRatioLessOne;

        // Парциальное давление в продуктах горения //
        double m_pressureCO2AtAirFlowRationLessOne;
        double m_pressureCOAtAirFlowRationLessOne;
        double m_pressureH2OAtAirFlowRationLessOne;
        double m_pressureH2AtAirFlowRationLessOne;
        double m_pressureN2AtAirFlowRationLessOne;
};




#endif
// End gasExplosionCalc.h
