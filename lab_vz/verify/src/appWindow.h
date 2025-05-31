// Begin appWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H 1

#include <QApplication>
#include <QWidget>
#include "labSolver.h"

class QAppWindow : public QWidget {

    Q_OBJECT

    public:
        QAppWindow(QWidget *parent = 0);
        ~QAppWindow();

    private:
        const int m_appWindowWidth = 1390;
        const int m_appWindowHeight = 750;
        LabSolver* m_labSolver;
};


#endif
// End appWindow.h
