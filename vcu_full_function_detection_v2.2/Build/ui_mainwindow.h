/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_start;
    QComboBox *comboBox_type;
    QGroupBox *groupBox;
    QLabel *label_timer;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_state_text;
    QLabel *label_state_img;
    QTableWidget *tableWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1002, 602);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(800, 510, 191, 51));
        pushButton_start->setStyleSheet(QString::fromUtf8(""));
        comboBox_type = new QComboBox(centralWidget);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName(QString::fromUtf8("comboBox_type"));
        comboBox_type->setGeometry(QRect(800, 260, 191, 28));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(800, 10, 191, 241));
        label_timer = new QLabel(groupBox);
        label_timer->setObjectName(QString::fromUtf8("label_timer"));
        label_timer->setGeometry(QRect(80, 180, 61, 61));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 210, 54, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 210, 16, 16));
        label_state_text = new QLabel(groupBox);
        label_state_text->setObjectName(QString::fromUtf8("label_state_text"));
        label_state_text->setGeometry(QRect(10, 120, 171, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(25);
        font.setBold(true);
        font.setWeight(75);
        label_state_text->setFont(font);
        label_state_img = new QLabel(groupBox);
        label_state_img->setObjectName(QString::fromUtf8("label_state_img"));
        label_state_img->setGeometry(QRect(40, 10, 112, 112));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 781, 551));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251VCU\347\261\273\345\236\213", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("MainWindow", "CV01A_220_001D00", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("MainWindow", "CV02A_220_001A00", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("MainWindow", "CV03A_220_001A00", nullptr));
        comboBox_type->setItemText(4, QCoreApplication::translate("MainWindow", "CV03B_220_001A00", nullptr));
        comboBox_type->setItemText(5, QCoreApplication::translate("MainWindow", "CV03C_220_001A00", nullptr));

        groupBox->setTitle(QString());
        label_timer->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213\350\256\241\346\227\266\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\247\222", nullptr));
        label_state_text->setText(QString());
        label_state_img->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
