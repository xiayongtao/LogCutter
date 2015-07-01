#include "analyer.h"
#include "msganalyser.h"
#include "mloganalyser.h"
#include "m3762analyser.h"
#include "QFile"


Analyser::Analyser()
{

}

Analyser::~Analyser()
{

}

QList<MsgItem> Analyser::analyserMsg(MsgItem msg)
{

    MsgAnalyser         *msganalyser = NULL;        //报文解析类对象
    MsgItem             remanentMsg;                //解析之后余下未解析的报文
    MsgItem             inputMsg;                   //输入的待解析报文
    QList<MsgItem>      anaRet;                     //报文解析类对象输出的解析结果
    QList<MsgItem>      retList;                    //待返回的列表

    //刚开始剩余的报文就是输入的报文
    remanentMsg = msg;

    while(remanentMsg.msgType !=MsgItem::MSG_NONE)
    {
        inputMsg = remanentMsg;

        //根据报文内容生成不同的解析类
        switch(inputMsg.msgType)
        {
        case MsgItem::MSG_LOG:
            msganalyser = new MlogAnalyser();
            break;
        case MsgItem::MSG_3762:
            msganalyser = new M3762Analyser();
            break;

        default:
            return retList;
        }

        //解析报文
        anaRet = msganalyser->analyseMsg(inputMsg,&remanentMsg);
        retList.append(anaRet);

        //释放生成的解析类
        delete msganalyser;
        msganalyser = NULL;
    }
    return retList;
}


int Analyser::analyserFile(QString filePath, QList<QString> *analyseRet)
{
    QFile               logFile(filePath);
    char                buf[1024];
    QList<MsgItem>      msgAnaRet;
    bool                first = true;
    QString             msgAnaRetStr;
    MsgItem             msgAnaRetItem;

    if(!logFile.open(QFile::ReadOnly))
    {
        return -1;
    }

    while(logFile.readLine(buf, sizeof(buf)) != -1)
    {
        msgAnaRetStr.clear();
        msgAnaRet = analyserMsg(MsgItem(MsgItem::MSG_LOG,QString(buf)));
        if(first)
        {
            QList<MsgItem> allNode;
            MsgItem        allNodeItem;
            bool           isFound = false;

            allNode.append(MsgAnalyser::getAllarn());
            allNode.append(MlogAnalyser::getAllarn());
            allNode.append(M3762Analyser::getAllarn());

            foreach (msgAnaRetItem, msgAnaRet)
            {
                isFound = false;
                foreach (allNodeItem, allNode)
                {
                    if(allNodeItem.msgType == msgAnaRetItem.msgType)
                    {
                        msgAnaRetStr.append(allNodeItem.msgData+",");
                        isFound = true;
                        break;
                    }
                }
                if(!isFound)
                {
                    msgAnaRetStr.append(",");
                }
            }
            analyseRet->append(msgAnaRetStr);
            msgAnaRetStr.clear();
            first = false;
        }
        foreach (msgAnaRetItem, msgAnaRet)
        {
            msgAnaRetStr.append(msgAnaRetItem.msgData+",");
        }
        analyseRet->append(msgAnaRetStr);
    }

    logFile.close();
    return 0;
}













MsgItem::MsgItem()
    :msgType(0),msgData(QString(""))
{

}

MsgItem::MsgItem(int msgType, QString msgData)
    :msgType(msgType),msgData(msgData)
{

}

MsgItem::~MsgItem()
{

}


void MsgItem::setData(QString msgData, bool isText)
{
    if(isText || !isText)
        this->msgData = msgData;
}

QByteArray MsgItem::toByteArray(int base)
{
    QString     realmsgData = msgData;
    QByteArray  bytearray;
    bool        ok;

    for(int i = 0; i < realmsgData.length(); i+=2)
    {
        bytearray.append(realmsgData.mid(i,2).toInt(&ok,base));
    }
    return bytearray;
}


