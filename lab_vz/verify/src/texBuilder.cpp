// Begin texBuilder.cpp

#include "texBuilder.h"

TeXBuilder::TeXBuilder(){
}

TeXBuilder::~TeXBuilder(){
}

void TeXBuilder::init(LabSolver* solver){
    m_labSolver = solver;

    m_iData = m_labSolver->getInputData();
    m_oData = m_labSolver->getOutData();
    m_rData = m_labSolver->getRawData();
}

QString TeXBuilder::getInitDataTeX(QString str1){
    QString res;
    res = R"(
        \text{%1:} \\
        \text{ - диаметр цилиндрического резервуара со сжатым газом d = %2 м;}\\
        \text{ - длина цилиндрического резервуара со сжатым газом l = %3 м;} \\
        \text{ - показатель адиабаты сжатого газа в резервуаре }
        \text{$k_\text{г} = %4$;} \\
        \text{ - избыточное давление сжатого газа в резервуаре }
        p_1 = %5 \text{ кПа}; \\
        \text{ - плотность газа при нормальных условиях $\rho_\text{г} = %6$}
        \text{кг/м$^3$}; \\
        \text{ - температура воздуха $t = %7^{\text{\LARGE{\circ}}}$C;} \\
        \text{ - коэффициент перехода $k_\text{ув} = %8$;} \\
        \text{ - расстояние от центра взрыва системы до приёмника ударной }
        \text{волны $R_\text{пр} = %9$ м.} \\
    )";

    const InputData& iData = m_labSolver->getInputData();
    QString str2 = getNumericString(iData.gasTankDiameter, "three");
    QString str3 = getNumericString(iData.gasTankLength, "three");
    QString str4 = getNumericString(iData.gasAdiabaticIndex, "two");
    QString str5 = getNumericString(iData.tankBurstPressure, "one");
    QString str6 = getNumericString(iData.ntpTankGasDensity, "two");
    QString str7 = getNumericString(iData.airTemperature, "one");
    QString str8 = getNumericString(iData.releaseFraction, "two");
    QString str9 = getNumericString(iData.standoffDistance, "one");


    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6).
              arg(str7).arg(str8).arg(str9);
    return res;
}

QString TeXBuilder::getStage01_BurstEnergyTeX(){
    QString res;
    res = R"(\text{Алгоритм расчёта параметров ударной волны.} \\
    \text{1. Определяется значение энергии $(E_\text{п})$ аварийного взрыва }
    \text{резервуара} \\
    \text{с нереагирующим газом высокого давления.} \\
    \text{    Абсолютное давление $(P_1)$ газа в сосуде непосредственно перед }
    \text{взрывом, кПа.} \\
    \begin{gather}
        P_1 = p_1 + P_0 = %1 + %2 = %3;
    \end{gather} \\

    \text{где $P_0$ - атмосферное давление, $P_0 = %2$, кПа.} \\
    \text{    Объём $(V_\text{г})$ сосуда с газом, м$^3$.} \\
    \begin{gather}
        V_\text{г} = \pi \cdot \left(\frac{d}{2} \right)^2 \cdot l =
        %4 \cdot \left( \frac{%5}{2} \right)^2 \cdot %6 = %7.
    \end{gather} \\
    \text{    Потенциальная энергия $(E_\text{п})$ взрывной системы, кДж. } \\
    \begin{gather}
         E_\text{п} = \frac{P_1 - P_0}{k_\text{г} - 1} \cdot V_\text{г} =
         \frac{p_1}{k_\text{г} - 1} \cdot V_\text{г} =
         \frac{%1}{%8 - 1} \cdot %7 = %9.
    \end{gather} \\
    )";

    const InputData& iData = m_labSolver->getInputData();
    const RawData&   rData = m_labSolver->getRawData();

    QString str1 = getNumericString(iData.tankBurstPressure);
    QString str2 = getNumericString(iData.airPressure);
    QString str3 = getNumericString(rData.absTankBurstPressure);
    QString str4 = getNumericString(m_labSolver->getPI(), "verb");
    QString str5 = getNumericString(iData.gasTankDiameter, "three");
    QString str6 = getNumericString(iData.gasTankLength, "three");
    QString str7 = getNumericString(rData.tankVolume, "verb");
    QString str8 = getNumericString(iData.gasAdiabaticIndex, "two");
    QString str9 = getNumericString(rData.burstEnergy, "two");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6)
             .arg(str7).arg(str8).arg(str9);
    return res;
}

