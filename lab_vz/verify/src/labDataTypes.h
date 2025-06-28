// Begin labInputs.h
#ifndef LABINPUTS_H
#define LABINPUTS_H 1

#include <vector>

// Исходные данные для расчёта
struct InputData {
    // 1. Диаметр цилиндрического резервуара со сжатым газом, м.
    double gasTankDiameter;
    // 2. Длина цилиндрического резервуара со сжатым газом, м.
    double gasTankLength;
    // 3. Показатель адиабаты сжатого газа в резервуаре.
    double gasAdiabaticIndex;
    // 4. Избыточное давление сжатого газа в резервуаре при взрыве, кПа
    double tankBurstPressure;
    // 5. Плотность газа при нормальных условиях, кг/м^3.
    double ntpTankGasDensity;
    // 6. Температура воздуха, град. Цельсия.
    double airTemperature;
    // 7. Коэффициент перехода
    double releaseFraction;
    // 8. Расстояние от центра взрывной системы до приёмника уд. волны, м.
    double standoffDistance;
    // 9. Атмосферное давление, кПа.
    double airPressure;
    // 10. Показатель адиабаты воздуха.
    double airAdiabaticIndex;
    // 11. Плотность воздуха, кг/м^3.
    double airDensity;
    // 12. Удельная энергия взрывчатого разложения тротилла, кДж/кг.
    double tntSpecificEnergy;
    // 13. Энергетический параметр (alpha) взрыва.
    double alpha;
    // 14. Итерационная глубина при расчёте безразмерного времени.
    int tauItCount;
    // 15. Масса тела человека, кг.
    double humanMass;
};

// Итоговые резуальтаты расчёта
struct OutData{
    // 1. Избыточное давление (p_s) воздуха на фронте ударной волны, кПа.
    double waveBurstPressure;
    // 2. Удельный положительный импульс фазы сжатия.
    double compressImpulse;
    // 3. Относит. избыт. давление (P_отн) воздуха на фронте уд. волны, кПа.
    double relativeWaveBurstPressure;
    // 4. Импульс фазы сжатия (i'_s) приведённый к атм. давл. и массе человека
    double compressImpulseA;
    // 5. Импульс фазы сжатия, приведённый к масе тела человека
    double compressImpulseB;
    // 6. Уровень звукового давления у приёмника ударной волны, дБ
    double loud;
};

// Промежуточные данные с ходом расчёта
struct RawData{
    // Абсолютное давление (P_1) газа в сосуде перед взрывом, кПа.
    double absTankBurstPressure ;
    // Объём (V_г) сосуда с газом, м^3.
    double tankVolume;
    // Потенциальная энергия (E_п) взрывной системы, кДж.
    double burstEnergy;
    // Тротилловый эквивалент взрыва, кг.
    double tntEquivalent;
    // Динамический параметр (X_0), м.
    double dynParamX0;
    // Безразмерное расстояние (R_s) от центра взрыва до фронта ударной волны.
    double rsDistance;
    // Избыточное давление (p_s) воздуха на фронте ударной волны, кПа.
    double waveBurstPressure;
    // Скорость звука при атмосферном давлении, м/с.
    double airSndSpeed;
    // Скорость воздушного потока (V_s), м/c.
    double airFlowSpeed;
    // Скорость движения фронта (D) ударной волны, м/с.
    double waveBurstSpeed;
    // Динамический параметр времени (T_0), с.
    double dynParamT0;
    // Безразмерное расстояние (R_alpha), зависящее от энергетического параметра
    double raDistance;
    // Величина dR для итерационного цикла от 1 до 500
    double deltaR;
    // Безразмерное время (tau).
    double tauResult;
    // Массив итерационных величин безразмерного времени (tau).
    std::vector<double> tauArray;
    // Время (T) перемещения волны от центра взрывной системы до приёмника.
    double standoffTime;
    // Удельный положительный импульс фазы сжатия.
    double compressImpulse;
    // Длительность фазы сжатия (tau_s), с.
    double compressTau;
    // Плотность воздуха при давлении на фронте ударной волны (rho_s), кг/м^3.
    double airBurstDensity;
    // Динамический (скоростной) напор (p_ск) воздуха на твёрдую преграду, Па.
    double flowSpeedPressure;
    // Относительное избыт. давление (P_отн) воздуха на фронте уд. волны, кПа.
    double relativeWaveBurstPressure;
    // Импульс фазы сжатия (i'_s) приведённый к атм. давлению и массе человека
    double compressImpulseA;
    // Импульс фазы сжатия, приведённый к масе тела человека
    double compressImpulseB;
    // Уровень звукового давления у приёмника ударной волны, дБ
    double loud;
};

#endif
// End labInputs.h
