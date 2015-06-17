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
    QString     retStr = QString("");

    remanentMsg = msg;


    while(remanentMsg.msgType == MSG_NONE)
    {
        inputMsg = remanentMsg;

        //根据报文内容生成不通的解析类
        switch(inputMsg.msgType)
        {

        default:
            return retStr;
        }

        if(msganalyser != NULL)
        {
            delete msganalyser;
            msganalyser = NULL;
        }
        msganalyser = new MsgAnalyser();

        anaRet = msganalyser->analyseMsg(inputMsg,&remanentMsg);

        //释放生成的解析类
        delete msganalyser;
        msganalyser = NULL;


        for(int i = 0; i < anaRet.length(); i++)
        {
            retStr.append(anaRet.at(i).nodeData);
        }
    }
    return retStr;
}