QString TeXBuilder::getStage02_TNTEquivalentTeX(){
    QString res;
    res = R"(\text{2. Вычисляется значение ТНТ-эквивалента $(W_\text{тнт})$ }
    \text{взрыва.} \\
    \text{    Удельная энергия $(Q_\text{тнт})$ взрывчатого разложения }
    \text{тротилла, кДж/кг.} \\
    \begin{gather}
        Q_\text{тнт} = %1.
    \end{gather} \\
    \text{    Тротиловый эквивалент взрыва $(W_\text{тнт})$, кг.} \\
    \begin{gather}
        W_\text{тнт} = \frac{E_\text{п}}{Q_\text{тнт}} = \frac{%2}{%1} = %3.
    \end{gather}
    )";

    const InputData& iData = m_labSolver->getInputData();
    const RawData&   rData = m_labSolver->getRawData();

    QString str1 = getNumericString(iData.tntSpecificEnergy);
    QString str2 = getNumericString(rData.burstEnergy, "two");
    QString str3 = getNumericString(rData.tntEquivalent, "three");

    res = res.arg(str1).arg(str2).arg(str3);

    return res;
}

QString TeXBuilder::getStage03_WaveBurstPressureTeX(){
    QString res;
    res = R"(\text{3. Рассчитывается значение избыточного давлнеия $(p_S)$ }
    \text{воздуха на фронте } \\
    \text{ударной волны для заданного расстояния $(R_\text{пр})$ }
    \text{от источника взрыва до приёмника.} \\
    \text{    Динамический параметр $X_0$, м.} \\
    \begin{gather}
        X_0 = \sqrt[3]{\frac{k_\text{ув} \cdot E_\text{п}}{P_0}} =
              \sqrt[3]{\frac{%1 \cdot %2}{%3}} = %4.
    \end{gather} \\
    \text{    Безразмерное расстояние $(R_s)$ от центра взрыва до фронта }
    \text{ударной волны} \\
    \begin{gather}
        R_s = \frac{R_\text{пр}}{X_0} = \frac{%5}{%4} = %6.
    \end{gather} \\
    \text{    Избыточное давление $(p_s)$ воздуха на фронте ударной волны, кПа.}
    \\
    )";

    const InputData& iData = m_labSolver->getInputData();
    const RawData&   rData = m_labSolver->getRawData();
    const OutData&   oData = m_labSolver->getOutData();

    QString str1 = getNumericString(iData.releaseFraction, "two");
    QString str2 = getNumericString(rData.burstEnergy, "two");
    QString str3 = getNumericString(iData.airPressure);
    QString str4 = getNumericString(rData.dynParamX0, "verb");
    QString str5 = getNumericString(iData.standoffDistance, "one");
    QString str6 = getNumericString(rData.rsDistance, "verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6);

    if (rData.rsDistance <= 2.0){
        QString resA;
        resA = R"(
            \text{    При $0 < R_s \leq 2$. }\\
            \begin{gather}
                p_s = \frac{P_0}
                {\raisebox{-0.45em}{$0,6$ \cdot}
                    \left( -1 + \sqrt{1+29,847755 \cdot R_s^3}
                   \right)}
                     = \frac{%1}
                {\raisebox{-0.25em}{$0,6$ \cdot}
                    \left( -1 + \sqrt{1+29,847755 \cdot %2^3}
                    \right)} = %3.
            \end{gather}
            \\
            \text{    При $R_s > 2$. } \\
            \begin{gather}
                p_s = \frac{P_0}
                {\raisebox{-0.15em}{0,6 \cdot}
                    \left( -1 + \sqrt{1+70 \cdot R_s^2 \cdot
                    \left(\ln{\frac{R_s}{2}} + 1 \right)}
                    \right)}.
            \end{gather}
            \\
        )";

        QString strA1 = getNumericString(iData.airPressure);
        QString strA2 = getNumericString(rData.rsDistance, "verb");
        QString strA3 = getNumericString(oData.waveBurstPressure, "verb");

        resA = resA.arg(strA1).arg(strA2).arg(strA3);
        res = res + resA;
    }
    else if (rData.rsDistance > 2.0){
        QString resB;

        resB = R"(
            \text{    При $0 < R_s \leq 2$. }\\
            \begin{gather}
                p_s = \frac{P_0}
                {\raisebox{-0.45em}{0,6 \cdot}
                    \left( -1 + \sqrt{1+29,847755 \cdot R_s^3}
                   \right)}.
            \end{gather}
            \\
            \text{    При $R_s > 2$. } \\
            \begin{gather}
                p_s = \frac{P_0}
                {\raisebox{-0.15em}{0,6 \cdot}
                    \left( -1 + \sqrt{1+70 \cdot R_s^2 \cdot
                    \left(\ln{\frac{R_s}{2}} + 1 \right)}
                    \right)} = \frac{%1}
                    {\raisebox{-0.15em}{0,6 \cdot}
                        \left( -1 + \sqrt{1+70 \cdot %2^2 \cdot
                        \left(\ln{\left(\frac{%2}{2}\right)} + 1 \right)}
                        \right)} = %3.
            \end{gather}
            \\
        )";

        QString strB1 = getNumericString(iData.airPressure);
        QString strB2 = getNumericString(rData.rsDistance, "verb");
        QString strB3 = getNumericString(oData.waveBurstPressure, "verb");

        resB = resB.arg(strB1).arg(strB2).arg(strB3);
        res += resB;
    }

    return res;
}

