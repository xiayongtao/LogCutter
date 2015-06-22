#ifndef MLOGANALYSER_H
#define MLOGANALYSER_H

#include "all.h"
#include "msganalyser.h"


class MlogAnalyser : public MsgAnalyser
{
public:
    MlogAnalyser();
    ~MlogAnalyser();

    const static AnaylyseRetNode DATE_NODE;     //日期信息节点
    const static AnaylyseRetNode TIME_NODE;     //时间信息节点
    const static AnaylyseRetNode DIRECTION_NODE;//方向信息节点

    QList<AnaylyseRetNode> analyseMsg(Msg msg, Msg *remanentMsg);


private:
    QList<QString> dateReg;
    QList<QString> timeReg;
    QList<QString> directionReg;

};

#endif // MLOGANALYSER_H
