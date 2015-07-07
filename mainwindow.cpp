#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//连接主界面中的信号和槽
void MainWindow::connectUi()
{
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(ui->actionToCsv,SIGNAL(triggered(bool)),this,SLOT(saveAsCsv()));
    connect(ui->actionToExcel,SIGNAL(triggered(bool)),this,SLOT(saveAsExcel()));
}


void MainWindow::openFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("打开"),QString("*.log; *.sub"));

    Analyser loganalyser;
    loganalyser.analyserFile(filepath, ui->analyseSheet);
}

void MainWindow::saveAsExcel()
{
    int ret;
    QString retStr;

    QString filepath = QFileDialog::getSaveFileName(this, QString("导出到Excel"),QString("*.xls; *xlsx"));
    if(filepath.isEmpty())
        return;
    ret = ui->analyseSheet->exportToExcel(filepath);
    if(ret == 0)
        retStr = QString("导出成功");
    else
        retStr = QString("导出失败");
    QMessageBox::warning(this,this->windowTitle() ,retStr,QMessageBox::Cancel);
}

void MainWindow::saveAsCsv()
{
    int ret;
    QString retStr;

    QString filepath = QFileDialog::getSaveFileName(this, QString("导出到CSV"),QString("*.csv"));
    if(filepath.isEmpty())
        return;
    ret = ui->analyseSheet->exportToCsv(filepath);
    if(ret == 0)
        retStr = QString("导出成功");
    else
        retStr = QString("导出失败");
    QMessageBox::warning(this,this->windowTitle() ,retStr,QMessageBox::Cancel);
}



