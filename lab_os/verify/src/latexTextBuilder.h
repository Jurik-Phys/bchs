// Begin latexTextBuilder.h

#ifndef LATEXTEXTBUILDER_H
#define LATEXTEXTBUILDER_H 1

#include "gasExplosionCalc.h"

class LatexTextBuilder {

    public:
        LatexTextBuilder();
        ~LatexTextBuilder();

        void init(GasExplosionCalc*);
        QString getTextStage01();
        QString getTextStage02();
        QString getTextStage03();
        QString getTextStage04();

    private:
        GasExplosionCalc* m_appCalc;
        QString getNumericString(double, QString fmt = "short");
};

#endif
// End latexTextBuilder.h
