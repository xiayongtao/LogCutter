#ifndef MSGANALYSER_H
#define MSGANALYSER_H

#include "analyer.h"
//#include "analyserall.h"

class MsgAnalyser
{
public:
    MsgAnalyser();
    ~MsgAnalyser();

    //解析一条报文
    virtual QList<AnaylyseRetNode> analyseMsg(Msg msg, Msg &remanentMsg);

    const static AnaylyseRetNode DEBUG_NODE;

};

#endif // MSGANALYSER_H
