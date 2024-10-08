#include "mydevice.h"

myDevice::myDevice(QObject *parent) : QObject(parent)
{

}
bool myDevice::Start(int baudrate)
{
    if(!InitCanDevice(baudrate))
    {
        return false;
    }
    is_running_ = true;
    th_receive_ = std::thread(&myDevice::ReceiveCanData, this);  // 收数据线程
    return true;
}

void myDevice::Stop()
{
    if(is_running_)
    {
        is_running_ = false;
        if (th_receive_.joinable()) th_receive_.join();
    }
    VCI_CloseDevice(device_type_, device_index_);
}

bool myDevice::InitCanDevice(int baudrate)
{
    DWORD dwRel;
    dwRel = VCI_OpenDevice(device_type_, device_index_, 0);  // 打开can口
    if(dwRel != STATUS_OK)
    {
        return false;
    }

    VCI_INIT_CONFIG config;
    config.AccCode = 0;
    config.AccMask = 0xFFFFFFFF;
    if(baudrate == 500)
    {
        config.Timing0 = 0x00;
    }else if(baudrate == 250)
    {
        config.Timing0 = 0x01;
    }
    config.Timing1 = 0x1C;
    config.Filter = 1;
    config.Reserved = 0;
    config.Mode = 0;

    dwRel = VCI_InitCAN(device_type_, device_index_, device_index_, &config);  // 初始化can
    if(dwRel != STATUS_OK)
    {
        VCI_CloseDevice(device_type_, device_index_);
        return false;
    }

    dwRel = VCI_StartCAN(device_type_, device_index_, device_index_);  // 启动 CAN 卡的某一个 CAN 通道
    if(dwRel != STATUS_OK)
    {
        return false;
    }
    return true;
}

void myDevice::ReceiveCanData()
{
    int frame_num = 0;
    while(is_running_)
    {
        frame_num = VCI_GetReceiveNum(device_type_, device_index_, device_index_);  // 获取指定 CAN 通道的接收缓冲区中，接收到但尚未被读取的帧数量
        if(frame_num <= 0)
        {
           // std::this_thread::sleep_for(std::chrono::seconds(1));  // 没数据休眠1s
            continue;
        }

        VCI_CAN_OBJ can_data[frame_num];
        auto receive_num = VCI_Receive(device_type_, device_index_, device_index_, can_data, frame_num, -1);
        for (int i = 0; i < receive_num; ++i)
        {
            emit canDataReceived(can_data[i]);
        }
    }

}

void myDevice::ClearBuffer()
{
    VCI_ClearBuffer(device_type_, device_index_, device_index_);
}

bool myDevice::SendCanData(VCI_CAN_OBJ frame)
{
    auto num = VCI_Transmit(device_type_, device_index_, device_index_, &frame, 1);

    if(num>0)
    {
        return true;
    }
    return false;
}

void myDevice::PrintData(const VCI_CAN_OBJ frame, std::string str)
{
    std::cout<< str << ": " << std::hex <<frame.ID << " [" << (int)frame.DataLen << "] ";
    for (int j = 0; j < frame.DataLen; j++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(frame.Data[j]) << " ";
//        printf("%02x ", frame.Data[j]);
    }
    std::cout << std::endl;
}