QString TeXBuilder::getStage04_AirFlowSpeedTeX(){
    QString res;
    res = R"(
    \text{4. Определяется скорость частиц воздуха $(V_s$) движущихся за фронтом}
    \text{ волны.} \\
    \text{    Скорость звука $(C_1)$ при атмосферном давлении, м/c.} \\
    \begin{gather}
        C_1 = \sqrt{\frac{k_0 \cdot P_0}{\rho_0}} =
              \sqrt{\frac{%1 \cdot %2 \cdot 1000}{%3}} = %4;
    \end{gather} \\
    \text{где  $k_0$ - показатель адиабаты для воздуха, $k_0 = %1$;} \\
    \text{$\rho_0$ - плотность воздуха, $\rho_0 = 1,293$ кг/м$^3$.} \\
    \text{    Скорость воздушного потока $V_s$, м/с.} \\
    )";

    const InputData& iData = m_labSolver->getInputData();
    const RawData&   rData = m_labSolver->getRawData();
    const OutData&   oData = m_labSolver->getOutData();

    QString str1 = getNumericString(iData.airAdiabaticIndex, "one");
    QString str2 = getNumericString(iData.airPressure);
    QString str3 = getNumericString(iData.airDensity, "three");
    QString str4 = getNumericString(rData.airSndSpeed, "verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4);

    if (rData.rsDistance <= 2){
        QString resA;
        resA = R"(
            \text{    При $0 < R_s \leq 2$. } \\
            \begin{gather}
                V_s = \frac{0,30507 \cdot C_1}{R_s^{1,5}}
                    = \frac{0,30507 \cdot %1}{%2^{1,5}} = %3.
            \end{gather} \\
            \text{    При $R_s > 2$.} \\
            \begin{gather}
                V_s = \frac{0,21571 \cdot C_1}
                {R_s \cdot \sqrt{\ln{\left( \frac{R_s}{2} \right) + 1}}}.
            \end{gather}
        )";

        QString strA1 = getNumericString(rData.airSndSpeed, "verb");
        QString strA2 = getNumericString(rData.rsDistance, "verb");
        QString strA3 = getNumericString(rData.airFlowSpeed, "verb");

        resA = resA.arg(strA1).arg(strA2).arg(strA3);
        res += resA;
    }
    else {
        QString resB;
        resB = R"(
            \text{    При $0 < R_s \leq 2$. } \\
            \begin{gather}
                V_s = \frac{0,30507 \cdot C_1}{R_s^{1,5}}.
            \end{gather} \\
            \text{    При $R_s > 2$.} \\
            \begin{gather}
                V_s = \frac{0,21571 \cdot C_1}
                {R_s \cdot \sqrt{\ln{\left( \frac{R_s}{2} \right) + 1}}}
                    = \frac{0,21571 \cdot %1}
                    {%2 \cdot \sqrt{\ln{\left( \frac{%2}{2} \right) + 1}}} = %3.
            \end{gather}
        )";

        QString strB1 = getNumericString(rData.airSndSpeed, "verb");
        QString strB2 = getNumericString(rData.rsDistance, "verb");
        QString strB3 = getNumericString(rData.airFlowSpeed, "verb");

        resB = resB.arg(strB1).arg(strB2).arg(strB3);
        res += resB;
    }

    return res;
}

