#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InterfaceUi();

    timer = new QTimer(this);
    myAnalysisclass=new myAnalysis();
    myReceiveclass =new myreceivedata();
    myMethodclass=new mymethod();

    connect(timer, &QTimer::timeout, this, [this]() { updateTimer();});
    connect(myAnalysisclass->myDeviceclass, &myDevice::canDataReceived, myReceiveclass, &myreceivedata::ReceiveCanData);
    connect(myReceiveclass ,&myreceivedata::ResultSignal,this,&MainWindow::ResultSolt);

    folderPath = QDir::currentPath() + "/checkout";
    exportFilePath = folderPath + "/result_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".xlsx";
}
MainWindow::~MainWindow()
{
    delete ui;
    myAnalysisclass->myDeviceclass->Stop();
}
void MainWindow::InterfaceUi()
{
    setFixedSize(1000, 600);
    state_png_gray = "border-image: url(:/img/state0.png)";
    state_png_green = "border-image: url(:/img/state1.png)";
    state_png_red = "border-image: url(:/img/state2.png)";

    ui->label_state_img->setStyleSheet(state_png_gray);
    ui->label_state_text->setText("待连接");
    ui->label_state_text->setAlignment(Qt::AlignCenter);
    QFont stateFont("楷体", 20, QFont::Bold);
    ui->label_state_text->setFont(stateFont);

    ui->label_timer->setText("0");
    ui->label_timer->setAlignment(Qt::AlignCenter);

    QFont timerFont = ui->label_timer->font();
    QFont timeFont("宋体", 24);
    ui->label_timer->setFont(timeFont);
    setupTableWidget();
}

void MainWindow::setupTableWidget()
{
    // 设置行数和列数
    ui->tableWidget->setRowCount(1); // 包含标题的行
    ui->tableWidget->setColumnCount(3); // 三列，第一列为行号

    ui->tableWidget->horizontalHeader()->setVisible(false);  // 隐藏水平表头
    ui->tableWidget->verticalHeader()->setVisible(false);    // 隐藏垂直表头

    // 设置第一行标题
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(" "));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("检测内容"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("检测结果"));

    for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
     {
         QTableWidgetItem *item = ui->tableWidget->item(0, col);  // 获取当前单元格项
         if (item)
         {
             item->setTextAlignment(Qt::AlignCenter);  // 居中显示
             item->setFont(QFont("Arial", 11, QFont::Bold)); // 文字加粗
             item->setBackground(QColor("#f5f5f5")); // 背景颜色为 #f5f5f5
         }
     }
    // 设置表头左对齐
    QHeaderView *header = ui->tableWidget->horizontalHeader();
    header->setDefaultAlignment(Qt::AlignLeft);

    // 设置列宽
    ui->tableWidget->setColumnWidth(0, 20);  // 行号列较窄
    ui->tableWidget->setColumnWidth(1, 200); // 检测内容列宽度
    ui->tableWidget->setColumnWidth(2, 554); // 检测结果列宽度

    // 设置表格不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void MainWindow::updateTimer()
{
    int elapsedSeconds = startTime.secsTo(QTime::currentTime());
    ui->label_timer->setText(QString::number(elapsedSeconds));
}

void MainWindow::updateUIForDetectionStart()
{
    ui->label_state_text->setText("检测中");
    ui->label_state_img->setStyleSheet(state_png_gray);
    ui->label_state_text->setStyleSheet("QLabel { color : blue; }");
    ui->pushButton_start->setEnabled(false);
    ui->comboBox_type->setEnabled(false);
    ui->label_timer->setText("0");
    ui->comboBox_type->setEnabled(false);
}


