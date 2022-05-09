#ifndef IIM42652_H
#define IIM42652_H

#include <QObject>

//--------------------------------------
// ------------ REGISTERS --------------
//--------------------------------------

/*
 * User Bank 0
 */
#define REG_DEVICE_CONFIG 0x11
#define REG_DRIVE_CONFIG 0x13
#define REG_INT_CONFIG 0x14
#define REG_FIFO_CONFIG 0x16
#define	REG_TEMP_DATA1_UI 0x1D
#define	REG_ACCEL_DATA_X1_UI 0x1F
#define	REG_ACCEL_DATA_Y1_UI 0x21
#define REG_ACCEL_DATA_Z1_UI 0x23
#define REG_GYRO_DATA_X1_UI 0x25
#define	REG_GYRO_DATA_Y1_UI 0x27
#define	REG_GYRO_DATA_Z1_UI 0x29
#define	REG_TMST_FSYNCH 0x2B
#define REG_INT_STATUS 0x2D
#define REG_FIFO_COUNTH 0x2E
#define REG_FIFO_COUNTL 0x2F
#define	REG_FIFO_DATA 0x30
#define REG_APEX_DATA0 0x31
#define	REG_APEX_DATA1 0x32
#define	REG_APEX_DATA2 0x33
#define	REG_APEX_DATA3 0x34
#define	REG_APEX_DATA4 0x35
#define	REG_APEX_DATA5 0x36
#define	REG_INT_STATUS2 0x37
#define	REG_INT_STATUS3 0x38
#define	REG_SIGNAL_PATH_RESET 0x4B
#define REG_INTF_CONFIG0 0x4C
#define REG_INTF_CONFIG1 0x4D
#define	REG_PWR_MGMT0 0x4E
#define	REG_GYRO_CONFIG0 0x4F
#define	REG_ACCEL_CONFIG0 0x50
#define REG_GYRO_CONFIG1 0x51
#define	REG_GYRO_ACCEL_CONFIG0 0x52
#define REG_ACCEL_CONFIG1 0x53
#define REG_TMST_CONFIG 0x54
#define REG_APEX_CONFIG0 0x56
#define REG_SMD_CONFIG 0x57
#define REG_FIFO_CONFIG1 0x5F
#define REG_FIFO_CONFIG2 0x60
#define REG_FIFO_CONFIG3 0x61
#define REG_FSYNC_CONFIG 0x62
#define REG_INT_CONFIG0 0x63
#define REG_INT_CONFIG1 0x64
#define REG_INT_SOURCE0 0x65
#define REG_INT_SOURCE1 0x66
#define REG_INT_SOURCE3 0x68
#define REG_INT_SOURCE4 0x69
#define REG_FIFO_LOST_PKT0 0x6C
#define REG_FIFO_LOST_PKT1 0x6D
#define REG_SELF_TEST_CONFIG 0x70
#define REG_WHO_AM_I 0x75
#define REG_REG_BANK_SEL 0x76

/*
 * User Bank 1
 */
#define REG_SENSOR_CONFIG0 0x03
#define REG_GYRO_CONFIG_STATIC2 0x0B
#define REG_GYRO_CONFIG_STATIC3 0x0C
#define REG_GYRO_CONFIG_STATIC4 0x0D
#define REG_GYRO_CONFIG_STATIC5 0x0E
#define REG_GYRO_CONFIG_STATIC6 0x0F
#define REG_GYRO_CONFIG_STATIC7 0x10
#define REG_GYRO_CONFIG_STATIC8 0x11
#define REG_GYRO_CONFIG_STATIC9 0x12
#define REG_GYRO_CONFIG_STATIC10 0x13
#define REG_XG_ST_DATA 0x5F
#define	REG_YG_ST_DATA 0x5F
#define REG_ZG_ST_DATA 0x5F
#define REG_TMSTVAL0 0x62
#define REG_TMSTVAL1 0x63
#define REG_TMSTVAL2 0x64
#define REG_INTF_CONFIG4 0x7A
#define REG_INTF_CONFIG5 0x7B
#define REG_INTF_CONFIG6 0x7C

/*
 * User Bank 2
 */
