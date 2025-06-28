// Begin latexTextBuilder.cpp

#include "latexTextBuilder.h"

LatexTextBuilder::LatexTextBuilder(){
}

LatexTextBuilder::~LatexTextBuilder(){

}

void LatexTextBuilder::init(GasExplosionCalc* calculator){
    m_appCalc = calculator;
}

QString LatexTextBuilder::getTextInitData(QString str1){
    QString res;
    res = R"(
        \text{%1:} \\
        \text{ - число атомов углерода в углеводородном газе x = %2 ед;} \\
        \text{ - число атомов водорода в углеводородном газе y = %3 ед;} \\
        \text{ - теплота сгорания углеводородного газа Q = %4 МДж/м}^3; \\
        \text{ - верхний концентрационный предел воспламенения }
                                    \text{газа e}_{\text{в}}\text{ = %5\%;} \\

        \text{ - плотность газа при нормальных условиях ρ}_0
                                                        \text{= %6 кг/м}^3; \\
        \text{ - нормальная скорость распространения пламени V}_\text{н}
                                                        \text{ = %7 м/c;} \\
        \text{ - масса газа, образовавшего огневой шар G = %8 т;} \\
        \text{ - расстояние от зоны горения до приёмника }
                                            \text{ИК излучения h = %9 м;} \\
        \text{ - время действия излучения на сетчатку глаза человека }
                                        \text{t}_{\text{имп}}\text{ = %10 с.} \\
    )" ;

    QString str2 = getNumericString(m_appCalc->getCarbonAtomCount());
    QString str3 = getNumericString(m_appCalc->getHydrogenAtomCount()); ;
    QString str4 = getNumericString(m_appCalc->getGasHeatOfCombustion()); ;
    QString str5 = getNumericString(m_appCalc->getUpperFlammabilityLimit()); ;
    QString str6 = getNumericString(m_appCalc->getGasDensity()); ;
    QString str7 = getNumericString(m_appCalc->getNormalFlameSpeed()); ;
    QString str8 = getNumericString(m_appCalc->getGasMass()); ;
    QString str9 = getNumericString(m_appCalc->getDistanceToReceiver()); ;
    QString str10 = getNumericString(m_appCalc->getEyeRadiationTime()); ;

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6)
            .arg(str7).arg(str8).arg(str9).arg(str10);
    return res;
}

QString LatexTextBuilder::getTextStage01(){
    QString res;
    res = R"(
        \text{Алгоритм расчёта параметров техногенного пожара.} \\
        \text{1. Задаётся средняя температура $(T_{g})$ зоны горения в первом }
        \text{приближении, $^{\text{\LARGE{\circ}}}$C.}\\
        \begin{align}
            T_{g} =  %1.
        \end{align}
    )" ;

    QString str1 = getNumericString(m_appCalc->getInitTg("first"));

    res = res.arg(str1);

    return res;
}

QString LatexTextBuilder::getTextStage02(){
    QString res;
    res = R"(
        \text{2. По значению предельной концентрации газа в богатой смеси }
        \text{определяется}\\ \text{коэффициент расхода воздуха ($n$) }
        \text{для первой стадии горения.}
        \\
        \begin{align}
            n = \frac{(100 - e_\text{в}) \cdot 0\mathord{,}24}{e_\text{в}
                                                                    \cdot O_1}.
        \end{align}
        \\
        \text{    $O_1$ - удельное теоретическое количество кислорода при полном }
        \text{горении} \\ \text{углеводородного газа $C_x H_y$, м$^3$/м$^3$.}\\
        \text{    Для пропана $C_{%1} H_{%2}$:}\\
        \begin{gather}
            O_1 = x + \frac{y}{4} = %3 + \frac{%4}{4} = {%5}. \\

            n = \frac{(100 - e_\text{в})\cdot 0\mathord{,}2415}{e_\text{в}\cdot O_1} =
            \frac{(100 - {%6})\cdot 0\mathord{,}2415}{{%6}\cdot {%7}} = %8.
        \end{gather}
    )";

    QString str1 = getNumericString(m_appCalc->getCarbonAtomCount());
    QString str2 = getNumericString(m_appCalc->getHydrogenAtomCount()); ;
    QString str3 = str1;
    QString str4 = str2;
    QString str5 = getNumericString(m_appCalc->getTheoryOxygenRequire());
    QString str6 = getNumericString(m_appCalc->getUpperFlammabilityLimit());
    QString str7 = str5;
    QString str8 = getNumericString(m_appCalc->getAirFlowRatio(),"verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).
              arg(str6).arg(str7).arg(str8);

    return res;
}

