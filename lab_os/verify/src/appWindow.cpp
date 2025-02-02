// Begin appWindow.cpp

#include "appWindow.h"
#include "qt_texwidget.h"

QAppWindow::QAppWindow(QWidget *parent) : QWidget(parent) {

    this->resize(m_appWindowWidth, m_appWindowHeight);
    this->setWindowTitle("Лаб. работа \"Техногенный взрыв\". "
                         "Проверочный расчёт");

    setHeaderFrame();
    setInputDataFrame();
    setTexFrame();
    setSummaryFrame();
    setAppLayout();

    // Calculator
    m_gasExplosionCalc = new GasExplosionCalc();

    // Latex text generator
    m_latexTextBuilder = new LatexTextBuilder();
    m_latexTextBuilder->init(m_gasExplosionCalc);
}

QAppWindow::~QAppWindow(){
}

void QAppWindow::showErrorMessge(QString errorMessage){
    QMessageBox msgBox(this);
    msgBox.setStyleSheet("QLabel{min-width: 175px;}");
    // msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Ошибка");
    msgBox.setText("Что-то пошло не так ...");
    msgBox.setInformativeText(errorMessage);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void QAppWindow::getInputData(){
    qDebug() << "[II] Get input data from table";
    for (int row = 0; row < table->rowCount(); ++row) {
        QTableWidgetItem* item = table->item(row, 1);

        if (item) {
            bool ok = false;
            double value = item->text().toDouble(&ok);
            if (ok) {
                switch (row) {
                    case 0:
                        m_gasExplosionCalc->setCarbonAtomCount(value);
                        qDebug() << " >>  CarbonAtomCount:        " << m_gasExplosionCalc->getCarbonAtomCount();
                        break;
                    case 1:
                        m_gasExplosionCalc->setHydrogenAtomCount(value);
                        qDebug() << " >>  HydrogenAtomCount:      " << m_gasExplosionCalc->getHydrogenAtomCount();
                        break;
                    case 2:
                        m_gasExplosionCalc->setGasHeatOfCombustion(value);
                        qDebug() << " >>  GasHeatOfCombustion:    " << m_gasExplosionCalc->getGasHeatOfCombustion();
                        break;
                    case 3:
                        m_gasExplosionCalc->setUpperFlammabilityLimit(value);
                        qDebug() << " >>  UpperFlammabilityLimit: " << m_gasExplosionCalc->getUpperFlammabilityLimit();
                        break;
                    case 4:
                        m_gasExplosionCalc->setGasDensity(value);
                        qDebug() << " >>  GasDensity:             " << m_gasExplosionCalc->getGasDensity();
                        break;
                    case 5:
                        m_gasExplosionCalc->setNormalFlameSpeed(value);
                        qDebug() << " >>  NormalFlameSpeed:       " << m_gasExplosionCalc->getNormalFlameSpeed();
                        break;
                    case 6:
                        m_gasExplosionCalc->setGasMass(value);
                        qDebug() << " >>  GasMass:                " << m_gasExplosionCalc->getGasMass();
                        break;
                    case 7:
                        m_gasExplosionCalc->setDistanceToReceiver(value);
                        qDebug() << " >>  DistanceToReceiver:     " << m_gasExplosionCalc->getDistanceToReceiver();
                        break;
                    case 8:
                        m_gasExplosionCalc->setEyeRadiationTime(value);
                        qDebug() << " >>  EyeRadiationTime:       " << m_gasExplosionCalc->getEyeRadiationTime();
                        break;
                }
            } else {
                qDebug() << "[EE] Read table value error!!!";
                showErrorMessge("[EE] Read table value error!!!");
            }
        }
    }
}

void QAppWindow::gasExplosionCalculation(){
    getInputData();
    m_gasExplosionCalc->getResult();

    addToTexFrame(m_latexTextBuilder->getTextStage01());
    addToTexFrame(m_latexTextBuilder->getTextStage02());
    addToTexFrame(m_latexTextBuilder->getTextStage03());
}

void QAppWindow::setTexFrame(){
    // ScrollContaner for used QScrollArea
    m_scrollContainer = new QFrame();
    m_scrollContainer->setFrameShape(QFrame::NoFrame);
    m_scrollContainer->setFrameShadow(QFrame::Raised);

    QVBoxLayout* scrollContainerLayout = new QVBoxLayout(m_scrollContainer);
    scrollContainerLayout->setContentsMargins(0, 0, 0, 0);

    m_texFrame = new QFrame;
    m_texFrame->setFrameShape(QFrame::NoFrame);
    m_texFrame->setStyleSheet("background-color: white;");
    m_texLayout = new QVBoxLayout(m_texFrame);
    m_texLayout->setContentsMargins(0, 0, 0, 0);

    // For upper position of the new texWidget
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding,
                                                        QSizePolicy::Expanding);
    m_texLayout->addSpacerItem(spacer);

    scrollContainerLayout->addWidget(m_texFrame);

    m_texScrollArea = new QScrollArea(m_scrollContainer);
    m_texScrollArea->setWidgetResizable(true);
    m_texScrollArea->setWidget(m_texFrame);
    m_texScrollArea->resize(m_appWindowWidth/2  - 20,
                            m_scrollContainer->frameRect().height());

    connect(this, &QAppWindow::scrollContainerResized,
            this, &QAppWindow::onScrollResized);
}

