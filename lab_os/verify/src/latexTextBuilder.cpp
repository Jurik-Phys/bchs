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
        \text{приближении, $^{\Large{\circ}}$C.}\\
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
