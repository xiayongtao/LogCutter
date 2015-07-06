#ifndef MLOGANALYSER_H
#define MLOGANALYSER_H

#include "all.h"
#include "msganalyser.h"


class MlogAnalyser : public MsgAnalyser
{
public:
    MlogAnalyser();
    ~MlogAnalyser();

    static QList<MsgItem> getAllarn();

    const static MsgItem DATE_NODE;         //日期信息节点
    const static MsgItem TIME_NODE;         //时间信息节点
    const static MsgItem DIRECTION_NODE;    //方向信息节点

    QList<MsgItem> analyseMsg(MsgItem msg, MsgItem *remanentMsg);

private:
    QList<QString> dateReg;
    QList<QString> timeReg;
    QList<QString> directionReg;

};

#endif // MLOGANALYSER_H
