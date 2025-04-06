// Begin appWindow.cpp

#include "appWindow.h"
#include "qt_texwidget.h"

QAppWindow::QAppWindow(QWidget *parent) : QWidget(parent) {

    this->resize(m_appWindowWidth, m_appWindowHeight);
    this->setWindowTitle("Лаб. работа «Техногенный пожар». "
                         "Проверочный расчёт");

    setHeaderFrame();
    setInputDataFrame();
    setTexFrame();
    setSummaryFrame();
    setBtnFrame();
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
    for (int row = 0; row < m_table->rowCount(); ++row) {
        QTableWidgetItem* item = m_table->item(row, 1);

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

    clearTexForm();

    addToTexFrame(m_latexTextBuilder->getTextStage01());
    addToTexFrame(m_latexTextBuilder->getTextStage02());
    addToTexFrame(m_latexTextBuilder->getTextStage03());
    addToTexFrame(m_latexTextBuilder->getTextStage04());
    addToTexFrame(m_latexTextBuilder->getTextStage05());
    addToTexFrame(m_latexTextBuilder->getTextStage06());
    addToTexFrame(m_latexTextBuilder->getTextStage07());
    addToTexFrame(m_latexTextBuilder->getTextStage08());
    addToTexFrame(m_latexTextBuilder->getTextStage09());

    updResultFrame(m_gasExplosionCalc);
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

    connect(this, &QAppWindow::scrollContainerResized,
            this, &QAppWindow::onScrollResized);
}

void QAppWindow::onScrollResized(int width, int height){
    m_texScrollArea->setFixedHeight(height);
    m_texScrollArea->setFixedWidth(width);
}

void QAppWindow::appExit(){
    QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Подтверждение выхода", "Вы действительно хотите выйти?",
            QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void QAppWindow::clearTexForm(){
    qDebug() << "\n[II] Clear tex \"frames\" from output";

    // One is a spacer in m_texLayout;
    int framesCount = m_texLayout->count() - 1;
    qDebug() << "[II] Separate tex frames count:"<< framesCount;
    for (int i = framesCount; i >= 0; --i) {
        QLayoutItem* item = m_texLayout->itemAt(i);
        if (item) {
            QWidget* widget = item->widget();
            if (widget){
                m_texLayout->removeWidget(widget);
                widget->deleteLater();
            }
            else {
                qDebug() << "[II] Probably a layout or stretch with index" << i;
            }
        }
    }
    qDebug() << "[II] Clear tex \"frames\" done";

    rstResultFrame();
}

void QAppWindow::dataVariantSelected(int index){

    QVector<InputData> inDataVariants = {
        {3.0, 8.0,  93.6, 9.5, 1.90, 0.40, 50.0, 200.0, 0.10},
        {3.0, 8.0,  94.0, 9.5, 1.90, 0.50, 20.0, 210.0, 0.10},
        {3.1, 8.2,  96.0, 9.2, 1.95, 0.49, 30.0, 220.0, 0.11},
        {3.2, 8.4,  98.0, 8.9, 2.00, 0.48, 40.0, 230.0, 0.12},
        {3.3, 8.6, 100.0, 8.6, 2.05, 0.47, 50.0, 240.0, 0.10},
        {3.4, 8.8, 102.0, 8.3, 2.10, 0.46, 20.0, 250.0, 0.11},
        {3.5, 9.0, 104.0, 8.0, 2.15, 0.45, 30.0, 260.0, 0.12},
        {3.6, 9.2, 108.0, 7.7, 2.20, 0.44, 40.0, 270.0, 0.10},
        {3.7, 9.4, 110.0, 7.4, 3.25, 0.43, 50.0, 280.0, 0.11},
        {3.8, 9.6, 112.0, 7.1, 3.30, 0.42, 20.0, 290.0, 0.12},
        {3.9, 9.8, 114.0, 6.8, 3.35, 0.41, 30.0, 300.0, 0.10}
    };

    InputData data = inDataVariants[index];

    m_table->setItem(0, 1,
                   new QTableWidgetItem(QString::number(data.carbonAtomCount)));
    m_table->setItem(1, 1,
                 new QTableWidgetItem(QString::number(data.hydrogenAtomCount)));
    m_table->setItem(2, 1,
               new QTableWidgetItem(QString::number(data.gasHeatOfCombustion)));
    m_table->setItem(3, 1,
            new QTableWidgetItem(QString::number(data.upperFlammabilityLimit)));
    m_table->setItem(4, 1,
                   new QTableWidgetItem(QString::number(data.gasDensity)));
    m_table->setItem(5, 1,
                  new QTableWidgetItem(QString::number(data.normalFlameSpeed)));
    m_table->setItem(6, 1,
                   new QTableWidgetItem(QString::number(data.gasMass)));
    m_table->setItem(7, 1,
                new QTableWidgetItem(QString::number(data.distanceToReceiver)));
    m_table->setItem(8, 1,
                  new QTableWidgetItem(QString::number(data.eyeRadiationTime)));

    // Edit only for manual input data
    if (index != 0){
        m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    else {
        m_table->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }
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
    m_headFrame->setFixedWidth(m_appWindowWidth/2.33);

    // Left header block
    QLabel *labTitle = new QLabel("Лабораторная работа\n«Техногенный пожар»");
    labTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    labTitle->setFont(font);

    // Center of header block
    QComboBox *inputDataType = new QComboBox();
    inputDataType->addItem("Ручной ввод данных");
    inputDataType->addItem("Вариант расчёта №1");
    inputDataType->addItem("Вариант расчёта №2");
    inputDataType->addItem("Вариант расчёта №3");
    inputDataType->addItem("Вариант расчёта №4");
    inputDataType->addItem("Вариант расчёта №5");
    inputDataType->addItem("Вариант расчёта №6");
    inputDataType->addItem("Вариант расчёта №7");
    inputDataType->addItem("Вариант расчёта №8");
    inputDataType->addItem("Вариант расчёта №9");
    inputDataType->addItem("Вариант расчёта №10");
    QObject::connect(inputDataType, &QComboBox::activated,
                                        this, &QAppWindow::dataVariantSelected);

    // Right of header block
    QPushButton* clkBtn = new QPushButton();
    clkBtn->setText("Запустить расчёт");
    QObject::connect(clkBtn, &QPushButton::clicked, this,
                                          &QAppWindow::gasExplosionCalculation);

    hHeadFrameLayout->addWidget(labTitle);
    hHeadFrameLayout->addWidget(inputDataType);
    hHeadFrameLayout->addWidget(clkBtn);
}

void QAppWindow::setInputDataFrame(){
    m_inputFrame = new QFrame;
    m_inputFrame->setFrameShape(QFrame::StyledPanel);
    m_inputFrame->setFrameShadow(QFrame::Raised);
    m_inputFrame->setFixedWidth(m_appWindowWidth/2.33);

    m_table = new QTableWidget(9, 2, m_inputFrame);

    QHBoxLayout* hInputFrameLayout = new QHBoxLayout(m_inputFrame);
    hInputFrameLayout->addWidget(m_table);

    // Horizontal
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->horizontalHeader()
           ->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Vertical
    int tableTotalHeight = m_table->horizontalHeader()->height();
    for (int row = 0; row < m_table->rowCount(); ++row) {
        tableTotalHeight += m_table->rowHeight(row);
    }
    m_table->setFixedHeight(tableTotalHeight + 2);
    m_inputFrame->setFixedHeight(tableTotalHeight + 27);

    QStringList tableHeaders;
    tableHeaders << "Название величины" << "Значение";
    m_table->setHorizontalHeaderLabels(tableHeaders);

    QStringList valueNameList = {
        "Число атомов углерода в углеводородном газе (x), ед.",
        "Число атомов водорода в углеводородном газе (y), ед.",
        "Теплота сгорания углеводородного газа (Q), МДж/м<sup>3</sup>",
        "Верхний концентрационный предел воспламенения "
                                    "углеводородного газа (e<sub>в</sub>), %",
        "Плотность углеводородного газа при нормальных условиях "
                                          "(ρ<sub>0</sub>), кг/м<sup>3</sup>",
        "Нормальная скорость распространения пламени (V<sub>н</sub>), м/c",
        "Масса углеводородного газа, образовавшего огневой шар (G), т",
        "Расстояние от зоны горения до приёмника инфракрасного излучения "
                                                                     "(h), м",
        "Время действия излучения на сетчатку глаза человека "
                                                       "(t<sub>имп</sub>), с" };

    for (int row = 0; row < m_table->rowCount(); ++row) {
        QLabel *label = new QLabel(valueNameList[row]);
        m_table->setCellWidget(row,0, label);
    }

    // Initial data values (manual input with r/w)
    dataVariantSelected(0);
}

void QAppWindow::setSummaryFrame(){
    QString noResult("...");

    m_sumFrame = new QFrame;
    m_sumFrame->setFrameShape(QFrame::StyledPanel);
    m_sumFrame->setFrameShadow(QFrame::Raised);
    m_sumFrame->setFixedWidth(m_appWindowWidth/2.33);

    // Summary data output initialize
    m_sumFrameVLayout   = new QVBoxLayout(m_sumFrame);

    // Set result output title
    QLabel* outTitle = new QLabel();
    outTitle->setText("Результаты расчёта");
    outTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    outTitle->setFont(font);

    // 1. fireTime
    m_fireTime          = new QLabel();
    m_fireTimeText = QString("- время выгорания газа в огневом шаре, "
                                                          "<i>t</i> = %1 c;" );

    // 2. qDensity
    m_qDensity          = new QLabel();
    m_qDensityText = QString("- плотность потока энергии у приёмника "
                   "инфракрасного излучения, <i>q</i> = %1 Вт/м<sup>2</sup>;");

    // 3. eyeRadiationTime
    m_eyeRadiationTime  = new QLabel();
    m_eyeRadiationTimeText = QString("- время действия излучения на сетчатку "
                              "глаза человека <i>t</i><sub>имп</sub> = %1 c;");

    // 4. fireBallEyeSize
    m_fireBallEyeSize   = new QLabel();
    m_fireBallEyeSizeText = QString("- диаметр отображения огневого шара на "
                                            "сетчатке глаза, <i>d</i> = %1 мм");

    // 5. eyeEnDensity
    m_eyeEnDensity      = new QLabel();
    m_eyeEnDensityText = QString("- удельная энергия, поздействующая на "
                "сетчатку глаза, <i>Q</i><sub>имп</sub> = %1 Дж/м<sup>2</sup>");

    m_sumFrameVLayout->addWidget(outTitle);
    m_sumFrameVLayout->addWidget(m_fireTime);
    m_sumFrameVLayout->addWidget(m_qDensity);
    m_sumFrameVLayout->addWidget(m_eyeRadiationTime);
    m_sumFrameVLayout->addWidget(m_fireBallEyeSize);
    m_sumFrameVLayout->addWidget(m_eyeEnDensity);

    // Устанавливаем layout на frame
    m_sumFrame->setLayout(m_sumFrameVLayout);

    m_fireTime->setText(m_fireTimeText.arg(noResult));
    m_qDensity->setText(m_qDensityText.arg(noResult));
    m_eyeRadiationTime->setText(m_eyeRadiationTimeText.arg(noResult));
    m_fireBallEyeSize->setText(m_fireBallEyeSizeText.arg(noResult));
    m_eyeEnDensity->setText(m_eyeEnDensityText.arg(noResult));
}

void QAppWindow::setBtnFrame(){
    m_btnFrame = new QFrame;
    m_btnFrame->setFrameShape(QFrame::StyledPanel);
    m_btnFrame->setFrameShadow(QFrame::Raised);
    m_btnFrame->setFixedHeight(70);
    m_btnFrame->setFixedWidth(m_appWindowWidth/2.33);

    QHBoxLayout* btnFrameHLayout = new QHBoxLayout(m_btnFrame);

    QPushButton* closeBtn = new QPushButton;
    QPushButton* clearBtn = new QPushButton;
    QPushButton* saveBtn  = new QPushButton;

    closeBtn->setText("Выход");
    saveBtn->setText("Сохранить");
    clearBtn->setText("Сброс");

    btnFrameHLayout->addWidget(saveBtn);
    btnFrameHLayout->addWidget(clearBtn);
    btnFrameHLayout->addWidget(closeBtn);

    m_btnFrame->setLayout(btnFrameHLayout);

    QObject::connect(closeBtn, &QPushButton::clicked,
                                                    this, &QAppWindow::appExit);
    QObject::connect(clearBtn, &QPushButton::clicked,
                                               this, &QAppWindow::clearTexForm);
    QObject::connect(saveBtn, &QPushButton::clicked,
                                                this, &QAppWindow::saveTexForm);

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
    vLColumnLayout->addWidget(m_btnFrame);
    vRColumnLayout->addWidget(m_scrollContainer);

    setLayout(m_appVLayout);
}

void QAppWindow::updResultFrame(GasExplosionCalc* calc){
    QString fireTimeVal = QString::number(calc->getFireTime());
    m_fireTime->setText(m_fireTimeText.arg(fireTimeVal));

    QString qDensityVal = QString::number(calc->getQDensity());
    m_qDensity->setText(m_qDensityText.arg(qDensityVal));

    QString eyeRadiationTime = QString::number(calc->getEyeRadiationTime());
    m_eyeRadiationTime->setText(m_eyeRadiationTimeText.arg(eyeRadiationTime));

    QString fireBallEyeSizeVal = QString::number(round(calc->
                                                         getFireBallEyeSize()));
    m_fireBallEyeSize->setText(m_fireBallEyeSizeText.arg(fireBallEyeSizeVal));

    QString eyeEnDensityVal = QString::number(calc->getEyeEnDensity());
    m_eyeEnDensity->setText(m_eyeEnDensityText.arg(eyeEnDensityVal));
}

void QAppWindow::rstResultFrame(){
    QString noResult("...");
    m_fireTime->setText(m_fireTimeText.arg(noResult));
    m_qDensity->setText(m_qDensityText.arg(noResult));
    m_eyeRadiationTime->setText(m_eyeRadiationTimeText.arg(noResult));
    m_fireBallEyeSize->setText(m_fireBallEyeSizeText.arg(noResult));
    m_eyeEnDensity->setText(m_eyeEnDensityText.arg(noResult));
}

void QAppWindow::saveTexForm(){
    qDebug() << "[II] save LaTeX output";

    QString fileName = QFileDialog::getSaveFileName(this,
                             "Сохранить изображение", "", "PNG Images (*.png)");

    if (!fileName.isEmpty()){
        if (!fileName.endsWith(".png", Qt::CaseInsensitive)){
            fileName += ".png";
        }

        QPixmap pixmap(m_texFrame->size());
        m_texFrame->render(&pixmap);

        if (!pixmap.save(fileName)) {
            qDebug() << "[WW] Не удалось сохранить изображение";
        }
    }
}

void QAppWindow::addToTexFrame(QString text){

    TeXWidget* texWidget = new TeXWidget(nullptr, m_texTextSize);
    texWidget->setLaTeX(text.toStdString());

    // Each added texWidget is located in a separate QFrame
    QFrame* texFrame = new QFrame;
    texFrame->setFrameShape(QFrame::NoFrame);
    texFrame->setFrameShadow(QFrame::Plain);
    texFrame->setFixedHeight(texWidget->getRenderHeight() - 18.0);
    texFrame->setFixedWidth(m_appWindowWidth/1.86);
    QVBoxLayout* vTexFrame = new QVBoxLayout(texFrame);
    vTexFrame->setContentsMargins(0, 0, 0, 0);
    vTexFrame->addWidget(texWidget);

    // Add vTexFrame to m_texLayout
    m_texLayout->insertWidget(m_texLayout->count() - 1, texFrame, 0,
                            Qt::AlignmentFlag::AlignTop);
}
// End appWindow.cpp
