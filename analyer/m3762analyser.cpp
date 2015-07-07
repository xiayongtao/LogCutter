#include "m3762analyser.h"
#include <QTextCodec>

M3762Analyser::M3762Analyser()
{

}

M3762Analyser::~M3762Analyser()
{

}

const MsgItem M3762Analyser::LENGTH_NODE(M3762_ANALYSER_NODE_START+1,QTextCodec::codecForName("UTF-8")->toUnicode("376.2报文长度"));
const MsgItem M3762Analyser::CONTROL_NODE(M3762_ANALYSER_NODE_START+2,"376.2控制码");
const MsgItem M3762Analyser::INFO_NODE(M3762_ANALYSER_NODE_START+3,"376.2信息域");
const MsgItem M3762Analyser::SOUADDR_NODE(M3762_ANALYSER_NODE_START+4,"376.2源地址");
const MsgItem M3762Analyser::DESADDR_NODE(M3762_ANALYSER_NODE_START+5,"376.2目的地址");
const MsgItem M3762Analyser::AFN_NODE(M3762_ANALYSER_NODE_START+6,"376.2应用功能码");
const MsgItem M3762Analyser::Fn_NODE(M3762_ANALYSER_NODE_START+7,"376.2信息类");
const MsgItem M3762Analyser::DATA_NODE(M3762_ANALYSER_NODE_START+8,"376.2数据域");
const MsgItem M3762Analyser::METER_NODE(M3762_ANALYSER_NODE_START+9,"操作的电表地址");

int M3762Analyser::checkMsg(QString msgData)
{
    int             msgLength = 0;
    bool            toIntOk;
    unsigned char   msgCs = 0;

    if(msgData.left(2) != "68")
        return -1;
    msgLength = msgData.mid(4,2).append(msgData.mid(2,2)).toInt(&toIntOk,16);
    if(!toIntOk || msgLength < 12 || msgLength > 65535)
    {
        return -1;
    }
    if(msgData.mid((msgLength-1)*2,2) != "16")
    {
        return -1;
    }
    for(int i = 6; i < (msgLength-2)*2; i+=2)
    {
        msgCs += msgData.mid(i,2).toInt(&toIntOk,16);
        if(!toIntOk)
            return -1;
    }
    if(msgCs != msgData.mid((msgLength-2)*2,2).toInt(&toIntOk,16))
    {
        return -1;
    }
    return msgLength*2;
}


QList<MsgItem> M3762Analyser::analyseMsg(MsgItem msg, MsgItem *remanentMsg)
{
    QList<MsgItem> arnList;
    MsgItem arn;
    bool ok;

    if(msg.msgType != MsgItem::MSG_3762)
    {
        arn.msgType = DEBUG_NODE.msgType;
        arn.setData(QString("此报文不是376.2报文"));
        remanentMsg->msgType = MsgItem::MSG_NONE;
        arnList.append(arn);
        return arnList;
    }

    int msgLength;
    int AFNpos = 0;

    msgLength = checkMsg(msg.msgData);
    if(msgLength < 0)
    {
        arn.msgType = DEBUG_NODE.msgType;
        arn.setData(QString("此报文不符合376.2报文格式"));
        remanentMsg->msgType = MsgItem::MSG_NONE;
        arnList.append(arn);
        return arnList;
    }

    //报文长度
    arn.msgType = LENGTH_NODE.msgType;
    arn.setData(QString("%1").arg(msgLength/2),false);
    arnList.append(arn);

    //控制码
    arn.msgType = CONTROL_NODE.msgType;
    arn.setData(msg.msgData.mid(6,2));
    arnList.append(arn);
    bool msgDir;
    QByteArray tmp = arn.toByteArray();
    if((arn.toByteArray().at(0) & 0x80) == 0)
        msgDir = false;    //下行
    else
        msgDir = true;     //上行

    //信息域
    arn.msgType = INFO_NODE.msgType;
    arn.setData(msg.msgData.mid(8,12));
    arnList.append(arn);

    if((arn.toByteArray()[0] & 0x04) != 0)
    {
        //存在地址域
        arn.msgType = SOUADDR_NODE.msgType;
        arn.setData(overthrow(msg.msgData.mid(20,12)));
        arnList.append(arn);

        arn.msgType = DESADDR_NODE.msgType;
        arn.setData(overthrow(msg.msgData.mid(32,12)));
        arnList.append(arn);
        AFNpos = 44;
    }
    else
    {
        arn.msgType = SOUADDR_NODE.msgType;
        arn.setData(QString(""));
        arnList.append(arn);

        arn.msgType = DESADDR_NODE.msgType;
        arn.setData(QString(""));
        arnList.append(arn);
        AFNpos = 20;
    }

    arn.msgType = AFN_NODE.msgType;
    arn.setData(msg.msgData.mid(AFNpos,2));
    arnList.append(arn);
    int AFN = arn.msgData.toInt(&ok,16);

    arn.msgType = Fn_NODE.msgType;
    arn.setData(msg.msgData.mid(AFNpos+2,4));
    arnList.append(arn);
    QString Fn = msg.msgData.mid(AFNpos+2,4);


    arn.msgType = DATA_NODE.msgType;
    arn.setData(msg.msgData.mid(AFNpos+6,msgLength-AFNpos-10));
    arnList.append(arn);

    if(msgDir && AFN == 0x14 && Fn == "0100")
    {
        MsgItem arnTemp = arn;
        arn.msgType = METER_NODE.msgType;
        arn.setData(overthrow(arnTemp.msgData.mid(2,12)));
        arnList.append(arn);
    }

    remanentMsg->msgType = MsgItem::MSG_NONE;

    return arnList;
}

QList<MsgItem> M3762Analyser::getAllarn()
{
    QList<MsgItem> arnList;
    arnList.append(LENGTH_NODE);
    arnList.append(CONTROL_NODE);
    arnList.append(INFO_NODE);
    arnList.append(SOUADDR_NODE);
    arnList.append(DESADDR_NODE);
    arnList.append(AFN_NODE);
    arnList.append(Fn_NODE);
    arnList.append(DATA_NODE);
    arnList.append(METER_NODE);
    return arnList;
}

int M3762Analyser::getFormat(int msgType)
{
    switch(msgType)
    {
    case M3762_ANALYSER_NODE_START+1:
        return MsgItem::FORMAT_COMMON;

    case M3762_ANALYSER_NODE_START+2:
    case M3762_ANALYSER_NODE_START+3:
    case M3762_ANALYSER_NODE_START+4:
    case M3762_ANALYSER_NODE_START+5:
    case M3762_ANALYSER_NODE_START+6:
    case M3762_ANALYSER_NODE_START+7:
    case M3762_ANALYSER_NODE_START+8:
        return MsgItem::FORMAT_STRING;
    default:
        return -1;
    }
}