QString LatexTextBuilder::getTextStage03(){
    QString res;
    res = R"(
        \text{3. Проводится расчёт неполного горения и рассчитывается состав }
        \text{продуктов} \\ \text{горения.}
        \\
        \text{    Удельное количество ($V$) продуктов горения (ПГ),
                                                                   м$^3$/м$^3$.}
        \\
        \text{    При $n = 1$.}
        \\
        \begin{gather}
            V_{\text{CO}_2}^{n = 1} = x = {%1} \\
            V_{{\text{H}_2}O}^{n = 1} = \frac{y}{2} = \frac{%2}{2} = {%3}
        \end{gather}
        \\
        \text{    При $n < 1$.} \\
        \text{    $k_p$ - константа равновесия}.
        \\
        \begin{gather}
            -\lg{k_p} = \frac{2059}{T_g + 273}
            - 1\mathord{,}5904 \cdot \lg{(T_g + 273)}
            + 0\mathord{,}001817 \cdot (T_g + 273)\ - \\
            - 0\mathord{,}565 \cdot 10^{-6} \cdot (T_g + 273)^2
            + 8\mathord{,}24 \cdot 10^{-11} \cdot (T_g + 273)^3
            + 1\mathord{,}5313 =
            \\
            = \frac{2059}{{%4} + 273}
            - 1\mathord{,}5904 \cdot \lg{({%4} + 273)}
            + 0\mathord{,}001817 \cdot ({%4} + 273)\ - \\
            - 0\mathord{,}565 \cdot 10^{-6} \cdot ({%4} + 273)^2
            + 8\mathord{,}24 \cdot 10^{-11} \cdot ({%4} + 273)^3
            + 1\mathord{,}5313 = {%5}.
            \\
            k_p = \frac{1}{10^{-\lg{k_p}}} = \frac{1}{10^{%5}} = {%6}
        \end{gather}
        \\
        \text{    $b_1$, $b_2$ - вспомогательные величины.}
        \\
        \begin{gather}
            b_2 = V_{H_2 O}^{n = 1} - (k_p - 2) \cdot V_{CO_2}^{n = 1}
            + 2 \cdot O_1 \cdot (1 - n)(k_p - 1) =
            \\
            = {%7} - ({%6} - 2) \cdot {%8} + 2 \cdot {%9} \cdot
            (1 - {%10})({%6} - 1) = {%11}.
            \\
            b_1 = -b_2 + \sqrt{ b_2^2 + 4 \cdot \left(k_p - 1\right) \cdot V_{CO_2}^{n=1}
            \cdot \left(V_{CO_2}^{n = 1} + V_{H_2 O}^{n = 1}
            -2 \cdot O_1 \cdot (1 - n)\right)} = \\
            = -{%11} + \sqrt{ {%11}^2 + 4 \cdot \left({%6} - 1\right) \cdot {%1}
            \cdot \left({%1} + {%3}
            -2 \cdot {%9} \cdot (1 - {%10})\right)} = {%12}. \\
        \end{gather} \\
        \begin{align}
            V_{CO_2}^{n < 1} & = \frac{b_1}{2\cdot (k_p - 1)} =
                                 \frac{%12}{2\cdot ({%6} - 1)} = {%13}. \\
            V_{CO}^{n < 1}   & = V_{CO_2}^{n = 1} - V_{CO_2}^{n < 1} =
                                {%1} - {%13} = {%14}.\\
            V_{Н_2 O}^{n < 1}& = V_{CO_2}^{n = 1} + V_{H_2 0}^{n = 1}
                                - V_{CO_2}^{n < 1} - 2 \cdot (1 - n) \cdot O_1 =
                                \\
                                & = {%1} + {%3} - {%13} - 2 \cdot (1 - {%10})
                                \cdot {%9} = {%15}. \\
            V_{H_2}^{n < 1} & = V_{CO_2}^{n < 1} - V_{CO_2}^{n=1} + 2 \cdot
                                (1 - n ) \cdot O_1 = \\
                            & = {%13} - {%1} - 2 \cdot (1 - {%10}) \cdot {%9} =
                                                                        {%16}.\\
            V_{N_2}^{n < 1} & = 3\mathord{,}76 \cdot n \cdot O_1 =
                                                      3\mathord{,}76 \cdot {%10}
                                \cdot {%9} = {%17}. \\
            V_\text{ПГ}^{n < 1} & = V_{CO_2}^{n<1} + V_{H_2 O}^{n<1}
                                + V_{CO}^{n<1} + V_{N_2}^{n<1} + V_{H_2}^{n<1} =
                                \\
                                & = {%13} + {%15} + {%14} + {%17} + {%16} = %18.
        \end{align} \\
        \text{    Парциальное давление $(P)$ в продуктах неполного горения }
        \text{углеводородного газа.} \\
        \begin{align}
            P_{CO_2} = V_{CO_2}^{n < 1} / V_{\text{ПГ}}^{n < 1} = {%13}/{%18}
                     = {%19}.\\
            P_{CO} = V_{CO}^{n < 1} / V_{\text{ПГ}}^{n < 1} = {%14} / {%18}
                     = {%20}. \\
            P_{H_2 O} = V_{H_2 O}^{n < 1} / V_{\text{ПГ}}^{n<1} = {%15} / {%18}
                     = {%21}. \\
            P_{H_2} = V_{H_2}^{n < 1} / V_{\text{ПГ}}^{n<1} = {%16} / {%18}
                     = {%22}. \\
            P_{N_2} = V_{N_2}^{n < 1} / V_{\text{ПГ}}^{n<1} = {%17} / {%18}
                     = {%23}.
        \end{align}
    )";
    QString str1 = getNumericString(m_appCalc->
                                             getVolCO2AtAirFlowRatioEqualOne());
    QString str2 = getNumericString(m_appCalc->getHydrogenAtomCount()); ;
    QString str3 = getNumericString(m_appCalc->
                                             getVolH2OAtAirFlowRatioEqualOne());
    QString str4 = getNumericString(m_appCalc->getInitTg("first"));
    QString str5 = getNumericString(m_appCalc->getMinusLgKp("first"), "verb" );
    QString str6 = getNumericString(m_appCalc->getKp("first"), "verb" );
    QString str7 = getNumericString(m_appCalc->
                                             getVolH2OAtAirFlowRatioEqualOne());
    QString str8 = getNumericString(m_appCalc->
                                             getVolCO2AtAirFlowRatioEqualOne());
    QString str9 = getNumericString(m_appCalc->getTheoryOxygenRequire());
    QString str10 = getNumericString(m_appCalc->getAirFlowRatio(),"verb");
    QString str11 = getNumericString(m_appCalc->getB2("first"), "verb");
    QString str12 = getNumericString(m_appCalc->getB1("first"), "verb");
    QString str13 = getNumericString(m_appCalc->
                               getVolCO2AtAirFlowRatioLessOne("first"), "verb");
    QString str14 = getNumericString(m_appCalc->
                                getVolCOAtAirFlowRatioLessOne("first"), "verb");
    QString str15 = getNumericString(m_appCalc->
                               getVolH2OAtAirFlowRatioLessOne("first"), "verb");
    QString str16 = getNumericString(m_appCalc->
                                getVolH2AtAirFlowRatioLessOne("first"), "verb");
    QString str17 = getNumericString(m_appCalc->
                                getVolN2AtAirFlowRatioLessOne("first"), "verb");
    QString str18 = getNumericString(m_appCalc->
                               getVolSumAtAirFlowRatioLessOne("first"), "verb");
    QString str19 = getNumericString(m_appCalc->
                          getPressureCO2AtAirFlowRationLessOne("first"),"verb");
    QString str20 = getNumericString(m_appCalc->
                           getPressureCOAtAirFlowRationLessOne("first"),"verb");
    QString str21 = getNumericString(m_appCalc->
                          getPressureH2OAtAirFlowRationLessOne("first"),"verb");
    QString str22 = getNumericString(m_appCalc->
                           getPressureH2AtAirFlowRationLessOne("first"),"verb");
    QString str23 = getNumericString(m_appCalc->
                           getPressureN2AtAirFlowRationLessOne("first"),"verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6)
             .arg(str7).arg(str8).arg(str9).arg(str10).arg(str11).arg(str12)
             .arg(str13).arg(str14).arg(str15).arg(str16).arg(str17).arg(str18)
             .arg(str19).arg(str20).arg(str21).arg(str22).arg(str23);

    return res;
}

