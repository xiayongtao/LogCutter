#ifndef ANALYSEMSGSHEET_H
#define ANALYSEMSGSHEET_H

#include <QTableWidget>
#include <QProgressDialog>

class AnalyseMsgSheet : public QTableWidget
{
    Q_OBJECT
public:
    AnalyseMsgSheet(QWidget *parent = 0);
    ~AnalyseMsgSheet();

    void clean();
    int exportToExcel(QString fileName);
    int exportToCsv(QString fileName);

private:
    QProgressDialog *progressExport;

    void initUi();


};

#endif // ANALYSEMSGSHEET_H
