#include "imu.h"

float AccFSRConversion(uint8_t AccelFSR)
{
    float value = 0;

    switch(AccelFSR)
    {
    case IIM42652_Accelerometer_16G:
        value = 2048;
        break;
    case IIM42652_Accelerometer_8G:
         value = 4096;
        break;
    case IIM42652_Accelerometer_4G:
         value = 8192;
        break;
    case IIM42652_Accelerometer_2G:
         value = 16384;
        break;
    }

    return value;
}

float GyroFSRConversion(uint8_t GyroFSR)
{
     float value = 0;
     switch (GyroFSR)
     {
     case IIM42652_Gyroscope_2000dps:
         value = 16.4;
         break;
     case IIM42652_Gyroscope_1000dps:
         value = 32.8;
         break;
     case IIM42652_Gyroscope_500dps:
         value = 65.5;
         break;
     case IIM42652_Gyroscope_250dps:
         value = 131;
         break;
     case IIM42652_Gyroscope_125dps:
         value = 262;
         break;
     case IIM42652_Gyroscope_62_5dps:
         value = 524.3;
         break;
     case IIM42652_Gyroscope_31_25dps:
         value = 1048.6;
         break;
     case IIM42652_Gyroscope_15_625dps:
         value = 2097.2;
         break;
     }

     return value;
}

float AccFSRtoValue(uint8_t AccelFSR)
{
    float value = 0;

    switch(AccelFSR)
    {
    case IIM42652_Accelerometer_16G:
        value = 16;
        break;
    case IIM42652_Accelerometer_8G:
         value = 8;
        break;
    case IIM42652_Accelerometer_4G:
         value = 4;
        break;
    case IIM42652_Accelerometer_2G:
         value = 2;
        break;
    }

    return value;
}

float GyroFSRtoValue(uint8_t GyroFSR)
{
    float value = 0;
    switch (GyroFSR)
    {
    case IIM42652_Gyroscope_2000dps:
        value = 2000;
        break;
    case IIM42652_Gyroscope_1000dps:
        value = 1000;
        break;
    case IIM42652_Gyroscope_500dps:
        value = 500;
        break;
    case IIM42652_Gyroscope_250dps:
        value = 250;
        break;
    case IIM42652_Gyroscope_125dps:
        value = 125;
        break;
    case IIM42652_Gyroscope_62_5dps:
        value = 62.5;
        break;
    case IIM42652_Gyroscope_31_25dps:
        value = 31.25;
        break;
    case IIM42652_Gyroscope_15_625dps:
        value = 15.625;
        break;
    }

    return value;
}

float ImuODRtoValue(uint8_t ODR)
{
    float value = 0;

    switch(ODR)
    {
    case IIM42652_Accelerometer_32kHz:
        value = 32000;
        break;
    case IIM42652_Accelerometer_16kHz:
         value = 16000;
        break;
    case IIM42652_Accelerometer_8kHz:
         value = 8000;
        break;
    case IIM42652_Accelerometer_4kHz:
         value = 4000;
        break;
    case IIM42652_Accelerometer_2kHz:
        value = 2000;
        break;
    case IIM42652_Accelerometer_1kHz:
         value = 1000;
        break;
    case IIM42652_Accelerometer_500Hz:
         value = 500;
        break;
    case IIM42652_Accelerometer_200Hz:
         value = 200;
        break;
    case IIM42652_Accelerometer_100Hz:
        value = 100;
        break;
    case IIM42652_Accelerometer_50Hz:
         value = 50;
        break;
    case IIM42652_Accelerometer_25Hz:
         value = 25;
        break;
    case IIM42652_Accelerometer_12_5Hz:
         value = 12.5;
        break;
    case IIM42652_Accelerometer_6_25Hz:
         value = 6.25;
        break;
    case IIM42652_Accelerometer_3_125Hz:
         value = 3.125;
        break;
    case IIM42652_Accelerometer_1_5625Hz:
        value = 1.5625;
        break;
    }

    return value;
}
