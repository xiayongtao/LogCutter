#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->getPath,SIGNAL(clicked()),this,SLOT(getLogFilePath()));
    connect(ui->startAnalyse,SIGNAL(clicked()),this,SLOT(startAnalyseLogFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getLogFilePath()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"),tr("*.log; *.sub"));
    ui->logFilePath->setText(filepath);
}

void MainWindow::startAnalyseLogFile()
{
    Analyser loganalyser;
    QList<QString> analyseRet;

    loganalyser.analyserFile(ui->logFilePath->text(),&analyseRet);

    foreach(QString str,analyseRet)
    {
        ui->MsgOutput->append(str);
        ui->MsgOutput->update();
    }
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