void MainWindow::on_pushButton_start_clicked()
{
    QList<QTableWidgetItem*> headerItems;
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        headerItems.append(ui->tableWidget->takeItem(0, col));
    }

    // 清除所有行
    ui->tableWidget->setRowCount(0); // 只保留列数

    // 重新插入第一行的数据
    ui->tableWidget->insertRow(0);
    for (int col = 0; col < headerItems.size(); ++col) {
        if (headerItems[col]) {
            ui->tableWidget->setItem(0, col, headerItems[col]);
        }
    }

    // 检查VCU类型选择
    if (ui->comboBox_type->currentIndex() == 0)
    {
        QMessageBox::warning(this, "提示", "请选择 VCU 类型！");
        return;
    }

    myAnalysisclass->myDeviceclass->ClearBuffer();

    // 尝试启动CAN
    bool canResult = myAnalysisclass->StartCan();
    if (!canResult)
    {
         QMessageBox::warning(this, "提示", "Can卡打开失败");
        timer->stop();
        return;
    }

    // 获取VCU类型及其名称
    int index = ui->comboBox_type->currentIndex();
    QString vcuTypeName = ui->comboBox_type->currentText();
    exportData.append("VCU类型：" + vcuTypeName);
    performVCUDetection(static_cast<VCUType>(index));

    // 开始定时器
    timer->start(1000);

    //定时传参数给接收数据函数，获取解析的数据
    TimingResults();

    // 更新UI状态
    updateUIForDetectionStart();

    startTime = QTime::currentTime();

}


void MainWindow::performVCUDetection(VCUType vcuType)
{
    switch (static_cast<VCUType>(vcuType))
    {
    case CV01A_220_001A00:
        myReceiveclass->vcutype(CV01A_220_001A00);
        myAnalysisclass->ActiveTestModel(CV01A_220_001A00);
        AnalyzeCanData(16,0,0,8,8,
                       7 + 9, 9, 0,
                       8, 1, 2, 8,
                       3,3);

//         HardSwitchInput_num, int SoftSwitchInput_num, int FrequencyInputChannel_num,
//       int HighDriveInitChannel_num, int LowDriveInitChannel_num,

//       int SwitchInput_num, int SwitchLowDriver_num, int FrequencyLowDriver_num,
//       int SwitchHighDriver_num, int Can_num, int FrequencyInput_num, int AnalogQuantity_num,
//       int AdcCheckChannel_num, int WakeUpDetection_num)
        break;
    case CV02A_220_001D00:
        myAnalysisclass->ActiveTestModel(CV02A_220_001D00);
        myReceiveclass->vcutype(CV02A_220_001D00);
        AnalyzeCanData(6,10,2,8,9,
                       10 + 6, 9, 4,
                       8, 2, 2, 6 + 4,
                       3,4);
        break;
    case CV03A_220_001A00:
        myAnalysisclass->ActiveTestModel(CV03A_220_001A00);
        myReceiveclass->vcutype(CV03A_220_001A00);
        AnalyzeCanData(12,12,4,12,8,
                      12 + 12, 8, 6,
                      12, 5, 4, 10,
                      3,4);
//                 HardSwitchInput_num, int SoftSwitchInput_num, int FrequencyInputChannel_num,
//               int HighDriveInitChannel_num, int LowDriveInitChannel_num,

//               int SwitchInput_num, int SwitchLowDriver_num, int FrequencyLowDriver_num,
//               int SwitchHighDriver_num, int Can_num, int FrequencyInput_num, int AnalogQuantity_num,
//               int AdcCheckChannel_num, int WakeUpDetection_num)
        break;
    case CV03B_220_001A00:
        myAnalysisclass->ActiveTestModel(CV03B_220_001A00);
        myReceiveclass->vcutype(CV03B_220_001A00);
        AnalyzeCanData(12,12,4,12,8,
                       12 + 12, 8, 6,
                       12, 5, 4, 10,
                       3,4);
        break;
    case CV03C_220_001A00:
        myAnalysisclass->ActiveTestModel(CV03C_220_001A00);
        myReceiveclass->vcutype(CV03C_220_001A00);
        AnalyzeCanData(12,12,4,12,8,
                       12 + 12, 8, 6,
                       12, 5, 4, 10,
                       3,4);
        break;
    default:
        QMessageBox::warning(this, "提示", "请选择 VCU 类型！");
        break;
    }

}
void MainWindow::AnalyzeCanData(int HardSwitchInput_num, int SoftSwitchInput_num, int FrequencyInputChannel_num, int HighDriveInitChannel_num, int LowDriveInitChannel_num, int SwitchInput_num, int SwitchLowDriver_num, int FrequencyLowDriver_num, int SwitchHighDriver_num, int Can_num, int FrequencyInput_num, int AnalogQuantity_num, int AdcCheckChannel_num, int WakeUpDetection_num)
{
    int index = ui->comboBox_type->currentIndex();
    QVector<ChannelParameters> channelParams =
    {
        {HardSwitchInputInitChannel, HardSwitchInput_num, VCU},
        {SoftSwitchInputInitChannel, SoftSwitchInput_num, VCU},
        {FrequencyInputInitChannelCheck,FrequencyInputChannel_num,VCU},
        {HighDriveInitChannel,HighDriveInitChannel_num,TestBoard},
        {LowDriveInitChannel,LowDriveInitChannel_num,TestBoard},

        {SwitchInputChannel, SwitchInput_num, TestBoard},
        {SwitchLowDriverChannel, SwitchLowDriver_num, VCU},
        {FrequencyLowDriverChannel, FrequencyLowDriver_num, VCU},
        {SwitchHighDriverChannel, SwitchHighDriver_num, VCU},
        {CanChannel, Can_num, VCU},
        {FrequencyInputChannel, FrequencyInput_num, TestBoard},
        {AdcCheckChannel, AdcCheckChannel_num, TestBoard},
        {AnalogQuantityChannel, AnalogQuantity_num, TestBoard},
    };
    if(index==CV01A_220_001A00)
    {
        channelParams.append(ChannelParameters{WakeUpDetection, WakeUpDetection_num, TestBoard});
    }
    else
    {
        channelParams.append(ChannelParameters{WakeUpDetection, WakeUpDetection_num, TestBoard});
        channelParams.append(ChannelParameters{WakeUpDetection, WakeUpDetection_num, VCU});
    }

    for (const ChannelParameters& params : channelParams) {
        myAnalysisclass->GenerateCanData(params.name, params.sendNum, params.type);
        myReceiveclass->ChannelParameter(params);
    }
}

