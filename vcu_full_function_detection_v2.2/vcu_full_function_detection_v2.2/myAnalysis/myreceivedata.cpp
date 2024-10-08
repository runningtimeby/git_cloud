#include "myreceivedata.h"

myreceivedata::myreceivedata(QObject *parent) : QObject(parent)
{

}
void myreceivedata::vcutype(VCUType vcutype)
{
    vcuType=vcutype;
}
void myreceivedata::ChannelParameter(const ChannelParameters &params)
{
    switch (params.name)
    {
    case SwitchInputChannel:
        switchInputParams = params;
        break;
    case SwitchLowDriverChannel:
        switchLowDriverParams = params;
        break;
    case FrequencyLowDriverChannel:
        frequencyLowDriverParams = params;
        break;
    case SwitchHighDriverChannel:
        switchHighDriverParams = params;
        break;
    case CanChannel:
        canParams = params;
        break;
    case FrequencyInputChannel:
        frequencyInputParams = params;
        break;
    case AnalogQuantityChannel:
        analogQuantityParams = params;
        break;
    case AdcCheckChannel:
        adcCheckChannelParams= params;
        break;
    case WakeUpDetection:
        wakeupDetectionParams= params;
        break;
    case HardSwitchInputInitChannel:
        hardSwitchInputInitParams= params;
        break;
    case SoftSwitchInputInitChannel:
        softSwitchInitParams= params;
        break;
    case FrequencyInputInitChannelCheck:
        frequencyInitParams= params;
        break;
    case HighDriveInitChannel:
        highDriveInitParams= params;
        break;
    case LowDriveInitChannel:
        lowDriveInitParams= params;
        break;
    default:
        qDebug() << "未知通道类型";
        break;
    }
}


void myreceivedata::TimerResultdata(int channelNum)//定时获取结果函数
{
    switch (channelNum)
    {
    case 1:
        ExamineData(hardSwitchInputInitParams.sendNum,HardSwitchInput_set,"硬件开关量初始化检测",switchInputStr);
        break;
    case 2:
        ExamineData(softSwitchInitParams.sendNum,SoftSwitchInput_set,"软件开关量初始化检测",switchInputStr);
        break;
    case 3:
        ExamineData(frequencyInitParams.sendNum,FrequencyChannelInput_set,"频率量输入初始化检测",switchInputStr);
        break;
    case 4:
        ExamineData(highDriveInitParams.sendNum,HighDriveInit_set,"高边驱动初始化检测",switchInputStr);
        break;
    case 5:
        ExamineData(lowDriveInitParams.sendNum,LowDriveInit_set,"低边驱动初始化检测",switchInputStr);
        break;
    case 6:
        ExamineData(switchInputParams.sendNum, SwitchInput_set,"开关量输入检测",switchInputStr);
        break;
    case 7:
        ExamineData(switchLowDriverParams.sendNum, SwitchLowDriver_set,"开关型低边驱动",switchLowDriverStr);
        break;
    case 8:
        ExamineData(frequencyLowDriverParams.sendNum,FrequencyLowDriver_set,"频率型低边驱动",frequencyLowStr);
        break;
    case 9:
        ExamineData(switchHighDriverParams.sendNum,SwitchHighDriver_set,"开关型高边驱动",switchHighStr);
        break;
    case 10:
        ExamineData(canParams.sendNum,Can_set,"CAN检测",canStr);
        break;
    case 11:
        ExamineData(frequencyInputParams.sendNum,FrequencyInput_set,"频率量输入检测",frequencyInputStr);
        break;
    case 12:
        ExamineData(analogQuantityParams.sendNum,AnalogQuantity_set,"模拟量输入检测",analogQuantityStr);
        break;
    case 13:
        ExamineData(adcCheckChannelParams.sendNum,AdcCheckChannel_set,"5V输出检测",AdcCheckChannelStr);
        break;

    case 14:
        if(vcuType == CV01A_220_001A00)
        {
            ExamineData(wakeupDetectionParams.sendNum,WakeUpDetection_set,"唤醒输入检测",WakeUpDetectionStr);
        }
        else
        {
            ExamineWakeUpData(wakeupDetectionParams.sendNum,WakeUpDetection_set,"唤醒输入检测",WakeUpDetectionStr);
        }
        break;
    default:
        return;
    }
}

