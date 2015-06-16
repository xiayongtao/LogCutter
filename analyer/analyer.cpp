#include "analyer.h"
#include "msganalyser.h"

Analyer::Analyer()
{

}

Analyer::~Analyer()
{

}

QString Analyer::analyserMsg(Msg msg)
{

    MsgAnalyser *msganalyser = NULL;
    Msg         remanentMsg;
    Msg         inputMsg;
    QList<AnaylyseRetNode> anaRet;
    QString     retStr;

    remanentMsg = msg;
    do
    {
        inputMsg = remanentMsg;
        switch(inputMsg.msgType)
        {
        case MSG_UNKNOW:

            break;
        case MSG_LOG:

            break;

        default:
            retStr = QString("");
            return retStr;
        }
        if(msganalyser != NULL)
        {
            delete msganalyser;
            msganalyser = NULL;
        }
        msganalyser = new MsgAnalyser();

        anaRet = msganalyser->analyseMsg(inputMsg,&remanentMsg);

        for(int i = 0; i < anaRet.length(); i++)
        {
            retStr.append(anaRet.at(i).nodeData);
        }
    }while(remanentMsg.msgType == MSG_UNKNOW);

    if(msganalyser != NULL)
    {
        delete msganalyser;
        msganalyser = NULL;
    }

    return retStr;
}