QString LatexTextBuilder::getTextStage04(){
    QString res, res0, res1a, res1b, res2, res3NaN, res3Low, res3Hi;

    QString str1 = getNumericString(m_appCalc->
                           getPressureN2AtAirFlowRationLessOne("first"),"verb");
    QString str2 = getNumericString(m_appCalc->
                           getPressureCOAtAirFlowRationLessOne("first"),"verb");
    QString str3 = getNumericString(m_appCalc->
                           getPressureH2AtAirFlowRationLessOne("first"),"verb");
    QString str4 = getNumericString(m_appCalc->
                          getPressureCO2AtAirFlowRationLessOne("first"),"verb");
    QString str5 = getNumericString(m_appCalc->
                          getPressureH2OAtAirFlowRationLessOne("first"),"verb");
    QString str6 = getNumericString(m_appCalc->getEnthalpy("first"),"verb");
    QString str7 = getNumericString(m_appCalc->
                                getVolSumAtAirFlowRatioLessOne("first"),"verb");
    QString str8 = getNumericString(m_appCalc->getGasHeatLoss("first"),"verb");
    QString str9 = getNumericString(m_appCalc->getGasHeatOfCombustion());
    QString str10 =getNumericString(m_appCalc->getInitAccurateTg("first"));

    res0 = R"(
        \text{4. По уровнению теплового баланса уточняется значение температуры}
        \\
        \text{ и при необходимости осуществляется возврат к п.1.}
        \\
        \text{    Энтальпия $(I)$ продуктов сгорания при }
        \text{$2200^{\text{\,\LARGE\circ}}$C, кДж/м$^3$.}
        \\
        \begin{align}
            I & = \left( 1\mathord{,}465 \cdot P_{N_2}
                + 1\mathord{,}516 \cdot P_{CO}
                + 1\mathord{,}424 \cdot P_{H_2}
                + 2\mathord{,}449 \cdot P_{CO_2}
                + 2\mathord{,}001 \cdot P_{H_2 0}\right) \cdot 2200 = \\
              & = ( 1\mathord{,}465 \cdot {%1}
                + 1\mathord{,}516 \cdot {%2}
                + 1\mathord{,}424 \cdot {%3}
                + 2\mathord{,}449 \cdot {%4}
                + 2\mathord{,}001 \cdot {%5} )\ \times \\
              & \times\ 2200 = {%6}.
        \end{align}
        \\
        \text{    Теплота химического недожога $(Q_\text{н})$ продуктов}
        \text{неполного горения, МДж/м$^3$.}\\
        \begin{gather}
            Q_\text{н} = ( 12\mathord{,}65 \cdot P_{CO}
                        + 10\mathord{,}77 \cdot P_{H_2} ) \cdot
                                                        V_{\text{ПГ}}^{n<1}\ =\\
                       = ( 12\mathord{,}65 \cdot {%2}
                        + 10\mathord{,}77 \cdot {%3} ) \cdot {%7} = {%8}.
        \end{gather}
        \\
        \text{    Уточнение средней температуры $T_g$ зоны горения, }
        \text{$^{\LARGE\circ}$C}.
        \\
    )";
    res0 = res0.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6)
             .arg(str7).arg(str8);

    // Температура газа > 950
    res1a = R"(
        \text{    При $T_g \ge 950$.}
        \\
        \begin{align}
            T_g & = \left (
                    \frac{(Q - Q_{\text{н}})\cdot 1000}
                         {V_{\text{ПГ}}^{n<1} \cdot I} + 0\mathord{,}075
                  \right ) \cdot 2050 = \\
                & = \left (
                    \frac{({%1} - {%2})\cdot 1000}
                         {{%3}\cdot {%4}} + 0\mathord{,}075
                  \right ) \cdot 2050 = {%5}.
        \end{align}
        \\
        \text{    При $T_g < 950$.}
        \\
        \begin{gather}
            T_g =
            \frac{ \left (
                  2695 \cdot \frac{(Q - Q_{\text{н}})\cdot 1000}
                                                        {V_{\text{ПГ}}^{n<1}}
                                                                       \right )}
            { \left (
                I + 0,3 \cdot
                     \frac{(Q - Q_{\text{н})\cdot 1000}}{V_{\text{ПГ}}^{n < 1}}
                                                                      \right )}.
        \end{gather}
    )";

    res1a = res1a.arg(str9).arg(str8).arg(str7).arg(str6).arg(str10);

    res1b = R"(
        \text{    При $T_g \ge 950$.}
        \\
        \begin{align}
            T_g & = \left (
                    \frac{(Q - Q_{\text{н}})\cdot 1000}
                         {V_{\text{ПГ}}^{n<1} \cdot I} + 0\mathord{,}075
                  \right ) \cdot 2050.
            \\
        \end{align}
        \\
        \text{    При $T_g < 950$.}
        \\
        \begin{gather}
            T_g =
            \frac{ \left (
                  2695 \cdot \frac{(Q - Q_{\text{н}})\cdot 1000}
                                                        {V_{\text{ПГ}}^{n<1}}
                                                                       \right )}
            { \left (
                I + 0,3 \cdot
                      \frac{(Q - Q_{\text{н})\cdot 1000}}{V_{\text{ПГ}}^{n < 1}}
                                                                    \right )}
                =
            \frac{ \left (
                  2695 \cdot \frac{({%2} - {%3})\cdot 1000}
                                                        {{%4}}
                                                                       \right )}
            { \left (
                {%1} + 0,3 \cdot
                     \frac{({%2} - {%3})\cdot 1000}{{%4}} \right )}\ = {%5}
        \end{gather}
    )";

    res1b = res1b.arg(str6).arg(str9).arg(str8).arg(str7).arg(str10);

    res2 = R"(
        \\
        \text{    После {%1} итераций п. 1 - 4 средняя температура зоны }
        \text{горения: }
        \\
        \begin{gather}
            T_g = {%2}.
        \end{gather}
        \\
        \text{    Tочность расчёта температуры между последними итерациями }
        \text{$\Delta T <{%3}$}
        \text{$^{\text{ \LARGE\circ}}$C.}
        \\
        \text{    Уточнённое значение парциального давления $(P)$ в продуктах }
        \\
        \text{ неполного горения углеводородного газа, }
        \text{при $T_g = %2^{\text{ \LARGE\circ}}$C$.}
        \\
        \begin{align}
            P_{CO_2}  & = {%4}. \\
            P_{CO}    & = {%5}. \\
            P_{H_2 O} & = {%6}. \\
            P_{H_2}   & = {%7}. \\
            P_{N_2}   & = {%8}.
        \end{align}
    )";

    QString str11 = getNumericString(m_appCalc->getCalcIterationCounter());
    QString str12 = getNumericString(m_appCalc->getInitTg());
    QString str13 = getNumericString(m_appCalc->getAaccuracyCalcAvgT());
    QString str14 = getNumericString(m_appCalc->
                               getPressureCO2AtAirFlowRationLessOne(), "verb");
    QString str15 = getNumericString(m_appCalc->
                               getPressureCOAtAirFlowRationLessOne(), "verb");
    QString str16 = getNumericString(m_appCalc->
                               getPressureH2OAtAirFlowRationLessOne(), "verb");
    QString str17 = getNumericString(m_appCalc->
                               getPressureH2AtAirFlowRationLessOne(), "verb");
    QString str18 = getNumericString(m_appCalc->
                               getPressureN2AtAirFlowRationLessOne(), "verb");

    res2 = res2.arg(str11).arg(str12).arg(str13).arg(str14).arg(str15).
                arg(str16).arg(str17).arg(str18);

    res3NaN = R"(
        \\
        \text{    После {%1} итераций п. 1 - 4 средняя температура зоны }
        \text{горения: }
        \\
        \textcolor{red}{
            \begin{gather}
                T_g = {%2}.
            \end{gather}
        }
        \\
        \text{  }
        \\
        \textcolor{red}{
        \begin{gather}
            \text{Ошибка расчёта средней температуры зоны горения, nan - }
            \text{not a number.}
        \end{gather}
        }
        \\
        \textcolor{red}{
        \begin{gather}
            \text{Уточните исходные данные и повторите расчёт!}
        \end{gather}
        }
        \\
    )";

    res3NaN = res3NaN.arg(str11).arg(str12);

    res3Low = R"(
        \\
        \text{    После {%1} итераций п. 1 - 4 средняя температура зоны }
        \text{горения: }
        \\
        \textcolor{red}{
            \begin{gather}
                T_g = {%2}.
            \end{gather}
        }
        \\
        \text{  }
        \\
        \begin{gather}
            \textcolor{red}\text{  Ошибка расчёта средней температуры зоны }
            \textcolor{red}\text{горения, отрицательное значение.}
        \end{gather}
        \\
        \textcolor{red}{
        \begin{gather}
            \text{Уточните исходные данные и повторите расчёт!}
        \end{gather}
        }
        \\
    )";

    res3Low = res3Low.arg(str11).arg(str12);

    res3Hi = R"(
        \\
        \text{    После {%1} итераций п. 1 - 4 средняя температура зоны }
        \text{горения: }
        \\
        \textcolor{red}{
            \begin{gather}
                T_g = {%2}.
            \end{gather}
        }
        \\
        \text{  }
        \\
        \begin{gather}
            \textcolor{red}\text{  Ошибка расчёта средней температуры зоны }
            \textcolor{red}\text{горения, значение более }
            \textcolor{red}\text{$2050^{\text{ \LARGE\circ}}$C$.}
        \end{gather}
        \\
        \textcolor{red}{
        \begin{gather}
            \text{Уточните исходные данные и повторите расчёт!}
        \end{gather}
        }
        \\
    )";

    res3Hi = res3Hi.arg(str11).arg(str12);

    // 2050 - максимальная температура при сжигании углеводородного газа
    if (m_appCalc->getInitTg() > 0.0 && m_appCalc->getInitTg() < 2050.0){
        if (m_appCalc->getInitTg("first") >= 950) {
            res = res0 + res1a + res2;
        }
        else {
            res = res0 + res1b + res2;
        }
    }
    else {
        if (std::isnan(m_appCalc->getInitTg())){
            res = res0 + res3NaN;
        }
        if (m_appCalc->getInitTg() < 0){
            res = res0 + res3Low;
        }
        if (m_appCalc->getInitTg() > 2050){
            res = res0 + res3Hi;
        }
    }
    return res;
}

