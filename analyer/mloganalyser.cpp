#include "mloganalyser.h"
#include "QRegExp"
#include "m3762analyser.h"

MlogAnalyser::MlogAnalyser()
{
    //添加日期查找规则
    dateReg.append("([0-9]{4}) ([0-9]{2}/[0-9]{2})");

    //添加时间查找规则
    timeReg.append("[0-9]{2}:[0-9]{2}:[0-9]{2}");

    //添加方向查找规则
    directionReg.append("Send");
    directionReg.append("Recv");


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
        remanentMsg->msgType = MSG_NONE;
        arnList.append(arn);
        return arnList;
    }

    int         i;
    int         pos;
    QRegExp     regExp;

    //在报文中查找日期
    for(i = 0; i < dateReg.length(); i++)
    {
        regExp.setPattern(dateReg.at(i));
        pos = regExp.indexIn(msg.msgData);
        if(pos >= 0) //找到了匹配的表达式
            break;

    }
    if(i >= dateReg.length())
    {
        arn.nodeType = DATE_NODE.nodeType;
        arn.nodeData = QString("");
        arnList.append(arn);
    }
    else
    {
        arn.nodeType = DATE_NODE.nodeType;
        if(i == 0)
            arn.nodeData = regExp.cap(1) + "/" + regExp.cap(2);
        arnList.append(arn);
    }

    //在报文中查找时间
    for(i = 0; i < timeReg.length(); i++)
    {
        regExp.setPattern(timeReg.at(i));
        pos = regExp.indexIn(msg.msgData);
        if(pos >= 0) //找到了匹配的表达式
            break;
    }
    if(i >= timeReg.length())
    {
        arn.nodeType = TIME_NODE.nodeType;
        arn.nodeData = QString("");
        arnList.append(arn);
    }
    else
    {
        arn.nodeType = TIME_NODE.nodeType;
        if(i == 0)
            arn.nodeData = regExp.cap(0);
        arnList.append(arn);
    }

    //在报文中查找方向信息
    for(i = 0; i < directionReg.length(); i++)
    {
        regExp.setPattern(directionReg.at(i));
        pos = regExp.indexIn(msg.msgData);
        if(pos >= 0) //找到了匹配的表达式
            break;
    }
    if(i >= directionReg.length())
    {
        arn.nodeType = DIRECTION_NODE.nodeType;
        arn.nodeData = QString("");
        arnList.append(arn);
    }
    else
    {
        arn.nodeType = DIRECTION_NODE.nodeType;
        if(i >= 0 && i <= 1)
            arn.nodeData = regExp.cap(0);
        arnList.append(arn);
    }

    //识别报文中包含的规约帧
    remanentMsg->msgType = MSG_NONE;
    regExp.setPattern("68");
    int remanentMsgLength = 0;
    while((pos = regExp.indexIn(msg.msgData,pos)) != -1)
    {
        remanentMsgLength = M3762Analyser::checkMsg(msg.msgData.mid(pos,msg.msgData.length()-pos));
        if(remanentMsgLength > 0)
        {
            remanentMsg->msgType = MSG_3762;
            remanentMsg->msgData = msg.msgData.mid(pos,remanentMsgLength);
        }
        pos += regExp.matchedLength();
    }

    return arnList;
}
