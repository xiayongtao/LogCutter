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

const MsgItem MlogAnalyser::DATE_NODE(MLOG_ANALYSER_NODE_START, QString("报文日期"));
const MsgItem MlogAnalyser::TIME_NODE(MLOG_ANALYSER_NODE_START+1, QString("报文时间"));
const MsgItem MlogAnalyser::DIRECTION_NODE(MLOG_ANALYSER_NODE_START+2, QString("报文方向"));

QList<MsgItem> MlogAnalyser::analyseMsg(MsgItem msg, MsgItem *remanentMsg)
{
    QList<MsgItem>   arnList;
    MsgItem          arn;

    if(msg.msgType != MsgItem::MSG_LOG)
    {
        arn.msgType = DEBUG_NODE.msgType;
        arn.setData(QString("此报文不是日志报文;"));
        remanentMsg->msgType = MsgItem::MSG_NONE;
        arnList.append(arn);
        return arnList;
    }

    int         i;
    int         pos = 0;
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
        arn.msgType = DATE_NODE.msgType;
        arn.setData(QString(""));
        arnList.append(arn);
    }
    else
    {
        arn.msgType = DATE_NODE.msgType;
        if(i == 0)
            arn.setData(regExp.cap(1) + "/" + regExp.cap(2),false);
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
        arn.msgType = TIME_NODE.msgType;
        arn.setData(QString(""));
        arnList.append(arn);
    }
    else
    {
        arn.msgType = TIME_NODE.msgType;
        if(i == 0)
            arn.setData(regExp.cap(0),false);
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
        arn.msgType = DIRECTION_NODE.msgType;
        arn.setData(QString(""));
        arnList.append(arn);
    }
    else
    {
        arn.msgType = DIRECTION_NODE.msgType;
        if(i >= 0 && i <= 1)
            arn.setData(regExp.cap(0));
        arnList.append(arn);
    }

    //识别报文中包含的规约帧
    remanentMsg->msgType = MsgItem::MSG_NONE;
    regExp.setPattern("68");
    int remanentMsgLength = 0;
    while((pos = regExp.indexIn(msg.msgData,pos)) != -1)
    {
        remanentMsgLength = M3762Analyser::checkMsg(msg.msgData.mid(pos,msg.msgData.length()-pos));
        if(remanentMsgLength > 0)
        {
            remanentMsg->msgType = MsgItem::MSG_3762;
            remanentMsg->msgData = msg.msgData.mid(pos,remanentMsgLength);
            break;
        }
        pos += regExp.matchedLength();
    }

    return arnList;
}

QList<MsgItem> MlogAnalyser::getAllarn()
{
    QList<MsgItem> arnList;
    arnList.append(DATE_NODE);
    arnList.append(TIME_NODE);
    arnList.append(DIRECTION_NODE);
    return arnList;
}

int MlogAnalyser::getFormat(int msgType)
{
    switch(msgType)
    {
    case MLOG_ANALYSER_NODE_START:
    case MLOG_ANALYSER_NODE_START+1:
    case MLOG_ANALYSER_NODE_START+2:
        return MsgItem::FORMAT_COMMON;

    default:
        return -1;
    }
}
