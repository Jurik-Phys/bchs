// Begin latexTextBuilder.h

#ifndef LATEXTEXTBUILDER_H
#define LATEXTEXTBUILDER_H 1

#include "gasExplosionCalc.h"

class LatexTextBuilder {

    public:
        LatexTextBuilder();
        ~LatexTextBuilder();

        void init(GasExplosionCalc*);
        QString getTextStep01();
        QString getTextStep02();
        QString getTextStep03();

    private:
        GasExplosionCalc* m_appCalc;
        QString getNumericString(double, QString fmt = "short");
};

#endif
// End latexTextBuilder.h
