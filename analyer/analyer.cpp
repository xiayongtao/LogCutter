#include "analyer.h"
#include "msganalyser.h"
#include "mloganalyser.h"
#include "m3762analyser.h"

Analyser::Analyser()
{

}

Analyser::~Analyser()
{

}

QString Analyser::analyserMsg(Msg msg)
{

    MsgAnalyser *msganalyser = NULL;
    Msg         remanentMsg;
    Msg         inputMsg;
    QList<AnaylyseRetNode> anaRet;
    QString     retStr = QString("");

    remanentMsg = msg;


    while(remanentMsg.msgType != MSG_NONE)
    {
        inputMsg = remanentMsg;

        //根据报文内容生成不同的解析类
        switch(inputMsg.msgType)
        {
        case MSG_LOG:
            msganalyser = new MlogAnalyser();
            break;
        case MSG_3762:
            msganalyser = new M3762Analyser();
            break;

        default:
            return retStr;
        }

        //解析报文
        anaRet = msganalyser->analyseMsg(inputMsg,&remanentMsg);

        for(int i = 0; i < anaRet.length(); i++)
        {
            retStr.append(anaRet.at(i).nodeData);
            retStr.append(" ");
        }

        //释放生成的解析类
        delete msganalyser;
        msganalyser = NULL;
    }
    return retStr;
}


