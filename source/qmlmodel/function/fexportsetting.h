#ifndef FEXPORTSETTING_H
#define FEXPORTSETTING_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class ValveCommandItem
{
public:
    QString mReadCommand;
    QString mWriteCommand;
    QString mValue;

    ValveCommandItem(){}
    ValveCommandItem(const ValveCommandItem& copy):mReadCommand (copy.mReadCommand ),
                                                   mWriteCommand(copy.mWriteCommand),
                                                   mValue       (copy.mValue       ){}

    ~ValveCommandItem(){}

    ValveCommandItem& operator=(const ValveCommandItem& other)
    {

        mReadCommand  = other.mReadCommand ;
        mWriteCommand = other.mWriteCommand;
        mValue        = other.mValue       ;

        return *this;
    }

    void setCommand(QString readCmd, QString writeCmd)
    {
        mReadCommand = readCmd;
        mWriteCommand = writeCmd;
    }
};

class FExportSetting : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(int      mAccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode         )

public:
    QString mErrMsg                  = "";
    int     mProgress                = 0 ;

    QString getErrMsg     (){ return mErrMsg    ; }
    int     getProgress   (){ return mProgress  ; }

    void    setErrMsg     (QString value){if(mErrMsg                    == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg     (value);}
    void    setProgress   (int     value){if(mProgress                  == value)return; mProgress                = value; emit signalEventChangedProgress   (value);}

signals:
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );
    void signalEventCompletedApply                (             );


public:
    explicit FExportSetting(QObject *parent = nullptr): QObject(parent)
    {


    }
    ~FExportSetting()
    {
    }

    void run()
    {

    }

public slots:

private:
    int                     mExportCmdIdx = 0;
    QList<ValveCommandItem> mExportCmdList;
    int                     mImportCmdIdx = 0;
    QList<QString>          mImportCmdList;
};
#endif // FEXPORTSETTING_H
