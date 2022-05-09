#include "usbcommprotocol.h"

USBCommProtocol::USBCommProtocol(QObject *parent)
    : QObject{parent}
{

}

void USBCommProtocol::saveUserConfig(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandSaveUserData));
    command.push_back((char)0x01);
}

void USBCommProtocol::setConfigMode(QByteArray &command, uint8_t EnableFlag)
{
    command.push_back(static_cast<char>(CommandType::commandSetConfigMode));
    command.push_back((char)EnableFlag);
}

void USBCommProtocol::getConfigMode(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetConfigMode));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setTelemetryEn(QByteArray &command, uint8_t EnableFlag)
{
    command.push_back(static_cast<char>(CommandType::commandSetTelemetry));
    command.push_back((char)EnableFlag);
}

void USBCommProtocol::getTelemetryEn(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetTelemetry));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setAccelODR(QByteArray &command, uint8_t AccelODR)
{
    command.push_back(static_cast<char>(CommandType::commandSetAccODR));
    command.push_back(static_cast<char>(AccelODR));
}

void USBCommProtocol::getAccelODR(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetAccODR));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setGyroODR(QByteArray &command, uint8_t GyroODR)
{
    command.push_back(static_cast<char>(CommandType::commandSetGyroODR));
    command.push_back(static_cast<char>(GyroODR));
}

void USBCommProtocol::getGyroODR(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetGyroODR));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setAccelFSR(QByteArray &command, uint8_t AccelFSR)
{
    command.push_back(static_cast<char>(CommandType::commandSetAccFSR));
    command.push_back(static_cast<char>(AccelFSR));
}

void USBCommProtocol::getAccelFSR(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetAccFSR));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setGyroFSR(QByteArray &command, uint8_t GyroFSR)
{
    command.push_back(static_cast<char>(CommandType::commandSetGyroFSR));
    command.push_back(static_cast<char>(GyroFSR));
}

void USBCommProtocol::getGyroFSR(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetGyroFSR));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setAccelBW(QByteArray &command, uint8_t AccelBW)
{
    command.push_back(static_cast<char>(CommandType::commandSetAccBW));
    command.push_back(static_cast<char>(AccelBW));
}

void USBCommProtocol::getAccelBW(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetAccBW));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setGyroBW(QByteArray &command, uint8_t GyroBW)
{
    command.push_back(static_cast<char>(CommandType::commandSetGyroBW));
    command.push_back(static_cast<char>(GyroBW));
}

void USBCommProtocol::getGyroBW(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetGyroBW));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setWOMXth(QByteArray &command, uint8_t threshold)
{
    command.push_back(static_cast<char>(CommandType::commandSetWomXTh));
    command.push_back(static_cast<char>(threshold));
}

void USBCommProtocol::getWOMXth(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetWomXTh));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setWOMYth(QByteArray &command, uint8_t threshold)
{
    command.push_back(static_cast<char>(CommandType::commandSetWomYTh));
    command.push_back(static_cast<char>(threshold));
}

void USBCommProtocol::getWOMYth(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetWomYTh));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setWOMZth(QByteArray &command, uint8_t threshold)
{
    command.push_back(static_cast<char>(CommandType::commandSetWomZTh));
    command.push_back(static_cast<char>(threshold));
}

void USBCommProtocol::getWOMZth(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetWomZTh));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setWOMIntMode(QByteArray &command, uint8_t mode)
{
    command.push_back(static_cast<char>(CommandType::commandSetWomIntMode));
    command.push_back(static_cast<char>(mode));
}

void USBCommProtocol::getWOMIntMode(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetWomIntMode));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setWOMMode(QByteArray &command, uint8_t mode)
{
    command.push_back(static_cast<char>(CommandType::commandSetWomMode));
    command.push_back(static_cast<char>(mode));
}

void USBCommProtocol::getWOMMode(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetWomMode));
    command.push_back(static_cast<char>(dummy));
}

void USBCommProtocol::setSMDMode(QByteArray &command, uint8_t mode)
{
    command.push_back(static_cast<char>(CommandType::commandSetSmdMode));
    command.push_back(static_cast<char>(mode));
}

void USBCommProtocol::getSMDMode(QByteArray &command)
{
    command.push_back(static_cast<char>(CommandType::commandGetSmdMode));
    command.push_back(static_cast<char>(dummy));
}
