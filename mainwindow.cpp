#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_settings(new connectionDialog)
    , m_Protocol(new USBCommProtocol)
{
    ui->setupUi(this);

    QThread::currentThread()->setObjectName("Mainwindow thread");
    qInfo() << "Mainwindow created on thread: " << QThread::currentThread();
    InitMainWindow();
    InitActionConnection();
    InitConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*****************************************************************************
 * Initializations
 ****************************************************************************/
void MainWindow::InitMainWindow()
{
    /* Widget syle */
//    QPalette p = palette();
//    p.setColor(QPalette::Base, Qt::black);
//    p.setColor(QPalette::Text, Qt::cyan);
//    ui->serialLogPlainText->setPalette(p);

//    ui->serialLogPlainText->setMaximumBlockCount(4096);
//    ui->serialLogPlainText->setOverwriteMode(true);

    setButtonsStatus(Button_Group::SerialButton, false);
    setButtonsStatus(Button_Group::ConfigModeOnlyButton, false);
    setButtonsStatus(Button_Group::GeneralImuButton, false);

    /* Fill combo box */
    InitIMUParamBox();

    /* Plots */
    InitPlots();

    /* Status bar */
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::InitActionConnection()
{
    ;
}

void MainWindow::InitConnection()
{
    connect(&mSaveUserConfigTimer, SIGNAL(timeout()), this, SLOT(saveUserConfigTimeout()));
}

void MainWindow::InitPlots()
{
    QColor FFTPlotFillColor(40,40,40,100);

    /* Accelerations */
    QFont legendFont = font();
    legendFont.setPointSize(10);

    //X-Axis
    ui->accXPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
    ui->accXPlot->legend->setVisible(false);
    ui->accXPlot->legend->setFont(legendFont);
    ui->accXPlot->legend->setSelectedFont(legendFont);
    ui->accXPlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->accXPlot->axisRect()->setAutoMargins(QCP::msAll);
    ui->accXPlot->yAxis->setLabel("X-Axis[g]");
//    ui->accXPlot->xAxis->setLabel("Time");
    ui->accXPlot->yAxis->setRange(-8.0, 8.0);
    ui->accXPlot->clearGraphs();
    ui->accXPlot->addGraph(ui->accXPlot->xAxis, ui->accXPlot->yAxis);
    ui->accXPlot->graph(SIGNAL_CHARTS)->setPen(QPen(Qt::red));
    ui->accXPlot->graph(SIGNAL_CHARTS)->setName("X-Acceleration");
    ui->accXPlot->graph(SIGNAL_CHARTS)->setSelectable(QCP::stSingleData);
    ui->accXPlot->addGraph(ui->accXPlot->xAxis2, ui->accXPlot->yAxis2);
    ui->accXPlot->xAxis2->setVisible(true);
    ui->accXPlot->yAxis2->setVisible(true);
    ui->accXPlot->graph(FFT_CHARTS)->setBrush(QBrush(FFTPlotFillColor));
    ui->accXPlot->yAxis2->setRange(0, 1);
    ui->accXPlot->yAxis2->setLabel("PSD[dB/Hz]");
    ui->accXPlot->graph(FFT_CHARTS)->setPen(QPen(Qt::black));
    ui->accXPlot->graph(FFT_CHARTS)->setName("FFT");
    ui->accXPlot->graph(FFT_CHARTS)->setSelectable(QCP::stSingleData);
    ui->accXPlot->xAxis2->setRange(0, 4000);
    ui->accXPlot->xAxis2->ticker()->setTickCount(20);
    ui->accXPlot->addGraph();
    ui->accXPlot->graph(INTERRUPT_CHARTS)->setPen(QPen(Qt::darkYellow));
    ui->accXPlot->graph(INTERRUPT_CHARTS)->setSelectable(QCP::stNone);

    connect(ui->accXPlot, &QCustomPlot::mousePress, this, &MainWindow::accXPlotPressed);
    connect(ui->accXPlot, &QCustomPlot::mouseRelease, this, &MainWindow::mouseReleasedOnPlot);
    connect(ui->accXPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::plotSelectionChange);

    /*
    accXcursor = new QCPItemLine(ui->accXPlot);
    accXcursor->setPen(QPen(Qt::black));
    accXcursor->start->setCoords(0, 0);
    accXcursor->end->setCoords(0, 0);
    connect(ui->accXPlot, &QCustomPlot::mouseMove, this, &MainWindow::showAccXCursor);
    */



    //Y-Axis
    ui->accYPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
    ui->accYPlot->legend->setVisible(false);
    ui->accYPlot->legend->setFont(legendFont);
    ui->accYPlot->legend->setSelectedFont(legendFont);
    ui->accYPlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->accYPlot->axisRect()->setAutoMargins(QCP::msAll);
    ui->accYPlot->yAxis->setLabel("Y-Axis[g]");
//    ui->accYPlot->xAxis->setLabel("Time");
    ui->accYPlot->yAxis->setRange(-8.0, 8.0);
    ui->accYPlot->clearGraphs();
    ui->accYPlot->addGraph();
    ui->accYPlot->graph(SIGNAL_CHARTS)->setPen(QPen(Qt::green));
    ui->accYPlot->graph(SIGNAL_CHARTS)->setName("Y-Acceleration");
    ui->accYPlot->graph(SIGNAL_CHARTS)->setSelectable(QCP::stSingleData);
    ui->accYPlot->addGraph(ui->accYPlot->xAxis2, ui->accYPlot->yAxis2);
    ui->accYPlot->xAxis2->setVisible(true);
    ui->accYPlot->yAxis2->setVisible(true);
    ui->accYPlot->graph(FFT_CHARTS)->setBrush(QBrush(FFTPlotFillColor));
    ui->accYPlot->yAxis2->setRange(0, 1);
    ui->accYPlot->yAxis2->setLabel("PSD[dB/Hz]");
    ui->accYPlot->graph(FFT_CHARTS)->setPen(QPen(Qt::black));
    ui->accYPlot->graph(FFT_CHARTS)->setName("FFT");
    ui->accYPlot->graph(FFT_CHARTS)->setSelectable(QCP::stSingleData);
    ui->accYPlot->xAxis2->setRange(0, 4000);
    ui->accYPlot->xAxis2->ticker()->setTickCount(20);
    ui->accYPlot->addGraph();
    ui->accYPlot->graph(INTERRUPT_CHARTS)->setPen(QPen(Qt::darkYellow));
    ui->accYPlot->graph(INTERRUPT_CHARTS)->setSelectable(QCP::stNone);

    connect(ui->accYPlot, &QCustomPlot::mousePress, this, &MainWindow::accYPlotPressed);
    connect(ui->accYPlot, &QCustomPlot::mouseRelease, this, &MainWindow::mouseReleasedOnPlot);
    connect(ui->accYPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::plotSelectionChange);

    // Z-Axes
    ui->accZPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
    ui->accZPlot->legend->setVisible(false);
    ui->accZPlot->legend->setFont(legendFont);
    ui->accZPlot->legend->setSelectedFont(legendFont);
    ui->accZPlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->accZPlot->axisRect()->setAutoMargins(QCP::msAll);
    ui->accZPlot->yAxis->setLabel("Z-Axis[g]");
//    ui->accZPlot->xAxis->setLabel("Time");
    ui->accZPlot->yAxis->setRange(-8.0, 8.0);
    ui->accZPlot->clearGraphs();
    ui->accZPlot->addGraph();
    ui->accZPlot->graph(SIGNAL_CHARTS)->setPen(QPen(Qt::blue));
    ui->accZPlot->graph(SIGNAL_CHARTS)->setName("Z-Acceleration");
    ui->accZPlot->graph(SIGNAL_CHARTS)->setSelectable(QCP::stSingleData);
    ui->accZPlot->addGraph(ui->accZPlot->xAxis2, ui->accZPlot->yAxis2);
    ui->accZPlot->xAxis2->setVisible(true);
    ui->accZPlot->yAxis2->setVisible(true);
    ui->accZPlot->graph(FFT_CHARTS)->setBrush(QBrush(FFTPlotFillColor));
    ui->accZPlot->yAxis2->setRange(0, 1);
    ui->accZPlot->yAxis2->setLabel("PSD[dB/Hz]");
    ui->accZPlot->graph(FFT_CHARTS)->setPen(QPen(Qt::black));
    ui->accZPlot->graph(FFT_CHARTS)->setName("FFT");
    ui->accZPlot->graph(FFT_CHARTS)->setSelectable(QCP::stSingleData);
    ui->accZPlot->xAxis2->setRange(0, 4000);
    ui->accZPlot->xAxis2->ticker()->setTickCount(20);
    ui->accZPlot->addGraph();
    ui->accZPlot->graph(INTERRUPT_CHARTS)->setPen(QPen(Qt::darkYellow));
    ui->accZPlot->graph(INTERRUPT_CHARTS)->setSelectable(QCP::stNone);

    connect(ui->accZPlot, &QCustomPlot::mousePress, this, &MainWindow::accZPlotPressed);
    connect(ui->accZPlot, &QCustomPlot::mouseRelease, this, &MainWindow::mouseReleasedOnPlot);
    connect(ui->accZPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::plotSelectionChange);

    /* Rotations */
    ui->gyroPlot->setInteraction(QCP::iSelectPlottables, true);
    ui->gyroPlot->legend->setVisible(true);
    legendFont = font();
    legendFont.setPointSize(10);
    ui->gyroPlot->legend->setFont(legendFont);
    ui->gyroPlot->legend->setSelectedFont(legendFont);
    ui->gyroPlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->gyroPlot->yAxis->setLabel("rps[°/s]");
    ui->gyroPlot->xAxis->setLabel("Time");
    ui->gyroPlot->yAxis->setRange(-2000, 2000);
    ui->gyroPlot->clearGraphs();

    connect(ui->gyroPlot, &QCustomPlot::mousePress, this, &MainWindow::mousePressedOnPlot);
    connect(ui->gyroPlot, &QCustomPlot::mouseRelease, this, &MainWindow::mouseReleasedOnPlot);

    //X-Axis
    ui->gyroPlot->addGraph();
    ui->gyroPlot->graph(0)->setPen(QPen(Qt::red));
    ui->gyroPlot->graph(0)->setName("X-Rotation");

    //Y-Axis
    ui->gyroPlot->addGraph();
    ui->gyroPlot->graph(1)->setPen(QPen(Qt::green));
    ui->gyroPlot->graph(1)->setName("Y-Rotation");

    //Z-Axis
    ui->gyroPlot->addGraph();
    ui->gyroPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->gyroPlot->graph(2)->setName("Z-Rotation");

    /* Temperature */
    ui->tempPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
    ui->tempPlot->legend->setVisible(false);
    legendFont = font();
    legendFont.setPointSize(10);
    ui->tempPlot->legend->setFont(legendFont);
    ui->tempPlot->legend->setSelectedFont(legendFont);
    ui->tempPlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->tempPlot->axisRect()->setAutoMargins(QCP::msLeft | QCP::msBottom);
    ui->tempPlot->yAxis->setLabel("Temp[°C]");
//    ui->tempPlot->xAxis->setLabel("Time");
    ui->tempPlot->yAxis->setRange(-40, 85);
    ui->tempPlot->clearGraphs();

    ui->tempPlot->addGraph();
    ui->tempPlot->graph(0)->setPen(QPen(Qt::darkMagenta));
    ui->tempPlot->graph(0)->setName("Temperature");

//    /* DO */
//    ui->DOPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
//    ui->DOPlot->legend->setVisible(false);
//    legendFont = font();
//    legendFont.setPointSize(10);
//    ui->DOPlot->legend->setFont(legendFont);
//    ui->DOPlot->legend->setSelectedFont(legendFont);
//    ui->DOPlot->legend->setSelectableParts(QCPLegend::spItems);
//    ui->DOPlot->axisRect()->setAutoMargins(QCP::msAll);
//    ui->DOPlot->yAxis->setLabel("State[0:1]");
////    ui->DOPlot->xAxis->setLabel("Time");
//    ui->DOPlot->yAxis->setRange(0, 2);
//    ui->DOPlot->clearGraphs();
//    ui->DOPlot->addGraph();
//    ui->DOPlot->graph(0)->setPen(QPen(Qt::darkYellow));
//    ui->DOPlot->graph(0)->setName("DO");
//    ui->DOPlot->yAxis2->setVisible(true);
//    ui->DOPlot->yAxis2->setLabel("Dummy");

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerDataSlot()));
    mDataTimer.start(1000);

    connect(&mChartUpdateTimer, SIGNAL(timeout()), this, SLOT(timerChartUpdateSlot()));
    mChartUpdateTimer.start(CHARTS_REFRESH_MS);
}

