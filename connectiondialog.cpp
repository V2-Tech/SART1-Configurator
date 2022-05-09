#include "connectiondialog.h"
#include "ui_connectiondialog.h"

static const char blankString[] = QT_TRANSLATE_NOOP("connectionDialog", "N/A");

connectionDialog::connectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectionDialog)
{
    ui->setupUi(this);

    connect(ui->portBox, &QComboBox::currentIndexChanged, this, &connectionDialog::updatePortInfo);

    fillPortsParameters();
    fillPortsList();

    applySettings();
}

connectionDialog::~connectionDialog()
{
    delete ui;
}

connectionDialog::SerialSettings connectionDialog::getSerialSettings()
{
    return m_currentSettings;
}

void connectionDialog::on_applyButton_clicked()
{
    applySettings();
    accept();
}

void connectionDialog::fillPortsParameters()
{
    ui->baudrateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudrateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudrateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudrateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->baudrateBox->setCurrentIndex(3);
}

void connectionDialog::fillPortsList()
{
    ui->portBox->clear();
    QString description;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        description = info.description();
        QStringList list;
        list << info.portName()
             << (!description.isEmpty() ? description : blankString);

        ui->portBox->addItem(list.first(), list);
    }
}

void connectionDialog::applySettings()
{
    m_currentSettings.name = ui->portBox->currentText();

    m_currentSettings.baudRate = ui->baudrateBox->currentText().toInt();

    m_currentSettings.stringBaudRate = QString::number(m_currentSettings.baudRate);

    m_currentSettings.dataBits = QSerialPort::Data8;
    m_currentSettings.stringDataBits = QString::number(m_currentSettings.dataBits);

    m_currentSettings.parity = QSerialPort::NoParity;
    m_currentSettings.stringParity = QString::number(m_currentSettings.parity);

    m_currentSettings.stopBits = QSerialPort::OneStop;
    m_currentSettings.stringStopBits = QString::number(m_currentSettings.stopBits);

    m_currentSettings.flowControl = QSerialPort::NoFlowControl;
    m_currentSettings.stringFlowControl = QString::number(m_currentSettings.flowControl);
}

void connectionDialog::on_realoadButton_clicked()
{
    fillPortsList();
}

void connectionDialog::updatePortInfo(int index)
{
    if (index == -1)
    {
        return;
    }

    const QStringList list = ui->portBox->itemData(index).toStringList();
    ui->descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
}

