#include "m3762analyser.h"

M3762Analyser::M3762Analyser()
{

}

M3762Analyser::~M3762Analyser()
{

}

const AnaylyseRetNode M3762Analyser::LENGTH_NODE = {M3762_ANALYSER_NODE_START+1,"376.2报文长度"};
const AnaylyseRetNode M3762Analyser::CONTROL_NODE = {M3762_ANALYSER_NODE_START+2,"376.2控制码"};
const AnaylyseRetNode M3762Analyser::INFO_NODE = {M3762_ANALYSER_NODE_START+3,"376.2信息域"};
const AnaylyseRetNode M3762Analyser::SOUADDR_NODE = {M3762_ANALYSER_NODE_START+4,"376.2源地址"};
const AnaylyseRetNode M3762Analyser::DESADDR_NODE = {M3762_ANALYSER_NODE_START+5,"376.2目的地址"};
const AnaylyseRetNode M3762Analyser::AFN_NODE = {M3762_ANALYSER_NODE_START+6,"376.2应用功能码"};
const AnaylyseRetNode M3762Analyser::Fn_NODE = {M3762_ANALYSER_NODE_START+7,"376.2信息类"};
const AnaylyseRetNode M3762Analyser::DATA_NODE = {M3762_ANALYSER_NODE_START+2,"376.2数据域"};


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


QList<AnaylyseRetNode> M3762Analyser::analyseMsg(Msg msg, Msg *remanentMsg)
{
    QList<AnaylyseRetNode> arnList;
    AnaylyseRetNode arn;

    if(msg.msgType != MSG_3762)
    {
        arn.nodeType = DEBUG_NODE.nodeType;
        arn.nodeData = QString("此报文不是376.2报文;");
        remanentMsg->msgType = MSG_NONE;
        arnList.append(arn);
        return arnList;
    }

    int msgLength;
    int AFNpos = 0;

    msgLength = checkMsg(msg.msgData);
    if(msgLength < 0)
    {
        arn.nodeType = DEBUG_NODE.nodeType;
        arn.nodeData = QString("此报文不符合376.2报文格式;");
        remanentMsg->msgType = MSG_NONE;
        arnList.append(arn);
        return arnList;
    }

    arn.nodeType = LENGTH_NODE.nodeType;
    arn.nodeData = QString("%1").arg(msgLength/2);
    arnList.append(arn);

    arn.nodeType = CONTROL_NODE.nodeType;
    arn.nodeData = msg.msgData.mid(6,2);
    arnList.append(arn);

    arn.nodeType = INFO_NODE.nodeType;
    arn.nodeData = msg.msgData.mid(8,12);
    arnList.append(arn);

    if((arn.nodeData.at(11).cell() & 0x04) != 0)
    {
        //存在地址域
        arn.nodeType = SOUADDR_NODE.nodeType;
        arn.nodeData = overthrow(msg.msgData.mid(20,12));
        arnList.append(arn);

        arn.nodeType = DESADDR_NODE.nodeType;
        arn.nodeData = overthrow(msg.msgData.mid(32,12));
        arnList.append(arn);
        AFNpos = 44;
    }
    else
    {
        arn.nodeType = SOUADDR_NODE.nodeType;
        arn.nodeData = QString("");
        arnList.append(arn);

        arn.nodeType = DESADDR_NODE.nodeType;
        arn.nodeData = QString("");
        arnList.append(arn);
        AFNpos = 20;
    }

    arn.nodeType = AFN_NODE.nodeType;
    arn.nodeData = msg.msgData.mid(AFNpos,2);
    arnList.append(arn);

    arn.nodeType = Fn_NODE.nodeType;
    arn.nodeData = msg.msgData.mid(AFNpos+2,4);
    arnList.append(arn);

    arn.nodeType = DATA_NODE.nodeType;
    arn.nodeData = msg.msgData.mid(AFNpos+6,msgLength-AFNpos-10);
    arnList.append(arn);

    remanentMsg->msgType = MSG_NONE;

    return arnList;
}

