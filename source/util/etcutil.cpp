#include "etcutil.h"

#include <QDateTime>
#include <QProcess>

EtcUtil::EtcUtil()
{

}

qint64 EtcUtil::getCurrentMSec()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

char * EtcUtil::toStringFromChar(QString str, int charBufferSize)
{
    const QByteArray stringData = str.toUtf8();
    char * pText;

    pText = (char *)malloc(charBufferSize);

    pText[qMin(charBufferSize - 1, stringData.size())]='\0';
    std::copy(stringData.constBegin(),stringData.constBegin()+qMin(charBufferSize - 1,stringData.size()),pText);

    return pText;
}

int EtcUtil::checkMaxDay(int year, int month)
{
    if(month == 2)
    {
        if((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

void EtcUtil::getDiskSpace(qint64 * total, qint64 * free)
{
    QProcess process;

    process.start("df ");
    process.waitForFinished(-1); // will wait forever until finished

    QString output = process.readAllStandardOutput();
    QStringList outputLine = output.split("\n");
    QString root;

    for(int i = 0; i < outputLine.size(); i ++)
    {
        if(outputLine.at(i).startsWith("/dev/root"))
        {
            root = outputLine.at(i);
            break;
        }
    }

    QStringList colList = root.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);

    *total = colList.at(1).toDouble() * 1024;
    *free = colList.at(3).toDouble() * 1024;
}
