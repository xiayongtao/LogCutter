#ifndef ANALYER_H
#define ANALYER_H

#include "all.h"


class Analyer
{
public:
    Analyer();
    ~Analyer();

    //解析一条报文
    QString analyserMsg(Msg msg);

};

#endif // ANALYER_H
