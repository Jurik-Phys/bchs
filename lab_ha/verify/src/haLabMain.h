// Begin haLabMain.h
#ifndef HALABMAIN_H
#define HALABMAIN_H 1

#include "microtex.h"
#include "qt_texwidget.h"
#include <QApplication>

class QHaLabMain : public QWidget {

    Q_OBJECT

    public:
        QHaLabMain(QWidget *parent = 0);
        ~QHaLabMain();

        void AppExit();

    signals:

    public slots:

    private:
        const int m_appWindowWidth = 1390;
        const int m_appWindowHeight = 750;
        const int m_texTextSize = 18;
};
#endif
// End haLabMain.h
