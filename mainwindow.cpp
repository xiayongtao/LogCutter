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
    updateMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//连接主界面中的信号和槽
void MainWindow::connectUi()
{
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(ui->actionAppendOpen,SIGNAL(triggered(bool)),this,SLOT(appendOpenFile()));
    connect(ui->actionToCsv,SIGNAL(triggered(bool)),this,SLOT(saveAsCsv()));
    connect(ui->actionToExcel,SIGNAL(triggered(bool)),this,SLOT(saveAsExcel()));
    connect(ui->actionClose,SIGNAL(triggered(bool)),this,SLOT(closeFile()));
}


void MainWindow::updateMenu()
{
    if(ui->analyseSheet->rowCount() == 0 ||
            ui->analyseSheet->columnCount() == 0)
    {
        ui->actionClose->setEnabled(false);
        ui->actionToCsv->setEnabled(false);
        ui->actionToExcel->setEnabled(false);
    }
    else
    {
        ui->actionClose->setEnabled(true);
        ui->actionToCsv->setEnabled(true);
        ui->actionToExcel->setEnabled(true);
    }
}


void MainWindow::openFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("打开"),QString("*.log; *.sub"));
    ui->analyseSheet->clean();
    Analyser loganalyser;
    loganalyser.analyserFile(filepath, ui->analyseSheet);
    updateMenu();
}

void MainWindow::appendOpenFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("追加打开"),QString("*.log; *.sub"));
    Analyser loganalyser;
    loganalyser.analyserFile(filepath, ui->analyseSheet);
    updateMenu();
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
    QMessageBox::warning(this,this->windowTitle() ,retStr,QMessageBox::Ok);
    updateMenu();
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
    QMessageBox::warning(this,this->windowTitle() ,retStr,QMessageBox::Ok);
    updateMenu();
}

void MainWindow::closeFile()
{
    int ret = QMessageBox::warning(this,this->windowTitle() ,QString("是否关闭当前文件"),QMessageBox::Yes | QMessageBox::Cancel);
    if(ret == QMessageBox::Yes)
        ui->analyseSheet->clean();
    updateMenu();
}