void QAppWindow::onScrollResized(int width, int height){
    m_texScrollArea->setFixedHeight(height);
    m_texScrollArea->setFixedWidth(width);
}

void QAppWindow::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        emit scrollContainerResized(m_scrollContainer->frameRect().width(),
                                    m_scrollContainer->frameRect().height());
}

void QAppWindow::setHeaderFrame(){
    m_headFrame = new QFrame;
    QHBoxLayout* hHeadFrameLayout = new QHBoxLayout(m_headFrame);

    m_headFrame->setFrameShape(QFrame::StyledPanel);
    m_headFrame->setFrameShadow(QFrame::Raised);
    m_headFrame->setFixedHeight(70);
    m_headFrame->setFixedWidth(m_appWindowWidth/2  - 10);

    // Left header block
    QLabel *labTitle = new QLabel("Лабораторная работа\nТехногенный пожар");
    labTitle->setAlignment(Qt::AlignCenter);

    QFont font = labTitle->font();
    font.setPointSize(14);
    font.setBold(true);
    labTitle->setFont(font);

    // Center of header block
    QComboBox *inputDataType = new QComboBox();
    inputDataType->addItem("Ручной ввод исходных данных");

    // Right of header block
    QPushButton* clkBtn = new QPushButton();
    clkBtn->setText("Запустить расчёт");
    QObject::connect(clkBtn, &QPushButton::clicked, this, &QAppWindow::gasExplosionCalculation);

    hHeadFrameLayout->addWidget(labTitle);
    hHeadFrameLayout->addWidget(inputDataType);
    hHeadFrameLayout->addWidget(clkBtn);
}