#define REG_ACCEL_CONFIG_STATIC2 0x03
#define REG_ACCEL_CONFIG_STATIC3 0x04
#define REG_ACCEL_CONFIG_STATIC4 0x05
#define REG_XA_ST_DATA 0x3B
#define REG_YA_ST_DATA 0x3C
#define REG_ZA_ST_DATA 0x3D

/*
 * User Bank 3
 */
#define REG_PU_PD_CONFIG1 0x06
#define REG_PU_PD_CONFIG2 0x0E

/*
 * User Bank 4
 */
#define REG_FDR_CONFIG 0x09
#define REG_APEX_CONFIG1 0x40
#define REG_APEX_CONFIG2 0x41
#define REG_APEX_CONFIG3 0x42
#define REG_APEX_CONFIG4 0x43
#define REG_APEX_CONFIG5 0x44
#define REG_APEX_CONFIG6 0x45
#define REG_APEX_CONFIG7 0x46
#define REG_APEX_CONFIG8 0x47
#define REG_APEX_CONFIG9 0x48
#define REG_APEX_CONFIG10 0x49
#define REG_ACCEL_WOM_X_THR 0x4A
#define REG_ACCEL_WOM_Y_THR 0x4B
#define REG_ACCEL_WOM_Z_THR 0x4C
#define REG_INT_SOURCE6 0x4D
#define REG_INT_SOURCE7  0x4E
#define REG_INT_SOURCE8  0x4F
#define REG_INT_SOURCE9  0x50
#define REG_INT_SOURCE10  0x51
#define REG_OFFSET_USER0 0x77
#define REG_OFFSET_USER1 0x78
#define REG_OFFSET_USER2 0x79
#define REG_OFFSET_USER3 0x7A
#define REG_OFFSET_USER4 0x7B
#define REG_OFFSET_USER5 0x7C
#define REG_OFFSET_USER6 0x7D
#define REG_OFFSET_USER7 0x7E
#define REG_OFFSET_USER8 0x7F

//--------------------------------------
// --------- GENERAL VALUE -------------
//--------------------------------------
#define WOM_RESOLUTION 0.0039
#define FIFO_INVALID_SAMPLE -32768

//--------------------------------------
// ------------ ENUMERTORS -------------
//--------------------------------------

/**
 * @brief  Parameter for accelerometer range
 */
enum IIM42652_AccFSValues
{
    IIM42652_Accelerometer_16G = 0x00, /*!< Range is +- 16G */
    IIM42652_Accelerometer_8G = 0x01,
    IIM42652_Accelerometer_4G = 0x02,
    IIM42652_Accelerometer_2G = 0x03
} ;

/**
 * @brief  Parameter for gyroscope range
 */
enum IIM42652_GyroFSValues
{
    IIM42652_Gyroscope_2000dps = 0x00, /*!< Range is +- 2000degree/sec */
    IIM42652_Gyroscope_1000dps = 0x01,
    IIM42652_Gyroscope_500dps = 0x02,
    IIM42652_Gyroscope_250dps = 0x03,
    IIM42652_Gyroscope_125dps = 0x04,
    IIM42652_Gyroscope_62_5dps = 0x05,
    IIM42652_Gyroscope_31_25dps = 0x06,
    IIM42652_Gyroscope_15_625dps = 0x07
} ;

/**
 * @brief  Parameter for accelerometer output data rate (ODR)
 */
enum IIM42652_AccODRValues
{
    IIM42652_Accelerometer_32kHz = 0x01, /*!< ODR is 32kHz */
    IIM42652_Accelerometer_16kHz = 0x02,
    IIM42652_Accelerometer_8kHz = 0x03, /* Require LN mode */
    IIM42652_Accelerometer_4kHz = 0x04, /* Require LN mode */
    IIM42652_Accelerometer_2kHz = 0x05, /* Require LN mode */
    IIM42652_Accelerometer_1kHz = 0x06, /* Default value, require LN mode */
    IIM42652_Accelerometer_200Hz = 0x07, /* Require LN or LP mode */
    IIM42652_Accelerometer_100Hz = 0x08, /* Require LN or LP mode */
    IIM42652_Accelerometer_50Hz = 0x09, /* Require LN or LP mode */
    IIM42652_Accelerometer_25Hz = 0x0A, /* Require LN or LP mode */
    IIM42652_Accelerometer_12_5Hz = 0x0B, /* Require LN or LP mode */
    IIM42652_Accelerometer_6_25Hz = 0x0C, /* Require LP mode */
    IIM42652_Accelerometer_3_125Hz = 0x0D, /* Require LP mode */
    IIM42652_Accelerometer_1_5625Hz = 0x0E, /* Require LP mode */
    IIM42652_Accelerometer_500Hz = 0x0F /* Require LN or LP mode */
} ;

