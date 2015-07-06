#ifndef ANALYSEMSGSHEET_H
#define ANALYSEMSGSHEET_H

#include "QTableWidget"


class AnalyseMsgSheet : public QTableWidget
{
    Q_OBJECT
public:
    AnalyseMsgSheet(QWidget *parent = 0);
    ~AnalyseMsgSheet();

    void clean();

    int exportToExcel(QString fileName);

    int exportToCsv(QString fileName);




};

#endif // ANALYSEMSGSHEET_H