void myreceivedata::ReceiveCanData(const VCI_CAN_OBJ &frame)
{
    if(frame.ID > 0x60) return;
    if(frame.Data[0] != QTApp) return;

    std::cout<< "REC:" << ": " << std::hex <<frame.ID << " [" << (int)frame.DataLen << "] ";
    for (int j = 0; j < frame.DataLen; j++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(frame.Data[j]) << " ";
    }
    std::cout << std::endl;

    switch (frame.Data[1])
    {
    case 0x01:  // 开关量输入
        ParseSwitchInput(frame);
        break;
    case 0x02:  // 开关型低边驱动
        ParseSwitchLowDriver(frame);
        break;
    case 0x03:  // 频率型低边驱动
        ParseFrequencyLowDriver(frame);
        break;
    case 0x04:  // 开关型高边驱动
        ParseSwitchHighDriver(frame);
        break;
    case 0x05:  // can
        ParseCanChannel(frame);
        break;
    case 0x06: //频率输入
        ParseFrequencyInput(frame);
        break;
    case 0x07: //模拟量
        ParseAnalogQuantity(frame);
        break;
    case 0x08:  // ADC检测
        ParseAdcCheckChannel(frame);
        break;
    case 0x09:  //唤醒检测
        ParseWakeUpDetection(frame);
        break;
    case 0x0A://硬件型开关量通道初始化检测
        ParseHardSwitchInputInit(frame);
        break;
    case 0x0B://软件型开关量通道初始化检测
        ParseSoftSwitchInputInit(frame);
        break;
    case 0x0C://频率型通道初始化检测
        ParseFrequencyInputInit(frame);
        break;
    case 0x0D://高边驱动初始化
        ParseLowDriveInit(frame);
        break;
    case 0x0E://低边驱动初始化
         ParseHighDriveInit(frame);
        break;
    default:
        break;
    }
}
void myreceivedata::ParseSwitchInput(const VCI_CAN_OBJ &frame)
{
    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);
    qDebug() << " 开关量输入: " << value << "  "<< state;
    switchInputStr.append(QString::number(value) + ":" + QString::number(state)+" ");

    int my_state = 0; //低有效
    if(vcuType == CV02A_220_001D00 || vcuType == CV01A_220_001A00)
    {
        my_state = 1; //高有效
    }
    if(state == my_state)
    {
        SwitchInput_set.insert(value);
    }
}
void myreceivedata::ParseSwitchLowDriver(const VCI_CAN_OBJ &frame)
{
    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);
    qDebug() << "开关低边驱动: " << value << "  "<< state;
    switchLowDriverStr.append(QString::number(value) + ":" + QString::number(state)+" ");
    if(state == 0)
    {
        SwitchLowDriver_set.insert(value);
    }
}
void myreceivedata::ParseFrequencyLowDriver(const VCI_CAN_OBJ &frame)
{
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]);
    float num2 = ((frame.Data[5] << 8) | frame.Data[6]);

    int value = static_cast<int>(frame.Data[2]);
    qDebug() << "频率低边驱动: " << value << "  "<< num1 << "  "<< num2;
    frequencyLowStr.append(QString::number(value) + ":" + "num1="+QString::number(num1)+" "+ "num2="+QString::number(num2)+" ");

    if((num1 < frequency_ + 20 && num1 > frequency_ - 20) &&
            num2 < duty_cycle_ + 5 && num2 > duty_cycle_ - 5)
    {
        FrequencyLowDriver_set.insert(value);
    }
}