void MainWindow::TimingResults()
{
    QTimer *timer = new QTimer(this);
    int step = 0;
    const int maxSteps = 14; // 设定步数上限

    // 先等待3秒钟再启动循环
    QTimer::singleShot(2000, this, [=]() mutable {
        timer->start(1500); // 每秒触发一次

        connect(timer, &QTimer::timeout, this, [=]() mutable
        {
            if (step > 0 && step <= maxSteps) // 限制 step 范围在 1-10
            {
                myReceiveclass->TimerResultdata(step); // 动态传入 step
            }
            step++;
            if (step > maxSteps) // 如果超出最大步数，停止计时器
            {
                timer->stop();
                timer->deleteLater();
                UpdateResultStatus();
            }
        });
    });
}
void MainWindow::ResultSolt(const DetectionResult &ResultData,int resultFlag,QString stateData)
{
    exportData.append(ResultData.resultName);
    exportData.append(ResultData.resultData);
    exportData.append(stateData);
    resultFlagArray.append(resultFlag);

    // 获取当前行数
    int rowCount = ui->tableWidget->rowCount();

    // 在末尾插入新行
    ui->tableWidget->insertRow(rowCount);

    // 设置行号
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(rowCount))); // 设置行号

    // 设置检测内容和结果
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(ResultData.resultName));
    ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(ResultData.resultData));
    QTableWidgetItem* resultItem = ui->tableWidget->item(rowCount, 2);
    if (!resultFlag)
    {
        resultItem->setForeground(Qt::red);
    }
    else
    {
        resultItem->setForeground(Qt::black);
    }

}
void MainWindow::UpdateResultStatus()
{
    bool containsZero = resultFlagArray.contains(0);

    if (!containsZero)
    {
        ui->label_state_img->setStyleSheet(state_png_green);
        ui->label_state_text->setText("合格");
        exportData.append("检测结果：合格");
        ui->label_state_text->setStyleSheet("QLabel { color : green; }");
    }
    else
    {
        ui->label_state_img->setStyleSheet(state_png_red);
        ui->label_state_text->setText("不合格");
        exportData.append("检测结果：不合格");
        ui->label_state_text->setStyleSheet("QLabel { color : red; }");
    }
    ui->pushButton_start->setEnabled(true);
    ui->comboBox_type->setEnabled(true);

    exportData.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    //数据保存成excel
    myMethodclass->createExcelFileIfNotExists(folderPath,exportFilePath);
    myMethodclass->appendToExcel(exportData);

    timer->stop();
    resultFlagArray.clear();
    exportData.clear();
    channelParams.clear();
}
