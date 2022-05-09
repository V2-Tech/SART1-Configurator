#ifndef USBCOMMPROTOCOL_H
#define USBCOMMPROTOCOL_H

#include <QObject>
#include "IIM42652.h"
#include "imu.h"

#define ENABLE 1
#define DISABLE 0

class USBCommProtocol : public QObject
{
    Q_OBJECT
public:
    explicit USBCommProtocol(QObject *parent = nullptr);

    void saveUserConfig(QByteArray &command);

    void setConfigMode(QByteArray &command, uint8_t EnableFlag);
    void getConfigMode(QByteArray &command);
    void setTelemetryEn(QByteArray &command, uint8_t EnableFlag);
    void getTelemetryEn(QByteArray &command);

    void setAccelODR(QByteArray &command, uint8_t AccelODR);
    void getAccelODR(QByteArray &command);
    void setGyroODR(QByteArray &command, uint8_t GyroODR);
    void getGyroODR(QByteArray &command);
    void setAccelFSR(QByteArray &command, uint8_t AccelFSR);
    void getAccelFSR(QByteArray &command);
    void setGyroFSR(QByteArray &command, uint8_t GyroFSR);
    void getGyroFSR(QByteArray &command);
    void setAccelBW(QByteArray &command, uint8_t AccelBW);
    void getAccelBW(QByteArray &command);
    void setGyroBW(QByteArray &command, uint8_t GyroBW);
    void getGyroBW(QByteArray &command);
    void setWOMXth(QByteArray &command, uint8_t threshold);
    void getWOMXth(QByteArray &command);
    void setWOMYth(QByteArray &command, uint8_t threshold);
    void getWOMYth(QByteArray &command);
    void setWOMZth(QByteArray &command, uint8_t threshold);
    void getWOMZth(QByteArray &command);
    void setWOMIntMode(QByteArray &command, uint8_t mode);
    void getWOMIntMode(QByteArray &command);
    void setWOMMode(QByteArray &command, uint8_t mode);
    void getWOMMode(QByteArray &command);
    void setSMDMode(QByteArray &command, uint8_t mode);
    void getSMDMode(QByteArray &command);
private:
    uint8_t dummy = (char)0x00;

signals:

};

enum class CommandType : uint8_t {
    commandSaveUserData = 0xF0,
    commandLoadUserData = 0xF1,
    commandSetTelemetry = 0xFA,
    commandGetTelemetry = 0xFB,
    commandSetConfigMode = 0xFC,
    commandGetConfigMode = 0xFD,
    commandDeviceReset = 0xFE,

    commandAck = 0xAC,

    commandIMUdata = 0xD0,
    commandDOState = 0xD1,
    commandString = 0xD2,

    commandSetAccODR = 0x10,
    commandGetAccODR = 0x11,
    commandSetAccFSR = 0x12,
    commandGetAccFSR = 0x13,
    commandSetAccBW = 0x14,
    commandGetAccBW = 0x15,

    commandSetGyroODR = 0x20,
    commandGetGyroODR = 0x21,
    commandSetGyroFSR = 0x22,
    commandGetGyroFSR = 0x23,
    commandSetGyroBW = 0x24,
    commandGetGyroBW = 0x25,

    commandSetWomXTh = 0x30,
    commandGetWomXTh = 0x31,
    commandSetWomYTh = 0x32,
    commandGetWomYTh = 0x33,
    commandSetWomZTh = 0x34,
    commandGetWomZTh = 0x35,
    commandSetWomIntMode = 0x36,
    commandGetWomIntMode = 0x37,
    commandSetWomMode = 0x38,
    commandGetWomMode = 0x39,
    commandSetSmdMode = 0x3A,
    commandGetSmdMode = 0x3B,
};

enum CommandGroup : uint8_t {
    CommandGroup_AC1Menagment = 0xF,

    CommandGroup_Ack = 0xA,

    CommandGroup_Generic = 0xD,

    CommandGroup_Accel = 0x1,

    CommandGroup_Gyro = 0x2,

    CommandGroup_APEX_INT2 = 0x3,
};

typedef enum
{
    OMD_COMM_ACK_OK	= 0x10,
    OMD_COMM_ACK_ERR = 0x01,
} OMD_ack_values;

#endif // USBCOMMPROTOCOL_H
