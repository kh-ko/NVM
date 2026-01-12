#ifndef PMVIEWMODEL_H
#define PMVIEWMODEL_H

#include <QObject>
#include <QList>
#include "source/service/coreservice.h"
#include "source/pmmodel/pmvalvemodel.h"

class PmViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      AccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(QString  StrStatus               READ getStrStatus                NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString  ErrMsg                  READ getErrMsg                   NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(int      Progress                READ getProgress                 NOTIFY signalEventChangedProgress           )

public:
    int      AccessMode = ValveEnumDef::ACCESS_LOCAL;
    QString  StrStatus  = "ready";
    QString  ErrMsg     = "";
    int      Progress   = 100 ;

    int     getAccessMode (){ return AccessMode; }
    QString getStrStatus  (){ return StrStatus ; }
    QString getErrMsg     (){ return ErrMsg    ; }
    int     getProgress   (){ return Progress  ; }

    void    setAccessMode (int     value){if(AccessMode == value)return; AccessMode = value; emit signalEventChangedAccessMode (value);}
    void    setStrStatus  (QString value){if(StrStatus  == value)return; StrStatus  = value; emit signalEventChangedStrStatus  (value);}
    void    setErrMsg     (QString value){if(ErrMsg     == value)return; ErrMsg     = value; emit signalEventChangedErrMsg     (value);}
    void    setProgress   (int     value){if(Progress   == value)return; Progress   = value; emit signalEventChangedProgress   (value);}

signals:

    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);


public:
    explicit PmViewModel(QObject *parent = nullptr): QObject(parent)
    {
        mpValveModel = PmValveModel::getInstance();

        ENABLE_SLOT_VALVE_CHANGED_ACCESS;

        onValveChangedAccess();
    }
    ~PmViewModel()
    {
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    Q_INVOKABLE PmValveItemModel * findItemModel(QString path)
    {
        return mpValveModel->findItem(path);
    }

protected:
    PmValveModel * mpValveModel = nullptr;
};
#endif // PMVIEWMODEL_H