void myreceivedata::ParseSwitchHighDriver(const VCI_CAN_OBJ &frame)
{
    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);
    qDebug() << "开关高边驱动: " << value << "  "<< state;
    switchHighStr.append(QString::number(value) + ":" + QString::number(state)+" ");
    if(state == 1)
    {
        SwitchHighDriver_set.insert(value);
    }
}
void myreceivedata::ParseCanChannel(const VCI_CAN_OBJ &frame)
{
    int value = static_cast<int>(frame.Data[2]);
    int state = frame.Data[3];
    qDebug() << "CAN: " << value << "  "<< state;
    canStr.append(QString::number(value) + ":" + QString::number(state)+" ");
    if(state == 1)
    {
        Can_set.insert(value);
    }
}
void myreceivedata::ParseFrequencyInput(const VCI_CAN_OBJ &frame)
{
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]) / 10.0;
    float num2 = ((frame.Data[5] << 8) | frame.Data[6]) / 10.0;
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "频率输入: " << value << "  "<< num1 << "  "<< num2;
    frequencyInputStr.append(QString::number(value) + ":" + "num1="+QString::number(num1)+" "+ "num2="+QString::number(num2)+" ");
    switch (vcuType) {
    case CV03A_220_001A00:
    case CV03C_220_001A00:
    case CV03B_220_001A00:
    case CV02A_220_001D00:
        if((num1 < frequency_ + 20 && num1 > frequency_ - 20) &&
                num2 < duty_cycle_ + 5 && num2 > duty_cycle_ - 5)
        {
            FrequencyInput_set.insert(value);
        }
        break;
    case CV01A_220_001A00:
        if((num1 < 100 + 2 && num1 > 100 - 2) &&
                num2 == 0) {
            FrequencyInput_set.insert(value);
        }
        break;
    default:
        break;
    }
}

void myreceivedata::ParseAnalogQuantity(const VCI_CAN_OBJ &frame)//模拟量
{
    switch (vcuType) {
    case CV03A_220_001A00:
    case CV03C_220_001A00:
        ParseAnalogQuantity_cv03a(frame);
        break;
    case CV03B_220_001A00:
        ParseAnalogQuantity_cv03b(frame);
        break;
    case CV01A_220_001A00:
        ParseAnalogQuantity_cv01a(frame);
        break;
    case CV02A_220_001D00:
        ParseAnalogQuantity_cv02a(frame);
        break;
    default:
        break;
    }
}

void myreceivedata::ParseAnalogQuantity_cv03a(const VCI_CAN_OBJ frame)
{
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]) / 10.0;
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "模拟量: " << value << "  "<< num1;
    analogQuantityStr.append(QString::number(value) + ":" + QString::number(num1)+" ");

    if (1 <= value && value <= 4)
    {
        if (std::abs(num1 - voltage_) <= 0.5)
        {
            AnalogQuantity_set.insert(value);
        }
    }
    else if (5 <= value && value <= 10)
    {
        if (std::abs(num1 - 3.3) <= 0.2)
        {
            AnalogQuantity_set.insert(value);
        }
    }
}

void myreceivedata::ParseAnalogQuantity_cv03b(const VCI_CAN_OBJ frame)
{
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]) / 10.0;
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "模拟量: " << value << "  "<< num1;
    analogQuantityStr.append(QString::number(value) + ":" + QString::number(num1)+" ");

    if (1 <= value && value <= 6)
    {
        if (std::abs(num1 - voltage_) <= 0.5)
        {
            AnalogQuantity_set.insert(value);
        }
    }
    else if (9 == value || value == 10)
    {
        if (std::abs(num1 - voltage_) <= 0.5)
        {
            AnalogQuantity_set.insert(value);
        }
    }
    else if (7 == value || value == 8)
    {
        if (std::abs(num1 - 3.3) <= 0.2)
        {
            AnalogQuantity_set.insert(value);
        }
    }
}
void myreceivedata::ParseAnalogQuantity_cv02a(const VCI_CAN_OBJ frame)
{
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]) / 10.0;
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "模拟量: " << value << "  "<< num1;
    analogQuantityStr.append(QString::number(value) + ":" + QString::number(num1)+" ");

    if (1 <= value && value <= 6)
    {
        if (std::abs(num1 - voltage_) <= 0.5)
        {
            AnalogQuantity_set.insert(value);
        }
    }
    else if (7 <= value && value <= 10)
    {
        if (std::abs(num1 - 3.3) <= 0.2)
        {
            AnalogQuantity_set.insert(value);
        }
    }
}

void myreceivedata::ParseAnalogQuantity_cv01a(const VCI_CAN_OBJ frame)
{
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "模拟量: " << value << "  "<< num1;

    if (3 <= value && value <= 8) {
        if (std::abs(num1 - 2) <= 0.2) {
            AnalogQuantity_set.insert(value);
        }
    }else if (2 == value) {
        if (std::abs(num1 - 31) <= 0.2 || std::abs(num1 - 2) <= 0.2) {
              AnalogQuantity_set.insert(value);
        }
    }else if (1 == value) {
        if (std::abs(num1 - 2) <= 0.2) {
            AnalogQuantity_set.insert(value);
        }
    }
}

