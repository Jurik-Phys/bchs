// Begin appWindow.cpp

#include "appWindow.h"

QAppWindow::QAppWindow(QWidget *parent) : QWidget(parent){
    this->resize(m_appWindowWidth, m_appWindowHeight);
    this->setWindowTitle("Лабораторная работа «Техногенный взрыв». "
                                                        "Проверочный расчёт");

    // Initialize input data throught demo data
    m_iData = labDataVariants[0];

    setAboutFrame();
    setHeaderFrame();
    setInputTableFrame();
    setTeXFrame();
    setResFrame();
    setBtnFrame();
    setMainWindowLayout();

    m_labSolver = new LabSolver();
    m_labSolver->setInputData(m_iData);

    m_texBuilder = new TeXBuilder();
    m_texBuilder->init(m_labSolver);
}

QAppWindow::~QAppWindow(){
}

void QAppWindow::setAboutFrame(){
    m_aboutFrame = new QFrame();
    m_aboutFrame->setFrameShape(QFrame::StyledPanel);
    m_aboutFrame->setFrameShadow(QFrame::Plain);
    m_aboutFrame->setFixedHeight(38);
    m_aboutFrame->setFixedWidth(m_appWindowWidth/2.33);

    QHBoxLayout* aboutFrameHLayout = new QHBoxLayout(m_aboutFrame);

    QString text = "Овсянников Ю.М. "
                "<style>a { text-decoration: none; }</style>"
                "(<a href=jurik-phys.net>https://jurik-phys.net</a>) "
                "по материалам кафедры БЖД "
                "ИГЭУ (<a href=http://ispu.ru>http://ispu.ru</a>)";

    QLabel* textOutLabel = new QLabel(text);
    textOutLabel->setOpenExternalLinks(true);
    textOutLabel->setTextFormat(Qt::RichText);
    textOutLabel->setAlignment(Qt::AlignCenter);

    aboutFrameHLayout->addWidget(textOutLabel);
}

void QAppWindow::setHeaderFrame(){
    // * Widget
    m_headerFrame = new QFrame();
    m_headerFrame->setFrameShape(QFrame::StyledPanel);
    m_headerFrame->setFrameShadow(QFrame::Raised);
    m_headerFrame->setFixedHeight(70);
    m_headerFrame->setFixedWidth(m_appWindowWidth/2.33);

    // * Widget layout
    QHBoxLayout* hHeaderFrameLayout = new QHBoxLayout(m_headerFrame);

    // Left header block
    QLabel *labTitle = new QLabel("Лабораторная работа\n«Техногенный взрыв»");
    labTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    labTitle->setFont(font);

    // Center of header block
    m_inputSelector = new QComboBox();
    m_inputSelector->addItem("Ручной ввод данных");
    m_inputSelector->addItem("Вариант расчёта №1");
    m_inputSelector->addItem("Вариант расчёта №2");
    m_inputSelector->addItem("Вариант расчёта №3");
    m_inputSelector->addItem("Вариант расчёта №4");
    m_inputSelector->addItem("Вариант расчёта №5");
    m_inputSelector->addItem("Вариант расчёта №6");
    m_inputSelector->addItem("Вариант расчёта №7");
    m_inputSelector->addItem("Вариант расчёта №8");
    m_inputSelector->addItem("Вариант расчёта №9");
    m_inputSelector->addItem("Вариант расчёта №10");
    QObject::connect(m_inputSelector, &QComboBox::activated,
                                        this, &QAppWindow::dataVariantSelected);

    // Right of header block
    QPushButton* runSolve = new QPushButton();
    runSolve->setText("Запустить расчёт");
    QObject::connect(runSolve, &QPushButton::clicked, this,
                                                   &QAppWindow::labSolveAndTex);
    QObject::connect(runSolve, &QPushButton::clicked,[this]() {
                                                 m_saveBtn->setEnabled(true);});

    hHeaderFrameLayout->addWidget(labTitle);
    hHeaderFrameLayout->addWidget(m_inputSelector);
    hHeaderFrameLayout->addWidget(runSolve);
}

