#ifndef ANALYER_H
#define ANALYER_H

#include "all.h"
#include "QTableWidget"
#include "ui/analysemsgsheet.h"

class MsgItem;

class Analyser
{

public:
    Analyser();
    ~Analyser();

    //解析一条报文
    QList<MsgItem> analyserMsg(MsgItem msg);
    //解析一个文件
    int analyserFile(QString filePath, QList<QString> *analyseRet);
    //解析一个文件
    int analyserFile(QString filePath, AnalyseMsgSheet *analyseRet);


private:
    void getAllNode(QList<MsgItem> *allNode);

};



//报文信息类，用于存储待解析报文和解析结果
class MsgItem
{
public:
    MsgItem();
    MsgItem(int msgType, QString msgData);
    ~MsgItem();

    enum
    {
        MSG_NONE,              //没有报文
        MSG_LOG,               //日志报文
        MSG_3761,              //3761报文
        MSG_3762,              //3762报文
        MSG_METER07,           //07表报文
        MSG_METER97,           //97表报文
        MSG_UNKNOW,            //未知报文
    };                         //报文类型

    enum
    {
        FORMAT_COMMON = 0,     //通常类型
        FORMAT_STRING,         //文本类型
    };



    int         msgType;   //信息类型
    QString     msgData;   //信息内容


    QByteArray toByteArray(int base = 16);
    void setData(QString msgData, bool isText = true);

    static int getFormat(int msgType);

};

#endif // ANALYER_H