void myreceivedata::ParseAdcCheckChannel(const VCI_CAN_OBJ &frame)
{
    int value = static_cast<int>(frame.Data[2]);
    float num1 = ((frame.Data[3] << 8) | frame.Data[4]) / 10.0;
    qDebug() << "ADC: " << value << "  "<< num1;
    AdcCheckChannelStr.append(QString::number(value) + ":" + QString::number(num1)+" ");
    if (num1 >= 4.9 && num1 <= 5)
    {
        AdcCheckChannel_set.insert(value);
    }
}

void myreceivedata::ParseWakeUpDetection(const VCI_CAN_OBJ &frame)
{

    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);


    if(vcuType==CV01A_220_001A00)
    {
        qDebug() << " 唤醒: " << value << "  "<< state;
        WakeUpDetectionStr.append(QString::number(value) + ":" + QString::number(state)+" ");

        int my_state = 1; //触发
        if(state == my_state)
        {
            WakeUpDetection_set.insert(value);
        }
    }
    else
    {
        qDebug() << "唤醒: " << value ;
        if(frame.ID == 0x27)
        {
            WakeUpDetection_set.insert(value);
            WakeUpDetectionStr.append(QString::number(value) +" ");
        }
    }
}

void myreceivedata::ParseHardSwitchInputInit(const VCI_CAN_OBJ frame)
{
    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);

    int my_state = 1; //低有效
    if(vcuType == CV02A_220_001D00 || vcuType == CV01A_220_001A00){
        my_state = 0; //高有效或没触发
    }
    qDebug() << "硬件型开关量通道初始化检测: " << value << "  "<< state;

    if(vcuType == CV01A_220_001A00)
    {
        if(state == my_state  && value != 3)
        {
            HardSwitchInput_set.insert(value);
        }
        else if(value == 3 && state == 2)
        {
            HardSwitchInput_set.insert(value);
        }
    }
    else
    {
        if(state == my_state)
        {
            HardSwitchInput_set.insert(value);
        }
    }

}

void myreceivedata::ParseSoftSwitchInputInit(const VCI_CAN_OBJ frame)
{
    float Voltage = ((frame.Data[3] << 8) | frame.Data[4]) / 10.0;
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "软件型开关量通道初始化检测: " << value << "  "<< Voltage;

    if(std::abs(Voltage - 2.5) <= 0.2)
    {
        SoftSwitchInput_set.insert(value);
    }
}

void myreceivedata::ParseFrequencyInputInit(const VCI_CAN_OBJ frame)
{
    float Duty = ((frame.Data[5] << 8) | frame.Data[6]) / 10;
    int value = static_cast<int>(frame.Data[2]);

    qDebug() << "频率量输入通道初始化检测: " << value << "  "<< Duty;

    if(value == 2)
    {
        if(vcuType == CV03A_220_001A00 || vcuType == CV03B_220_001A00 || vcuType == CV02A_220_001D00)
        {
            if(Duty == 100)
            {
                FrequencyChannelInput_set.insert(value);
            }
        }
        if(vcuType == CV03C_220_001A00)
        {
            if(Duty >= 45  && Duty <= 55 )
            {
                FrequencyChannelInput_set.insert(value);
            }
        }
    }
    else
    {
        if(Duty == 0)
        {
            FrequencyChannelInput_set.insert(value);
        }
    }
}

void myreceivedata::ParseHighDriveInit(const VCI_CAN_OBJ frame)
{
    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);

    int my_state = 0; //未打开驱动状态
    qDebug() << "高边驱动初始化: " << value << "  "<< state;
    if(state == my_state)
    {
        HighDriveInit_set.insert(value);
    }
}

