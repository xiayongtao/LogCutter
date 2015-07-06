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
    connect(ui->actionSaveAs,SIGNAL(triggered(bool)),this,SLOT(saveAs()));
}


void MainWindow::openFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("打开"),QString("*.log; *.sub"));

    Analyser loganalyser;
    loganalyser.analyserFile(filepath, ui->analyseSheet);
}

void MainWindow::saveAs()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("另存为"));
    if(filepath.isEmpty())
        return;
    ui->analyseSheet->exportToCsv(filepath);
}



