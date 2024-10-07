// Begin appWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H 1

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "microtex.h"
#include "qt_texwidget.h"

class QAppWindow : public QWidget {

    Q_OBJECT

    public:
        QAppWindow(QWidget *parent = 0);
        ~QAppWindow();

    protected:
        TeXWidget* _texwidget;
};

#endif
// End appWindow.h
