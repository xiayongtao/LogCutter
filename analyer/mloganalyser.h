#ifndef MLOGANALYSER_H
#define MLOGANALYSER_H

#include "msganalyser.h"
#include "analyer.h"


class MlogAnalyser : public MsgAnalyser
{
public:
    MlogAnalyser();
    ~MlogAnalyser();

    const static AnaylyseRetNode DATE_NODE;     //日期信息节点
    const static AnaylyseRetNode TIME_NODE;     //时间信息节点
    const static AnaylyseRetNode DIRECTION_NODE;//方向信息节点

    QList<AnaylyseRetNode> analyseMsg(Msg msg, Msg *remanentMsg);

};

#endif // MLOGANALYSER_H
