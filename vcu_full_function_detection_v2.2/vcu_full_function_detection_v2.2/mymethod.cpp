#include "mymethod.h"

mymethod::mymethod(QObject *parent) : QObject(parent)
{

}

void mymethod::createExcelFileIfNotExists(QString folderPath, QString excelPath)
{
    exportFilePath=excelPath;
    if (!QDir().exists(folderPath))
    {
        QDir().mkpath(folderPath);
    }
    if (QFile::exists(exportFilePath))
    {
        return;
    }
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *workbooks = excel.querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Add()");
    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

    workbook->dynamicCall("SaveAs(const QString&)", exportFilePath);
    workbook->dynamicCall("Close()");
    excel.dynamicCall("Quit()");

    if (worksheet) delete worksheet;
    if (workbook) delete workbook;
    if (workbooks) delete workbooks;
}

void mymethod::appendToExcel(const QVector<QString> &exportData)
{

    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);  // 隐藏 Excel 界面

    QAxObject *workbooks = excel.querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", exportFilePath);
    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

    int nextRow = currentRow;

    for (int i = 0; i < exportData.size(); ++i)
    {
        QAxObject *cell = worksheet->querySubObject("Cells(int,int)", nextRow, i + 1);

        QAxObject *column = worksheet->querySubObject("Columns(int)", i + 1);
        column->setProperty("ColumnWidth", 30);

        QAxObject *row = worksheet->querySubObject("Rows(int)", nextRow);
        row->setProperty("RowHeight", 50);  // 设置行高

        cell->setProperty("NumberFormatLocal", "@");  // 设置为文本格式
        QString data = exportData[i];
        cell->setProperty("Value2", data);  // 写入数据
        cell->setProperty("WrapText", true);  // 自动换行
    }
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel.dynamicCall("Quit()");

    if (worksheet) delete worksheet;
    if (workbook) delete workbook;
    if (workbooks) delete workbooks;
    currentRow++;
}
