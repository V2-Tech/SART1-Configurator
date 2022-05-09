#ifndef IMU_H
#define IMU_H

#include <QObject>
#include "IIM42652.h"

//--------------------------------------
// -------------- STRUCTS --------------
//--------------------------------------
typedef struct {
    /* Accel */
    float Accel_X_mps2;
    float Accel_Y_mps2;
    float Accel_Z_mps2;

    /* Gyro */
    float Gyro_X_rps;
    float Gyro_Y_rps;
    float Gyro_Z_rps;

    /* Temperature */
    float Temp_C;

    /* Timestamp */
    uint16_t TimeStamp_ODR;

} IMU_Data_Packet_t;

typedef struct {
    /* Accel */
    int16_t m_FIFO_Accel_X;
    int16_t m_FIFO_Accel_Y;
    int16_t m_FIFO_Accel_Z;

    /* Gyro */
    int16_t m_FIFO_Gyro_X;
    int16_t m_FIFO_Gyro_Y;
    int16_t m_FIFO_Gyro_Z;

    /* Temperature */
    int8_t m_FIFO_Temp;

    /* Timestamp */
    uint16_t m_FIFO_TimeStamp;

    /* APEX INT */
    uint8_t m_APEX_INT;

} IMU_Packet_t;

//--------------------------------------
// ------------ FUNCTIONS --------------
//--------------------------------------
float AccFSRConversion(uint8_t AccelFSR);
float GyroFSRConversion(uint8_t GyroFSR);
float AccFSRtoValue(uint8_t AccelFSR);
float GyroFSRtoValue(uint8_t GyroFSR);
float ImuODRtoValue(uint8_t ODR);
#endif // IMU_H
