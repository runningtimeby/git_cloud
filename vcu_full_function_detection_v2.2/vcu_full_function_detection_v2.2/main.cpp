#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("VCU全功能检测工具V2.0");
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint); // 禁用最大化按钮
    qRegisterMetaType<VCI_CAN_OBJ>("VCI_CAN_OBJ");
    w.show();

    return a.exec();
}
