#ifndef FTDHELPER_H
#define FTDHELPER_H

#include <QObject>

class FTDHelper
{
public:
    FTDHelper();
    bool readyPort(long comport, QString errMsg);
    bool finishPort(long comport, QString errMsg);
};

#endif // FTDHELPER_H
