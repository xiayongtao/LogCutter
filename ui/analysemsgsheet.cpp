#include "analysemsgsheet.h"

#include <QAxObject>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>

#include <QDebug>

AnalyseMsgSheet::AnalyseMsgSheet(QWidget *parent)
    :QTableWidget(parent)
{
    setSelectionMode(ContiguousSelection);

    //exportToExcel();
}

AnalyseMsgSheet::~AnalyseMsgSheet()
{

}


void AnalyseMsgSheet::clean()
{
    setRowCount(0);
    setColumnCount(0);
}


int AnalyseMsgSheet::exportToExcel(QString fileName)
{
    if (fileName.isEmpty())
    {
        return -1;
    }

    QAxObject *excel = new QAxObject("Excel.Application");

    excel->dynamicCall("SetVisible(bool)", true);
    excel->setProperty("Visible", false);

    QAxObject *workbooks = excel->querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

    QAxObject *range = NULL;
    for(int row = 0; row < this->rowCount(); row ++)
    {
        for(int col = 0; col < this->columnCount(); col++)
        {
            range = worksheet->querySubObject("Cells(int,int)",row+1,col+1);
            if(range != NULL)
            {
                range->setProperty("Value", this->item(row,col) ? this->item(row,col)->text():"");
            }
        }
    }

    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));
    QMessageBox::information(this, tr("OK"), tr("保存成功！"));
    workbook->dynamicCall("Close()");
    worksheet->clear();//释放所有工作表
    excel->dynamicCall("Quit()");
    delete excel;//释放excel
    return 0;
}


int AnalyseMsgSheet::exportToCsv(QString fileName)
{
    if(fileName.isEmpty())
        return -1;

    QFile *csvFile = new QFile(fileName);
    if(!csvFile->open(QFile::WriteOnly))
    {
        return -2;
    }
    csvFile->resize(0);
    QTextStream csvFileStream(csvFile);

    QString lineStr;

    for(int row = 0; row < this->rowCount(); row ++)
    {
        lineStr.clear();
        for(int col = 0; col < this->columnCount(); col++)
        {
            lineStr.append(QString(this->item(row,col) ? this->item(row,col)->text():"") + QString(","));
        }
        lineStr.append("\n");
        csvFileStream << lineStr;
    }
    csvFile->close();
    delete csvFile;
    return 0;
}

