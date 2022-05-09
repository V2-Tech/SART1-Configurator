#include "fft.h"

fft::fft(QObject *parent)
    : QObject{parent}
{
    ;
}

fft::~fft()
{
    qInfo() << this << "FFT thread ended on thread: " << QThread::currentThread();
}

void fft::Start(QList<double> dataIn, double samplingRate)
{
    QThread::currentThread()->setObjectName("FFT thread");
    qInfo() << this << "FFT thread start on thread: " << QThread::currentThread();

    m_DataIn = dataIn;
    m_samplingRate = samplingRate;

//    float sin_val;
//    uint i = 0;
//    SignalTestBuffer.clear();

//    freq = 2;

//    do {
//        /* Calculate sinus value */
//        sin_val = 0;

//        sin_val += (float)1 * (float)sin((float)2 * (float)3.14159265359 * (float)1 * (float)freq * (float)i / (float)(FFT_SIZE));
//        sin_val += (float)0.5 * (float)sin((float)2 * (float)3.14159265359 * (float)2 * (float)freq * (float)i / (float)(FFT_SIZE));
//        sin_val += (float)0.2 * (float)sin((float)2 * (float)3.14159265359 * (float)3 * (float)freq * (float)i / (float)(FFT_SIZE));

//        SignalTestBuffer.append(sin_val);

//        i++;
//    } while (i<FFT_SIZE);

    m_DataOut.resize(dataIn.size());
    FFTComputation(m_DataIn);
//    m_DataOut.resize(FFT_SIZE);
//    FFTComputation(SignalTestBuffer);

    delete this;
}

void fft::FFTComputation(QList<double> &dataIn)
{
    int nSample = dataIn.count();
    double *outData = m_DataOut.data();
    fftw_plan plan = fftw_plan_r2r_1d(nSample, dataIn.data(), m_DataOut.data(), FFTW_R2HC, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_cleanup();

    //Normalize, scale and calc absolute value of output
    for(int i = 0; i < m_DataOut.count()/2; i++)
    {
        if (i == 0)
        {
            m_DataOut[i] = abs((outData[i] * m_scale)/nSample);
        }
        else
        {
            //Compute FFT magnitude
            m_DataOut[i] = sqrt(outData[i]*outData[i] + outData[nSample-i]*outData[nSample-i]);
            m_DataOut[nSample-i] = 0;

            //Optain power spectral density
            double kFactor = m_scale / (m_samplingRate * nSample);
            m_DataOut[i] *= m_DataOut[i];
            m_DataOut[i] *= kFactor;
        }
    }

    emit complete(m_DataOut);
}
