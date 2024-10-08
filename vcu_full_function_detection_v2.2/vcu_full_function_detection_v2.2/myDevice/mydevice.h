#ifndef MYDEVICE_H
#define MYDEVICE_H

#include <QMainWindow>
#include <QObject>
#include "ControlCANx86/ControlCAN.h"
#include <thread>
#include <QDebug>
#include <iostream>
#include <iomanip>


class myDevice : public QObject
{
    Q_OBJECT


public:
    explicit myDevice(QObject *parent = nullptr);

    std::thread th_receive_;

    bool is_running_ = false;

    int const device_type_ = 3; /* USBCAN1 */
    int const device_index_ = 0; /* 索引号0 */
    int const can_index_ = 0;


 public:
    bool Start(int baudrate = 250);

    void Stop();

    bool SendCanData(VCI_CAN_OBJ frame);

    void ClearBuffer();

    void PrintData(const VCI_CAN_OBJ frame, std::string str);

    bool InitCanDevice(int baudrate);

    void ReceiveCanData();
signals:
    void canDataReceived(const VCI_CAN_OBJ &canData);

public slots:
};

#endif // MYDEVICE_H