QString TeXBuilder::getStage05_WaveBurstSpeedTeX(){
    QString res;
    res = R"(\text{5. Рассчитывается скорость движения фронта $(D)$ ударной }
    \text{волны, м/c.} \\
    \begin{align}
        D & = 0,25 \cdot (k_0 + 1) \cdot V_s + 0,5 \cdot
              \sqrt{0,25 \cdot (k_0 + 1)^2 \cdot V_s^2 + 4 \cdot C_1^2} = \\
          & = 0,25 \cdot (%1 + 1) \cdot %2 + 0,5 \cdot
              \sqrt{0,25 \cdot (%1 + 1)^2 \cdot %2^2 + 4 \cdot %3^2} = %4.
    \end{align} \\
    )";

    const InputData& iData = m_labSolver->getInputData();
    const RawData& rData = m_labSolver->getRawData();

    QString str1 = getNumericString(iData.airAdiabaticIndex, "one");
    QString str2 = getNumericString(rData.airFlowSpeed, "one");
    QString str3 = getNumericString(rData.airSndSpeed, "two");
    QString str4 = getNumericString(rData.waveBurstSpeed, "two");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4);

    return res;
}

QString TeXBuilder::getStage06_StandoffTimeTeX(){
    QString res;
    res = R"(\text{6. Определяется время $(T)$ перемещения волны от центра }
    \text{взрывной системы} \\
    \text{до приёмника.} \\
    \text{    Динамический параметр времени $(T_0)$, c.} \\
    \begin{gather}
        T_0 = X_0 \cdot \sqrt{\frac{\rho_0}{P_0}} =
               %1 \cdot \sqrt{\frac{%2}{%3 \cdot 1000}} = %4.
    \end{gather} \\

    \text{    Энергетический параметр $(\alpha)$ взрыва. } \\
    \text{    При $k_0 = 1,4$ $\alpha = %5$. } \\
    \text{    Безразмерное расстояние $(R_\alpha)$, зависящее }
    \text{от энергетического параметра.} \\
    \begin{gather}
        R_\alpha = \frac{0,01}{\alpha^{0,2}} = \frac{0,01}{%5^2} = %6.

    \end{gather} \\
    \text{    Безразмерная величина времени $(\tau)$ определяется} \\
    \text{с помощью итерационного цикла.} \\
    \begin{gather}
        \tau = \tau + \frac{\Delta R \cdot 5 \cdot \sqrt{\alpha} \cdot
                            \left(R_\alpha + \Delta R \cdot i \right)^{1,5}}
                           {1 + \sqrt{25 \cdot k_0 \cdot \alpha \cdot
                           \left(R_\alpha + \Delta R \cdot i \right)^2}},
    \end{gather} \\
    \text{где $i$ - итерационная переменная, изменяется от 1 до 500.} \\
    \text{    Для итерационного цикла от 1 до 500} \\
    \begin{gather}
        \Delta R = \frac{R_s - R_\alpha}{500} = \frac{%7 - %6}{500} = %8.
    \end{gather} \\
    \text{    Перед началом цикла \tau = 0,00001.} \\
    \text{    При i = 1.} \\
    \begin{align}
        \tau & = \tau + \frac{\Delta R \cdot 5 \cdot \sqrt{\alpha} \cdot
                            \left(R_\alpha + \Delta R \cdot i \right)^{1,5}}
                           {1 + \sqrt{25 \cdot k_0 \cdot \alpha \cdot
                           \left(R_\alpha + \Delta R \cdot i \right)^2}} = \\
             & = %10  + \frac{ %8 \cdot 5 \cdot \sqrt{%5} \cdot
                            \left(%6 + %8 \cdot 1 \right)^{1,5}}
                           {1 + \sqrt{25 \cdot %9 \cdot %5 \cdot
                           \left(%6 + %8 \cdot 1 \right)^2}} = %11.\\
    \end{align} \\
    \text{    При i = 2.} \\
    \begin{align}
        \tau & = \tau + \frac{\Delta R \cdot 5 \cdot \sqrt{\alpha} \cdot
                            \left(R_\alpha + \Delta R \cdot i \right)^{1,5}}
                           {1 + \sqrt{25 \cdot k_0 \cdot \alpha \cdot
                           \left(R_\alpha + \Delta R \cdot i \right)^2}} = \\
             & = %11  + \frac{ %8 \cdot 5 \cdot \sqrt{%5} \cdot
                            \left(%6 + %8 \cdot 2 \right)^{1,5}}
                           {1 + \sqrt{25 \cdot %9 \cdot %5 \cdot
                           \left(%6 + %8 \cdot 2 \right)^2}} = %12.\\
    \end{align} \\
    \text{    После 500 итераций, при i = 500.} \\
    \begin{align}
        \tau & = \tau + \frac{\Delta R \cdot 5 \cdot \sqrt{\alpha} \cdot
                            \left(R_\alpha + \Delta R \cdot i \right)^{1,5}}
                           {1 + \sqrt{25 \cdot k_0 \cdot \alpha \cdot
                           \left(R_\alpha + \Delta R \cdot i \right)^2}} = \\
             & = %13  + \frac{ %8 \cdot 5 \cdot \sqrt{%5} \cdot
                            \left(%6 + %8 \cdot 500 \right)^{1,5}}
                           {1 + \sqrt{25 \cdot %9 \cdot %5 \cdot
                           \left(%6 + %8 \cdot 500 \right)^2}} = %14.\\
    \end{align} \\
    \text{    Время $(T)$ перемещения волны от центра взрывной системы до }
    \text{приёмника, с.} \\
    \begin{gather}
        T = \tau \cdot T_0 = %14 \cdot %15 = %16.
    \end{gather}
    )";

    const InputData& iData = m_labSolver->getInputData();
    const RawData&   rData = m_labSolver->getRawData();

    QString str1 = getNumericString(rData.dynParamX0,"verb");
    QString str2 = getNumericString(iData.airDensity, "three");
    QString str3 = getNumericString(iData.airPressure, "short");
    QString str4 = getNumericString(rData.dynParamT0, "verb");
    QString str5 = getNumericString(iData.alpha, "verb");
    QString str6 = getNumericString(rData.raDistance, "verb");
    QString str7 = getNumericString(rData.rsDistance, "verb");
    QString str8 = getNumericString(rData.deltaR, "verb");
    QString str9 = getNumericString(iData.airAdiabaticIndex);
    QString str10 = getNumericString(rData.tauArray[0], "pow");
    QString str11 = getNumericString(rData.tauArray[1], "pow");
    QString str12 = getNumericString(rData.tauArray[2], "pow");
    QString str13 = getNumericString(rData.tauArray[499], "verb");
    QString str14 = getNumericString(rData.tauArray[500], "verb");
    QString str15 = getNumericString(rData.dynParamT0, "verb");
    QString str16 = getNumericString(rData.standoffTime, "verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6)
             .arg(str7).arg(str8).arg(str9).arg(str10).arg(str11).arg(str12)
             .arg(str13).arg(str14).arg(str15).arg(str16);

    return res;
}

