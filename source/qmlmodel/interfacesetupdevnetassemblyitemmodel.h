#ifndef INTERFACESETUPDEVNETASSEMBLYITEMMODEL_H
#define INTERFACESETUPDEVNETASSEMBLYITEMMODEL_H

#include <QObject>
#include "source/service/coreservice.h"

class InterfaceSetupDevNetAssemblyItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsSelected READ getIsSelected NOTIFY signalEventChangedIsSelected)
    Q_PROPERTY(int     mSeq        READ getSeq        NOTIFY signalEventChangedSeq       )
    Q_PROPERTY(int     mIndex      READ getIndex      NOTIFY signalEventChangedIndex     )
    Q_PROPERTY(QString mName       READ getName       NOTIFY signalEventChangedName      )
    Q_PROPERTY(int     mLength     READ getLength     NOTIFY signalEventChangedLength    )
    Q_PROPERTY(QString mType       READ getType       NOTIFY signalEventChangedType      )
    Q_PROPERTY(QString mAddInfo    READ getAddInfo    NOTIFY signalEventChangedAddInfo   )
    Q_PROPERTY(int     mDepSeq     READ getDepSeq     NOTIFY signalEventChangedDepSeq    )

public:
    bool    mIsSelected;
    int     mSeq       ;
    int     mIndex     ;
    QString mName      ;
    int     mLength    ;
    QString mType      ;
    QString mAddInfo   ;
    int     mDepSeq    ;

    bool    getIsSelected(){return mIsSelected;}
    int     getSeq       (){return mSeq       ;}
    int     getIndex     (){return mIndex     ;}
    QString getName      (){return mName      ;}
    int     getLength    (){return mLength    ;}
    QString getType      (){return mType      ;}
    QString getAddInfo   (){return mAddInfo   ;}
    int     getDepSeq    (){return mDepSeq    ;}

    void setIsSelected(bool    value){if(mIsSelected == value)return; mIsSelected = value; if(value == false) setIndex(-1); emit signalEventChangedIsSelected(value);}
    void setSeq       (int     value){if(mSeq        == value)return; mSeq        = value; emit signalEventChangedSeq       (value);}
    void setIndex     (int     value){if(mIndex      == value)return; mIndex      = value; emit signalEventChangedIndex     (value);}
    void setName      (QString value){if(mName       == value)return; mName       = value; emit signalEventChangedName      (value);}
    void setLength    (int     value){if(mLength     == value)return; mLength     = value; emit signalEventChangedLength    (value);}
    void setType      (QString value){if(mType       == value)return; mType       = value; emit signalEventChangedType      (value);}
    void setAddInfo   (QString value){if(mAddInfo    == value)return; mAddInfo    = value; emit signalEventChangedAddInfo   (value);}
    void setDepSeq    (int     value){if(mDepSeq     == value)return; mDepSeq     = value; emit signalEventChangedDepSeq    (value);}

signals:
    void signalEventChangedIsSelected(bool    value);
    void signalEventChangedSeq       (int     value);
    void signalEventChangedIndex     (int     value);
    void signalEventChangedName      (QString value);
    void signalEventChangedLength    (int     value);
    void signalEventChangedType      (QString value);
    void signalEventChangedAddInfo   (QString value);
    void signalEventChangedDepSeq    (int     value);

public:
    explicit InterfaceSetupDevNetAssemblyItemModel(QObject *parent = nullptr): QObject(parent)
    {}
    explicit InterfaceSetupDevNetAssemblyItemModel(DNetAssemblyItem item, QObject *parent = nullptr): QObject(parent)
    {
        mIsSelected = false;
        mSeq        = item.mSeq    ;
        mIndex      = -1           ;
        mName       = item.mName   ;
        mLength     = item.mLength ;
        mType       = item.mType   ;
        mAddInfo    = item.mAddInfo;
        mDepSeq     = item.mDepSeq ;
    }

    ~InterfaceSetupDevNetAssemblyItemModel()
    {
    }
};

#endif // INTERFACESETUPDEVNETASSEMBLYITEMMODEL_H
