#ifndef ANALYER_H
#define ANALYER_H

#include "all.h"

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

class Analyser
{
public:
    Analyser();
    ~Analyser();

    //解析一条报文
    QString analyserMsg(Msg msg);

};

#endif // ANALYER_H