void MainWindow::InitIMUParamBox()
{
    /* Fill combo box */
    //Accel ODR
//    Not supported by AC1 firmware: too much interrupt signals.
    ui->accelODRBox->addItem(QStringLiteral("32000Hz"), IIM42652_Accelerometer_32kHz);
    ui->accelODRBox->addItem(QStringLiteral("16000Hz"), IIM42652_Accelerometer_16kHz);
    ui->accelODRBox->addItem(QStringLiteral("8000Hz"), IIM42652_Accelerometer_8kHz);
    ui->accelODRBox->addItem(QStringLiteral("4000Hz"), IIM42652_Accelerometer_4kHz);
    ui->accelODRBox->addItem(QStringLiteral("2000Hz"), IIM42652_Accelerometer_2kHz);
    ui->accelODRBox->addItem(QStringLiteral("1000Hz"), IIM42652_Accelerometer_1kHz);
    ui->accelODRBox->addItem(QStringLiteral("500Hz"), IIM42652_Accelerometer_500Hz);
    ui->accelODRBox->addItem(QStringLiteral("200Hz"), IIM42652_Accelerometer_200Hz);
    ui->accelODRBox->addItem(QStringLiteral("100Hz"), IIM42652_Accelerometer_100Hz);
    ui->accelODRBox->addItem(QStringLiteral("50Hz"), IIM42652_Accelerometer_50Hz);
    ui->accelODRBox->addItem(QStringLiteral("25Hz"), IIM42652_Accelerometer_25Hz);
    ui->accelODRBox->addItem(QStringLiteral("12.5Hz"), IIM42652_Accelerometer_12_5Hz);

//    Need Low Power mode
//    ui->accelODRBox->addItem(QStringLiteral("6.25Hz"), IIM42652_Accelerometer_6_25Hz);
//    ui->accelODRBox->addItem(QStringLiteral("3.125Hz"), IIM42652_Accelerometer_3_125Hz);
//    ui->accelODRBox->addItem(QStringLiteral("1.5625Hz"), IIM42652_Accelerometer_1_5625Hz);

    ui->accelODRBox->setCurrentIndex(1);

    //Accel FSR
    ui->accelFSRBox->addItem(QStringLiteral("16G"), IIM42652_Accelerometer_16G);
    ui->accelFSRBox->addItem(QStringLiteral("8G"), IIM42652_Accelerometer_8G);
    ui->accelFSRBox->addItem(QStringLiteral("4G"), IIM42652_Accelerometer_4G);
    ui->accelFSRBox->addItem(QStringLiteral("2G"), IIM42652_Accelerometer_2G);

    ui->accelFSRBox->setCurrentIndex(1);

    //Gyro ODR
//    Not supported by AC1 firmware: too much interrupt signals.
    ui->gyroODRBox->addItem(QStringLiteral("32000Hz"), IIM42652_Gyroscope_32kHz);
    ui->gyroODRBox->addItem(QStringLiteral("16000Hz"), IIM42652_Gyroscope_16kHz);
    ui->gyroODRBox->addItem(QStringLiteral("8000Hz"), IIM42652_Gyroscope_8kHz);
    ui->gyroODRBox->addItem(QStringLiteral("4000Hz"), IIM42652_Gyroscope_4kHz);
    ui->gyroODRBox->addItem(QStringLiteral("2000Hz"), IIM42652_Gyroscope_2kHz);
    ui->gyroODRBox->addItem(QStringLiteral("1000Hz"), IIM42652_Gyroscope_1kHz);
    ui->gyroODRBox->addItem(QStringLiteral("500Hz"), IIM42652_Gyroscope_500Hz);
    ui->gyroODRBox->addItem(QStringLiteral("200Hz"), IIM42652_Gyroscope_200Hz);
    ui->gyroODRBox->addItem(QStringLiteral("100Hz"), IIM42652_Gyroscope_100Hz);
    ui->gyroODRBox->addItem(QStringLiteral("50Hz"), IIM42652_Gyroscope_50Hz);
    ui->gyroODRBox->addItem(QStringLiteral("25Hz"), IIM42652_Gyroscope_25Hz);
    ui->gyroODRBox->addItem(QStringLiteral("12.5Hz"), IIM42652_Gyroscope_12_5Hz);

    ui->gyroODRBox->setCurrentIndex(1);

    //Gyro FSR
    ui->gyroFSRBox->addItem(QStringLiteral("2000dps"), IIM42652_Gyroscope_2000dps);
    ui->gyroFSRBox->addItem(QStringLiteral("1000dps"), IIM42652_Gyroscope_1000dps);
    ui->gyroFSRBox->addItem(QStringLiteral("500dps"), IIM42652_Gyroscope_500dps);
    ui->gyroFSRBox->addItem(QStringLiteral("250dps"), IIM42652_Gyroscope_250dps);
    ui->gyroFSRBox->addItem(QStringLiteral("125dps"), IIM42652_Gyroscope_125dps);
    ui->gyroFSRBox->addItem(QStringLiteral("62.5dps"), IIM42652_Gyroscope_62_5dps);
    ui->gyroFSRBox->addItem(QStringLiteral("31.25dps"), IIM42652_Gyroscope_31_25dps);
    ui->gyroFSRBox->addItem(QStringLiteral("15.625dps"), IIM42652_Gyroscope_15_625dps);

    ui->gyroFSRBox->setCurrentIndex(0);

    //Accel BW
    ui->accelBWBox->addItem(QStringLiteral("Low latency, Dec2 at 8*ODR"), IIM42652_Accelerometer_ODR_LLx8);
    ui->accelBWBox->addItem(QStringLiteral("Low latency, Dec2 at ODR"), IIM42652_Accelerometer_ODR_LL);
    ui->accelBWBox->addItem(QStringLiteral("ODR/2"), IIM42652_Accelerometer_ODR_2);
    ui->accelBWBox->addItem(QStringLiteral("ODR/4"), IIM42652_Accelerometer_ODR_4);
    ui->accelBWBox->addItem(QStringLiteral("ODR/5"), IIM42652_Accelerometer_ODR_5);
    ui->accelBWBox->addItem(QStringLiteral("ODR/8"), IIM42652_Accelerometer_ODR_8);
    ui->accelBWBox->addItem(QStringLiteral("ODR/10"), IIM42652_Accelerometer_ODR_10);
    ui->accelBWBox->addItem(QStringLiteral("ODR/16"), IIM42652_Accelerometer_ODR_16);
    ui->accelBWBox->addItem(QStringLiteral("ODR/20"), IIM42652_Accelerometer_ODR_20);
    ui->accelBWBox->addItem(QStringLiteral("ODR/40"), IIM42652_Accelerometer_ODR_40);

    ui->accelBWBox->setCurrentIndex(3);

    //Gyro BW
    ui->gyroBWBox->addItem(QStringLiteral("Low latency, Dec2 at 8*ODR"), IIM42652_Gyroscope_ODR_LLx8);
    ui->gyroBWBox->addItem(QStringLiteral("Low latency, Dec2 at ODR"), IIM42652_Gyroscope_ODR_LL);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/2"), IIM42652_Gyroscope_ODR_2);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/4"), IIM42652_Gyroscope_ODR_4);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/5"), IIM42652_Gyroscope_ODR_5);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/8"), IIM42652_Gyroscope_ODR_8);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/10"), IIM42652_Gyroscope_ODR_10);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/16"), IIM42652_Gyroscope_ODR_16);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/20"), IIM42652_Gyroscope_ODR_20);
    ui->gyroBWBox->addItem(QStringLiteral("ODR/40"), IIM42652_Gyroscope_ODR_40);

    ui->gyroBWBox->setCurrentIndex(3);

    /* Interrupt */
    //Th
    ui->womXthSpinBox->setValue(98);
    ui->womXthValueLabel->setText("= " + QString::number(WOM_RESOLUTION * ui->womXthSpinBox->value(),'f',4) + "g");
    ui->womYthSpinBox->setValue(98);
    ui->womYthValueLabel->setText("= " + QString::number(WOM_RESOLUTION * ui->womYthSpinBox->value(),'f',4) + "g");
    ui->womZthSpinBox->setValue(98);
    ui->womZthValueLabel->setText("= " + QString::number(WOM_RESOLUTION * ui->womZthSpinBox->value(),'f',4) + "g");

    //WOM INT mode
    ui->womIntModeBox->addItem(QStringLiteral("OR accel Axes"), IMU_WOMIntMode_OR);
    ui->womIntModeBox->addItem(QStringLiteral("AND accel Axes"), IMU_WOMIntMode_AND);

    ui->womIntModeBox->setCurrentIndex(0);

    //WOM mode
    ui->womModeBox->addItem(QStringLiteral("Compare with start up"), IMU_WOMMode_Initial);
    ui->womModeBox->addItem(QStringLiteral("Compare with previous"), IMU_WOMMode_Previous);

    ui->womModeBox->setCurrentIndex(0);

    //SMD mode
    ui->smdModeBox->addItem(QStringLiteral("Disable SMD INT"), IMU_SMDMode_Disabled);
    ui->smdModeBox->addItem(QStringLiteral("SMD INT by WOM"), IMU_SMDMode_WOM);
    ui->smdModeBox->addItem(QStringLiteral("SMD INT by 2WOM in 1s"), IMU_SMDMode_WOM_short);
    ui->smdModeBox->addItem(QStringLiteral("SMD INT by 2WOM in 3s"), IMU_SMDMode_WOM_long);

    ui->smdModeBox->setCurrentIndex(0);
}

