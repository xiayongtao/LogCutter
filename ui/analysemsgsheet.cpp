#include <QAxObject>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "analysemsgsheet.h"
#include "amgsheetcell.h"

AnalyseMsgSheet::AnalyseMsgSheet(QWidget *parent)
    :QTableWidget(parent)
{
    setItemPrototype(new AmgSheetCell);
    initUi();
}

AnalyseMsgSheet::~AnalyseMsgSheet()
{
    delete progressExport;
}


void AnalyseMsgSheet::initUi()
{
    //设置表格显示效果
    setSelectionMode(ContiguousSelection);

    //设置导出进度条显示效果
    progressExport = new QProgressDialog(this);
    progressExport->setWindowModality(Qt::WindowModal);
    progressExport->setMinimumDuration(5);
    progressExport->setWindowTitle(tr("请稍候"));
    progressExport->setLabelText(tr("正在导出......      "));
    progressExport->setCancelButtonText(QString("取消"));
    progressExport->resize(200,100);
    progressExport->setRange(0,100);
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

    if(excel == NULL)
    {
        return -2;
    }
    excel->dynamicCall("SetVisible(bool)", true);
    excel->setProperty("Visible", false);

    QAxObject *workbooks = excel->querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

    QAxObject *range = NULL;
    AmgSheetCell *cell;

    //设置单元格格式
    for(int col = 0; col < this->columnCount(); col++)
    {
        range = worksheet->querySubObject("Columns(int)",col+1);
        range->setProperty("ColumnWidth",15);
        cell = (AmgSheetCell*)item(0,col);
        if(cell != NULL && MsgItem::getFormat(cell->getCellType()) == MsgItem::FORMAT_STRING)
        {
            range->setProperty("NumberFormat","@");
        }
    }

    for(int row = 0; row < this->rowCount(); row ++)
    {
        for(int col = 0; col < this->columnCount(); col++)
        {
            range = worksheet->querySubObject("Cells(int,int)",row+1,col+1);
            if(range != NULL)
            {
                cell = (AmgSheetCell*)item(row,col);
                if(cell != NULL)
                {
                    range->setProperty("Value", cell->text());
                }
                else
                {
                    range->setProperty("Value", "");
                }
            }
        }
        progressExport->setValue(((row+1)*100)/this->rowCount());
    }

    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));
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
        progressExport->setValue(((row+1)*100)/this->rowCount());
    }
    csvFile->close();
    delete csvFile;
    return 0;
}

