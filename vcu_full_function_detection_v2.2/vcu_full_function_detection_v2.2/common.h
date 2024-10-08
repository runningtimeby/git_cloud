#ifndef COMMON_H
#define COMMON_H

#pragma once
#include<iostream>
#include <QString>

//#define CV01A_220_001A00_HardSwitchInput 0
//#define CV01A_220_001A00_SoftSwitchInput 0
//#define CV01A_220_001A00_FrequencyInputChannel 0
//#define CV01A_220_001A00_HighDriveInitChannel 0
//#define CV01A_220_001A00_LowDriveInitChannel 0
//#define CV01A_220_001A00_SwitchInput 16
//#define CV01A_220_001A00_SwitchLowDriver 9
//#define CV01A_220_001A00_FrequencyLowDriver 0
//#define CV01A_220_001A00_SwitchHighDriver 8
//#define CV01A_220_001A00_Can 1
//#define CV01A_220_001A00_FrequencyInput 2
//#define CV01A_220_001A00_AnalogQuantity 8
//#define CV01A_220_001A00_AdcCheckChannel 3
//#define CV01A_220_001A00_WakeUpDetection 4

typedef enum
{
    SwitchInputChannel = 1,  // 开关量输入
    SwitchLowDriverChannel = 2,  // 开关型低边驱动
    FrequencyLowDriverChannel = 3,  // 频率型低边驱动
    SwitchHighDriverChannel = 4,  // 开关型高边驱动
    CanChannel = 5,
    FrequencyInputChannel = 6,  // 频率量检测输入
    AnalogQuantityChannel = 7,  // 模拟量  （电阻4、模拟量6）

    AdcCheckChannel = 8,//ADC检测
    WakeUpDetection = 9,//唤醒检测

    HardSwitchInputInitChannel = 10,  // 硬件型开关量初始化
    SoftSwitchInputInitChannel = 11,//软件型开关量初始化
    FrequencyInputInitChannelCheck = 12,//频率量检测输入初始化

    HighDriveInitChannel = 13,  // 高边驱动初始化
    LowDriveInitChannel = 14, //低边驱动初始化

}ChannelType;

typedef enum{
    CV01A_220_001A00 = 1,  // 1 开发顺序
    CV02A_220_001D00 = 2,  // 2
    CV03A_220_001A00 = 3,  // 5
    CV03B_220_001A00 = 4,  // 4
    CV03C_220_001A00 = 5   // 3
}VCUType;

typedef enum{
    VCU = 2,
    TestBoard = 3,
    QTApp = 1
}BoardType;

struct ChannelParameters {
    ChannelType name;  // 的通道名称
    int sendNum;       // 发送的数据量
    BoardType type;    // 设备板类型
};
struct DetectionResult {
   QString resultName;  // 检测结果的名称
   QString resultData; // 检测结果
};
#endif // COMMON_H