/*****************************************************************************
 * Style manager
 ****************************************************************************/
void MainWindow::setButtonsStatus(Button_Group group, bool EnableState)
{
    if (group == Button_Group::SerialButton)
    {
        if (EnableState)
        {
            ui->actionConnect->setEnabled(!EnableState);
            ui->actionDisconnect->setEnabled(EnableState);
            ui->actionSettings->setEnabled(!EnableState);
//            ui->SerialInputText->setEnabled(EnableState);
//            ui->sendButton->setEnabled(EnableState);
            ui->StartLogButton->setEnabled(EnableState && !AC1_ConfigMode_status);
            ui->setAC1ConfigModeButton->setEnabled(EnableState);
            ui->sendSaveUserConfigButton->setEnabled(EnableState);
        }
        else
        {
            ui->actionConnect->setEnabled(!EnableState);
            ui->actionDisconnect->setEnabled(EnableState);
            ui->actionSettings->setEnabled(!EnableState);
//            ui->SerialInputText->setEnabled(EnableState);
//            ui->sendButton->setEnabled(EnableState);
            ui->StartLogButton->setEnabled(EnableState && !AC1_ConfigMode_status);
            ui->setAC1ConfigModeButton->setEnabled(EnableState);
            ui->sendSaveUserConfigButton->setEnabled(EnableState);

            ui->IMUparametersBox->setPalette(this->style()->standardPalette());
        }
    }
    else if (group == Button_Group::GeneralImuButton)
    {
        if (EnableState)
        {
            ui->sendAccelODRButton->setEnabled(EnableState);
            ui->sendAccelFSRButton->setEnabled(EnableState);
            ui->sendGyroODRButton->setEnabled(EnableState);
            ui->sendGyroFSRButton->setEnabled(EnableState);
            ui->sendAllParamButton->setEnabled(EnableState && AC1_ConfigMode_status);
        }
        else
        {
            ui->sendAccelODRButton->setEnabled(EnableState);
            ui->sendAccelFSRButton->setEnabled(EnableState);
            ui->sendGyroODRButton->setEnabled(EnableState);
            ui->sendGyroFSRButton->setEnabled(EnableState);
            ui->sendAllParamButton->setEnabled(EnableState && AC1_ConfigMode_status);
        }
    }
    else if (group == Button_Group::ConfigModeOnlyButton)
    {
        if (EnableState)
        {
            QPalette palette = ui->IMUparametersBox->palette();
            QColor color;

            color = QColor::fromRgb(250,225,135);
            palette.setColor(QPalette::Window, color);
            ui->IMUparametersBox->setPalette(palette);

            ui->sendAccelBWButton->setEnabled(EnableState);
            ui->sendGyroBWButton->setEnabled(EnableState);
            ui->sendWomXthButton->setEnabled(EnableState);
            ui->sendWomYthButton->setEnabled(EnableState);
            ui->sendWomZthButton->setEnabled(EnableState);
            ui->sendWomIntModeButton->setEnabled(EnableState);
            ui->sendWomModeButton->setEnabled(EnableState);
            ui->sendSmdModeButton->setEnabled(EnableState);
            ui->sendAllParamButton->setEnabled(EnableState);
        }
        else
        {
            ui->IMUparametersBox->setPalette(this->style()->standardPalette());

            ui->sendAccelBWButton->setEnabled(EnableState);
            ui->sendGyroBWButton->setEnabled(EnableState);
            ui->sendWomXthButton->setEnabled(EnableState);
            ui->sendWomYthButton->setEnabled(EnableState);
            ui->sendWomZthButton->setEnabled(EnableState);
            ui->sendWomIntModeButton->setEnabled(EnableState);
            ui->sendWomModeButton->setEnabled(EnableState);
            ui->sendSmdModeButton->setEnabled(EnableState);
            ui->sendAllParamButton->setEnabled(EnableState);
        }
    }
}

/*****************************************************************************
 * Threads manager
 ****************************************************************************/
void MainWindow::createSerialThread(MainWindow *manager, const Serial::ConnectionSettings &settings,
                                    QList<QByteArray> *ptrRxBuff, QList<QByteArray> *ptrTxBuff,
                                    QMutex * ptrRxQueueMutex, QMutex * ptrTxQueueMutex)
{
    qInfo() << "Creating serial thread on thread: " << QThread::currentThread();
    Serial* m_Serial = new Serial();
    connect(manager, &MainWindow::serialDisconnect, m_Serial, &Serial::Quit);
    connect(manager, &MainWindow::commandSend, m_Serial, &Serial::sendData);
    connect(m_Serial, &Serial::commandFound, manager, &MainWindow::commandProcessing);
    connect(m_Serial, &Serial::connected, manager, &MainWindow::serialConnected);
    connect(m_Serial, &Serial::disconnected, manager, &MainWindow::serialDisconnected);
    connect(m_Serial, &Serial::error, manager, &MainWindow::serialError);
    connect(m_Serial, &Serial::dataReceived, manager, &MainWindow::serialDataCounting);

    m_Serial->Start(settings, ptrRxBuff, ptrTxBuff, ptrRxQueueMutex, ptrTxQueueMutex);
}

void MainWindow::_SEND_COMMANDS()
{
    emit commandSend();
}
void MainWindow::_ADD_COMMAND(QByteArray &command)
{
    QMutexLocker locker(&txQueueMutex);
    txCommandQueue.push_front(command);
    command.clear();
}
void MainWindow::_ADD_SEND_COMMAND(QByteArray &command)
{
    _ADD_COMMAND(command);
    _SEND_COMMANDS();
}

