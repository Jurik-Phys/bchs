// Begin appWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H 1

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTableWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QStringList>
#include <QLabel>
#include "microtex.h"
#include "qt_texwidget.h"
#include "gasExplosionCalc.h"
#include "latexTextBuilder.h"

class QAppWindow : public QWidget {

    Q_OBJECT

    public:
        QAppWindow(QWidget *parent = 0);
        ~QAppWindow();

    signals:
        void scrollContainerResized(int, int);

    protected:
        TeXWidget*    texwidget;
        QTableWidget* table;
        QStringList   valueNameList;
        QStringList   valuesList;

        void getInputData();
        void gasExplosionCalculation();

        void showErrorMessge(QString);
        void resizeEvent(QResizeEvent *event) override;

        GasExplosionCalc* m_gasExplosionCalc;
        LatexTextBuilder* m_latexTextBuilder;
        QVBoxLayout*      m_texLayout;

    private slots:
        void onScrollResized(int, int);

    private:
        const int    m_appWindowWidth = 1600;
        const int    m_appWindowHeight = 750;
        const int    m_texTextSize = 18;
        QFrame*      m_headFrame;
        QFrame*      m_inputFrame;
        QFrame*      m_texFrame;
        QFrame*      m_sumFrame;
        QVBoxLayout* m_appVLayout;
        QScrollArea* m_texScrollArea;
        QFrame*      m_scrollContainer;

        void setHeaderFrame();
        void setInputDataFrame();
        void setTexFrame();
        void setSummaryFrame();
        void setAppLayout();

        void addToTexFrame(QString);

};

#endif
// End appWindow.h
