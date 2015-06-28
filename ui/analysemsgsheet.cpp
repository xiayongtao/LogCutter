#include "analysemsgsheet.h"

AnalyseMsgSheet::AnalyseMsgSheet(QWidget *parent)
    :QTableWidget(parent)
{
    setSelectionMode(ContiguousSelection);
    setRowCount(0);
    setColumnCount(0);
    setRowCount(100);
    setColumnCount(10);
}

AnalyseMsgSheet::~AnalyseMsgSheet()
{

}