void MainWindow::createFFTThread(MainWindow *manager, QList<double> dataIn, double samplingRate)
{
    qInfo() << "Creating FFT thread on thread: " << QThread::currentThread();
    fft* m_FFT = new fft();
    connect(m_FFT, &fft::complete, manager, &MainWindow::fftElabFinished);

    m_FFT->Start(dataIn, samplingRate);
}

/*****************************************************************************
 * Filter manager
 ****************************************************************************/


/*****************************************************************************
 * Status bar manager
 ****************************************************************************/

void MainWindow::updateStatusMessage(const QString &message)
{
    ui->statusBar->showMessage(message);
}

/*****************************************************************************
 * Charts manager
 ****************************************************************************/
uint8_t MainWindow::AC1FirstReading()
{
    QByteArray command;

    m_Protocol->getTelemetryEn(command);
    _ADD_COMMAND(command);

    m_Protocol->getAccelODR(command);
    _ADD_COMMAND(command);

    m_Protocol->getAccelFSR(command);
    _ADD_COMMAND(command);

    m_Protocol->getGyroODR(command);
    _ADD_COMMAND(command);

    m_Protocol->getGyroFSR(command);
    _ADD_COMMAND(command);

    m_Protocol->getAccelBW(command);
    _ADD_COMMAND(command);

    m_Protocol->getGyroBW(command);
    _ADD_COMMAND(command);

    m_Protocol->getWOMXth(command);
    _ADD_COMMAND(command);

    m_Protocol->getWOMYth(command);
    _ADD_COMMAND(command);

    m_Protocol->getWOMZth(command);
    _ADD_COMMAND(command);

    m_Protocol->getWOMIntMode(command);
    _ADD_COMMAND(command);

    m_Protocol->getWOMMode(command);
    _ADD_COMMAND(command);

    m_Protocol->getSMDMode(command);
    _ADD_COMMAND(command);

    /*
    m_Protocol->setConfigMode(command, true);
    AC1_ConfigMode_status = false;
    _ADD_COMMAND(command);
    */

    _SEND_COMMANDS();
    return 0;
}

void MainWindow::checkVectorOverflow(QVector<double> &vector, int64_t limit)
{
    if (vector.size()>=limit)
    {
        vector.removeLast();
    }
}

bool MainWindow::checkFIFOValidData(int16_t FIFOValue)
{
    return FIFOValue != FIFO_INVALID_SAMPLE;
}

//void MainWindow::updateDOChart()
//{
//    static double currentTime = 0;

//    if (m_serialStatus)
//    {
//        double tempVal = CHARTS_REFRESH_MS;
//        tempVal /= 1000;

//        currentTime += tempVal;
//        ui->DOPlot->graph(0)->addData(currentTime, this->DOState);
//        ui->DOPlot->xAxis->setRange(currentTime, this->actDORange, Qt::AlignRight);
//    }
//}

void MainWindow::convertImuPacket(QByteArray &packet, IMU_Packet_t *data)
{
    /* Accel X */
    data->m_FIFO_Accel_X = packet[0];
    data->m_FIFO_Accel_X = (data->m_FIFO_Accel_X << 8);
    data->m_FIFO_Accel_X |= (packet[1] & 0x00ff);
    /* Accel Y */
    data->m_FIFO_Accel_Y = packet[2];
    data->m_FIFO_Accel_Y = (data->m_FIFO_Accel_Y << 8);
    data->m_FIFO_Accel_Y |= (packet[3] & 0x00ff);
    /* Accel Z */
    data->m_FIFO_Accel_Z = packet[4];
    data->m_FIFO_Accel_Z = (data->m_FIFO_Accel_Z << 8);
    data->m_FIFO_Accel_Z |= (packet[5] & 0x00ff);
    /* Gyro X */
    data->m_FIFO_Gyro_X = packet[6];
    data->m_FIFO_Gyro_X = (data->m_FIFO_Gyro_X << 8);
    data->m_FIFO_Gyro_X |= (packet[7] & 0x00ff);
    /* Gyro Y */
    data->m_FIFO_Gyro_Y = packet[8];
    data->m_FIFO_Gyro_Y = (data->m_FIFO_Gyro_Y << 8);
    data->m_FIFO_Gyro_Y |= (packet[9] & 0x00ff);
    /* Gyro Z */
    data->m_FIFO_Gyro_Z = packet[10];
    data->m_FIFO_Gyro_Z = (data->m_FIFO_Gyro_Z << 8);
    data->m_FIFO_Gyro_Z |= (packet[11] & 0x00ff);
    /* Temperature */
    data->m_FIFO_Temp = (packet[12]& 0x00ff);
    /* Timestamp */
    data->m_FIFO_TimeStamp = packet[13];
    data->m_FIFO_TimeStamp = (data->m_FIFO_TimeStamp << 8);
    data->m_FIFO_TimeStamp |= (packet[14] & 0x00ff);

    /* APEX interrupt */
    data->m_APEX_INT = packet[15];
}

void MainWindow::updateIMUPlot(IMU_Packet_t imuData)
{
    double tempValue;
    double accelXAxesScale = ODR_RESOLUTION;
    static double lastAccODR = 0;
    static double lastGyroODR = 0;
    static double lastTempODR = 0;
    static double lastDOODR = 0;
    static double MemLastAccValidODR = 0;
    static double MemLastGyroValidODR = 0;
    bool AccDataValid = true;
    bool GyroDataValid = true;
    bool TempDataValid = true;

    // X-Acceleration
    if (checkFIFOValidData(imuData.m_FIFO_Accel_X))
    {
        tempValue = (double)imuData.m_FIFO_Accel_X / AccelScaleFactor;
        //Simulation of a ringbuffer
        checkVectorOverflow(accX, FFT_SAMPLE_NUMBER);
        accX.push_front(tempValue);
    }
    else
    {
        AccDataValid = false;
    }

    // Y-Acceleration
    if (checkFIFOValidData(imuData.m_FIFO_Accel_Y))
    {
        tempValue = (double)imuData.m_FIFO_Accel_Y / AccelScaleFactor;
        //Simulation of a ringbuffer
        checkVectorOverflow(accY, FFT_SAMPLE_NUMBER);
        accY.push_front(tempValue);
    }
    else
    {
        AccDataValid = false;
    }

    // Z-Acceleration
    if (checkFIFOValidData(imuData.m_FIFO_Accel_Z))
    {
        tempValue = (double)imuData.m_FIFO_Accel_Z / AccelScaleFactor;
        //Simulation of a ringbuffer
        checkVectorOverflow(accZ, FFT_SAMPLE_NUMBER);
        accZ.push_front(tempValue);
    }
    else
    {
        AccDataValid = false;
    }

    // X-Rotation
    if (checkFIFOValidData(imuData.m_FIFO_Gyro_X))
    {
        tempValue = (double)imuData.m_FIFO_Gyro_X / GyroScaleFactorDegree;
        //Simulation of a ringbuffer
        checkVectorOverflow(gyroX, FFT_SAMPLE_NUMBER);
        gyroX.push_front(tempValue);
    }
    else
    {
        GyroDataValid = false;
    }

    // Y-Rotation
    if (checkFIFOValidData(imuData.m_FIFO_Gyro_Y))
    {
        tempValue = (double)imuData.m_FIFO_Gyro_Y / GyroScaleFactorDegree;
        //Simulation of a ringbuffer
        checkVectorOverflow(gyroY, FFT_SAMPLE_NUMBER);
        gyroY.push_front(tempValue);
    }
    else
    {
        GyroDataValid = false;
    }

    // Z-Rotation
    if (checkFIFOValidData(imuData.m_FIFO_Gyro_Z))
    {
        tempValue = (double)imuData.m_FIFO_Gyro_Z / GyroScaleFactorDegree;
        //Simulation of a ringbuffer
        checkVectorOverflow(gyroZ, FFT_SAMPLE_NUMBER);
        gyroZ.push_front(tempValue);
    }
    else
    {
        GyroDataValid = false;
    }

    // Temperature
    if (checkFIFOValidData(imuData.m_FIFO_Temp))
    {
        tempValue = ((double)imuData.m_FIFO_Temp / 2.07) + 25;
        //Simulation of a ringbuffer
        checkVectorOverflow(temperature, FFT_SAMPLE_NUMBER);
        temperature.push_front(tempValue);
    }
    else
    {
        TempDataValid = false;
    }

    // DO
    tempValue = (double)imuData.m_APEX_INT;
    DO.push_front(tempValue);

    // ODR
    tempValue = (double)imuData.m_FIFO_TimeStamp;
    //Simulation of a ringbuffer
    checkVectorOverflow(ODRacc, FFT_SAMPLE_NUMBER);
    checkVectorOverflow(ODRgyro, FFT_SAMPLE_NUMBER);

    /*
     * Plot data
    */
    if(AccDataValid)
    {
        ODRacc.push_front(lastAccODR + (tempValue + MemLastAccValidODR)*accelXAxesScale);
        lastAccODR = ODRacc.first();
        MemLastAccValidODR = 0;
    }
    else
    {
        MemLastAccValidODR += tempValue;
    }
    if(GyroDataValid)
    {
        ODRgyro.push_front(lastGyroODR + (tempValue + MemLastGyroValidODR)*accelXAxesScale);
        lastGyroODR = ODRgyro.first();
        MemLastGyroValidODR = 0;
    }
    else
    {
        MemLastGyroValidODR += tempValue;
    }
    ODRtemp.push_front(lastTempODR + tempValue*accelXAxesScale);
    lastTempODR = ODRtemp.first();

    ODRdo.push_front(lastDOODR + tempValue*accelXAxesScale);
    lastDOODR = ODRdo.first();

    if (!ODRacc.isEmpty() && !accX.isEmpty() && AccDataValid)
    {
        //Add new point to accX plot
        ui->accXPlot->graph(0)->addData(ODRacc.first(), accX.first());
        ui->accXPlot->graph(2)->addData(ODRdo.first(), DO.first());
        ui->accXPlot->xAxis->setRange(ODRacc.first(), this->actAccelRange, Qt::AlignRight);
    }
    if (!ODRacc.isEmpty() && !accY.isEmpty() && AccDataValid)
    {
        //Add new point to accY plot
        ui->accYPlot->graph(0)->addData(ODRacc.first(), accY.first());
        ui->accYPlot->graph(2)->addData(ODRdo.first(), DO.first());
        ui->accYPlot->xAxis->setRange(ODRacc.first(), this->actAccelRange, Qt::AlignRight);
    }
    if (!ODRacc.isEmpty() && !accZ.isEmpty() && AccDataValid)
    {
        //Add new point to accZ plot
        ui->accZPlot->graph(0)->addData(ODRacc.first(), accZ.first());
        ui->accZPlot->graph(2)->addData(ODRdo.first(), DO.first());
        ui->accZPlot->xAxis->setRange(ODRacc.first(), this->actAccelRange, Qt::AlignRight);
    }
    if (!ODRgyro.isEmpty() && !gyroX.isEmpty() && GyroDataValid)
    {
        //Add new point to gyroX plot
        ui->gyroPlot->graph(0)->addData(ODRgyro.first(), gyroX.first());
        ui->gyroPlot->xAxis->setRange(ODRgyro.first(), this->actGyroRange, Qt::AlignRight);
    }
    if (!ODRgyro.isEmpty() && !gyroY.isEmpty() && GyroDataValid)
    {
        //Add new point to gyroY plot
        ui->gyroPlot->graph(1)->addData(ODRgyro.first(), gyroY.first());
        ui->gyroPlot->xAxis->setRange(ODRgyro.first(), this->actGyroRange, Qt::AlignRight);
    }
    if (!ODRgyro.isEmpty() && !gyroZ.isEmpty() && GyroDataValid)
    {
        //Add new point to gyroZ plot
        ui->gyroPlot->graph(2)->addData(ODRgyro.first(), gyroZ.first());
        ui->gyroPlot->xAxis->setRange(ODRgyro.first(), this->actGyroRange, Qt::AlignRight);
    }
    if (!ODRtemp.isEmpty() && !temperature.isEmpty() && TempDataValid)
    {
        //Add new point to temperature plot
        ui->tempPlot->graph(0)->addData(ODRtemp.first(), temperature.first());
        ui->tempPlot->xAxis->setRange(ODRtemp.first(), this->actTempRange, Qt::AlignRight);
    }
//    if (!ODRdo.isEmpty() && !DO.isEmpty())
//    {
//        //Add new point to DO plot
//        ui->DOPlot->graph(0)->addData(ODRdo.first(), DO.first());
//        ui->DOPlot->xAxis->setRange(ODRdo.first(), this->actDORange, Qt::AlignRight);
//    }
}

