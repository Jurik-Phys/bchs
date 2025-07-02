// Begin haLabMain.h

#ifndef HALABMAIN_H
#define HALABMAIN_H 1

#include "microtex.h"
#include "qt_texwidget.h"
#include <QApplication>
#include "labSolverHA.h"

class QAppWindowHA : public QWidget {

    Q_OBJECT

    public:
        QAppWindowHA(QWidget *parent = 0);
        ~QAppWindowHA();

        void AppExit();

    signals:

    public slots:

    private:
        const int m_appWindowWidth = 1390;
        const int m_appWindowHeight = 750;
        const int m_texTextSize = 18;
        LabSolverHA* m_labSolverHA;
};
#endif

// End haLabMain.h
