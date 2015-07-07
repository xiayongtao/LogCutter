#include "msganalyser.h"

MsgAnalyser::MsgAnalyser()
{
    codec = QTextCodec::codecForName("GB18030");
}

MsgAnalyser::~MsgAnalyser()
{

}


const MsgItem MsgAnalyser::DEBUG_NODE(MSG_ANALYSER_NODE_START,QString("解析过程调试信息"));

QList<MsgItem> MsgAnalyser::analyseMsg(MsgItem msg, MsgItem *remanentMsg)
{

    QList<MsgItem>  arnList;
    MsgItem         arn;

    if(msg.msgType == MsgItem::MSG_NONE)
    {
        arn.msgType = DEBUG_NODE.msgType;
        arn.setData(QString("报文类型为没有报文"));
    }
    else
    {
        arn.msgType = DEBUG_NODE.msgType;
        arn.setData(QString("基类不能解析任何报文"));
    }

    arnList.append(arn);
    remanentMsg->msgType = MsgItem::MSG_NONE;

    return arnList;
}


QList<MsgItem> MsgAnalyser::getAllarn()
{
    QList<MsgItem> arnList;
    arnList.append(DEBUG_NODE);
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

bool MsgAnalyser::findDatafromList(QList<MsgItem> arnList, MsgItem *arNode)
{
    MsgItem arn;
    foreach (arn, arnList)
    {
        if(arn.msgType == arNode->msgType)
        {
            arNode->msgData = arn.msgData;
            return true;
        }
    }
    return false;
}

int MsgAnalyser::getFormat(int msgType)
{
    switch(msgType)
    {
    case MSG_ANALYSER_NODE_START:
        return MsgItem::FORMAT_STRING;

    default:
        return -1;
    }
}

