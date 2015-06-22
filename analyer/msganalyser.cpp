#include "msganalyser.h"

MsgAnalyser::MsgAnalyser()
{

}

MsgAnalyser::~MsgAnalyser()
{

}


const AnaylyseRetNode MsgAnalyser::DEBUG_NODE = {MSG_ANALYSER_NODE_START,"解析过程调试信息"};

QList<AnaylyseRetNode> MsgAnalyser::analyseMsg(Msg msg, Msg *remanentMsg)
{

    QList<AnaylyseRetNode> arnList;
    AnaylyseRetNode arn;

    if(msg.msgType == MSG_NONE)
    {
        arn.nodeType = DEBUG_NODE.nodeType;
        arn.nodeData = QString("报文类型为没有报文;");
    }
    else
    {
        arn.nodeType = DEBUG_NODE.nodeType;
        arn.nodeData = QString("基类不能解析任何报文;");
    }

    arnList.append(arn);
    remanentMsg->msgType = MSG_NONE;

    return arnList;
}

QString MsgAnalyser::overthrow(QString str, int offset, int strlength)
{
    QString reStr;
    if(strlength == 0)
    {
        strlength = str.length();
    }
    if(strlength % 2 != 0)
        strlength--;
    for(int i = offset; i < offset + strlength; i+=2)
    {
        reStr.insert(0,str.mid(i,2));
    }
    return reStr;
}

