// Begin labDataTypesHA.h

#ifndef LABDATATYPESHA_H
#define LABDATATYPESHA_H 1

#include <vector>
#include <QString>

// Исходные данные для расчёта
struct InputDataHA {
    QString toxicGasName;
    // 1. Молярная масса ядовитого газа (М) [кг/кмоль]
    double toxicGasMolarMass;
    // 2. Показатель адиабаты ядовитого газа (k)
    double toxicGasAdiabaticIndex;
    // 3. Диаметр трубопровода (d) [м]
    double pipelineDiameter;
    // 4. Избыточное давление газа в трубопроводе (р_1) [кПа]
    double pipelineGasPressure;
    // 5. Температура ядовитого газообразного вещества (Т_г) [К]
    double toxicGasTemperature;
    // 6. Температура атмосферного воздуха (Т_в) [К]
    double airTemperature;
    // 7. Cкорость ветра на высоте 10 м (V) [м/с]
    double airSpeed;
    // 8. Класс устойчивости атмосферы по Паскуиллу (К_уст)
    int   airPasquillClass;
    // 9. Эквивалентная шероховатость земной поверхности (z_h) [см]
    double groundRoughness;
    // 10. Высота точки выброса (h) [м]
    double toxicGasEmissionHeight;
    // 11. Расстояние от точки выброса до расчётной по оси X (x) [м]
    double xDistance;
    // 12. Расстояние от оси X до расчётной точки по оси Y (y) [м]
    double yDistance;
    // 13. Время выброса ядовитого газа в атмосферу (tau) [ч]
    double toxicGasEmissionTime;
    // 14. Время нахождения в зоне заражения (tau_з)[ч]
    double exposureTime;
    // 15. Пороговая токсическая доза (D_порог) [мг·мин/м^3]
    double toxicDoseThreshold;

    // Internal application values // Shared input data //
    // 16. Aтмосферное давление (P_0) [кПа]
    double airPressure = 101.3;
    // 17. Молярный объём (V_0) [м^3/кмоль]
    double molarVolume = 22.4;
    // 18. Универсальная газовая постоянная (R_0) [Дж/(кмоль·K)]
    double uniGasConstR = 8314.2;
    // 19. Ускорение свободного падения (g) [м/c^2]
    double gAcceleration = 9.81;
    // 20. Температура при нормальных условиях (T_0) [K]
    double normalTemperature = 273.0;

    // 21. Значения коэффициентов в зависимости
    //     от классов устойчивости атмосферы по Паскуиллу (M-2313 табл. 1)
    // C3
    double getC3() {
        switch (airPasquillClass){
            case 1: return 0.22;
            case 2: return 0.16;
            case 3: return 0.11;
            case 4: return 0.08;
            case 5: return 0.06;
            case 6: return 0.04;
        }
        return 0.0;
    };
    // A1
    double getA1() {
        switch (airPasquillClass){
            case 1: return 0.112;
            case 2: return 0.13;
            case 3: return 0.112;
            case 4: return 0.098;
            case 5: return 0.0609;
            case 6: return 0.0638;
        }
        return 0.0;
    };
    // B1
    double getB1() {
        switch (airPasquillClass){
            case 1: return 1.06;
            case 2: return 0.95;
            case 3: return 0.92;
            case 4: return 0.889;
            case 5: return 0.895;
            case 6: return 0.783;
        }
        return 0.0;
    };
    // A2
    double getA2() {
        switch (airPasquillClass){
            case 1: return 0.000538;
            case 2: return 0.000652;
            case 3: return 0.000905;
            case 4: return 0.001350;
            case 5: return 0.001960;
            case 6: return 0.001360;
        }
        return 0.0;
    };
    // B2
    double getB2() {
        switch (airPasquillClass){
            case 1: return 0.815;
            case 2: return 0.75;
            case 3: return 0.718;
            case 4: return 0.688;
            case 5: return 0.684;
            case 6: return 0.672;
        }
        return 0.0;
    };
    // SigmaMaxZ;
    double getSigmaMaxZ() {
        switch (airPasquillClass){
            case 1: return 1600.0;
            case 2: return 920.0;
            case 3: return 640.0;
            case 4: return 400.0;
            case 5: return 220.0;
            case 6: return 100.0;
        }
        return 0.0;
    };
    // 22. Значения коэффициентов в зависимости
    // от эквивалентной шероховатости земной поверхности (z_h)
    // Z0
    double getZ0(){
        int idx = getTableTwoColIdx();
        switch (idx){
            case 1: return 1.0;
            case 2: return 4.0;
            case 3: return 10.0;
            case 4: return 40.0;
            case 5: return 100.0;
            case 6: return 400.0;
        }
        return 0.0;
    }
    // C1
    double getC1(){
        int idx = getTableTwoColIdx();
        switch (idx){
            case 1: return 1.56;
            case 2: return 2.02;
            case 3: return 2.73;
            case 4: return 5.16;
            case 5: return 7.37;
            case 6: return 11.7;
        }
        return 0.0;
    }
    // D1
    double getD1(){
        int idx = getTableTwoColIdx();
        switch (idx){
            case 1: return 0.048;
            case 2: return 0.0269;
            case 3: return 0.0;
            case 4: return -0.098;
            case 5: return -0.00957;
            case 6: return -0.128;
        }
        return 0.0;
    }
    // C2
    double getC2(){
        int idx = getTableTwoColIdx();
        switch (idx){
            case 1: return 0.000625;
            case 2: return 0.000776;
            case 3: return 0.0;
            case 4: return 0.0538;
            case 5: return 0.000233;
            case 6: return 0.0000218;
        }
        return 0.0;
    }
    // D2
    double getD2(){
        int idx = getTableTwoColIdx();
        switch (idx){
            case 1: return 0.45;
            case 2: return 0.37;
            case 3: return 0.0;
            case 4: return 0.225;
            case 5: return 0.6;
            case 6: return 0.78;
        }
        return 0.0;
    }

    private:
        double getTableTwoColIdx(){
            int idx = 0;
            if (groundRoughness <= 2.0){
                idx = 1;
            }
            else if ( 2.0 < groundRoughness && groundRoughness <= 7.0 ) {
                idx = 2;
            }
            else if ( 7.0 < groundRoughness && groundRoughness  <= 25.0 ){
                idx = 3;
            }
            else if ( 25.0 < groundRoughness && groundRoughness <= 70.0 ){
                idx = 4;
            }
            else if ( 70.0 < groundRoughness && groundRoughness <= 250.0 ){
                idx = 5;
            }
            else if ( 250.0 < groundRoughness && groundRoughness ){
                idx = 6;
            }
            return idx;
        }
};

#endif

// End labDataTypesHA.h
