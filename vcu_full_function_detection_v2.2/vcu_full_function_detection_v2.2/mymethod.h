#ifndef MYMETHOD_H
#define MYMETHOD_H

#include <QMainWindow>
#include <QObject>
#include <QAxObject>
#include <QDir>
class mymethod : public QObject
{
    Q_OBJECT
public:
    explicit mymethod(QObject *parent = nullptr);\
public:
    int currentRow=1;
    QString exportFilePath;
public:
    void createExcelFileIfNotExists( QString folderPath, QString excelPath);
    void appendToExcel(const QVector<QString> &exportData);
signals:

};

#endif // MYMETHOD_H
