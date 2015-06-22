#ifndef MSGANALYSER_H
#define MSGANALYSER_H

#include "all.h"
#include "analyer.h"

#define MSG_ANALYSER_NODE_MAX_NUM       1000   //报文解析类以及其子类节点最大个数

#define MSG_ANALYSER_NODE_START         0      //报文解析类节点类型开始值
#define MLOG_ANALYSER_NODE_START        1000   //日志解析类节点类型开始值
#define M3762_ANALYSER_NODE_START       3000   //376.2解析类节点类型开始值

typedef struct
{
    int         nodeType;  //节点类型
    QString     nodeData;  //节点内容

} AnaylyseRetNode;         //解析结果节点


class MsgAnalyser
{
public:
    MsgAnalyser();
    virtual ~MsgAnalyser();

    const static AnaylyseRetNode DEBUG_NODE;     //调试信息节点


    //解析一条报文
    virtual QList<AnaylyseRetNode> analyseMsg(Msg msg, Msg *remanentMsg);


    QString overthrow(QString str, int offset = 0, int strlength = 0);

};

#endif // MSGANALYSER_H
