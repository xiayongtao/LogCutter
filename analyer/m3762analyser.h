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
    static QList<MsgItem> getAllarn();


    const static MsgItem LENGTH_NODE;       //376.2报文长度信息节点
    const static MsgItem CONTROL_NODE;      //376.2报文控制码信息节点
    const static MsgItem INFO_NODE;         //376.2报文信息域信息节点
    const static MsgItem SOUADDR_NODE;      //376.2报文源地址域信息节点
    const static MsgItem DESADDR_NODE;      //376.2报文目的地址域信息节点
    const static MsgItem AFN_NODE;          //376.2报文应用功能码信息节点
    const static MsgItem Fn_NODE;           //376.2报文信息类信息节点
    const static MsgItem DATA_NODE;         //376.2报文数据域信息节点
    const static MsgItem METER_NODE;        //376.2报文操作的电表地址信息节点

    QList<MsgItem> analyseMsg(MsgItem msg, MsgItem *remanentMsg);
};

#endif // M3762ANALYSER_H
