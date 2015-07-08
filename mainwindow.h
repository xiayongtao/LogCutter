#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analyer/analyer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();
    void appendOpenFile();
    void saveAsExcel();
    void saveAsCsv();
    void closeFile();

private:
    Ui::MainWindow *ui;
    void connectUi();
    void updateMenu();

};

#endif // MAINWINDOW_H
