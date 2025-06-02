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

    m_labSolver->getSolve();
    m_oData = m_labSolver->getOutData();
    m_rData = m_labSolver->getRawData();
}

QAppWindow::~QAppWindow(){
}

void QAppWindow::setAboutFrame(){
    m_aboutFrame = new QFrame();
    m_aboutFrame->setFrameShape(QFrame::StyledPanel);
    m_aboutFrame->setFrameShadow(QFrame::Plain);
    m_aboutFrame->setFixedHeight(35);
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
//    QObject::connect(m_inputSelector, &QComboBox::activated,
//                                        this, &QAppWindow::dataVariantSelected);

    // Right of header block
    QPushButton* runSolve = new QPushButton();
    runSolve->setText("Запустить расчёт");
//    QObject::connect(runSolve, &QPushButton::clicked, this,
//                                          &QAppWindow::gasExplosionCalculation);

    hHeaderFrameLayout->addWidget(labTitle);
    hHeaderFrameLayout->addWidget(m_inputSelector);
    hHeaderFrameLayout->addWidget(runSolve);
}

void QAppWindow::setInputTableFrame(){
    m_inputTableFrame = new QFrame();
    m_inputTableFrame->setFrameShape(QFrame::StyledPanel);
    m_inputTableFrame->setFrameShadow(QFrame::Raised);
    m_inputTableFrame->setFixedHeight(70);
    m_inputTableFrame->setFixedWidth(m_appWindowWidth/2.33);

    m_table = new QTableWidget(8, 2, m_inputTableFrame);

    // Set custom delegate to table
    // CustomTableDelegate* delegate = new CustomTableDelegate(m_table);
    // m_table->setItemDelegate(delegate);

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
                                "до приёмника уд. волны (R<sub>уд</sub>), м."
    };

    for (int row = 0; row < m_table->rowCount(); ++row) {
        QLabel *label = new QLabel(valueNameList[row]);
        m_table->setCellWidget(row,0, label);
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

void QAppWindow::setResFrame(){
    QString noResult("…");

    // (*) Widget
    m_resFrame = new QFrame();
    m_resFrame->setFrameShape(QFrame::StyledPanel);
    m_resFrame->setFrameShadow(QFrame::Raised);
    m_resFrame->setFixedWidth(m_appWindowWidth/2.33);

    // (**) Widget layout
    // Set parent "m_resFrame" for skip
    // m_resFrame->setLayout(m_resFrameVLayout)
    QVBoxLayout* resFrameVLayout = new QVBoxLayout(m_resFrame);

    // Title
    QLabel* resTitle = new QLabel();
    resTitle->setText("Результаты расчёта");
    resTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    resTitle->setFont(font);

    // 1.
    QString waveBurstPressureText = QString("- избыточное давление воздуха "
                            " на фронте ударной волны p<sub>s</sub> = %1 кПа;");
    m_waveBurstPressureOut = new QLabel(waveBurstPressureText.arg(noResult));

    // 2.
    QString compressImpulseText = QString("- удельный положительный импульс"
            "фазы сжатия i<sub>s</sub> = %1 Па·с;");
    m_compressImpulseOut = new QLabel(compressImpulseText.arg(noResult));

    // 3.
    QString relWaveBurstText = QString("- относительное избыточное давление "
            "воздуха на фронте ударной волны P<sub>отн</sub> = %1 кПа;");
    m_relativeWaveBurstPressureOut = new QLabel(relWaveBurstText.arg(noResult));

    // 4.
    QString compressImpulseAText = QString("- импульс фазы сжатия, приведённый "
            "к атм. давлению и массе тела человека "
                "i\u0305<sub>s</sub><sup>'</sup> = %1 √Па·с/кг<sup>1/3</sup>");
    m_compressImpulseOut = new QLabel(compressImpulseText.arg(noResult));
    m_compressImpulseAOut = new QLabel(compressImpulseAText.arg(noResult));
    // m_compressImpulseAOut = new QLabel(compressImpulseAText.arg(noResult));

    // 5.
    QString compressImpulseBText = QString("- импульс фазы сжатия, приведённый "
            " к масе тела человека i\u0305<sub>s</sub><sup>''</sup> = %1 "
            "Па·с/кг<sup>1/3</sup>;");
    m_compressImpulseBOut = new QLabel(compressImpulseBText.arg(noResult));

    // 6.
    QString loudText = QString("- уровень звукового давления у приёмника "
            "ударной волны L<sub>p</sub> = %1 дБ.");
    m_loudOut = new QLabel(loudText.arg(noResult));

    resFrameVLayout->addWidget(resTitle);
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
    QVBoxLayout* vTeXLayout = new QVBoxLayout(m_texFrame);
    vTeXLayout->setContentsMargins(0, 0, 0, 0);

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding,
                                                        QSizePolicy::Expanding);
    vTeXLayout->addSpacerItem(spacer);

    vTeXBaseFrameLayout->addWidget(m_texFrame);

    m_texScrollArea = new QScrollArea(m_texBaseFrame);
    m_texScrollArea->setWidgetResizable(true);
    m_texScrollArea->setWidget(m_texFrame);

// connect(this, &QAppWindow::texBaseFrameResized,
//                                        this, &QAppWindow::onScrollResized);
}

void QAppWindow::onScrollResized(int width, int height){
    m_texScrollArea->setFixedWidth(width);
    m_texScrollArea->setFixedHeight(height);
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

    QPushButton* closeBtn = new QPushButton;
    QPushButton* clearBtn = new QPushButton;
    QPushButton* saveBtn  = new QPushButton;

    closeBtn->setText("Выход");
    saveBtn->setText("Сохранить");
    clearBtn->setText("Сброс");

    btnFrameHLayout->addWidget(saveBtn);
    btnFrameHLayout->addWidget(clearBtn);
    btnFrameHLayout->addWidget(closeBtn);

    // m_btnFrame->setLayout(btnFrameHLayout);

    QObject::connect(closeBtn, &QPushButton::clicked,
                                                    this, &QAppWindow::appExit);
    // QObject::connect(clearBtn, &QPushButton::clicked,
    //                                            this, &QAppWindow::clearTexForm);
    // QObject::connect(clearBtn, &QPushButton::clicked,
    //                                            this, &QAppWindow::rstInputData);
    // QObject::connect(saveBtn, &QPushButton::clicked,
    //                                             this, &QAppWindow::saveTexForm);

}

void QAppWindow::appExit(){
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение выхода", "Вы действительно хотите выйти?",
                                            QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }

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
// End appWindow.cpp
