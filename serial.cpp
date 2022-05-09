#include "serial.h"

Serial::Serial(QObject *parent)
    : QObject{parent}
{
    m_serial = new QSerialPort;
    m_mutex = new QMutex;

    connect(m_serial, &QSerialPort::errorOccurred, this, &Serial::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &Serial::readData);
    connect(m_serial, &QSerialPort::bytesWritten, this, &Serial::dataWrote);
}

Serial::~Serial()
{
    Quit();
}

void Serial::Start(const ConnectionSettings &settings, QList<QByteArray> *ptrRxBuff, QList<QByteArray> *ptrTxBuff,
                   QMutex * ptrRxQueueMutex, QMutex * ptrTxQueueMutex)
{
    QThread::currentThread()->setObjectName("Serial thread");
    qInfo() << this << "Serial thread start on thread: " << QThread::currentThread();

    m_rxCommandQueue = ptrRxBuff;
    m_txCommandQueue = ptrTxBuff;
    m_rxQueueMutex = ptrRxQueueMutex;
    m_txQueueMutex = ptrTxQueueMutex;

    ConnectTo(settings);

    loop.exec();

    qInfo() << this << "Serial thread end on thread: " << QThread::currentThread();
    delete this;
}

void Serial::ConnectTo(const Serial::ConnectionSettings &settings)
{
    m_currentSettings = settings;

    m_serial->setPortName(m_currentSettings.name);
    m_serial->setBaudRate(m_currentSettings.baudRate);
    m_serial->setDataBits(m_currentSettings.dataBits);
    m_serial->setParity(m_currentSettings.parity);
    m_serial->setStopBits(m_currentSettings.stopBits);
    m_serial->setFlowControl(m_currentSettings.flowControl);

    if (m_serial->open(QIODevice::ReadWrite))
    {
        qInfo() << this << "Serial opened";
        emit connected(m_serial->portName(), QString::number(m_serial->baudRate()), QString::number(m_serial->dataBits()),
                       QString::number(m_serial->parity()), QString::number(m_serial->stopBits()),
                       QString::number(m_serial->flowControl()));
    }
    else
    {
        emit error(m_serial->portName(), tr("%1").arg(m_serial->errorString()));
    }
}

void Serial::DisonnectFrom()
{
    m_serial->close();

    qInfo() << this << "Serial closed";

    emit disconnected();

    loop.quit();
}

void Serial::readData()
{
    QByteArray data = m_serial->readAll();
    m_byteReceived = data.size();

    emit dataReceived(m_byteReceived);

    GiveRxData(data);
}

void Serial::handleError(QSerialPort::SerialPortError errorCode)
{
    if (errorCode == QSerialPort::ResourceError || errorCode == QSerialPort::UnknownError
            || errorCode == QSerialPort::ReadError || errorCode == QSerialPort::WriteError)
    {
        DisonnectFrom();
        emit error(m_portName, tr("%1").arg(m_serial->errorString()));
    }
}

void Serial::dataWrote()
{

}

void Serial::commandProcessed()
{
    m_mutex->unlock();
}

void Serial::sendData()
{
    while(!m_txCommandQueue->isEmpty())
    {
        QMutexLocker locker(m_txQueueMutex);

        QByteArray encodedData;
        QByteArray command = m_txCommandQueue->takeLast();

        COBSTrancoder::omdEncode(command, encodedData);

        m_serial->write(encodedData);
    }

}

void Serial::Quit()
{
    DisonnectFrom();

    m_exit = true;
}

void Serial::GiveRxData(QByteArray &rxData)
{
    QByteArray packet;

    MoveRxDataInBuffer(rxData, m_rxBuffer, packet);

    while (!packet.isEmpty()) {
        QByteArray decodedData;
        COBSTrancoder::DecodeStatus res;

        res = COBSTrancoder::omdDecode(packet, decodedData);

        if (res == COBSTrancoder::DecodeStatus::SUCCESS)
        {
            QMutexLocker locker(m_rxQueueMutex);
            m_rxCommandQueue->append(decodedData);
        }

        MoveRxDataInBuffer(rxData, m_rxBuffer, packet);
    }

    if (!m_rxCommandQueue->isEmpty())
    {
        emit commandFound();
    }
}

void Serial::MoveRxDataInBuffer(QByteArray &newRxData, std::deque<uint8_t> &rxDataBuffer, QByteArray &packet)
{
    // Clear any existing data from packet
    packet.clear();

    // Pop bytes from front of the queue
    while (!newRxData.isEmpty()) {
        uint8_t byteOfData = newRxData.front();
        newRxData.remove(0,1);

        rxDataBuffer.push_back(byteOfData);

        // Look for 0x00 EOF byte
        if (byteOfData == 0x00) {
            // End-of-packet found!
            // Move everything from the start to byteOfData
            // into a new packet
            for (auto it = rxDataBuffer.begin(); it != rxDataBuffer.end(); ++it) {
                packet.push_back(*it);
            }

            rxDataBuffer.clear();
            return;
        }
    }
}