QString LatexTextBuilder::getTextStage05(){
    QString res;
    res = R"(
        \text{5. С учётом плотности и массы углеводородного газа, находившегося}
        \text{ в резервуаре,}
        \\
        \text{определяются размеры газовоздушного облака.}
        \\
        \text{    Средний радиус $(R)$ зоны горения (огневого шара), м.}
        \\
        \begin{align}
        R & = \sqrt[3]{\frac{3}{4\cdot\pi}\cdot
                     \frac{G\cdot 1000 \cdot V_{\text{ПГ}}^{n<1}}{\rho_0}\cdot
                     \left(\frac{T_g + 273}{273}\right)} =
                     \\
          & = \sqrt[3]{\frac{3}{4\cdot{%1}}\cdot
                     \frac{{%2}\cdot 1000 \cdot {%3}}{{%4}}\cdot
                     \left(\frac{{%5} + 273}{273}\right)} = %6.
        \end{align}
        \\
    )";
    QString str1 = getNumericString(m_appCalc->getPI(), "verb");
    QString str2 = getNumericString(m_appCalc->getGasMass());
    QString str3 = getNumericString(m_appCalc->
                                      getVolSumAtAirFlowRatioLessOne(), "verb");
    QString str4 = getNumericString(m_appCalc->getGasDensity());
    QString str5 = getNumericString(m_appCalc->getInitTg());
    QString str6 = getNumericString(m_appCalc->getFireBallRadius(), "verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6);

    return res;
}