void myreceivedata::ParseLowDriveInit(const VCI_CAN_OBJ frame)
{
    int state = ((frame.Data[3] << 8) | frame.Data[4]);
    int value = static_cast<int>(frame.Data[2]);

    int my_state = 1; //未打开驱动状态
    qDebug() << "低边驱动初始化: " << value << "  "<< state;
    if(state == my_state)
    {
        LowDriveInit_set.insert(value);
    }
}
void myreceivedata::ExamineData(int sendNum, const QSet<int> setType, QString typeName,QString stateData)
{
    QList<int> Resultchannel;
    int resultFlag = -1;
    QString strResult;
    if(sendNum==0)
    {
        return;
    }
    if (setType.isEmpty())
    {
        resultFlag = 0;
        strResult = "不合格！异常通道: ";
        for (int i = 1; i <= sendNum; ++i)
        {
            strResult += QString::number(i) + " ";
        }
    }
    else
    {
        Resultchannel = GetUnusualNum(sendNum, setType);
        if (!Resultchannel.isEmpty())
        {
            resultFlag = 0;
            strResult ="不合格！异常通道: ";
            for (int channel : Resultchannel)
            {
                strResult += QString::number(channel) + " ";
            }
        }
        else
        {
            resultFlag = 1;
            strResult = "合格！";
        }
    }
    DetectionResult ResultData;
    ResultData.resultName=typeName;
    ResultData.resultData=strResult;
    emit ResultSignal(ResultData, resultFlag,stateData);
    if(typeName=="唤醒输入检测")
    {
        ClearBuff();
    }
}

void myreceivedata::ExamineWakeUpData(int sendNum, const QSet<int> setType, QString typeName,QString stateData)
{
    QList<int> Resultchannel;
    int resultFlag = -1;
    QString strResult;
    if(sendNum==0)
    {
        return;
    }
    if (setType.isEmpty())
    {
        resultFlag = 0;
        strResult = "不合格！异常通道: ";
        for (int i = 1; i <= sendNum; ++i)
        {
            strResult += QString::number(i) + " ";
        }
    }
    else
    {
        Resultchannel = GetUnusualNum(sendNum, setType);

        if(Resultchannel.size()!=1)
        {
            if(Resultchannel.size()==0)//如果等于0，代表最后一个通道回复数据了的，最后一个通道异常
            {
                resultFlag = 0;
                strResult =  "不合格！异常通道: ";
                strResult += QString::number(sendNum) + " ";
            }
            else
            {
                resultFlag = 0;
                strResult ="不合格！异常通道: ";
                for (int channel : Resultchannel)
                {
                    strResult += QString::number(channel) + " ";
                }
            }
        }
        else
        {
            if(Resultchannel.at(0)==4)
            {
                resultFlag = 1;
                strResult = "合格！";
            }
            else
            {
                resultFlag = 0;
                strResult =  "不合格！异常通道: ";
                for (int channel : Resultchannel)
                {
                    strResult += QString::number(channel) + " ";
                }
            }
        }

    }
    qDebug()<<typeName<<"set"<<setType;
    DetectionResult ResultData;
    ResultData.resultName=typeName;
    ResultData.resultData=strResult;
    emit ResultSignal(ResultData, resultFlag,stateData);
    ClearBuff();


}
QList<int> myreceivedata::GetUnusualNum(int send_num, const QSet<int> set)
{
    QList<int> unusual_channels;
    int unusual_num = 0;
    std::vector<bool> is_present(send_num + 1, false);
    for (const auto& num : set)
    {
        is_present[num] = true;
    }

    for (int i = 1; i <= send_num; ++i)
    {
        if (!is_present[i])
        {
            unusual_channels.append(i);
            qDebug()<<"异常通道"<<i;
            unusual_num++;
        }
    }
    return unusual_channels;
}
void myreceivedata::ClearBuff()
{
    SwitchInput_set.clear();
    Can_set.clear();
    SwitchLowDriver_set.clear();
    FrequencyLowDriver_set.clear();
    SwitchHighDriver_set.clear();
    FrequencyInput_set.clear();
    AnalogQuantity_set.clear();
    AdcCheckChannel_set.clear();
    WakeUpDetection_set.clear();
    HardSwitchInput_set.clear();
    SoftSwitchInput_set.clear();
    FrequencyChannelInput_set.clear();
    HighDriveInit_set.clear();
    LowDriveInit_set.clear();

    switchInputStr.clear();
    switchLowDriverStr.clear();
    frequencyLowStr.clear();
    switchHighStr.clear();
    canStr.clear();
    frequencyInputStr.clear();
    analogQuantityStr.clear();
    AdcCheckChannelStr.clear();
    WakeUpDetectionStr.clear();
}


