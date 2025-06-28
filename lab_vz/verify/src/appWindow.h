// Begin appWindow.h
#ifndef APPWINDOW_H
#define APPWINDOW_H 1

#include <QApplication>
#include <QBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>
#include <QFrame>
#include <QPushButton>
#include <QHeaderView>
#include "labSolver.h"
#include "labDataInput.h"
#include "texBuilder.h"
#include "customTableDelegate.h"
#include "microtex.h"
#include "qt_texwidget.h"

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
        void dataVariantSelected(int);
        void rstInputData();
        void labSolveAndTex();

    protected:
        void resizeEvent(QResizeEvent *event) override;

    private:
        const int m_appWindowWidth = 1390;
        const int m_appWindowHeight = 750;
        const int m_texTextSize = 18;
        LabSolver* m_labSolver;
        TeXBuilder* m_texBuilder;
        QVBoxLayout* m_vTeXLayout;
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
        void clsTeXFrame();
        void setResFrame();
        void updResFrame();
        void rstResFrame(QString status = "OK");
        void setBtnFrame();
        void setMainWindowLayout();
        void setTableValues();
        void syncTableValues(int, int);
        void addToTeXFrame(QString);
        void saveTeXForm();

        InputData m_iData;
        OutData   m_oData;

        QLabel* m_resTitle;
        QLabel* m_waveBurstPressureOut;
        QLabel* m_compressImpulseOut;
        QLabel* m_relativeWaveBurstPressureOut;
        QLabel* m_compressImpulseAOut;
        QLabel* m_compressImpulseBOut;
        QLabel* m_loudOut;
        QString* m_waveBurstPressureText;
        QString* m_compressImpulseText;
        QString* m_relWaveBurstText;
        QString* m_compressImpulseAText;
        QString* m_compressImpulseBText;
        QString* m_loudText;

        QPushButton* m_closeBtn;
        QPushButton* m_clearBtn;
        QPushButton* m_saveBtn;
};


#endif
// End appWindow.h