QString LatexTextBuilder::getTextStage06(){
    QString res;
    res = R"(
        \text{6. По температуре и размеру зоны горения, по количеству }
        \text{излучающих газов}
        \\
        \text{рассчитывается степень черноты ($\epsilon$) горящего облака.}
        \\
        \text{    Эффективная длина луча ($S_{\text{эф}}$) в огневом шаре, м.}
        \\
        \begin{gather}
            S_\text{эф} = 1,3 \cdot R = 1,3 \cdot {%1} = {%2}.
        \end{gather}
        \\
        \text{    Коэффициент ослабления лучей ($K_\text{Г}$)}.
        \\
        \begin{align}
            K_\text{Г} & = \frac{0,8 + 1,6 \cdot P_{H_2O}}
                {\sqrt{(P_{H_2O} + P_{CO_2})\cdot S_\text{эф}}}\cdot
                \left( 1 - 0,38 \cdot \frac{T_g + 273}{1000}\right) =
                \\
            & = \frac{0,8 + 1,6 \cdot {%3}}
                {\sqrt{({%3} + {%4})\cdot {%2}}}\cdot
                \left( 1 - 0,38 \cdot \frac{{%5} + 273}{1000}\right) = {%6}.
        \end{align}
        \\
        \text{    Степень черноты огневого шара ($\epsilon$).}
        \\
        \begin{gather}
            \epsilon =
            1 - e^{\left(-K_\text{Г} \cdot S_\text{эф} \cdot
                                                 ( P_{H2 O} + P_{CO_2}\right)} =
            1 - e^{\left(-{%6} \cdot {%2} \cdot ({%3} + {%4} \right)} = {%7}.
        \end{gather}
    )";

    QString str1 = getNumericString(m_appCalc->getFireBallRadius());
    QString str2 = getNumericString(m_appCalc->getEffPath());
    QString str3 = getNumericString(m_appCalc->
                                getPressureH2OAtAirFlowRationLessOne(), "verb");
    QString str4 = getNumericString(m_appCalc->
                                getPressureCO2AtAirFlowRationLessOne(), "verb");
    QString str5 = getNumericString(m_appCalc->getInitAccurateTg());
    QString str6 = getNumericString(m_appCalc->getRayDecreaseFactor(), "verb");
    QString str7 = getNumericString(m_appCalc->getFireBallBlackness(), "verb");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6).
              arg(str7);

    return res;
}