void MainWindow::setAccelScaleFactor(float AccelScale)
{
    this->AccelScaleFactor = AccelScale;
}

void MainWindow::setGyroScaleFactor(float GyroScale)
{
    this->GyroScaleFactorDegree = GyroScale;
}

void MainWindow::setAccelSampleRate(float ODR)
{
    this->actAccelSampleRate = ODR;
    ui->accXPlot->xAxis2->setRange(0, actAccelSampleRate/2);
    ui->accYPlot->xAxis2->setRange(0, actAccelSampleRate/2);
    ui->accZPlot->xAxis2->setRange(0, actAccelSampleRate/2);
}

void MainWindow::setGyroSampleRate(float ODR)
{
    this->actGyroSampleRate = ODR;
    //    ui->gyroXPlot->xAxis2->setRange(0, ODR/2);
}

void MainWindow::fftPlotClear()
{
    if(!ui->accXPlot->graph(FFT_CHARTS)->data()->isEmpty())
    {
        ui->accXPlot->graph(FFT_CHARTS)->data()->clear();
    }
    if(!ui->accYPlot->graph(FFT_CHARTS)->data()->isEmpty())
    {
        ui->accYPlot->graph(FFT_CHARTS)->data()->clear();
    }
    if(!ui->accZPlot->graph(FFT_CHARTS)->data()->isEmpty())
    {
        ui->accZPlot->graph(FFT_CHARTS)->data()->clear();
    }

//    ui->gyroXPlot->graph(FFT_CHARTS)->data()->clear();
//    ui->gyroYPlot->graph(FFT_CHARTS)->data()->clear();
//    ui->gyroZPlot->graph(FFT_CHARTS)->data()->clear();

    ui->accXPlot->replot(QCustomPlot::rpQueuedReplot);
    ui->accYPlot->replot(QCustomPlot::rpQueuedReplot);
    ui->accZPlot->replot(QCustomPlot::rpQueuedReplot);
}

/*****************************************************************************
 * Action commands
 ****************************************************************************/
void MainWindow::on_actionSettings_triggered()
{
    m_settings->exec();
}

void MainWindow::on_actionConnect_triggered()
{
    connectionDialog::SerialSettings setting = m_settings->getSerialSettings();
    Serial::ConnectionSettings cs;

    // Retrive serial settings from Connection dialog
    cs.name = setting.name;
    cs.baudRate = setting.baudRate;
    cs.dataBits = setting.dataBits;
    cs.parity = setting.parity;
    cs.stopBits = setting.stopBits;
    cs.flowControl = setting.flowControl;

    //Lauch serial thread
    QFuture<void> serial = QtConcurrent::run(createSerialThread, this, cs, &rxCommandQueue, &txCommandQueue, &rxQueueMutex, &txQueueMutex);
}

void MainWindow::on_actionDisconnect_triggered()
{
    DisconnectProcedure();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::DisconnectProcedure()
{
    static int8_t step = 0;
    QByteArray command;

    AC1_disconnecting_active = true;

    switch(step)
    {
    case 0:
        m_Protocol->setTelemetryEn(command, DISABLE);
        _ADD_SEND_COMMAND(command);
        telemetryEnabled = false;
        step = 10;
        break;
    case 10:
        emit serialDisconnect();
        step = 0;
        break;
    }
}
/*****************************************************************************
 * Data rate calc
 ****************************************************************************/

void MainWindow::timerDataSlot()
{
    sampleRate = (packetsReceived - lastDataReceived);
    if (m_serialStatus)
    {
        ui->chartStatusLabel->setText(tr("Packets received: %1, PPS: %2, Transfer speed: %3kBytes/s").arg(packetsReceived).arg(sampleRate).arg(byteReceived/1000));
    }
    else
    {
        ui->chartStatusLabel->setText(tr("Packets received: 0, PPS: 0, Transfer speed: 0kBytes/s"));
    }
    lastDataReceived = packetsReceived;
    byteReceived = 0;
}

/*****************************************************************************
 * Custom slots
 ****************************************************************************/
void MainWindow::timerChartUpdateSlot()
{
//    updateDOChart();

    ui->accXPlot->replot(QCustomPlot::rpQueuedReplot);
    ui->accYPlot->replot(QCustomPlot::rpQueuedReplot);
    ui->accZPlot->replot(QCustomPlot::rpQueuedReplot);

    ui->gyroPlot->replot(QCustomPlot::rpQueuedReplot);

    ui->tempPlot->replot(QCustomPlot::rpQueuedReplot);

//    ui->DOPlot->replot(QCustomPlot::rpQueuedReplot);
}

void MainWindow::serialConnected(const QString &name, const QString &baud, const QString &databit, const QString &parity, const QString &stop, const QString &flow)
{
    m_serialStatus = true;

    /* Update buttons status */
    setButtonsStatus(Button_Group::SerialButton, true);
    setButtonsStatus(Button_Group::GeneralImuButton, true);

    /* Update icons */
    resetAckIcon();

    /* Launch read AC1 settings procedure */
    AC1FirstReading();

    updateStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                      .arg(name, baud, databit,
                           parity, stop, flow));
}

void MainWindow::serialError(const QString &name, const QString &error)
{
    m_serialStatus = false;

    QMessageBox::critical(this, tr("Error"), error);

    updateStatusMessage(tr("Error when trying to open %1").arg(name));

    /* Update buttons status */
    setButtonsStatus(Button_Group::SerialButton, false);
    setButtonsStatus(Button_Group::ConfigModeOnlyButton, false);
    setButtonsStatus(Button_Group::GeneralImuButton, false);

    /* Update icons */
    resetAckIcon();

    updateStatusMessage(tr("Disconnected"));

    AC1_disconnecting_active = false;

    lastDataReceived = packetsReceived = 0;
}

