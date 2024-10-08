#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myDevice/mydevice.h"
#include "myAnalysis/myanalysis.h"
#include "myAnalysis/myreceivedata.h"
#include "mymethod.h"
#include "common.h"

#pragma once
#include <QWidget>
#include <QMainWindow>
#include<QDebug>
#include <QObject>
#include <QMessageBox>
#include <QTime>
#include <QDir>
#include <QDateTime>


namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private:
    Ui::MainWindow *ui;
private:
    myAnalysis *myAnalysisclass;
    myreceivedata *myReceiveclass;
    mymethod *myMethodclass;
private:
    QTimer *timer;//界面的计时器
    QTime startTime;
    QVector<ChannelParameters> channelParams;
    QVector<int> resultFlagArray;
public:
    QVector<QString> exportData;
    QString state_png_gray;
    QString state_png_green;
    QString state_png_red;
    bool stopFlag=0;

    QString folderPath;
    QString exportFilePath;
private:
    void InterfaceUi();
    void setupTableWidget();
private:
    void TimingResults();
private:
    void updateTimer();
    void updateUIForDetectionStart();
    void performVCUDetection(VCUType vcuType);
    void AnalyzeCanData(int HardSwitchInput_num,int SoftSwitchInput_num,int FrequencyInputChannel_num,int HighDriveInitChannel_num,int LowDriveInitChannel_num,int SwitchInput_num,int SwitchLowDriver_num,
                        int FrequencyLowDriver_num, int SwitchHighDriver_num,
                        int Can_num, int FrequencyInput_num, int AnalogQuantity_num,int AdcCheckChannel_num,int WakeUpDetection_num);
     void ResultSolt(const DetectionResult &ResultData,int resultFlag,QString stateData);
private slots:
    void on_pushButton_start_clicked();
    void UpdateResultStatus();

};

#endif // MAINWINDOW_H

