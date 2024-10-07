// Begin appWindow.cpp

#include "appWindow.h"
#include "qt_texwidget.h"

QAppWindow::QAppWindow(QWidget *parent) : QWidget(parent) {
    this->resize(800,350);
    this->setWindowTitle("Qt draw formula demo");

    // Main windows layout
    QHBoxLayout* layout = new QHBoxLayout;

    int text_size = 28;
    // the TeX widget is on the left
    _texwidget = new TeXWidget(nullptr, text_size);
    _texwidget->setMinimumWidth(120);

    layout->addWidget(_texwidget);

    setLayout(layout);

    QString text = "2^2 = 4;\\ \\int_a^b x^2 dx;\\ \\text{Привет Мир; Hello, World!!!}\\ V=\\frac{dx}{dt}";
    _texwidget->setLaTeX(text.toStdString());
}

QAppWindow::~QAppWindow(){
}

// End appWindow.cpp
