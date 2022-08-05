#ifndef ETCUTIL_H
#define ETCUTIL_H

#include <QObject>

#define ABS(a) ((a) < 0 ? -1 * (a) : (a))

class EtcUtil
{
public:
    EtcUtil();
    static qint64 getCurrentMSec();
    static char * toStringFromChar(QString str, int charBufferSize);
    static int checkMaxDay(int year, int month);
    static void getDiskSpace(qint64 * total, qint64 * free);
};

#endif // ETCUTIL_H