void MainWindow::serialDisconnected()
{
    m_serialStatus = false;

    /* Update buttons status */
    setButtonsStatus(Button_Group::SerialButton, false);
    setButtonsStatus(Button_Group::ConfigModeOnlyButton, false);
    setButtonsStatus(Button_Group::GeneralImuButton, false);

    /* Update icons */
    resetAckIcon();

    updateStatusMessage(tr("Disconnected"));

    AC1_disconnecting_active = false;

    lastDataReceived = packetsReceived = 0;
}

void MainWindow::serialDataCounting(qint64 nByteReceived)
{
    byteReceived += nByteReceived;
}

void MainWindow::commandProcessing()
{
    while (!rxCommandQueue.isEmpty())
    {
        QMutexLocker locker(&rxQueueMutex);

        QByteArray command = rxCommandQueue.takeLast();

        if (CheckCommandPacketValidity(command))
        {
            auto commandType = static_cast<CommandType>(command[0]);

            if (commandType == CommandType::commandIMUdata)
            {
                IMU_Packet_t imuData;

                // Remove command byte from packet
                command.remove(0,1);

                // Extract acceleration, rotation, temperature and ODR from packet
                convertImuPacket(command, &imuData);

                // Update charts
                updateIMUPlot(imuData);
            }
            if (commandType == CommandType::commandDOState)
            {
                //TODO
                this->DOState = command[1];
            }
            if (commandType == CommandType::commandAck)
            {
                auto exeCommand = static_cast<CommandType>(command[1]);
                uint8_t result = command[2];
                QPixmap mypix ("://images/CheckedSquare.png");

                if (exeCommand == CommandType::commandSaveUserData)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        mSaveUserConfigTimer.stop();
                        QMessageBox::information(this, tr("Info"), "Imu parameters have been saved into flash");
                    }
                }
                if (exeCommand == CommandType::commandSetConfigMode)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        AC1_ConfigMode_status ^= 1;

                        setButtonsStatus(Button_Group::ConfigModeOnlyButton, AC1_ConfigMode_status);
                    }
                }
                if (exeCommand == CommandType::commandGetConfigMode)
                {
                    AC1_ConfigMode_status = result;

                    setButtonsStatus(Button_Group::ConfigModeOnlyButton, AC1_ConfigMode_status);
                }
                if (exeCommand == CommandType::commandSetTelemetry)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        if (AC1_disconnecting_active)
                        {
                            DisconnectProcedure();
                        }
                    }
                }
                if (exeCommand == CommandType::commandGetTelemetry)
                {
                    telemetryEnabled = result;
                }
                if (exeCommand == CommandType::commandSetAccODR)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->accelODRAckLabel->setPixmap(mypix);
                        uint8_t value = ui->accelODRBox->currentData().toUInt();
                        setAccelSampleRate(ImuODRtoValue(value));
                    }
                }
                if (exeCommand == CommandType::commandGetAccODR)
                {
                    ui->accelODRAckLabel->setPixmap(mypix);
                    uint8_t index = ui->accelODRBox->findData(result);
                    ui->accelODRBox->setCurrentIndex(index);
                    setAccelSampleRate(ImuODRtoValue(result));
                }
                if (exeCommand == CommandType::commandSetAccFSR)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->accelFSRAckLabel->setPixmap(mypix);
                        uint8_t value = ui->accelFSRBox->currentData().toUInt();
                        setAccelScaleFactor(AccFSRConversion(value));
                        float scale = AccFSRtoValue(value);
                        ui->accXPlot->yAxis->setRange(-scale, scale);
                        ui->accYPlot->yAxis->setRange(-scale, scale);
                        ui->accZPlot->yAxis->setRange(-scale, scale);
                    }
                }
                if (exeCommand == CommandType::commandGetAccFSR)
                {
                    float tempVal = 0;
                    ui->accelFSRAckLabel->setPixmap(mypix);
                    uint8_t index = ui->accelFSRBox->findData(result);
                    ui->accelFSRBox->setCurrentIndex(index);
                    tempVal = AccFSRConversion(result);
                    setAccelScaleFactor(tempVal);
                    tempVal = AccFSRtoValue(result);
                    ui->accXPlot->yAxis->setRange(-tempVal, tempVal);
                    ui->accYPlot->yAxis->setRange(-tempVal, tempVal);
                    ui->accZPlot->yAxis->setRange(-tempVal, tempVal);
                }
                if (exeCommand == CommandType::commandSetGyroODR)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->gyroODRAckLabel->setPixmap(mypix);
                        uint8_t value = ui->gyroODRBox->currentData().toUInt();
                        setGyroSampleRate(ImuODRtoValue(value));
                    }
                }
                if (exeCommand == CommandType::commandGetGyroODR)
                {
                    ui->gyroODRAckLabel->setPixmap(mypix);
                    uint8_t index = ui->gyroODRBox->findData(result);
                    ui->gyroODRBox->setCurrentIndex(index);
                    setGyroSampleRate(ImuODRtoValue(result));
                }
                if (exeCommand == CommandType::commandSetGyroFSR)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->gyroFSRAckLabel->setPixmap(mypix);
                        uint8_t value = ui->gyroFSRBox->currentData().toUInt();
                        setGyroScaleFactor(GyroFSRConversion(value));
                        float scale = GyroFSRtoValue(value);
                        ui->gyroPlot->yAxis->setRange(-scale, scale);
                    }
                }
                if (exeCommand == CommandType::commandGetGyroFSR)
                {
                    float tempVal = 0;
                    ui->gyroFSRAckLabel->setPixmap(mypix);
                    uint8_t index = ui->gyroFSRBox->findData(result);
                    ui->gyroFSRBox->setCurrentIndex(index);
                    tempVal = GyroFSRConversion(result);
                    setGyroScaleFactor(tempVal);
                    tempVal = GyroFSRtoValue(result);
                    ui->gyroPlot->yAxis->setRange(-tempVal, tempVal);
                }
                if (exeCommand == CommandType::commandSetAccBW)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->accelBWAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetAccBW)
                {
                    ui->accelBWAckLabel->setPixmap(mypix);
                    uint8_t index = ui->accelBWBox->findData(result);
                    ui->accelBWBox->setCurrentIndex(index);
                }
                if (exeCommand == CommandType::commandSetGyroBW)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->gyroBWAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetGyroBW)
                {
                    ui->gyroBWAckLabel->setPixmap(mypix);
                    uint8_t index = ui->gyroBWBox->findData(result);
                    ui->gyroBWBox->setCurrentIndex(index);
                }
                if (exeCommand == CommandType::commandSetWomXTh)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->womXthAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetWomXTh)
                {
                    ui->womXthAckLabel->setPixmap(mypix);
                    ui->womXthSpinBox->setValue(result);
                    ui->womXthValueLabel->setText("= " + QString::number(WOM_RESOLUTION * ui->womXthSpinBox->value(),'f',4) + "g");
                }
                if (exeCommand == CommandType::commandSetWomYTh)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->womYthAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetWomYTh)
                {
                    ui->womYthAckLabel->setPixmap(mypix);
                    ui->womYthSpinBox->setValue(result);
                    ui->womYthValueLabel->setText("= " + QString::number(WOM_RESOLUTION * ui->womYthSpinBox->value(),'f',4) + "g");
                }
                if (exeCommand == CommandType::commandSetWomZTh)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->womZthAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetWomZTh)
                {
                    ui->womZthAckLabel->setPixmap(mypix);
                    ui->womZthSpinBox->setValue(result);
                    ui->womZthValueLabel->setText("= " + QString::number(WOM_RESOLUTION * ui->womZthSpinBox->value(),'f',4) + "g");
                }
                if (exeCommand == CommandType::commandSetWomIntMode)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->womIntModeAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetWomIntMode)
                {
                    ui->womIntModeAckLabel->setPixmap(mypix);
                    uint8_t index = ui->womIntModeBox->findData(result);
                    ui->womIntModeBox->setCurrentIndex(index);
                }
                if (exeCommand == CommandType::commandSetWomMode)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->womModeAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetWomMode)
                {
                    ui->womModeAckLabel->setPixmap(mypix);
                    uint8_t index = ui->womModeBox->findData(result);
                    ui->womModeBox->setCurrentIndex(index);
                }
                if (exeCommand == CommandType::commandSetSmdMode)
                {
                    if (result == OMD_COMM_ACK_OK)
                    {
                        ui->smdModeAckLabel->setPixmap(mypix);
                    }
                }
                if (exeCommand == CommandType::commandGetSmdMode)
                {
                    ui->smdModeAckLabel->setPixmap(mypix);
                    uint8_t index = ui->smdModeBox->findData(result);
                    ui->smdModeBox->setCurrentIndex(index);
                }
            }

            // Update serial's statistics
            packetsReceived++;

            emit commandProcessed();
        }
    }
}

