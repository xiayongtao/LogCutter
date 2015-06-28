#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loganalyser = new Analyser();

    connect(ui->getPath,SIGNAL(clicked()),this,SLOT(getLogFilePath()));
    connect(ui->startAnalyse,SIGNAL(clicked()),this,SLOT(startAnalyseLogFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loganalyser;
}


void MainWindow::getLogFilePath()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"),tr("*.log; *.sub"));
    ui->logFilePath->setText(filepath);
}

void MainWindow::startAnalyseLogFile()
{
    QFile logFile(ui->logFilePath->text());
    char  buf[1024];

    if(!logFile.open(QFile::ReadOnly))
    {
        return;
    }

    while(logFile.readLine(buf, sizeof(buf)) != -1)
    {
        //ui->MsgOutput->append(loganalyser->analyserMsg({MSG_LOG,QString(buf)}));
    }
    logFile.close();
}

void MainWindow::exportOutMsg()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"));
    QFile exportFile(filepath);
    if(!exportFile.open(QFile::ReadOnly))
    {
        return;
    }
    exportFile.close();

}