QString TeXBuilder::getStage07_FinalizeSolutionTeX(){
    QString res;
    res = R"(\text{7. По вычисленным значениям рассчитываются удельный }
    \text{положительный} \\
    \text{импульс $(i_s)$, длительность фазы сжатия $(\tau_s)$, }
    \text{динамический напор $(p_\text{ск})$ и др.} \\
    \text{    Удельный положительный импульс ($i_s$, импульс фазы сжатия), }
    \text{Па$\cdot$c.} \\
    \begin{gather}
        i_s = 0,04444 \cdot \frac{P_0 \cdot X_0}{С_1 \cdot R_s} =
              0,04444 \cdot \frac{%1 \cdot 1000 \cdot %2}{%3 \cdot %4} = %5.
    \end{gather} \\
    \text{    Длительность фазы сжатия $(\tau_s)$, с.} \\
    \begin{gather}
        \tau_s = \frac{2 \cdot i_s}{p_s} = \frac{2 \cdot %5}{%6 \cdot 1000} =%7.

    \end{gather} \\
    \text{    Плотность воздуха при давлении на фронте ударной волны $(\rho_s),}
    \text{ кг/м$^3$.} \\
    \begin{gather}
        \rho_s = \frac{(k_0 + 1) \cdot \rho_0}{(k_0 - 1)\cdot
                \left( 1 + 2 \cdot \frac{C_1^2}{D^2 \cdot (k_0 - 1)} \right)}=
                \frac{(%8 + 1) \cdot %9}{(%8 - 1)\cdot
                \left( 1 + 2 \cdot \frac{%3^2}{%4^2 \cdot (%8 - 1)} \right)}=
                %10.
    \end{gather}
    \\
    \text{    Динамический (скоростной) напор $(p_\text{cк})$ воздуха на }
    \text{твёрдую преграду, Па.} \\
    \begin{gather}
        p_\text{ск} = 0,5 \cdot \rho_s \cdot V_s^2 =
                      0,5 \cdot %10 \cdot %11^2 = %12.
    \end{gather} \\
    \text{    Относительное избыточное давление $(P_\text{отн})$ на фронте }
    \text{ударной волны, кПа.} \\
    \begin{gather}
        P_\text{отн} = \frac{p_s}{P_0} = \frac{%6}{%1} = %13.

    \end{gather} \\
    \text{    Импульс фазы сжатия $(\overline{i_s^{\text{'}}})$, приведённый к атмосферному }
    \text{давлению и массе $(m)$ } \\
    \text{тела человека, $\frac{\sqrt{\text{Па}}\cdot
                                            \text{с}}{\sqrt[3]{\text{кг}}}$.} \\
    \begin{gather}
        \overline{i_s^{\text{'}}} = \frac{i_s}{\sqrt{P_0} \cdot \sqrt[3]{m}} =
                      \frac{%5}{\sqrt{%1 \cdot 1000} \cdot \sqrt[3]{%14}} = %15;
    \end{gather} \\
    \text{где $m$ - масса тела человека, $m = %14$ кг.} \\
    \text{    Импульс фазы сжатия $(\overline{i_s^{\text{''}}})$, приведённый к массе тела }
    \text{человека, $\frac{\text{Па} \cdot \text{с}}{\sqrt[3]{\text{кг}}}$.} \\
    \begin{gather}
        \overline{i_s^{\text{''}}} = \frac{i_s}{\sqrt[3]{m}} =
                      \frac{%5}{\sqrt[3]{%14}} = %16;
    \end{gather} \\
    \text{    Уровень звукового давления $(L_p)$ у приёмника ударной волны, дБ.}
    \\
    \begin{gather}
        L_p = 20 \cdot \log10{\left( \frac{p_s}{P_\text{порог}}\right )} =
              20 \cdot \log10{\left( \frac{%6 \cdot 1000}{%1} \right)} = %17;
    \end{gather} \\
    \text{где $P_\text{порог}$ - пороговый уровень звукового давления, }
    \text{$P_\text{порог} = 2 \cdot 10^{-5}$ Па.}
    )";

    const InputData& iData = m_labSolver->getInputData();
    const OutData&   oData = m_labSolver->getOutData();
    const RawData&   rData = m_labSolver->getRawData();

    QString str1 = getNumericString(iData.airPressure, "short");
    QString str2 = getNumericString(rData.dynParamX0, "verb");
    QString str3 = getNumericString(rData.airSndSpeed, "verb");
    QString str4 = getNumericString(rData.rsDistance, "verb");
    QString str5 = getNumericString(rData.compressImpulse, "three");
    QString str6 = getNumericString(oData.waveBurstPressure, "verb");
    QString str7 = getNumericString(rData.compressTau, "verb");
    QString str8 = getNumericString(iData.airAdiabaticIndex, "short");
    QString str9 = getNumericString(iData.airDensity, "three");
    QString str10 = getNumericString(rData.airBurstDensity, "verb");
    QString str11 = getNumericString(rData.airFlowSpeed, "verb");
    QString str12 = getNumericString(rData.flowSpeedPressure, "two");
    QString str13 = getNumericString(rData.relativeWaveBurstPressure, "verb");
    QString str14 = getNumericString(iData.humanMass, "short");
    QString str15 = getNumericString(oData.compressImpulseA, "verb");
    QString str16 = getNumericString(oData.compressImpulseB, "three");
    QString str17 = getNumericString(oData.loud, "two");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6)
             .arg(str7).arg(str8).arg(str9).arg(str10).arg(str11).arg(str12)
             .arg(str13).arg(str14).arg(str15).arg(str16).arg(str17);

    return res;
}

QString TeXBuilder::getResultsTeX(){
    QString res;
    res = R"(
    \text{Результаты расчёта параметров ударной волны:} \\
    \text{    - избыточное давление воздуха на фронте ударной волны $p_s = %1$ }
    \text{кПа;} \\
    \text{    - удельный положительный импульс фазы сжатия $i_s = %2$ Па·с;} \\
    \text{    - относительное избыточное давление воздуха} \\
    \text{                                                                     }
    \text{      на фронте ударной волны $P_\text{отн} = %3;} \\
    \text{    - импульс фазы сжатия, приведённый к атмосферному давлению }  \\
    \text{                                                                     }
    \text{      и массе тела человека $\overline{i_s^{\text{'}}} = %4 }
    \text{\frac{\sqrt{\text{Па}} \cdot \text{с}}{\sqrt[3]{\text{кг}}}$;} \\
    \text{    - импульс фазы сжатия, приведённый к массе тела человека }
    \text{ $\overline{i_s^{\text{''}}} = %5 }
    \text{\frac{\text{Па} \cdot \text{с}}{\sqrt[3]{\text{кг}}}$;} \\
    \text{    - уровень звукового давления у приёмника ударной волны $L_p$ = %6}
    \text{ дБ.}
    )";

    const OutData& oData = m_labSolver->getOutData();

    QString str1 = getNumericString(oData.waveBurstPressure, "two");
    QString str2 = getNumericString(oData.compressImpulse, "two");
    QString str3 = getNumericString(oData.relativeWaveBurstPressure, "three");
    QString str4 = getNumericString(oData.compressImpulseA, "verb");
    QString str5 = getNumericString(oData.compressImpulseB, "two");
    QString str6 = getNumericString(oData.loud, "two");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6);

    return res;
}


QString TeXBuilder::getNumericString(double num, QString fmt){
    // fmt: "pow", "one" ("short"), "two", "three", "four", "five" ("verb")
    QString res;

    if (fmt == "pow"){
        QString exp;
        exp = QString::number(num, 'e', 2).replace(".", "\\mathord{,}");

        QStringList numParts = exp.split('e');
        QString mantissa = numParts[0];
        QString exponent = QString::number(numParts[1].toInt());
        res = mantissa + " \\cdot 10^{" + exponent + "}";
    }
    else {
        if (fabs(num - (int)num) < 1E-6){
            res = QString::number(num, 'f', 0);
        }
        else {
            if (fmt == "one" || fmt == "short") {
                res = QString::number(num, 'f', 1).replace(".", "\\mathord{,}");
            }
            else if (fmt == "two") {
                res = QString::number(num, 'f', 2).replace(".", "\\mathord{,}");
            }
            else if (fmt == "three") {
                res = QString::number(num, 'f', 3).replace(".", "\\mathord{,}");
            }
            else if (fmt == "four") {
                res = QString::number(num, 'f', 4).replace(".", "\\mathord{,}");
            }
            else if (fmt == "five" || fmt == "verb"){
                res = QString::number(num, 'f', 5).replace(".", "\\mathord{,}");
            }

            return res;

       }
    }

    return res;
}

// End texBuilder.cpp