bool MainWindow::CheckCommandPacketValidity(QByteArray &command)
{
    uint8_t commandType = (command[0]);
    qsizetype size;
    bool status = 0;

    if(((commandType >> 4) & 0xF) == CommandGroup::CommandGroup_AC1Menagment)
    {
        size = command.size();
        if (size == 2) status = true;
    }
    else if (((commandType >> 4) & 0xF) == CommandGroup::CommandGroup_Ack)
    {
        size = command.size();
        if (size == 3) status = true;
    }
    else if (((commandType >> 4) & 0xF) == CommandGroup::CommandGroup_Generic)
    {
        size = command.size();
        if (commandType == static_cast<uint8_t>(CommandType::commandIMUdata))
        {
            if (size == 17) status = true;
        }
        else
        {
            if (size >= 2) status = true;
        }
    }
    else if (((commandType >> 4) & 0xF) == CommandGroup::CommandGroup_Accel)
    {
        size = command.size();
        if (size == 2) status = true;
    }
    else if (((commandType >> 4) & 0xF) == CommandGroup::CommandGroup_Gyro)
    {
        size = command.size();
        if (size == 2) status = true;
    }
    else if (((commandType >> 4) & 0xF) == CommandGroup::CommandGroup_APEX_INT2)
    {
        size = command.size();
        if (size == 2) status = true;
    }

    return status;
}

void MainWindow::mousePressedOnPlot(QMouseEvent *e)
{

    if (e->button() == Qt::LeftButton)    // Left button...
    {
//        ui->accPlot->graph(0)->setSelectable(QCP::stDataRange);
//        ui->accPlot->graph(1)->setSelectable(QCP::stDataRange);
//        ui->accPlot->graph(2)->setSelectable(QCP::stDataRange);
//        ui->accPlot->setSelectionRectMode(QCP::srmNone);
//        ui->accPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iMultiSelect);

//        ui->gyroPlot->setSelectionRectMode(QCP::srmNone);
//        ui->gyroPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iMultiSelect);
    }
    else if (e->button() == Qt::RightButton)   // Right button...
    {
//        ui->accPlot->setSelectionRectMode(QCP::srmSelect);
//        ui->gyroPlot->setSelectionRectMode(QCP::srmSelect);
    }
}

void MainWindow::mouseReleasedOnPlot(QMouseEvent *e)
{
    ;
}

void MainWindow::showAccXCursor(QMouseEvent *event)
{
    double mouseX = ui->accXPlot->xAxis->pixelToCoord(event->pos().x());

    double start = ui->accXPlot->yAxis->pixelToCoord(0);
    double end = ui->accXPlot->yAxis->pixelToCoord(ui->accXPlot->size().height());

    accXcursor->start->setCoords(mouseX, start);
    accXcursor->end->setCoords(mouseX, end);

    ui->accXPlot->replot(QCustomPlot::rpQueuedReplot);
}

void MainWindow::accXPlotPressed(QMouseEvent *event)
{
    Q_UNUSED(event);
    PlotActive = AccXChart;
}

void MainWindow::accYPlotPressed(QMouseEvent *event)
{
    Q_UNUSED(event);
    PlotActive = AccYChart;
}

void MainWindow::accZPlotPressed(QMouseEvent *event)
{
    Q_UNUSED(event);
    PlotActive = AccZChart;
}

void MainWindow::plotSelectionChange()
{
    QCPDataSelection selection;
    QCPGraph *prtActGraph;
    double samplingRate;

    switch(PlotActive)
    {
    case AccXChart:
        selection = ui->accXPlot->graph(0)->selection();
        prtActGraph = ui->accXPlot->graph(0);
        samplingRate = this->actAccelSampleRate;
        break;
    case AccYChart:
        selection = ui->accYPlot->graph(0)->selection();
        prtActGraph = ui->accYPlot->graph(0);
        samplingRate = this->actAccelSampleRate;
        break;
    case AccZChart:
        selection = ui->accZPlot->graph(0)->selection();
        prtActGraph = ui->accZPlot->graph(0);
        samplingRate = this->actAccelSampleRate;
        break;
    case GyroXChart:
//        selection = ui->gyroXPlot->graph(0)->selection();
//        samplingRate = this->actGyroSampleRate;
        break;
    case GyroYChart:
//        selection = ui->gyroYPlot->graph(0)->selection();
//        samplingRate = this->actGyroSampleRate;
        break;
    case GyroZChart:
//        selection = ui->gyroZPlot->graph(0)->selection();
//        samplingRate = this->actGyroSampleRate;
        break;
    default:
        break;
    }

    if (!selection.isEmpty())
    {
        QList<double> dataToElab;
        foreach (QCPDataRange dataRange, selection.dataRanges())
        {
            QCPGraphDataContainer::const_iterator begin = prtActGraph->data()->at(dataRange.begin()); // get range begin iterator from index
            QCPGraphDataContainer::const_iterator end = prtActGraph->data()->at(dataRange.end()); // get range end iterator from index
            for (QCPGraphDataContainer::const_iterator it=begin; it!=end; ++it)
            {
                // iterator "it" will go through all selected data points
                //TODO: Add all data point values to a buffer and start FFT analisys task
                dataToElab.append(it->value);
            }
            //Lauch fft calculation on other thread
            QFuture<void> fftThread = QtConcurrent::run(createFFTThread, this, dataToElab, samplingRate);
        }
    }
}

void MainWindow::fftElabFinished(QList<double> dataOut)
{
    /* Create X-Axes vector */
    double freqStep = actAccelSampleRate / dataOut.count();
    double freq = 0;
    accFFTIndex.clear();
    while (freq < (actAccelSampleRate))
    {
        accFFTIndex.append(freq);
        freq += freqStep;
    }

    switch(PlotActive)
    {
    case AccXChart:
        ui->accXPlot->graph(1)->setData(accFFTIndex.mid(1,dataOut.count()/2 - 1), QVector<double>::fromList(dataOut.mid(1,dataOut.count()/2 - 1)));
//        ui->accXPlot->graph(FFT_CHARTS)->setData(accFFTIndex, QVector<double>::fromList(dataOut));
        ui->accXPlot->graph(FFT_CHARTS)->rescaleAxes();
        ui->accXPlot->replot(QCustomPlot::rpQueuedReplot);
        break;
    case AccYChart:
        ui->accYPlot->graph(1)->setData(accFFTIndex.mid(1,dataOut.count()/2 - 1), QVector<double>::fromList(dataOut.mid(1,dataOut.count()/2 - 1)));
//        ui->accYPlot->graph(FFT_CHARTS)->setData(accFFTIndex, QVector<double>::fromList(dataOut));
        ui->accYPlot->graph(FFT_CHARTS)->rescaleAxes();
        ui->accYPlot->replot(QCustomPlot::rpQueuedReplot);
        break;
    case AccZChart:
        ui->accZPlot->graph(1)->setData(accFFTIndex.mid(1,dataOut.count()/2 - 1), QVector<double>::fromList(dataOut.mid(1,dataOut.count()/2 - 1)));
//        ui->accZPlot->graph(FFT_CHARTS)->setData(accFFTIndex, QVector<double>::fromList(dataOut));
        ui->accZPlot->graph(FFT_CHARTS)->rescaleAxes();
        ui->accZPlot->replot(QCustomPlot::rpQueuedReplot);
        break;
    case GyroXChart:

        break;
    case GyroYChart:

        break;
    case GyroZChart:

        break;
    default:
        break;
    }
}

void MainWindow::saveUserConfigTimeout()
{
    QMessageBox::critical(this, tr("Error"), "Error occured during imu parameters saving procedure");
}

/*****************************************************************************
 * Charts modifiers
 ****************************************************************************/
void MainWindow::on_StartLogButton_clicked()
{
    QByteArray command;

    if (!AC1_ConfigMode_status)
    {
        if (telemetryEnabled)
        {
            m_Protocol->setTelemetryEn(command, DISABLE);
            telemetryEnabled = false;
        }
        else
        {
            m_Protocol->setTelemetryEn(command, ENABLE);
            telemetryEnabled = true;
            fftPlotClear();
        }

        _ADD_SEND_COMMAND(command);
    }
    else
    {
        //TODO: Messagebox
    }
}

