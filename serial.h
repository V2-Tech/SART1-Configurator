#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QMutexLocker>
#include <QThread>
#include <QEventLoop>
#include <vector>
#include <queue>

#include "cobstrancoder.h"

class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = nullptr);
    ~Serial();

    struct ConnectionSettings
    {
        QString name;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };
    void Start(const Serial::ConnectionSettings &settings, QList<QByteArray> *ptrRxBuff, QList<QByteArray> *ptrTxBuff,
               QMutex * ptrRxQueueMutex, QMutex * ptrTxQueueMutex);

    void ConnectTo(const Serial::ConnectionSettings &settings);
    void DisonnectFrom();

signals:
    void connected(const QString &name, const QString &baud, const QString &databit, const QString &parity, const QString &stop, const QString &flow);
    void disconnected();
    void error(const QString &name, const QString &error);
    void dataReceived(qint64 nByteReceived);
    void commandFound();

public slots:
    void commandProcessed();
    void sendData();
    void Quit();

private slots:
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void dataWrote();

private:
    QEventLoop loop;
    QSerialPort *  m_serial = nullptr;
    QMutex * m_mutex = nullptr;
    QString m_portName;
    qint64 m_byteReceived = 0;
    std::deque<uint8_t> m_rxBuffer;
    ConnectionSettings m_currentSettings;
    bool m_exit = false;
    QList<QByteArray> * m_rxCommandQueue = nullptr;
    QMutex * m_rxQueueMutex = nullptr;
    QList<QByteArray> * m_txCommandQueue = nullptr;
    QMutex * m_txQueueMutex = nullptr;

    /// \brief      Pass in received RX data to OMDCommProtocol and translate them to commands.
    /// \details    OMDCommProtocol will add this data to it's internal RX data buffer, and then
    ///             attempt to find and extract valid packets. If SerialFiller finds valid packets,
    ///             it will then call all callbacks associated with that topic.
    void GiveRxData(QByteArray &rxData);

    /// \details    Moves new RX data into the RX buffer, while looking for the
    ///             end-of-frame character. If EOF is found, packet will be populated
    ///             and this method will return.
    static void MoveRxDataInBuffer(QByteArray &newRxData, std::deque<uint8_t> &rxDataBuffer, QByteArray &packet);
};

#endif // SERIAL_H