QString LatexTextBuilder::getTextStage07(){
    QString res;
    res = R"(
        \text{7. По степени черноты, температуре и величине внешней }
        \text{поверхности зоны }
        \\
        \text{горения определяется интегральный поток }
        \text{собственного излучения ($E_\text{соб}$)}
        \\
        \text{огневого шара.}
        \\
        \text{    Постоянная Стефана - Больцмана для излучения абсолютно }
        \text{чёрного тела ($\sigma_0$),}
        \\
        \text{Вт/(м$^2\cdot$K$^4$).}
        \\
        \begin{align}
            \sigma_0 = {%1}.
        \end{align}
        \\
        \text{    Площадь внешней поверхности огневого шара ($F$), м$^2$.}
        \\
        \begin{align}
            F = 4 \cdot \pi \cdot R^2 = 4 \cdot {%2} \cdot {%3}^2 = {%4}.
        \end{align}
        \\
        \text{    Поток энергии инфракрасного излучения от огневого шара, Вт.}
        \\
        \begin{align}
            E_\text{соб} = \sigma_0 \cdot \epsilon \cdot (T_g + 273)^4 =
            {%1} \cdot {%5} \cdot ({%6}+ 273) = {%7} = {%8}
        \end{align}
    )";
    QString str1 = getNumericString(m_appCalc->getSigma(), "pow");
    QString str2 = getNumericString(m_appCalc->getPI(),"verb");
    QString str3 = getNumericString(m_appCalc->getFireBallRadius());
    QString str4 = getNumericString(m_appCalc->getFireBallArea());
    QString str5 = getNumericString(m_appCalc->getFireBallBlackness());
    QString str6 = getNumericString(m_appCalc->getInitTg());
    QString str7 = getNumericString(m_appCalc->getFireBallEnergyPower());
    QString str8 = getNumericString(m_appCalc->getFireBallEnergyPower(), "pow");

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).
              arg(str6).arg(str7).arg(str8);
    return res;
}

