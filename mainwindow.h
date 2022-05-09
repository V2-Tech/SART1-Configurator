#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QtConcurrent>
#include <QMutexLocker>
#include <QSharedPointer>
#include <QDebug>
#include "qcustomplot.h"
#include "fftw3.h"
#include "qcustomplot.h"
#include "connectiondialog.h"
#include "serial.h"
#include "imu.h"
#include "IIM42652.h"
#include "usbcommprotocol.h"
#include "fft.h"

#define FFT_SAMPLE_NUMBER 128
#define ODR_RESOLUTION 0.000001
#define CHARTS_REFRESH_MS 10
#define SIGNAL_CHARTS 0
#define FFT_CHARTS 1
#define INTERRUPT_CHARTS 2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class connectionDialog;

enum ImuTab_Page
{
    AccelerationsTab,
    RotationsTab
};
enum Button_Group
{
    GeneralImuButton,
    SerialButton,
    ConfigModeOnlyButton,
};
typedef enum
{
    AccXChart = 0,
    AccYChart = 1,
    AccZChart = 2,
    GyroXChart = 3,
    GyroYChart = 4,
    GyroZChart = 5,
} ImuGraph;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void convertImuPacket(QByteArray &packet, IMU_Packet_t *data);
    void updateIMUPlot(IMU_Packet_t imuData);
    void setAccelScaleFactor(float AccelScale);
    void setGyroScaleFactor(float GyroScale);

private slots:
    void on_actionSettings_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();

    void on_actionQuit_triggered();

    void timerDataSlot();
    void timerChartUpdateSlot();
    void serialConnected(const QString &name, const QString &baud, const QString &databit, const QString &parity, const QString &stop, const QString &flow);
    void serialError(const QString &name, const QString &error);
    void serialDisconnected();
    void serialDataCounting(qint64 nByteReceived);
    void commandProcessing();
    void mousePressedOnPlot(QMouseEvent *e);
    void mouseReleasedOnPlot(QMouseEvent *e);
    void showAccXCursor(QMouseEvent *event);
    void accXPlotPressed(QMouseEvent *event);
    void accYPlotPressed(QMouseEvent *event);
    void accZPlotPressed(QMouseEvent *event);
    void plotSelectionChange();
    void fftElabFinished(QList<double> dataOut);
    void saveUserConfigTimeout();

    void on_StartLogButton_clicked();

    void on_accelTimeExpandButton_clicked();
    void on_accelTimeCompressButton_clicked();
    void on_accelExpandButton_clicked();
    void on_accelCompressButton_clicked();

    void on_sendAccelODRButton_clicked();
    void on_sendAccelFSRButton_clicked();
    void on_sendGyroODRButton_clicked();
    void on_sendGyroFSRButton_clicked();

    void on_ImuTabWidget_currentChanged(int index);

    void on_sendAccelBWButton_clicked();
    void on_sendGyroBWButton_clicked();

    void on_womXthSpinBox_valueChanged(int arg1);
    void on_sendWomXthButton_clicked();
    void on_womYthSpinBox_valueChanged(int arg1);
    void on_sendWomYthButton_clicked();
    void on_womZthSpinBox_valueChanged(int arg1);
    void on_sendWomZthButton_clicked();
    void on_sendWomIntModeButton_clicked();
    void on_sendWomModeButton_clicked();
    void on_sendSmdModeButton_clicked();

    void on_setAC1ConfigModeButton_clicked();
    void on_sendSaveUserConfigButton_clicked();
signals:
    void commandProcessed();
    void commandSend();
    void serialDisconnect();

private:
    void InitMainWindow();
    void InitActionConnection();
    void InitConnection();
    void InitPlots();
    void InitIMUParamBox();
    void DisconnectProcedure();
    void updateStatusMessage(const QString &message);
    uint8_t AC1FirstReading();
    void checkVectorOverflow(QVector<double> &vector, int64_t limit);
    bool checkFIFOValidData(int16_t FIFOValue);
    void updateDOChart();
    void resetAckIcon();
    void setButtonsStatus(Button_Group group, bool EnableState);
    static void createSerialThread(MainWindow *manager, const Serial::ConnectionSettings &settings,
                                   QList<QByteArray> *ptrRxBuff, QList<QByteArray> *ptrTxBuff,
                                   QMutex * ptrRxQueueMutex, QMutex * ptrTxQueueMutex);
    void _SEND_COMMANDS();
    void _ADD_COMMAND(QByteArray &command);
    void _ADD_SEND_COMMAND(QByteArray &command);
    static void createFFTThread(MainWindow *manager, QList<double>dataIn, double samplingRate);
    void setFFTIndex(double dataIn);
    void setAccelSampleRate(float ODR);
    void setGyroSampleRate(float ODR);
    void fftPlotClear();
    bool CheckCommandPacketValidity(QByteArray &command);

    Ui::MainWindow *ui;
    connectionDialog * m_settings = nullptr;
    USBCommProtocol * m_Protocol = nullptr;
    bool m_serialStatus = false;
    QVector<double> accX, accY, accZ, gyroX, gyroY, gyroZ, temperature, DO, ODRacc, ODRgyro, ODRtemp, ODRdo;
    QVector<double> accXFFT, accFFTIndex;
    float AccelScaleFactor = 4096;
    float GyroScaleFactorDegree = 16.4;
    QTimer mDataTimer;
    QTimer mChartUpdateTimer;
    QTimer mSaveUserConfigTimer;
    double sampleRate = 0;
    qint64 packetsReceived = 0;
    qint64 lastDataReceived = 0;
    qint64 byteReceived = 0;
    double actAccelRange = 5;
    double actAccelSampleRate = 8000;
    double actGyroRange = 5;
    double actGyroSampleRate = 8000;
    double actDORange = 5;
    double actTempRange = 5;
    bool telemetryEnabled = false;
    bool AC1_first_reading_active = false;
    bool AC1_disconnecting_active = false;
    int8_t m_CurrentTab = 0;
    int8_t DOState = 0;
    QList<QByteArray> rxCommandQueue;
    QMutex rxQueueMutex;
    QList<QByteArray> txCommandQueue;
    QMutex txQueueMutex;
    bool AC1_ConfigMode_status = false;
    QCPItemLine *accXcursor = nullptr;
    QCPDataSelection ActPlotSelection;
    ImuGraph PlotActive;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
