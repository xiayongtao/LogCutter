#ifndef M3762ANALYSER_H
#define M3762ANALYSER_H

#include "all.h"
#include "msganalyser.h"


class M3762Analyser : public MsgAnalyser
{
public:
    M3762Analyser();
    ~M3762Analyser();

    static int checkMsg(QString msgData);



    const static AnaylyseRetNode LENGTH_NODE;       //376.2报文长度信息节点
    const static AnaylyseRetNode CONTROL_NODE;      //376.2报文控制码信息节点
    const static AnaylyseRetNode INFO_NODE;         //376.2报文信息域信息节点
    const static AnaylyseRetNode SOUADDR_NODE;      //376.2报文源地址域信息节点
    const static AnaylyseRetNode DESADDR_NODE;      //376.2报文目的地址域信息节点
    const static AnaylyseRetNode AFN_NODE;          //376.2报文应用功能码信息节点
    const static AnaylyseRetNode Fn_NODE;           //376.2报文信息类信息节点
    const static AnaylyseRetNode DATA_NODE;         //376.2报文数据域信息节点

    QList<AnaylyseRetNode> analyseMsg(Msg msg, Msg *remanentMsg);
};

#endif // M3762ANALYSER_H
