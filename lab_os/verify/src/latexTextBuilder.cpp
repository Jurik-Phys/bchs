// Begin latexTextBuilder.cpp

#include "latexTextBuilder.h"

LatexTextBuilder::LatexTextBuilder(){
}

LatexTextBuilder::~LatexTextBuilder(){

}

void LatexTextBuilder::init(GasExplosionCalc* calculator){
    m_appCalc = calculator;
}

QString LatexTextBuilder::getTextStep01(){
    QString res;
    res = R"(
        \text{1. Задаётся средняя температура $(T_{g})$ зоны горения в первом }
        \text{приближении, $^{\Large{\circ}}$C.}\\
        \begin{align}
            T_{g} =  %1.
        \end{align}
    )" ;

    QString str1 = QString::number(m_appCalc->getInitTg(), 'f',1);

    res = res.arg(str1);

    return res;
}

QString LatexTextBuilder::getTextStep02(){
    QString res;
    res = R"(
        \text{2. По значению предельной концентрации газа в богатой смеси }
        \text{определяется}\\ \text{коэффициент расхода воздуха ($n$) }
        \text{для первой стадии горения.}
        \\
        \begin{align}
            n = \frac{(100 - e_\text{в}) \cdot 0.24}{e_\text{в} \cdot O_1}.
        \end{align}
        \\
        \text{    $O_1$ - удельное теоретическое количество кислорода при полном }
        \text{горении} \\ \text{углеводородного газа $C_x H_y$, м$^3$/м$^3$.}\\
        \text{    Для пропана $C_{%1} H_{%2}$:}\\
        \begin{gather}
            O_1 = x + \frac{y}{4} = %3 + \frac{%4}{4} = {%5}. \\

            n = \frac{(100 - e_\text{в})\cdot 0.2415}{e_\text{в}\cdot O_1} =
            \frac{(100 - {%6})\cdot 0.2415}{{%6}\cdot {%7}} = %8.
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

QString LatexTextBuilder::getNumericString(double nVal, QString fmt){
    QString res;
    if (nVal - (int)nVal < 1E-6){
        res = QString::number(nVal, 'f', 0);
    }
    else {
        if (fmt == "verb"){
            res = QString::number(nVal, 'f', 5);
        }
        else {
            res = QString::number(nVal, 'f', 1);
        }
    }

    return res;
}

// End latexTextBuilder.cpp