void QAppWindow::dataVariantSelected(int index){
    // Load data to vairable;
    m_iData = labDataVariants[index];

    // Set edit only for manual input
    if (index != 0){
        m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    else {
        m_table->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }

    // Set table values
    setTableValues();
}

void QAppWindow::labSolveAndTex(){
    m_labSolver->setInputData(m_iData);
    m_labSolver->getSolve();

    m_oData = m_labSolver->getOutData();
    updResFrame();

    // Clear TeX frame
    clsTeXFrame();

    QString inputDataType = m_inputSelector->currentText();
    addToTeXFrame(m_texBuilder->getInitDataTeX(inputDataType));
    addToTeXFrame(m_texBuilder->getStage01_BurstEnergyTeX());
    addToTeXFrame(m_texBuilder->getStage02_TNTEquivalentTeX());
    addToTeXFrame(m_texBuilder->getStage03_WaveBurstPressureTeX());
    addToTeXFrame(m_texBuilder->getStage04_AirFlowSpeedTeX());
    addToTeXFrame(m_texBuilder->getStage05_WaveBurstSpeedTeX());
    addToTeXFrame(m_texBuilder->getStage06_StandoffTimeTeX());
    addToTeXFrame(m_texBuilder->getStage07_FinalizeSolutionTeX());
    addToTeXFrame(m_texBuilder->getResultsTeX());
}

void QAppWindow::updResFrame(){
    // 1.
    QString res1 = QString::number(m_oData.waveBurstPressure, 'f', 2);
    m_waveBurstPressureOut->setText(m_waveBurstPressureText->arg(res1));

    // 2.
    QString res2 = QString::number(m_oData.compressImpulse, 'f', 2);
    m_compressImpulseOut->setText(m_compressImpulseText->arg(res2));

    // 3.
    QString res3 = QString::number(m_oData.relativeWaveBurstPressure, 'f', 3);
    m_relativeWaveBurstPressureOut->setText(m_relWaveBurstText->arg(res3));

    // 4.
    QString res4 = QString::number(m_oData.compressImpulseA, 'f', 3);
    m_compressImpulseAOut->setText(m_compressImpulseAText->arg(res4));

    // 5.
    QString res5 = QString::number(m_oData.compressImpulseB, 'f', 2);
    m_compressImpulseBOut->setText(m_compressImpulseBText->arg(res5));

    // 6.
    QString res6 = QString::number(m_oData.loud, 'f',1);
    m_loudOut->setText(m_loudText->arg(res6));
}

void QAppWindow::rstResFrame(QString status){

    if (status == "EE"){
        // Reset after solver error
        m_resTitle->setStyleSheet("color: red;");
    }
    else {
        m_resTitle->setStyleSheet("");
    }

    QString noRes("…");
    m_waveBurstPressureOut->setText(m_waveBurstPressureText->arg(noRes));
    m_compressImpulseOut->setText(m_compressImpulseText->arg(noRes));
    m_relativeWaveBurstPressureOut->setText(m_relWaveBurstText->arg(noRes));
    m_compressImpulseAOut->setText(m_compressImpulseAText->arg(noRes));
    m_compressImpulseBOut->setText(m_compressImpulseBText->arg(noRes));
    m_loudOut->setText(m_loudText->arg(noRes));
}
void QAppWindow::setInputTableFrame(){
    m_inputTableFrame = new QFrame();
    m_inputTableFrame->setFrameShape(QFrame::StyledPanel);
    m_inputTableFrame->setFrameShadow(QFrame::Raised);
    m_inputTableFrame->setFixedHeight(70);
    m_inputTableFrame->setFixedWidth(m_appWindowWidth/2.33);

    m_table = new QTableWidget(8, 2, m_inputTableFrame);

    // Set custom delegate to table
    CustomTableDelegate* delegate = new CustomTableDelegate(m_table);
    m_table->setItemDelegate(delegate);

    QObject::connect(m_table, &QTableWidget::cellChanged, this,
                                                  &QAppWindow::syncTableValues);

    QHBoxLayout* hInputFrameLayout = new QHBoxLayout(m_inputTableFrame);
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
    m_inputTableFrame->setFixedHeight(tableTotalHeight + 27);

    QStringList tableHeaders;
    tableHeaders << "Название величины" << "Значение";
    m_table->setHorizontalHeaderLabels(tableHeaders);

    setTableValues();
}

void QAppWindow::setTableValues(){

    // Check exists name to prevent duplicate name values
    if ( m_table->item(1, 1) == nullptr ) {

        QStringList valueNameList = {
            "Диаметр цилиндрического резервуара со сжатым газом (d), м",
            "Длина цилиндрического резервуара со сжатым газом (l), м",
            "Показатель адиабаты сжатого газа в резервуаре (k<sub>г</sub>)",
            "Избыточное давление сжатого газа в резервуаре при "
                                                  "взрыве (p<sub>1</sub>), кПа",
            "Плотность газа при нормальных условиях "
                                            "(ρ<sub>г</sub>), кг/м<sup>3</sup>",
            "Температура воздуха (t), °C",
            "Коэффициент перехода (k<sub>ув</sub>) ",
            "Расстояние от центра взрывной системы"
                                    "до приёмника уд. волны (R<sub>уд</sub>), м"
        };

        for (int row = 0; row < m_table->rowCount(); ++row) {
            QLabel *label = new QLabel(valueNameList[row]);
            m_table->setCellWidget(row,0, label);
        }
    }

    for (int row = 0; row < m_table->rowCount(); ++row) {
        QString itemValue;
        switch (row){
            case 0:
                itemValue = QString::number(m_iData.gasTankDiameter);
                break;
            case 1:
                itemValue = QString::number(m_iData.gasTankLength);
                break;
            case 2:
                itemValue = QString::number(m_iData.gasAdiabaticIndex);
                break;
            case 3:
                itemValue = QString::number(m_iData.tankBurstPressure);
                break;
            case 4:
                itemValue = QString::number(m_iData.ntpTankGasDensity);
                break;
            case 5:
                itemValue = QString::number(m_iData.airTemperature);
                break;
            case 6:
                itemValue = QString::number(m_iData.releaseFraction);
                break;
            case 7:
                itemValue = QString::number(m_iData.standoffDistance);
                break;
            default:
                itemValue = "-/-";
        }
        QTableWidgetItem* item = new QTableWidgetItem(itemValue);
        m_table->setItem(row,1, item);
    }
}

void QAppWindow::syncTableValues(int row, int column){

    QString tableValue;
    tableValue = m_table->item(row, column)->text();

    // Write table value to m_iData if values none equal
    switch (row){
        case 0:
            if (QString::number(m_iData.gasTankDiameter) != tableValue){
                m_iData.gasTankDiameter = tableValue.toDouble();
            }
            break;
        case 1:
            if ( QString::number(m_iData.gasTankLength) != tableValue){
                m_iData.gasTankLength = tableValue.toDouble();
            }
            break;
        case 2:
            if ( QString::number(m_iData.gasAdiabaticIndex) != tableValue){
                m_iData.gasAdiabaticIndex = tableValue.toDouble();
            }
            break;
        case 3:
            if ( QString::number(m_iData.tankBurstPressure) != tableValue){
                m_iData.tankBurstPressure = tableValue.toDouble();
            }
            break;
        case 4:
            if ( QString::number(m_iData.ntpTankGasDensity) != tableValue){
                m_iData.ntpTankGasDensity = tableValue.toDouble();
            }
            break;
        case 5:
            if ( QString::number(m_iData.airTemperature) != tableValue){
                m_iData.airTemperature = tableValue.toDouble();
            }
            break;
        case 6:
            if ( QString::number(m_iData.releaseFraction) != tableValue){
                m_iData.releaseFraction = tableValue.toDouble();
            }
            break;
        case 7:
            if ( QString::number(m_iData.standoffDistance) != tableValue){
                m_iData.standoffDistance = tableValue.toDouble();
            }
            break;
    }
}

void QAppWindow::setResFrame(){
    QString noRes("…");

    // (*) Widget
    m_resFrame = new QFrame();
    m_resFrame->setFrameShape(QFrame::StyledPanel);
    m_resFrame->setFrameShadow(QFrame::Raised);
    m_resFrame->setFixedWidth(m_appWindowWidth/2.33);

    // (**) Widget layout
    QVBoxLayout* resFrameVLayout = new QVBoxLayout(m_resFrame);

    // Title
    m_resTitle = new QLabel();
    m_resTitle->setText("Результаты расчёта");
    m_resTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    m_resTitle->setFont(font);

    // 1.
    m_waveBurstPressureText = new QString("- избыточное давление воздуха "
                            " на фронте ударной волны p<sub>s</sub> = %1 кПа;");
    m_waveBurstPressureOut = new QLabel(m_waveBurstPressureText->arg(noRes));

    // 2.
    m_compressImpulseText = new QString("- удельный положительный импульс"
            "фазы сжатия i<sub>s</sub> = %1 Па·с;");
    m_compressImpulseOut = new QLabel(m_compressImpulseText->arg(noRes));

    // 3.
    m_relWaveBurstText = new QString("- относительное избыточное давление "
                   "воздуха на фронте ударной волны P<sub>отн</sub> = %1;");
    m_relativeWaveBurstPressureOut = new QLabel(m_relWaveBurstText->arg(noRes));

    // 4.
    m_compressImpulseAText = new QString("- импульс фазы сжатия, приведённый "
            "к атм. давлению и массе тела человека "
                "i\u0305<sub>s</sub><sup>'</sup> = %1 Па<sup>1/2</sup>"
                                                        "·с/кг<sup>1/3</sup>;");
    m_compressImpulseAOut = new QLabel(m_compressImpulseAText->arg(noRes));

    // 5.
    m_compressImpulseBText = new QString("- импульс фазы сжатия, приведённый "
            " к масе тела человека i\u0305<sub>s</sub><sup>''</sup> = %1 "
            "Па·с/кг<sup>1/3</sup>;");
    m_compressImpulseBOut = new QLabel(m_compressImpulseBText->arg(noRes));

    // 6.
    m_loudText = new QString("- уровень звукового давления у приёмника "
            "ударной волны L<sub>p</sub> = %1 дБ.");
    m_loudOut = new QLabel(m_loudText->arg(noRes));

    resFrameVLayout->addWidget(m_resTitle);
    resFrameVLayout->addWidget(m_waveBurstPressureOut);
    resFrameVLayout->addWidget(m_compressImpulseOut);
    resFrameVLayout->addWidget(m_relativeWaveBurstPressureOut);
    resFrameVLayout->addWidget(m_compressImpulseAOut);
    resFrameVLayout->addWidget(m_compressImpulseBOut);
    resFrameVLayout->addWidget(m_loudOut);
}

void QAppWindow::setTeXFrame(){
    // (*) Widget
    m_texBaseFrame = new QFrame();
    m_texBaseFrame->setFrameShape(QFrame::NoFrame);
    m_texBaseFrame->setFrameShadow(QFrame::Raised);

    // (*) Widget layout
    QVBoxLayout* vTeXBaseFrameLayout = new QVBoxLayout(m_texBaseFrame);
    vTeXBaseFrameLayout->setContentsMargins(0, 0, 0, 0);

    // (**) Widget
    m_texFrame = new QFrame();
    m_texFrame->setFrameShape(QFrame::NoFrame);
    m_texFrame->setStyleSheet("background-color: white;");

    // (**) Widget layout
    m_vTeXLayout = new QVBoxLayout(m_texFrame);
    m_vTeXLayout->setContentsMargins(0, 0, 0, 0);

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding,
                                                        QSizePolicy::Expanding);
    m_vTeXLayout->addSpacerItem(spacer);

    vTeXBaseFrameLayout->addWidget(m_texFrame);

    m_texScrollArea = new QScrollArea(m_texBaseFrame);
    m_texScrollArea->setWidgetResizable(true);
    m_texScrollArea->setWidget(m_texFrame);
}

void QAppWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    emit texBaseFrameResized(m_texBaseFrame->frameRect().width(),
                                        m_texBaseFrame->frameRect().height());
}

void QAppWindow::setBtnFrame(){
    m_btnFrame = new QFrame;
    m_btnFrame->setFrameShape(QFrame::StyledPanel);
    m_btnFrame->setFrameShadow(QFrame::Raised);
    m_btnFrame->setFixedHeight(70);
    m_btnFrame->setFixedWidth(m_appWindowWidth/2.33);

    QHBoxLayout* btnFrameHLayout = new QHBoxLayout(m_btnFrame);

    m_closeBtn = new QPushButton;
    m_clearBtn = new QPushButton;
    m_saveBtn  = new QPushButton;

    m_closeBtn->setText("Выход");
    m_saveBtn->setText("Сохранить");
    m_saveBtn->setEnabled(false);
    m_clearBtn->setText("Сброс");

    btnFrameHLayout->addWidget(m_saveBtn);
    btnFrameHLayout->addWidget(m_clearBtn);
    btnFrameHLayout->addWidget(m_closeBtn);

    QObject::connect(m_closeBtn, &QPushButton::clicked,
                                                    this, &QAppWindow::appExit);
    QObject::connect(m_clearBtn, &QPushButton::clicked,
                                               this, &QAppWindow::rstInputData);
    QObject::connect(m_clearBtn, &QPushButton::clicked,[this]() {
                                                m_saveBtn->setEnabled(false);});
    QObject::connect(m_clearBtn, &QPushButton::clicked,
                                                this, &QAppWindow::clsTeXFrame);
    QObject::connect(m_saveBtn, &QPushButton::clicked,
                                                this, &QAppWindow::saveTeXForm);

}