QString LatexTextBuilder::getTextStage08(){
    QString res;
    res = R"(
        \text{8. По величине интегрального потока собственного излучения }
        \text{и по расстоянию}
        \\
        \text{от центра зоны горения до приёмника вычисляется величина }
        \text{плотности потока}
        \\
        \text{энергии (q) инфракрасного излучения.}
        \\
        \text{    Площадь поверхности условной сферы ($F_\text{у.с.}$),}
        \text{образованной радиусом, равным}
        \\
        \text{расстоянию от центра зоны горения до приёмника}
        \text{теплового излучения, м$^2$.}
        \\
        \begin{gather}
            F_\text{у.с.} = 4 \cdot \pi \cdot (R + h)^2 =
               4 \cdot {%1} \cdot ({%2} + {%3})^2 = {%4}.
        \end{gather}
        \\
        \text{    Плотность потока энергкии (q) у приёмника инфракрасного }
        \text{излучения, Вт/м$^2$.}
        \\
        \begin{align}
            q & = \frac{E_\text{соб}}{F_\text{у.с.}} = \sigma_0 \cdot \epsilon
                              \cdot (T_g + 273)^4 \cdot \frac{R^2}{(R+h)^2} = \\
              & = {%5} \cdot {%6} \cdot ( {%7} + 273)^4 \cdot
                                           \frac{{%2}^2}{({%2}+{%3})^2} = {%8}.
        \end{align}
    )";

    QString str1 = getNumericString(m_appCalc->getPI(), "verb");
    QString str2 = getNumericString(m_appCalc->getFireBallRadius());
    QString str3 = getNumericString(m_appCalc->getDistanceToReceiver());
    QString str4 = getNumericString(m_appCalc->getRaySpreadSphereArea());
    QString str5 = getNumericString(m_appCalc->getSigma(), "pow");
    QString str6 = getNumericString(m_appCalc->getFireBallBlackness(), "verb");
    QString str7 = getNumericString(m_appCalc->getInitTg());
    QString str8 = getNumericString(m_appCalc->getQDensity());

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6).
              arg(str7).arg(str8);

    return res;
}

