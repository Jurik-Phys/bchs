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

QString TeXBuilder::getNumericString(double num, QString fmt){
    // fmt: "pow", "verb", "short"
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
            if (fmt == "verb"){
                res = QString::number(num, 'f', 5).replace(".", "\\mathord{,}");
            }
            else {
                res = QString::number(num, 'f', 1).replace(".", "\\mathord{,}");
            }
       }
    }

    return res;
}

// End texBuilder.cpp
