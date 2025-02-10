// Begin latexTextBuilder.cpp

#include "latexTextBuilder.h"

LatexTextBuilder::LatexTextBuilder(){
}

LatexTextBuilder::~LatexTextBuilder(){

}

void LatexTextBuilder::init(GasExplosionCalc* calculator){
    m_appCalc = calculator;
}

QString LatexTextBuilder::getTextStage01(){
    QString res;
    res = R"(
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
        \text{продуктов горения.}
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
    QString res, res0, res1a, res1b, res2;

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
            $T_g = {%2}$
        \end{gather}
        \\
        \text{    Tочность расчёта температуры между последними итерациями }
        \text{$\Delta T <{%3}$}
        \text{$^{\text{\LARGE\circ}}$C}
    )";

    QString str11 = getNumericString(m_appCalc->getCalcIterationCounter());
    QString str12 = getNumericString(m_appCalc->getInitTg());
    QString str13 = getNumericString(m_appCalc->getAaccuracyCalcAvgT());

    res2 = res2.arg(str11).arg(str12).arg(str13);

    if (m_appCalc->getInitTg("first") >= 950) {
        res = res0 + res1a + res2;
    }
    else {
        res = res0 + res1b + res2;
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
                     \left(\frac{{%5} + 273}{273}\right)} = %6
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

QString LatexTextBuilder::getNumericString(double nVal, QString fmt){
    QString res;
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

    return res;
}

// End latexTextBuilder.cpp