void MainWindow::on_accelTimeExpandButton_clicked()
{
    if (m_CurrentTab == AccelerationsTab)
    {
        ui->accXPlot->xAxis->scaleRange(.5, ui->accXPlot->xAxis->range().center());
        ui->accYPlot->xAxis->scaleRange(.5, ui->accYPlot->xAxis->range().center());
        ui->accZPlot->xAxis->scaleRange(.5, ui->accZPlot->xAxis->range().center());
        this->actAccelRange /= 2;
    }
    else if (m_CurrentTab == RotationsTab)
    {
        ui->gyroPlot->xAxis->scaleRange(.5, ui->gyroPlot->xAxis->range().center());

        this->actGyroRange /= 2;
    }

//    ui->DOPlot->xAxis->scaleRange(.5, ui->DOPlot->xAxis->range().center());
//    this->actDORange /= 2;
}
void MainWindow::on_accelTimeCompressButton_clicked()
{
    if (m_CurrentTab == AccelerationsTab)
    {
        ui->accXPlot->xAxis->scaleRange(2, ui->accXPlot->xAxis->range().center());
        ui->accYPlot->xAxis->scaleRange(2, ui->accYPlot->xAxis->range().center());
        ui->accZPlot->xAxis->scaleRange(2, ui->accZPlot->xAxis->range().center());
        this->actAccelRange *= 2;
    }
    else if (m_CurrentTab == RotationsTab)
    {
        ui->gyroPlot->xAxis->scaleRange(2, ui->gyroPlot->xAxis->range().center());
        this->actGyroRange *= 2;
    }

//    ui->DOPlot->xAxis->scaleRange(2, ui->DOPlot->xAxis->range().center());
//    this->actDORange *= 2;
}
void MainWindow::on_accelExpandButton_clicked()
{
    if (m_CurrentTab == AccelerationsTab)
    {
        ui->accXPlot->yAxis->scaleRange(.5, ui->accXPlot->yAxis->range().center());
        ui->accYPlot->yAxis->scaleRange(.5, ui->accYPlot->yAxis->range().center());
        ui->accZPlot->yAxis->scaleRange(.5, ui->accZPlot->yAxis->range().center());
    }
    else if (m_CurrentTab == RotationsTab)
    {
        ui->gyroPlot->yAxis->scaleRange(.5, ui->gyroPlot->yAxis->range().center());
    }
}
void MainWindow::on_accelCompressButton_clicked()
{
    if (m_CurrentTab == AccelerationsTab)
    {
        ui->accXPlot->yAxis->scaleRange(2, ui->accXPlot->yAxis->range().center());
        ui->accYPlot->yAxis->scaleRange(2, ui->accYPlot->yAxis->range().center());
        ui->accZPlot->yAxis->scaleRange(2, ui->accZPlot->yAxis->range().center());
    }
    else if (m_CurrentTab == RotationsTab)
    {
        ui->gyroPlot->yAxis->scaleRange(2, ui->gyroPlot->yAxis->range().center());
    }
}
void MainWindow::on_ImuTabWidget_currentChanged(int index)
{
    this->m_CurrentTab = index;
}
/*****************************************************************************
 * Imu parameters
 ****************************************************************************/
void MainWindow::resetAckIcon()
{
    QPixmap mypix ("://images/UncheckedSquare.png");
    ui->accelODRAckLabel->setPixmap(mypix);
    ui->gyroODRAckLabel->setPixmap(mypix);
    ui->accelFSRAckLabel->setPixmap(mypix);
    ui->gyroFSRAckLabel->setPixmap(mypix);
    ui->accelBWAckLabel->setPixmap(mypix);
    ui->gyroBWAckLabel->setPixmap(mypix);
    ui->womXthAckLabel->setPixmap(mypix);
    ui->womYthAckLabel->setPixmap(mypix);
    ui->womZthAckLabel->setPixmap(mypix);
    ui->womIntModeAckLabel->setPixmap(mypix);
    ui->womModeAckLabel->setPixmap(mypix);
    ui->smdModeAckLabel->setPixmap(mypix);
}

void MainWindow::on_sendAccelODRButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");
    ui->accelODRAckLabel->setPixmap(mypix);

    uint8_t value = ui->accelODRBox->currentData().toInt();
    m_Protocol->setAccelODR(command, value);

    _ADD_SEND_COMMAND(command);
}
void MainWindow::on_sendAccelFSRButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->accelFSRAckLabel->setPixmap(mypix);

    uint8_t value = ui->accelFSRBox->currentData().toInt();
    m_Protocol->setAccelFSR(command, value);

    _ADD_SEND_COMMAND(command);
}

void MainWindow::on_sendGyroODRButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->gyroODRAckLabel->setPixmap(mypix);

    uint8_t value = ui->gyroODRBox->currentData().toInt();
    m_Protocol->setGyroODR(command, value);

    _ADD_SEND_COMMAND(command);
}
void MainWindow::on_sendGyroFSRButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->gyroFSRAckLabel->setPixmap(mypix);

    uint8_t value = ui->gyroFSRBox->currentData().toInt();
    m_Protocol->setGyroFSR(command, value);

    _ADD_SEND_COMMAND(command);
}

void MainWindow::on_sendAccelBWButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->gyroBWAckLabel->setPixmap(mypix);

    uint8_t value = ui->accelBWBox->currentData().toInt();
    m_Protocol->setAccelBW(command, value);

    _ADD_SEND_COMMAND(command);
}

void MainWindow::on_sendGyroBWButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->gyroBWAckLabel->setPixmap(mypix);

    uint8_t value = ui->gyroBWBox->currentData().toInt();
    m_Protocol->setGyroBW(command, value);

    _ADD_SEND_COMMAND(command);
}

void MainWindow::on_womXthSpinBox_valueChanged(int arg1)
{
    float_t value;

    value = WOM_RESOLUTION * arg1;

    ui->womXthValueLabel->setText("= " + QString::number(value,'f',3) + "g");
}

void MainWindow::on_sendWomXthButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->womXthAckLabel->setPixmap(mypix);

    uint8_t value = ui->womXthSpinBox->value();
    m_Protocol->setWOMXth(command, value);

    _ADD_SEND_COMMAND(command);

}
void MainWindow::on_womYthSpinBox_valueChanged(int arg1)
{
    float_t value;

    value = WOM_RESOLUTION * arg1;

    ui->womYthValueLabel->setText("= " + QString::number(value,'f',3) + "g");
}
void MainWindow::on_sendWomYthButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->womYthAckLabel->setPixmap(mypix);

    uint8_t value = ui->womYthSpinBox->value();
    m_Protocol->setWOMYth(command, value);

    _ADD_SEND_COMMAND(command);
}
void MainWindow::on_womZthSpinBox_valueChanged(int arg1)
{
    float_t value;

    value = WOM_RESOLUTION * arg1;

    ui->womZthValueLabel->setText("= " + QString::number(value,'f',3) + "g");
}
void MainWindow::on_sendWomZthButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->womZthAckLabel->setPixmap(mypix);

    uint8_t value = ui->womZthSpinBox->value();
    m_Protocol->setWOMZth(command, value);

    _ADD_SEND_COMMAND(command);
}
void MainWindow::on_sendWomIntModeButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->womIntModeAckLabel->setPixmap(mypix);

    uint8_t value = ui->womIntModeBox->currentData().toInt();
    m_Protocol->setWOMIntMode(command, value);

    _ADD_SEND_COMMAND(command);
}
void MainWindow::on_sendWomModeButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->womModeAckLabel->setPixmap(mypix);

    uint8_t value = ui->womModeBox->currentData().toInt();
    m_Protocol->setWOMMode(command, value);

    _ADD_SEND_COMMAND(command);
}
void MainWindow::on_sendSmdModeButton_clicked()
{
    QByteArray command;
    QPixmap mypix ("://images/UncheckedSquare.png");

    ui->smdModeAckLabel->setPixmap(mypix);

    uint8_t value = ui->smdModeBox->currentData().toInt();
    m_Protocol->setSMDMode(command, value);

    _ADD_SEND_COMMAND(command);
}

void MainWindow::on_setAC1ConfigModeButton_clicked()
{
    QByteArray command;

    if (AC1_ConfigMode_status)
    {
        m_Protocol->setConfigMode(command, DISABLE);
    }
    else
    {
        m_Protocol->setConfigMode(command, ENABLE);
    }

    _ADD_SEND_COMMAND(command);
}

void MainWindow::on_sendSaveUserConfigButton_clicked()
{
    QByteArray command;
    m_Protocol->saveUserConfig(command);

    mSaveUserConfigTimer.setSingleShot(true);
    mSaveUserConfigTimer.start(1000);

    _ADD_SEND_COMMAND(command);
}
/*****************************************************************************
 * Keyboard events
 ****************************************************************************/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Shift:
            ui->accXPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->accXPlot->graph(0)->setSelectable(QCP::stDataRange);
            ui->accXPlot->setSelectionRectMode(QCP::srmSelect);

            ui->accYPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->accYPlot->graph(0)->setSelectable(QCP::stDataRange);
            ui->accYPlot->setSelectionRectMode(QCP::srmSelect);

            ui->accZPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->accZPlot->graph(0)->setSelectable(QCP::stDataRange);
            ui->accZPlot->setSelectionRectMode(QCP::srmSelect);

            ui->gyroPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->gyroPlot->graph(0)->setSelectable(QCP::stDataRange);
            ui->gyroPlot->graph(1)->setSelectable(QCP::stDataRange);
            ui->gyroPlot->graph(2)->setSelectable(QCP::stDataRange);
            ui->gyroPlot->setSelectionRectMode(QCP::srmSelect);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Shift:
            ui->accXPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->accXPlot->graph(0)->setSelectable(QCP::stSingleData);
            ui->accXPlot->setSelectionRectMode(QCP::srmNone);

            ui->accYPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->accYPlot->graph(0)->setSelectable(QCP::stSingleData);
            ui->accYPlot->setSelectionRectMode(QCP::srmNone);

            ui->accZPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->accZPlot->graph(0)->setSelectable(QCP::stSingleData);
            ui->accZPlot->setSelectionRectMode(QCP::srmNone);

            ui->gyroPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);
            ui->gyroPlot->graph(0)->setSelectable(QCP::stSingleData);
            ui->gyroPlot->graph(1)->setSelectable(QCP::stSingleData);
            ui->gyroPlot->graph(2)->setSelectable(QCP::stSingleData);
            ui->gyroPlot->setSelectionRectMode(QCP::srmNone);
        break;
    }
}