void QAppWindow::appExit(){
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение выхода", "Вы действительно хотите выйти?",
                                            QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }

}

void QAppWindow::rstInputData(){
    m_inputSelector->setCurrentIndex(0);
    dataVariantSelected(0);
    rstResFrame();
}

void QAppWindow::setMainWindowLayout(){
    QHBoxLayout* hAppLayout = new QHBoxLayout();

    QVBoxLayout* vLColumnLayout = new QVBoxLayout();
    QVBoxLayout* vRColumnLayout = new QVBoxLayout();

    hAppLayout->addLayout(vLColumnLayout);
    hAppLayout->addLayout(vRColumnLayout);

    vLColumnLayout->addWidget(m_aboutFrame);
    vLColumnLayout->addWidget(m_headerFrame);
    vLColumnLayout->addWidget(m_inputTableFrame);
    vLColumnLayout->addWidget(m_resFrame);
    vLColumnLayout->addWidget(m_btnFrame);
    vRColumnLayout->addWidget(m_texScrollArea);

    this->setLayout(hAppLayout);
}

void QAppWindow::clsTeXFrame(){
    qDebug() << "\n[II] Clear tex \"frames\" from output";

    // One is a spacer in m_texLayout;
    int framesCount = m_vTeXLayout->count() - 1;
    qDebug() << "[II] Separate tex frames count:"<< framesCount;
    for (int i = framesCount; i >= 0; --i) {
        QLayoutItem* item = m_vTeXLayout->itemAt(i);
        if (item) {
            QWidget* widget = item->widget();
            if (widget){
                m_vTeXLayout->removeWidget(widget);
                widget->deleteLater();
            }
            else {
                qDebug() << "[II] Probably a layout or stretch with index" << i;
            }
        }
    }
    qDebug() << "[II] Clear tex \"frames\" done";
}

void QAppWindow::addToTeXFrame(QString text){

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
    m_vTeXLayout->insertWidget(m_vTeXLayout->count() - 1, texFrame, 0,
                                                   Qt::AlignmentFlag::AlignTop);
}

void QAppWindow::saveTeXForm(){
    qDebug() << "[II] save LaTeX solver result";

    QString fileName = QFileDialog::getSaveFileName(this,
                             "Сохранить изображение", "", "PNG Images (*.png)");

    if (!fileName.isEmpty()){
        if (!fileName.endsWith(".png", Qt::CaseInsensitive)){
            fileName += ".png";
        }

        QPixmap pixmap(m_texFrame->size());
        m_texFrame->render(&pixmap);

        if (!pixmap.save(fileName)){
            qDebug() << "[WW] Не удалось сохранить изображение";
        }
    }
}
// End appWindow.cpp
