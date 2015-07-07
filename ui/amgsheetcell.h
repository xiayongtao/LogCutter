#ifndef AMGSHEETCELL_H
#define AMGSHEETCELL_H

#include <QTableWidgetItem>

#include "analyer/analyer.h"


class AmgSheetCell : public QTableWidgetItem
{
public:
    AmgSheetCell();
    AmgSheetCell(const QString &text);
    AmgSheetCell(MsgItem &msgItem);
    ~AmgSheetCell();

    void setCellType(int type);
    int  getCellType();

private:
    int cellType;

};

#endif // AMGSHEETCELL_H
