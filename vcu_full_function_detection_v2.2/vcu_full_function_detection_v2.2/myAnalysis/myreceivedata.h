#ifndef MYRECEIVEDATA_H
#define MYRECEIVEDATA_H

#include <QObject>
#include <QTimer>
#include "myDevice/mydevice.h"
#include "common.h"

class myreceivedata : public QObject
{
    Q_OBJECT
public:
    explicit myreceivedata(QObject *parent = nullptr);

public:
    VCUType vcuType;

    int examineFlag=1;
    uint16_t const frequency_ = 1000; //频率
    uint16_t const duty_cycle_ = 50;  //占空比
    uint16_t const voltage_ = 3;  //电压值
public://保存解析后的数据
    QString switchInputStr;
    QString switchLowDriverStr;
    QString frequencyLowStr;
    QString switchHighStr;
    QString canStr;
    QString frequencyInputStr;
    QString analogQuantityStr;
    QString AdcCheckChannelStr;
    QString WakeUpDetectionStr;
 public:   //解析后的数据正确的通道好会添加到集合中
    QSet<int> SwitchInput_set;      // 开关量输入 
    QSet<int> SwitchLowDriver_set;      // 开关型低边驱动
    QSet<int> FrequencyLowDriver_set;   // 频率型低边驱动
    QSet<int> SwitchHighDriver_set;     // 开关型高边驱动
    QSet<int> Can_set;                 // CAN
    QSet<int> FrequencyInput_set;       // 频率量检测输入
    QSet<int> AnalogQuantity_set;       // 模拟量

    QSet<int> AdcCheckChannel_set;  //ADC
    QSet<int> WakeUpDetection_set;  //唤醒

    QSet<int> HardSwitchInput_set; // 硬件开关量通道检测
    QSet<int> SoftSwitchInput_set; //软件型开关量通道检测
    QSet<int> FrequencyChannelInput_set; //频率量输入通道检测
    QSet<int> HighDriveInit_set; //高边驱动初始化
    QSet<int> LowDriveInit_set; //低边驱动初始化
public:
    ChannelParameters switchInputParams;
    ChannelParameters switchLowDriverParams;
    ChannelParameters frequencyLowDriverParams;
    ChannelParameters switchHighDriverParams;
    ChannelParameters canParams;
    ChannelParameters frequencyInputParams;
    ChannelParameters analogQuantityParams;

    ChannelParameters adcCheckChannelParams;
    ChannelParameters wakeupDetectionParams;

    ChannelParameters hardSwitchInputInitParams;
    ChannelParameters softSwitchInitParams;
    ChannelParameters frequencyInitParams;
    ChannelParameters highDriveInitParams;
    ChannelParameters lowDriveInitParams;
public:
    void ParseSwitchInput(const VCI_CAN_OBJ &frame);
    void ParseCanChannel(const VCI_CAN_OBJ &frame);
    void ParseSwitchLowDriver(const VCI_CAN_OBJ &frame);
    void ParseFrequencyLowDriver(const VCI_CAN_OBJ &frame);
    void ParseSwitchHighDriver(const VCI_CAN_OBJ &frame);
    void ParseFrequencyInput(const VCI_CAN_OBJ &frame);
    void ParseAnalogQuantity(const VCI_CAN_OBJ &frame);
    void ParseAnalogQuantity_cv03a(const VCI_CAN_OBJ frame);
    void ParseAnalogQuantity_cv03b(const VCI_CAN_OBJ frame);
    void ParseAnalogQuantity_cv02a(const VCI_CAN_OBJ frame);
    void ParseAnalogQuantity_cv01a(const VCI_CAN_OBJ frame);

    void ParseAdcCheckChannel(const VCI_CAN_OBJ &frame);
    void ParseWakeUpDetection(const VCI_CAN_OBJ &frame);
    void ParseHardSwitchInputInit(const VCI_CAN_OBJ frame);
    void ParseSoftSwitchInputInit(const VCI_CAN_OBJ frame);
    void ParseFrequencyInputInit(const VCI_CAN_OBJ frame);
    void ParseHighDriveInit(const VCI_CAN_OBJ frame);
    void ParseLowDriveInit(const VCI_CAN_OBJ frame);

public:
    void vcutype(VCUType vcutype);
    QList<int> GetUnusualNum(int send_num, const QSet<int> set);
    void ChannelParameter(const ChannelParameters& params);
    void ClearBuff();
public:
    void TimerResultdata(int channelNum);
    void ExamineData(int sendNum, const QSet<int> setType,QString typeName,QString stateData);
    void ExamineWakeUpData(int sendNum, const QSet<int> setType,QString typeName,QString stateData);
signals:
    void ResultSignal(const DetectionResult &ResultData,int resultFlag,QString stateData);

public slots:
    void ReceiveCanData(const VCI_CAN_OBJ &frame);


signals:

};

#endif // MYRECEIVEDATA_H