QString LatexTextBuilder::getTextStage09(){
    QString res;
    res = R"(
        \text{9. Определяются значения параметров воздействия.}
        \\
        \text{    Удельная энергия (импульс энергии, $Q_\text{имп}$), }
        \text{воздействующая}
        \\
        \text{на сетчатку глаза, Дж/м$^2$. }
        \\
        \begin{align}
            Q_\text{имп} = q \cdot t_\text{имп} = {%1} \cdot {%2} = {%3}.
        \end{align}
        \\
        \text{    Диаметр (d) отображения огневого шара на сетчатке глаза, мм}
        \\
        \begin{align}
            d = \lambda \cdot \frac{2 \cdot R}{h} = {%4} \cdot
                                                   \frac{2 \cdot %5}{%6} = {%7}.
        \end{align}
        \\
        \text{    Коэффициент кинематической вязкости продуктов горения (\nu), }
        \text{м/с$^2$.}
        \\
        \begin{gather}
            \nu = {%8}.
        \end{gather}
        \\
        \text{    Критерий Рейнольдса.}
        \\
        \begin{gather}
            \text{Re} = \frac{2 \cdot R \cdot V_\text{н}}{\nu} =
                    \frac{2 \cdot {%5} \cdot {%9}}{%8} = {%10}.
        \end{gather}
        \\
        \text{    Турбулентная скорость распространения пламени ($V_\text{т}), }
        \text{м/c.}
        \\
        \begin{align}
            V_\text{т} = 0,18 \cdot V_\text{н}^{0,26} \cdot \text{Re}^{0,24} =
            0,18 \cdot {%9}^{0,26} \cdot {%10}^{0,24} = {%11}.
        \end{align}
        \\
        \text{    Среднее значение переменной скорости ($V_\text{ср}$) }
        \text{перемещения фронта горения, м/c.}
        \\
        \begin{align}
            V_\text{ср} = \frac{V_\text{н} + V_\text{т}}{2} = \frac{{%9}+{%11}}
                                                                {2} = {%12}.
        \end{align}
        \\
        \text{    Время достижения максимальной температуры зоны горения, с.}
        \\
        \begin{align}
            t = \frac{2 \cdot R}{V_\text{ср}} = \frac{2 \cdot %5}{%12} = {%13}.
        \end{align}
    )";

    QString str1 = getNumericString(m_appCalc->getQDensity());
    QString str2 = getNumericString(m_appCalc->getEyeRadiationTime());
    QString str3 = getNumericString(m_appCalc->getEyeEnDensity());
    QString str4 = getNumericString(m_appCalc->getEyeFocus());
    QString str5 = getNumericString(m_appCalc->getFireBallRadius());
    QString str6 = getNumericString(m_appCalc->getDistanceToReceiver());
    QString str7 = getNumericString(m_appCalc->getFireBallEyeSize());
    QString str8 = getNumericString(m_appCalc->
                                            getSmokeKinematicViscosity(),"pow");
    QString str9 = getNumericString(m_appCalc->getNormalFlameSpeed());
    QString str10 = getNumericString(m_appCalc->getRe());
    QString str11 = getNumericString(m_appCalc->getTurboFlameSpeed(), "verb");
    QString str12 = getNumericString(m_appCalc->getAvgFlameSpeed(), "verb");
    QString str13 = getNumericString(m_appCalc->getFireTime());

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5).arg(str6).
              arg(str7).arg(str8).arg(str9).arg(str10).arg(str11).arg(str12).
              arg(str13);

    return res;
}

QString LatexTextBuilder::getResultTeX(){
    QString res;
    res = R"(
    \text{Результаты расчёта параметров аварийного горения газовоздушной смеси:}
    \\
    \text{    - время выгорания газа в огневом шаре $t = %1$ c;} \\
    \text{    - плотность потока энергии у приёмника ИК-излучения }
    \text{$q = %2$ Вт/м$^2$;} \\
    \text{    - время действия излучения на сетчатку глаза человека }
    \text{$t_\text{имп} = %3$ c; }; \\
    \text{    - диаметр отображения огневого шара на сетчатке глаза }
    \text{$d = %4$ мм;} \\
    \text{    - удельная энергия, воздействующая на сетчатку глаза }
    \text{$Q_\text{имп} = %5$ Дж/м$^2$.}
    )";

    QString str1 = getNumericString(m_appCalc->getFireTime());
    QString str2 = getNumericString(m_appCalc->getQDensity());
    QString str3 = getNumericString(m_appCalc->getEyeRadiationTime());
    QString str4 = getNumericString(m_appCalc->getFireBallEyeSize());
    QString str5 = getNumericString(m_appCalc->getEyeEnDensity());

    res = res.arg(str1).arg(str2).arg(str3).arg(str4).arg(str5);

    return res;
}

QString LatexTextBuilder::getNumericString(double nVal, QString fmt){
    // fmt: "pow", "verb"
    QString res;

    if (fmt == "pow"){
        QString exp;
        exp = QString::number(nVal, 'e', 2).replace(".", "\\mathord{,}");

        QStringList numParts = exp.split('e');
        QString mantissa = numParts[0];
        QString exponent = QString::number(numParts[1].toInt());
        res = mantissa + " \\cdot 10^{" + exponent + "}";
    }
    else {
        if (fabs(nVal - (int)nVal) < 1E-6){
            res = QString::number(nVal, 'f', 0);
        }
        else {
            if (fmt == "verb"){
                res = QString::number(nVal, 'f', 5).replace(".", "\\mathord{,}");
            }
            else {
                res = QString::number(nVal, 'f', 1).replace(".", "\\mathord{,}");
            }
       }
    }

    return res;
}

// End latexTextBuilder.cpp
