#ifndef FFT_H
#define FFT_H

#include <QObject>
#include <QDebug>
#include <QMutexLocker>
#include <QThread>
#include <QEventLoop>
#include "fftw3.h"

#define SAMPLE 128U
#define FFT_SIZE SAMPLE/2

class fft : public QObject
{
    Q_OBJECT
public:
    explicit fft(QObject *parent = nullptr);
    ~fft();

    void Start(QList<double> dataIn, double samplingRate);

signals:
    void complete(QList<double> dataOut);

public slots:

private:
    void FFTComputation(QList<double> &dataIn);

    QEventLoop loop;
    QList<double> m_DataIn;
    QList<double> m_DataOut;
    double * m_FFTOutput;
    double m_scale = 10;
    double m_samplingRate;

    uint16_t freq = 1;
    QList<double> SignalTestBuffer;
};

#endif // FFT_H
