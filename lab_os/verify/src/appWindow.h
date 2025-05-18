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
#include <QFileDialog>
#include <QHeaderView>
#include <QStringList>
#include <QLabel>
#include "microtex.h"
#include "qt_texwidget.h"
#include "gasExplosionCalc.h"
#include "latexTextBuilder.h"
#include "customTableDelegate.h"

class QAppWindow : public QWidget {

    Q_OBJECT

    public:
        QAppWindow(QWidget *parent = 0);
        ~QAppWindow();

    signals:
        void scrollContainerResized(int, int);

    protected:
        TeXWidget*    texwidget;
        QTableWidget* m_table;
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
        void appExit();
        void clearTexForm();
        void dataVariantSelected(int);

    private:
        const int    m_appWindowWidth = 1390;
        const int    m_appWindowHeight = 750;
        const int    m_texTextSize = 18;
        QFrame*      m_headFrame;
        QFrame*      m_inputFrame;
        QFrame*      m_texFrame;
        QFrame*      m_sumFrame;
        QFrame*      m_btnFrame;
        QVBoxLayout* m_appVLayout;
        QScrollArea* m_texScrollArea;
        QFrame*      m_scrollContainer;
        QVBoxLayout* m_sumFrameVLayout;
        QLabel*      m_fireTime;
        QString      m_fireTimeText;
        QLabel*      m_qDensity;
        QString      m_qDensityText;
        QLabel*      m_eyeRadiationTime;
        QString      m_eyeRadiationTimeText;
        QLabel*      m_fireBallEyeSize;
        QString      m_fireBallEyeSizeText;
        QLabel*      m_eyeEnDensity;
        QString      m_eyeEnDensityText;

        void setHeaderFrame();
        void setInputDataFrame();
        void setTexFrame();
        void setBtnFrame();
        void setSummaryFrame();
        void setAppLayout();

        void addToTexFrame(QString);
        void updResultFrame(GasExplosionCalc*);
        void rstResultFrame();
        void saveTexForm();

        struct InputData {
            double carbonAtomCount;
            double hydrogenAtomCount;
            double gasHeatOfCombustion;
            double upperFlammabilityLimit;
            double gasDensity;
            double normalFlameSpeed;
            double gasMass;
            double distanceToReceiver;
            double eyeRadiationTime;
        };
};

#endif
// End appWindow.h