void QAppWindow::setInputDataFrame(){
    m_inputFrame = new QFrame;
    m_inputFrame->setFrameShape(QFrame::StyledPanel);
    m_inputFrame->setFrameShadow(QFrame::Raised);
    m_inputFrame->setFixedWidth(m_appWindowWidth/2  - 10);

    table = new QTableWidget(9, 2, m_inputFrame);

    QHBoxLayout* hInputFrameLayout = new QHBoxLayout(m_inputFrame);
    hInputFrameLayout->addWidget(table);

    // Horizontal
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()
           ->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Vertical
    int tableTotalHeight = table->horizontalHeader()->height();
    for (int row = 0; row < table->rowCount(); ++row) {
        tableTotalHeight += table->rowHeight(row);
    }
    table->setFixedHeight(tableTotalHeight + 2);
    m_inputFrame->setFixedHeight(tableTotalHeight + 27);

    QStringList tableHeaders;
    tableHeaders << "Название величины" << "Значение величины";
    table->setHorizontalHeaderLabels(tableHeaders);

    valueNameList <<
        "Число атомов углерода в углеводородном газе (x), ед." <<
        "Число атомов водорода в углеводородном газе (y), ед." <<
        "Теплота сгорания углеводородного газа (Q), МДж/м<sup>3</sup>" <<
        "Верхний концентрационный предел воспламенения "
                                    "углеводородного газа (e<sub>в</sub>), %" <<
        "Плотность углеводородного газа при нормальных условиях "
                                          "(ρ<sub>0</sub>), кг/м<sup>3</sup>" <<
        "Нормальная скорость распространения пламени (V<sub>н</sub>), м/c" <<
        "Масса углеводородного газа, образовавшего огневой шар (G), т" <<
        "Расстояние от зоны горения до приёмника инфракрасного излучения "
                                                                     "(h), м" <<
        "Время действия излучения на сетчатку глаза человека "
                                                         "(t<sub>имп</sub>), с";

    valuesList << "3"     <<
                  "8"     <<
                  "93.6"  <<
                  "9.5"   <<
                  "1.9"   <<
                  "0.4"   <<
                  "50.0"  <<
                  "200.0" <<
                  "0.1";

    for (int row = 0; row < table->rowCount(); ++row) {
        QLabel *label = new QLabel(valueNameList[row]);
        table->setCellWidget(row,0, label);
        table->setItem(row, 1, new QTableWidgetItem(valuesList[row]));
    }
}

void QAppWindow::setSummaryFrame(){
    m_sumFrame = new QFrame;
    m_sumFrame->setFrameShape(QFrame::StyledPanel);
    m_sumFrame->setFrameShadow(QFrame::Raised);
    m_sumFrame->setFixedWidth(m_appWindowWidth/2  - 10);
}

void QAppWindow::setAppLayout(){
    // Window layout
    // AAAAA CCCCC
    // BBBBB CCCCC
    m_appVLayout = new QVBoxLayout;
    QHBoxLayout* hAppWindowLayout = new QHBoxLayout();
    m_appVLayout->addLayout(hAppWindowLayout);

    QVBoxLayout* vLColumnLayout = new QVBoxLayout();
    QVBoxLayout* vRColumnLayout = new QVBoxLayout();

    hAppWindowLayout->addLayout(vLColumnLayout);
    hAppWindowLayout->addLayout(vRColumnLayout);

    vLColumnLayout->addWidget(m_headFrame);
    vLColumnLayout->addWidget(m_inputFrame);
    vLColumnLayout->addWidget(m_sumFrame);
    vRColumnLayout->addWidget(m_scrollContainer);

    setLayout(m_appVLayout);
}

void QAppWindow::addToTexFrame(QString text){

    TeXWidget* texWidget = new TeXWidget(nullptr, m_texTextSize);
    texWidget->setLaTeX(text.toStdString());

    // Workaround for a potential bug where no TexWidget is painted
    // with a spacer in the layout
    QFrame* texFrame = new QFrame;
    texFrame->setFrameShape(QFrame::NoFrame);
    texFrame->setFrameShadow(QFrame::Plain);
    texFrame->setFixedHeight(texWidget->getRenderHeight());
    texFrame->setFixedWidth(m_appWindowWidth/2  - 40);
    QVBoxLayout* vTexFrame = new QVBoxLayout(texFrame);
    vTexFrame->setContentsMargins(0, 0, 0, 0);
    vTexFrame->addWidget(texWidget);

    // Add vTexFrame to m_texLayout
    m_texLayout->insertWidget(m_texLayout->count() - 1, texFrame, 0,
                            Qt::AlignmentFlag::AlignTop);
}
// End appWindow.cpp