/**
 * @brief  Parameter for gyroscope output data rate (ODR)
 */
enum IIM42652_GyroODRValues
{
    IIM42652_Gyroscope_32kHz = 0x01, /*!< ODR is 32kHz */
    IIM42652_Gyroscope_16kHz = 0x02,
    IIM42652_Gyroscope_8kHz = 0x03,
    IIM42652_Gyroscope_4kHz = 0x04,
    IIM42652_Gyroscope_2kHz = 0x05,
    IIM42652_Gyroscope_1kHz = 0x06, /* Default value */
    IIM42652_Gyroscope_200Hz = 0x07,
    IIM42652_Gyroscope_100Hz = 0x08,
    IIM42652_Gyroscope_50Hz = 0x09,
    IIM42652_Gyroscope_25Hz = 0x0A,
    IIM42652_Gyroscope_12_5Hz = 0x0B,
    IIM42652_Gyroscope_500Hz = 0x0F
} ;

/**
 * @brief  Parameter for accelerometer bandwidth
 */
typedef enum  {
    IIM42652_Accelerometer_ODR_2 = 0x00,
    IIM42652_Accelerometer_ODR_4 = 0x01, /* Default value */
    IIM42652_Accelerometer_ODR_5 = 0x02,
    IIM42652_Accelerometer_ODR_8 = 0x03,
    IIM42652_Accelerometer_ODR_10 = 0x04,
    IIM42652_Accelerometer_ODR_16 = 0x05,
    IIM42652_Accelerometer_ODR_20 = 0x06,
    IIM42652_Accelerometer_ODR_40 = 0x07,
    IIM42652_Accelerometer_ODR_LL = 0x0E,
    IIM42652_Accelerometer_ODR_LLx8 = 0x0F,
} IIM42652_AccBWValues;

/**
 * @brief  Parameter for gyroscope bandwidth
 */
typedef enum  {
    IIM42652_Gyroscope_ODR_2 = 0x00,
    IIM42652_Gyroscope_ODR_4 = 0x01, /* Default value */
    IIM42652_Gyroscope_ODR_5 = 0x02,
    IIM42652_Gyroscope_ODR_8 = 0x03,
    IIM42652_Gyroscope_ODR_10 = 0x04,
    IIM42652_Gyroscope_ODR_16 = 0x05,
    IIM42652_Gyroscope_ODR_20 = 0x06,
    IIM42652_Gyroscope_ODR_40 = 0x07,
    IIM42652_Gyroscope_ODR_LL = 0x0E,
    IIM42652_Gyroscope_ODR_LLx8 = 0x0F,
} IIM42652_GyroBWValues;

/**
 * @brief  Parameter for interrupt output pin chose
 */
typedef enum  {
    IMU_Int_1 = 1,
    IMU_Int_2 = 2,
    IMU_Int_1_2 = 3
} IIM42652_InterruptPinNumber;

/**
 * @brief  Parameter for interrupt output type (Pulsed or Latched)
 */
typedef enum  {
    IMU_Int_Pulsed = 0,
    IMU_Int_Latched = 1,
} IIM42652_InterruptType;

/**
 * @brief  Parameter for interrupt output circuit (Open drain or Push-pull)
 */
typedef enum  {
    IMU_Int_OpenDrain = 0,
    IMU_Int_PushPull = 1,
} IIM42652_InterruptCircuit;

/**
 * @brief  Parameter for interrupt output polarity (Active low or high)
 */
typedef enum  {
    IMU_Int_ActiveLow = 0,
    IMU_Int_ActiveHigh = 1,
} IIM42652_InterruptPolarity;

/**
 * @brief  Parameter for interrupt output duration chose (100usec or 8usec)
 */
