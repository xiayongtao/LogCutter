#ifndef MSGANALYSER_H
#define MSGANALYSER_H

typedef enum
{
    MSG_NONE,              //没有报文
    MSG_LOG,               //日志报文
    MSG_3761,              //3761报文
    MSG_3762,              //3762报文
    MSG_METER07,           //07表报文
    MSG_METER97,           //97表报文
    MSG_UNKNOW,            //未知报文

} MsgType;                 //报文类型


typedef struct
{
    MsgType     msgType;   //报文类型
    QString     msgData;   //报文内容

} Msg;                     //处理的报文

#define MSG_ANALYSER_NODE_MAX_NUM       1000   //报文解析类以及其子类节点最大个数

#define MSG_ANALYSER_NODE_START         0      //报文解析类节点类型开始值
#define MLOG_ANALYSER_NODE_START        1000   //日志解析类节点类型开始值

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

};

#endif // MSGANALYSER_H
