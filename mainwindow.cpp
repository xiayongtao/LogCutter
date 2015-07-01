#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"

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
}


void MainWindow::openFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("打开"),QString("*.log; *.sub"));

    Analyser loganalyser;
    loganalyser.analyserFile(filepath, ui->analyseSheet);

    /*
    QFile   logFile(filepath);
    char    buf[2048];


    if(!logFile.open(QFile::ReadOnly))
    {

    }

    ui->analyseSheet->clean();
    ui->analyseSheet->setColumnCount(1);

    while(logFile.readLine(buf, sizeof(buf)) != -1)
    {
        int crow = ui->analyseSheet->rowCount();
        ui->analyseSheet->insertRow(crow);
        ui->analyseSheet->setItem(crow,0,new QTableWidgetItem(QString(buf)));
    }
    */
}



