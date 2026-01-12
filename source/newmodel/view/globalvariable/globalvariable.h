#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QObject>
#include <QDebug>

#include "source/service/coreservice.h" // khko_temp

class GlobalVariable:QObject
{
    Q_OBJECT
public:
    int PosiResolution = 1;
    void SetPosiResolution(int value){if(PosiResolution == value)return; PosiResolution = value; emit signalEventChangedPosiResolution();}
    int  GetPosiResolution(){ return PosiResolution; }
    void regPosiResolution(QObject * regObj, const char * pMemberFunc){ connect(this, SIGNAL(signalEventChangedPosiResolution()), regObj, pMemberFunc); }

signals:
    void signalEventChangedPosiResolution();

public:
    static GlobalVariable * getInstance()
    {
        static GlobalVariable *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new GlobalVariable();
        }

        return mpSelf;
    }

    explicit GlobalVariable(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[" << Q_FUNC_INFO <<"]";

        ENABLE_SLOT_VALVE_CHANGED_POS_RESOLUTION;

        onValveChangedPositionResolution();
    }

public slots:
    void onValveChangedPositionResolution(){
        SetPosiResolution(pValveSP->getPositionResolution());
    }
};
#endif // GLOBALVARIABLE_H