typedef enum  {
    IMU_IntPuls_100u = 0,
    IMU_IntPuls_8u = 1,
} IIM42652_InterruptDuration;

/**
 * @brief  Parameter for interrupt output source event chose
 */
typedef enum  {
    /* INT_SOURCE0 or INT_SOURCE3 */
    IMU_IntSource_UI_FSYNC = 6,
    IMU_IntSource_PLL_RDY = 5,
    IMU_IntSource_RESET_DONE = 4,
    IMU_IntSource_UI_Data_RDY = 3,
    IMU_IntSource_FIFO_THS = 2,
    IMU_IntSource_FIFO_FULL = 1,
    IMU_IntSource_UI_AGC_RDY = 0,
    /* INT_SOURCE1 or INT_SOURCE4 */
    IMU_IntSource_SMD = 11,
    IMU_IntSource_WOM_Z = 10,
    IMU_IntSource_WOM_Y = 9,
    IMU_IntSource_WOM_X = 8
} IIM42652_InterruptSource;

/**
 * @brief  Parameter for Wake On Motion detection interrupt mode (OR or AND with all set accel threshold)
 */
typedef enum  {
    IMU_WOMIntMode_OR = 0,
    IMU_WOMIntMode_AND = 1,
} IIM42652_WOMInterruptMode;

/**
 * @brief  Parameter for Wake On Motion mode (compare with: initial or previous sample)
 */
typedef enum  {
    IMU_WOMMode_Initial = 0,
    IMU_WOMMode_Previous = 1,
} IIM42652_WOMMode;

/**
 * @brief  Parameter for Wake On Motion detection interrupt mode (OR or AND with all set accel threshold)
 */
typedef enum  {
    IMU_SMDMode_Disabled = 0,
    IMU_SMDMode_WOM = 1,
    IMU_SMDMode_WOM_short = 2, /* two WOM are detected 1 sec apart */
    IMU_SMDMode_WOM_long = 3 /* two WOM are detected 3 sec apart */
} IIM42652_SMDMode;

/**
 * @brief  Parameter for Accelerometer enabling mode
 */
typedef enum  {
    IMU_AccelMode_OFF = 0,
    IMU_AccelMode_LP = 2, /* Low power mode */
    IMU_AccelMode_LN = 3 /* Low noise mode */
} IIM42652_AccelMode;

/**
 * @brief  Parameter for Gyroscope enabling mode
 */
typedef enum  {
    IMU_GyroMode_OFF = 0,
    IMU_GyroMode_Standby = 1,
    IMU_GyroMode_LN = 3 /* Low noise mode */
} IIM42652_GyroMode;

/**
 * @brief  Parameter for select the FIFO steaming mode
 */
typedef enum  {
    IMU_FIFOMode_Bypass = 0,
    IMU_FIFOMode_Steam_Continuos = 1,
    IMU_FIFOMode_Steam_StopOnFull = 3
} IIM42652_FIFOMode;

/**
 * @brief  Parameter for select the FIFO counting mode
 */
typedef enum  {
    IMU_FIFOCountMode_Bytes = 0,
    IMU_FIFOCountMode_Records = 1 //(1 record = 16 bytes for header + gyro + accel + temp sensor data + time stamp, or 8 bytes for header + gyro/accel + temp sensor data)
} IIM42652_FIFOCountMode;

/**
 * @brief  Parameter for select the desired register bank
 */
typedef enum  {
    IMU_RegBank_0 = 0,
    IMU_RegBank_1 = 1,
    IMU_RegBank_2 = 2,
    IMU_RegBank_3 = 3,
    IMU_RegBank_4 = 4
} IIM42652_RegBankValue;

/**
 * @brief  Parameter for decrypt interrupt status register
 */
typedef enum  {
    IMU_IntStatus_AGC_Ready = 0,
    IMU_IntStatus_FIFO_Full = 1,
    IMU_IntStatus_FIFO_Ths = 2,
    IMU_IntStatus_Data_Ready = 3,
    IMU_IntStatus_Reset_Done = 4,
    IMU_IntStatus_PLL_Ready = 5,
    IMU_IntStatus_UiFSync = 6
} IIM42652_IntStatus_Bits;

#endif // IIM42652_H
