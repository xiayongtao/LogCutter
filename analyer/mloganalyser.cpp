#include "mloganalyser.h"

MlogAnalyser::MlogAnalyser()
{

}

MlogAnalyser::~MlogAnalyser()
{

}

const AnaylyseRetNode MlogAnalyser::DATE_NODE      = {MLOG_ANALYSER_NODE_START,    "报文日期"};
const AnaylyseRetNode MlogAnalyser::TIME_NODE      = {MLOG_ANALYSER_NODE_START+1,  "报文时间"};
const AnaylyseRetNode MlogAnalyser::DIRECTION_NODE = {MLOG_ANALYSER_NODE_START+2,  "报文方向"};

QList<AnaylyseRetNode> MlogAnalyser::analyseMsg(Msg msg, Msg *remanentMsg)
{
    QList<AnaylyseRetNode> arnList;
    AnaylyseRetNode arn;

    if(msg.msgType != MSG_LOG)
    {
        arn.nodeType = DEBUG_NODE.nodeType;
        arn.nodeData = QString("此报文不是日志报文;");
        remanentMsg->msgType = MSG_UNKNOW;
        arnList.append(arn);
        return arnList;
    }



    return arnList;
}
