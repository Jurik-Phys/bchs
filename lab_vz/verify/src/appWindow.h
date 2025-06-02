// Begin appWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H 1

#include <QApplication>
#include <QBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QMessageBox>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>
#include <QFrame>
#include <QPushButton>
#include <QHeaderView>
#include "labSolver.h"
#include "labDataInput.h"

class QAppWindow : public QWidget {

    Q_OBJECT

    public:
        QAppWindow(QWidget *parent = 0);
        ~QAppWindow();

        void appExit();

    signals:
        void texBaseFrameResized(int, int);

    public slots:
        void onScrollResized(int, int);

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private:
        const int m_appWindowWidth = 1390;
        const int m_appWindowHeight = 750;
        LabSolver* m_labSolver;
        QFrame*    m_aboutFrame;
        QFrame*    m_headerFrame;
        QFrame*    m_inputTableFrame;
        QFrame*    m_texFrame;
        QFrame*    m_texBaseFrame;
        QScrollArea*  m_texScrollArea;
        QFrame*    m_resFrame;
        QFrame*    m_btnFrame;
        QComboBox* m_inputSelector;
        QPushButton* m_runSolve;
        QTableWidget* m_table;
        void setAboutFrame();
        void setHeaderFrame();
        void setInputTableFrame();
        void setTeXFrame();
        void setResFrame();
        void setBtnFrame();
        void setMainWindowLayout();

        InputData m_iData;
        OutData   m_oData;
        RawData   m_rData;

        QLabel* m_waveBurstPressureOut;
        QLabel* m_compressImpulseOut;
        QLabel* m_relativeWaveBurstPressureOut;
        QLabel* m_compressImpulseAOut;
        QLabel* m_compressImpulseBOut;
        QLabel* m_loudOut;
};


#endif
// End appWindow.h
