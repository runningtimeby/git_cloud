#ifndef MY_ANALYSIS_H
#define MY_ANALYSIS_H

#include "myDevice/mydevice.h"

#include "common.h"

#include <QMainWindow>
#include <QObject>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QQueue>

class myAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit myAnalysis(QObject *parent = nullptr);
public:
    myDevice *myDeviceclass;

    uint16_t const frequency_ = 1000; //频率
    uint16_t const duty_cycle_ = 50;  //占空比
    uint16_t const voltage_ = 3;  //电压值
public:
    VCUType vcuType;
    QVector<VCI_CAN_OBJ> allFrame;
    int currentFrameIndex = 0;
    QTimer* timer;
    bool sendFlag=false;

    bool sendTestBoardNext = true;
    QVector<VCI_CAN_OBJ> WakeUpTestBoardData;
    QVector<VCI_CAN_OBJ> WakeUpVCUData;
    int currentWakeUpTestBoard = 0;
    int currentWakeUpVCU = 0;
public:
    bool StartCan();
    void GenerateCanData(ChannelType name, int send_num, BoardType type);
    void ActiveTestModel(VCUType vcutype);
    void TimerSendCanData();

};

#endif // MY_ANALYSIS_H
