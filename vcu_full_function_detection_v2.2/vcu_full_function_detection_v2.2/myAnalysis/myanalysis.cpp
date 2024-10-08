#include "myanalysis.h"

myAnalysis::myAnalysis(QObject *parent) : QObject(parent)
{
    myDeviceclass=new myDevice();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &myAnalysis::TimerSendCanData);
}

bool myAnalysis::StartCan()
{
    if (!myDeviceclass->Start(250))
    {
        return false;
    }
    else
    {
        return true;
    }
}
void myAnalysis::ActiveTestModel(VCUType vcutype)
{
    vcuType=vcutype;
    VCI_CAN_OBJ frame;

    frame.SendType = 0;  // 正常发送
    frame.RemoteFlag = 0;  // 数据帧
    frame.ExternFlag = 0;  // 标准帧
    frame.DataLen = 2;  // 数据长度
    frame.Data[0] = 1;
    frame.Data[1] = 1;

    switch (vcutype)
    {
    case CV01A_220_001A00:
        frame.ID = 0x41;
        break;
    case CV02A_220_001D00:
        frame.ID = 0x42;
        break;
    case CV03A_220_001A00:
        frame.ID = 0x43;
        break;
    case CV03B_220_001A00:
        frame.ID = 0x44;
        break;
    case CV03C_220_001A00:
        frame.ID = 0x45;
        break;
    default:
        break;
    }
    myDeviceclass->SendCanData(frame);
    QThread::msleep(500);
    myDeviceclass->SendCanData(frame);
    myDeviceclass->PrintData(frame, "send:");
    timer->start(50);

}
void myAnalysis::GenerateCanData(ChannelType name, int send_num, BoardType type)//生成数据
{
    if (send_num <= 0)
    {
        return;
    }
    VCI_CAN_OBJ frame;

    frame.SendType = 0;  // 正常发送
    frame.RemoteFlag = 0;  // 数据帧
    frame.ExternFlag = 0;  // 标准帧
    frame.DataLen = 7;  // 数据长度

    unsigned char data[frame.DataLen];
    memset(data,0,frame.DataLen);

    switch(type)
    {
    case VCU:
        data[0] = 0x02;
        break;
    case TestBoard:
        data[0] = 0x03;
        break;
    case QTApp:
        data[0] = 0x01;
        break;
    default:
        break;
    }

    switch(name)
    {
    case HardSwitchInputInitChannel://硬件型开关量通道初始化检测
        frame.ID = 0x19;
        data[1] = 0x0A;
        break;
    case SoftSwitchInputInitChannel://软件型开关量通道初始化检测
        frame.ID = 0x1A;
        data[1] = 0x0B;
        break;
    case FrequencyInputInitChannelCheck://频率量输入通道检测
        frame.ID = 0x1B;
        data[1] = 0x0C;
        break;
    case HighDriveInitChannel://高边驱动初始化
        frame.ID = 0x1D;
        data[1] = 0x0E;
        break;
    case LowDriveInitChannel://低边驱动初始化
        frame.ID = 0x1C;
        data[1] = 0x0D;
        break;
    case SwitchInputChannel:  // 开关量输入
        frame.ID = 0x11;
        data[1] = 0x01;
        if(vcuType == CV02A_220_001D00)
        {
            data[3] = 0x01;
        }
        if(vcuType == CV03A_220_001A00 || vcuType == CV03B_220_001A00 || vcuType == CV03C_220_001A00)
        {
            data[3] = 0x00;
        }
        break;
    case SwitchLowDriverChannel:  // 开关型低边驱动
        frame.ID = 0x12;
        data[1] = 0x02;
        data[3] = 0x01;
        break;
    case FrequencyLowDriverChannel:  // 频率型低边驱动
        frame.ID = 0x13;
        data[1] = 0x03;
        data[3] = ((frequency_ >> 8 )& 0xFF);
        data[4] = (frequency_ & 0xFF);
        data[5] = ((duty_cycle_ >> 8 )& 0xFF);
        data[6] = (duty_cycle_ & 0xFF);
        break;
    case SwitchHighDriverChannel:  // 开关型高边驱动
        frame.ID = 0x14;
        data[1] = 0x04;
        data[3] = 0x01;
        break;
    case CanChannel:  // can
        data[1] = 0x05;
        data[3] = 0x01;
        break;
    case FrequencyInputChannel:  // 频率量检测输入
        frame.ID = 0x15;
        data[1] = 0x06;
        data[3] = ((frequency_ >> 8 )& 0xFF);
        data[4] = (frequency_ & 0xFF);
        data[5] = ((duty_cycle_ >> 8 )& 0xFF);
        data[6] = (duty_cycle_ & 0xFF);
        break;
    case AnalogQuantityChannel:  // 模拟量  （电阻4、模拟量6）
        frame.ID = 0x16;
        data[1] = 0x07;
        data[3] = ((voltage_ >> 8 )& 0xFF);
        data[4] = (voltage_ & 0xFF);
        break;
    case AdcCheckChannel:  // ADC检测
        frame.ID = 0x17;
        data[1] = 0x08;
        break;
    case WakeUpDetection:  // 唤醒检测
        frame.ID = 0x18;
        data[1] = 0x09;
        data[3] = 0x01;
        break;
    default:
        break;
    }

    int count = 2;
    while (count > 0) {
        for(int i = 0; i < send_num; i++) {
            data[2] = static_cast<BYTE>(i  + 1);
            if(vcuType == CV01A_220_001A00 && name == SwitchInputChannel)
            {
                if(data[2] > 8 || data[2] == 1)
                {
                    data[3] = 0x00;
                }
                else
                {
                    data[3] = 0x01;
                }
            }

            if(name == CanChannel) {
                switch (data[2]) {
                case 1:
                    frame.ID = 0x51;
                    break;
                case 2:
                    frame.ID = 0x52;
                    break;
                case 3:
                    frame.ID = 0x53;
                    break;
                case 4:
                    frame.ID = 0x54;
                    break;
                case 5:
                    frame.ID = 0x55;
                    break;
                default:
                    break;
                }
            }
            if(name == WakeUpDetection)
            {
                memcpy(frame.Data, data, frame.DataLen);
                if(type == TestBoard)
                {
                    WakeUpTestBoardData.append(frame);
                }
                else if(type == VCU)
                {
                    WakeUpVCUData.append(frame);
                }
            }
            else//除唤醒以外的所有数据
            {
                memcpy(frame.Data, data, frame.DataLen);
                allFrame.append(frame);
            }

        }
        count--;
    }
}
void myAnalysis::TimerSendCanData()//发送数据槽函数
{
    // 发送普通帧
    if (currentFrameIndex < allFrame.size())
    {
        const VCI_CAN_OBJ& frame = allFrame[currentFrameIndex];
        if (!myDeviceclass->SendCanData(frame))
        {
            // 发送失败的处理逻辑
            return;
        }
        myDeviceclass->PrintData(frame, "send:");
        ++currentFrameIndex;
    }
    // 发送唤醒测试板或 VCU 数据
    else if (currentWakeUpTestBoard < WakeUpTestBoardData.size() || currentWakeUpVCU < WakeUpVCUData.size())
    {
        if (sendTestBoardNext) // 发送测试板数据
        {
            if (currentWakeUpTestBoard < WakeUpTestBoardData.size())
            {
                const VCI_CAN_OBJ& frameTestBoard = WakeUpTestBoardData[currentWakeUpTestBoard];
                if (!myDeviceclass->SendCanData(frameTestBoard))
                {
                    // 发送失败的处理逻辑
                    return;
                }
                myDeviceclass->PrintData(frameTestBoard, "send:");
                ++currentWakeUpTestBoard;
            }
        }
        else // 发送 VCU 数据
        {
            if (currentWakeUpVCU < WakeUpVCUData.size())
            {
                const VCI_CAN_OBJ& frameVCU = WakeUpVCUData[currentWakeUpVCU];
                if (!myDeviceclass->SendCanData(frameVCU))
                {
                    // 发送失败的处理逻辑
                    return;
                }
                myDeviceclass->PrintData(frameVCU, "send:");
                ++currentWakeUpVCU;
            }
        }
        sendTestBoardNext = !sendTestBoardNext;
    }
    // 清理和停止定时器
    else
    {
        timer->stop();

        QTimer::singleShot(1000, [this]() { myDeviceclass->Stop(); });
        // 清空数据
        allFrame.clear();
        WakeUpTestBoardData.clear();
        WakeUpVCUData.clear();

        // 重置索引
        currentFrameIndex = 0;
        currentWakeUpTestBoard = 0;
        currentWakeUpVCU = 0;
    }
}










