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
    arn.nodeType = DEBUG_NODE.nodeType;
    arn.nodeData = QString("基类不能解析任何报文;");
    remanentMsg->msgType = MSG_UNKNOW;
    arnList.append(arn);
    return arnList;
}

