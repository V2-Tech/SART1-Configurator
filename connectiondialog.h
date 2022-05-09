#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QLabel>
#include <QMessageBox>

#include <QDebug>

namespace Ui {
class connectionDialog;
}

class connectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit connectionDialog(QWidget *parent = nullptr);
    ~connectionDialog();

    struct SerialSettings
    {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
    };

    enum Status
    {
        DISCONNECTED = 0,
        CONNECTED = 1
    };

public: /* User methods */
    SerialSettings getSerialSettings();

    QString openSerialPort();
    QString closeSerialPort();

private slots:
    void on_applyButton_clicked();
    void on_realoadButton_clicked();

    void updatePortInfo(int index);
private:
    Ui::connectionDialog *ui;
    SerialSettings m_currentSettings;

private:
    void fillPortsParameters();
    void fillPortsList();
    void applySettings();
};

#endif // CONNECTIONDIALOG_H
