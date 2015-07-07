#include "amgsheetcell.h"

AmgSheetCell::AmgSheetCell()
{
    cellType = -1;
}

AmgSheetCell::~AmgSheetCell()
{

}

AmgSheetCell::AmgSheetCell(const QString &text)
    :QTableWidgetItem(text)
{
    cellType = -1;
}

AmgSheetCell::AmgSheetCell(MsgItem &msgItem)
    :QTableWidgetItem(msgItem.msgData)
{
    setCellType(msgItem.msgType);
}


void AmgSheetCell::setCellType(int type)
{
    cellType = type;
}

int AmgSheetCell::getCellType()
{
    return cellType;
}

