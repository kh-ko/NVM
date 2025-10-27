#ifndef INTERFACESETUPDEVNETRANGEDLGMODEL_H
#define INTERFACESETUPDEVNETRANGEDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class InterfaceSetupDevNetRangeItemModel : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString  mName READ getName NOTIFY signalEventChangedName )
    Q_PROPERTY(int      mType READ getType NOTIFY signalEventChangedType )
    Q_PROPERTY(QString  mFrom READ getFrom NOTIFY signalEventChangedFrom )
    Q_PROPERTY(QString  mTo   READ getTo   NOTIFY signalEventChangedTo   )

    Q_PROPERTY(bool     mIsEditType READ getIsEditType NOTIFY signalEventChangedIsEditType )
    Q_PROPERTY(bool     mIsEditFrom READ getIsEditFrom NOTIFY signalEventChangedIsEditFrom )
    Q_PROPERTY(bool     mIsEditTo   READ getIsEditTo   NOTIFY signalEventChangedIsEditTo   )

    Q_PROPERTY(bool     mErrType READ getErrType NOTIFY signalEventChangedErrType )
    Q_PROPERTY(bool     mErrFrom READ getErrFrom NOTIFY signalEventChangedErrFrom )
    Q_PROPERTY(bool     mErrTo   READ getErrTo   NOTIFY signalEventChangedErrTo   )
public:
    int      mId = 0;

    QString  mName = "";
    int      mType = 0;
    QString  mFrom = "";
    QString  mTo   = "";

    bool     mIsEditType = false;
    bool     mIsEditFrom = false;
    bool     mIsEditTo   = false;

    bool     mErrType = false;
    bool     mErrFrom = false;
    bool     mErrTo   = false;

    QString  getName(){ return mName; }
    int      getType(){ return mType; }
    QString  getFrom(){ return mFrom; }
    QString  getTo  (){ return mTo  ; }

    bool     getIsEditType(){ return mIsEditType; }
    bool     getIsEditFrom(){ return mIsEditFrom; }
    bool     getIsEditTo  (){ return mIsEditTo  ; }

    bool     getErrType(){ return mErrType; }
    bool     getErrFrom(){ return mErrFrom; }
    bool     getErrTo  (){ return mErrTo  ; }

    void     setName(QString value){ if(mName == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mName = value; emit signalEventChangedName(value); }
    void     setType(int     value){ if(mType == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mType = value; emit signalEventChangedType(value); }
    void     setFrom(QString value){ if(mFrom == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mFrom = value; emit signalEventChangedFrom(value); }
    void     setTo  (QString value){ if(mTo   == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mTo   = value; emit signalEventChangedTo  (value); }

    void     setIsEditType(bool    value){ if(mIsEditType == value) return; mIsEditType = value; emit signalEventChangedIsEditType(value); }
    void     setIsEditFrom(bool    value){ if(mIsEditFrom == value) return; mIsEditFrom = value; emit signalEventChangedIsEditFrom(value); }
    void     setIsEditTo  (bool    value){ if(mIsEditTo   == value) return; mIsEditTo   = value; emit signalEventChangedIsEditTo  (value); }

    void     setErrType(bool    value){ if(mErrType == value) return; mErrType = value; emit signalEventChangedErrType(value); }
    void     setErrFrom(bool    value){ if(mErrFrom == value) return; mErrFrom = value; emit signalEventChangedErrFrom(value); }
    void     setErrTo  (bool    value){ if(mErrTo   == value) return; mErrTo   = value; emit signalEventChangedErrTo  (value); }

signals:
    void signalEventChangedName      (QString value);
    void signalEventChangedType      (int     value);
    void signalEventChangedFrom      (QString value);
    void signalEventChangedTo        (QString value);
    void signalEventChangedIsEditType(bool    value);
    void signalEventChangedIsEditFrom(bool    value);
    void signalEventChangedIsEditTo  (bool    value);
    void signalEventChangedErrType   (bool    value);
    void signalEventChangedErrFrom   (bool    value);
    void signalEventChangedErrTo     (bool    value);

public:
    explicit InterfaceSetupDevNetRangeItemModel(QObject *parent = nullptr): QObject(parent){}
    ~InterfaceSetupDevNetRangeItemModel(){}

    Q_INVOKABLE void onCommandSetEditType(int     value){ mWriteType = value; setIsEditType(true); }
    Q_INVOKABLE void onCommandSetEditFrom(QString value){ mWriteFrom = value; setIsEditFrom(true); }
    Q_INVOKABLE void onCommandSetEditTo  (QString value){ mWriteTo   = value; setIsEditTo  (true); }

    bool IsNeedWriteType(){ return (getIsEditType() || getErrType() ); }
    bool IsNeedWriteFrom(){ return (getIsEditFrom() || getErrFrom() ); }
    bool IsNeedWriteTo  (){ return (getIsEditTo  () || getErrTo  () ); }

    bool getError()
    {
        return ( getErrType() || getErrFrom() || getErrTo  () );
    }

    void setIsEditReset(){
        setIsEditType(false);
        setIsEditFrom(false);
        setIsEditTo  (false);
    }

    void checkErrType(int     value){ setErrType( mWriteType != value);}
    void checkErrFrom(QString value){ setErrFrom( MathUtil::DoubleEqual(mWriteFrom , value) == false);}
    void checkErrTo  (QString value){ setErrTo  ( MathUtil::DoubleEqual(mWriteTo   , value) == false);}

    void setValueType(int     value){ setType (value);}
    void setValueFrom(QString value){ setFrom (value);}
    void setValueTo  (QString value){ setTo   (value);}

    void initWriteValue()
    {
        mWriteType = getType();
        mWriteFrom = getFrom();
        mWriteTo   = getTo()  ;
    }

public:
    int      mWriteType = 0;
    QString  mWriteFrom = "";
    QString  mWriteTo   = "";
};

class InterfaceSetupDevNetRangeDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode  READ getAccessMode  NOTIFY signalEventChangedAccessMode  )
    Q_PROPERTY(bool     mIsRS232Test READ getIsRS232Test NOTIFY signalEventChangedIsRS232Test )

    // status flag
    Q_PROPERTY(bool     mIsEdit      READ getIsEdit      NOTIFY signalEventChangedIsEdit      )
    Q_PROPERTY(QString  mStrStatus   READ getStrStatus   NOTIFY signalEventChangedStrStatus   )
    Q_PROPERTY(QString  mErrMsg      READ getErrMsg      NOTIFY signalEventChangedErrMsg      )
    Q_PROPERTY(QString  mErrMsg2     READ getErrMsg2     NOTIFY signalEventChangedErrMsg2     )
    Q_PROPERTY(int      mProgress    READ getProgress    NOTIFY signalEventChangedProgress    )

public:
    QList<InterfaceSetupDevNetRangeItemModel *> mPDOItemList;

    int     mAccessMode  = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test = false;
    bool    mErrDevID    = 0;

    bool    mIsEdit    = false;
    QString mStrStatus = "Loading";
    QString mErrMsg    = "";
    QString mErrMsg2   = "";
    int     mProgress  = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){return mIsRS232Test             ;}

    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}

    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);

    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit InterfaceSetupDevNetRangeDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;

        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_POS_UNIT     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_PRESSURE_UNIT;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_DATA_TYPE;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_RANGE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_DATA_TYPE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_RANGE;

        QStringList itemNames = {"(IN) pressure", "(IN) pressure sensor 1", "(IN) pressure sensor 2", "(IN) position", "(IN) target position", "(IN) cluster valve position", "(OUT) pressure setpoint", "(OUT) position setpoint", "(OUT) pressure alignment setpoint", "(OUT) external digital pressure 1", "(OUT) external digital pressure 2", "(OUT) cluster valve freeze position"};
        for(int i = 0; i < 12; i ++)
        {
            mPDOItemList.append(new InterfaceSetupDevNetRangeItemModel(this));
            mPDOItemList[i]->mId = i;
            mPDOItemList[i]->setName(itemNames[i]);
        }

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CTRL_01_TYPE);
    }
    ~InterfaceSetupDevNetRangeDlgModel()
    {
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedIsRS232Test()
    {
        setIsRS232Test(pValveSP->getIsRS232Test());
    }


    void onValveWrittenInterfaceConfigDNetPosUnit(ValveResponseDto dto)
    {
        setErrMsg(dto.mErrMsg);
        if(!dto.mIsSucc){ setState(mState); return; }

        if(mState == STATE_WRITE_POSI_UNIT)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]req = " << dto.mReqDto.mReqCommand << ", res = " << dto.mResData;
            setState((eState)(mState + 1));
        }
    }

    void onValveWrittenInterfaceConfigDNetPressureUnit(ValveResponseDto dto)
    {
        setErrMsg(dto.mErrMsg);
        if(!dto.mIsSucc){ setState(mState); return; }

        if(mState == STATE_WRITE_PRES_UNIT)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]req = " << dto.mReqDto.mReqCommand << ", res = " << dto.mResData;
            setState((eState)(mState + 1));
        }
    }

    void onValveReadedInterfaceCfgEthCATPDODataType(ValveResponseInterfaceConfigEthCATPDODataTypeDto dto)
    {
        onValveResponse(dto);
    }

    void onValveReadedInterfaceCfgEthCATPDORange(ValveResponseInterfaceConfigEthCATPDORangeDto dto)
    {
        onValveResponse(dto);
    }

    void onValveWrittenInterfaceCfgEthCATPDODataType(ValveResponseDto dto)
    {
        onValveResponse(dto);
    }

    void onValveWrittenInterfaceCfgEthCATPDORange(ValveResponseDto dto)
    {
        onValveResponse(dto);
    }

    void onValveResponse(ValveResponseDto dto)
    {
        setErrMsg(dto.mErrMsg);
        if(!dto.mIsSucc){ setState(mState); return; }


        qDebug() << "[" << Q_FUNC_INFO << "]";

        if(checkState(mState, dto) == false){ return; }

        qDebug() << "[" << Q_FUNC_INFO << "]req = " << dto.mReqDto.mReqCommand << ", res = " << dto.mResData;

        if(mIsWritten && (mState >= eState::STATE_READ_CTRL_01_TYPE && mState < eState::STATE_OVER))
        {
            checkTotalErrState(mState, dto);
        }
        else if(mIsWritten == false && (mState >= eState::STATE_READ_CTRL_01_TYPE && mState < eState::STATE_OVER))
        {
            setTotalValue(mState, dto);
        }

        if(mState == (eState::STATE_OVER - 1))
        {
            checkTotalWriteValue();
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE InterfaceSetupDevNetRangeItemModel * onCommandGetItemModel(int index)
    {
        return mPDOItemList[index];
    }

    Q_INVOKABLE void onCommandAutoPosiRange(int type)
    {
        switch(type)
        {
            case 1: // percent
            {
                mPDOItemList[ 3]->setFrom("0.0"); mPDOItemList[ 3]->setTo("100.0");
                mPDOItemList[ 4]->setFrom("0.0"); mPDOItemList[ 4]->setTo("100.0");
                mPDOItemList[ 5]->setFrom("0.0"); mPDOItemList[ 5]->setTo("100.0");
                mPDOItemList[ 7]->setFrom("0.0"); mPDOItemList[ 7]->setTo("100.0");
                mPDOItemList[11]->setFrom("0.0"); mPDOItemList[11]->setTo("100.0");
                break;
            }
            case 2: // degree
            {
                mPDOItemList[ 3]->setFrom("0.0"); mPDOItemList[ 3]->setTo("90.0");
                mPDOItemList[ 4]->setFrom("0.0"); mPDOItemList[ 4]->setTo("90.0");
                mPDOItemList[ 5]->setFrom("0.0"); mPDOItemList[ 5]->setTo("90.0");
                mPDOItemList[ 7]->setFrom("0.0"); mPDOItemList[ 7]->setTo("90.0");
                mPDOItemList[11]->setFrom("0.0"); mPDOItemList[11]->setTo("90.0");
                break;
            }
        }
    }

    Q_INVOKABLE void onCommandAutoPressRange(int type)
    {
        switch(type)
        {
            case 0: break;
            case 1: // percent
            {
                mPDOItemList[ 0]->setFrom("0.0"); mPDOItemList[ 0]->setTo("100.0");
                mPDOItemList[ 1]->setFrom("0.0"); mPDOItemList[ 1]->setTo("100.0");
                mPDOItemList[ 2]->setFrom("0.0"); mPDOItemList[ 2]->setTo("100.0");
                mPDOItemList[ 6]->setFrom("0.0"); mPDOItemList[ 6]->setTo("100.0");
                mPDOItemList[ 8]->setFrom("0.0"); mPDOItemList[ 8]->setTo("100.0");
                mPDOItemList[ 9]->setFrom("0.0"); mPDOItemList[ 9]->setTo("100.0");
                mPDOItemList[10]->setFrom("0.0"); mPDOItemList[10]->setTo("100.0");
                break;
            }
            default:
            {                         // "psi"                          ,"Torr"                              ,"mTorr"                              ,"bar"                              ,"mbar"                              ,"pa"                                ,"atm"
                int ui_unit[] = {0,0, UnitUtilEnumDef::PRESSURE_UNIT_PSI, UnitUtilEnumDef::PRESSURE_UNIT_TORR, UnitUtilEnumDef::PRESSURE_UNIT_MTORR, UnitUtilEnumDef::PRESSURE_UNIT_BAR, UnitUtilEnumDef::PRESSURE_UNIT_MBAR, UnitUtilEnumDef::PRESSURE_UNIT_PA, UnitUtilEnumDef::PRESSURE_UNIT_ATM };

                double max_pres = calFullScale(ui_unit[type]);
                mPDOItemList[ 0]->setFrom("0.0"); mPDOItemList[ 0]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                mPDOItemList[ 1]->setFrom("0.0"); mPDOItemList[ 1]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                mPDOItemList[ 2]->setFrom("0.0"); mPDOItemList[ 2]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                mPDOItemList[ 6]->setFrom("0.0"); mPDOItemList[ 6]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                mPDOItemList[ 8]->setFrom("0.0"); mPDOItemList[ 8]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                mPDOItemList[ 9]->setFrom("0.0"); mPDOItemList[ 9]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                mPDOItemList[10]->setFrom("0.0"); mPDOItemList[10]->setTo(QString("%1").arg(max_pres, 0, 'f', 4));
                break;
            }
        }
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply()
    {
        mIsWritten       = true;

        for(int i = 0; i < mPDOItemList.count(); i ++)
        {
            if(mPDOItemList[i]->getType() != 1)
                mPDOItemList[i]->onCommandSetEditType(1);
        }
        setErrMsg2("");

        setState(eState::STATE_WRITE_POSI_UNIT);
    }

private:
    enum eState{
        STATE_INIT                = 0,
        STATE_WRITE_POSI_UNIT     = STATE_INIT                + 1,
        STATE_WRITE_PRES_UNIT     = STATE_WRITE_POSI_UNIT     + 1,
        STATE_WRITE_CTRL_01_TYPE  = STATE_WRITE_PRES_UNIT     + 1,
        STATE_WRITE_CTRL_02_TYPE  = STATE_WRITE_CTRL_01_TYPE  + 1,
        STATE_WRITE_CTRL_03_TYPE  = STATE_WRITE_CTRL_02_TYPE  + 1,
        STATE_WRITE_CTRL_04_TYPE  = STATE_WRITE_CTRL_03_TYPE  + 1,
        STATE_WRITE_CTRL_05_TYPE  = STATE_WRITE_CTRL_04_TYPE  + 1,
        STATE_WRITE_CTRL_06_TYPE  = STATE_WRITE_CTRL_05_TYPE  + 1,
        STATE_WRITE_CTRL_07_TYPE  = STATE_WRITE_CTRL_06_TYPE  + 1,
        STATE_WRITE_CTRL_08_TYPE  = STATE_WRITE_CTRL_07_TYPE  + 1,
        STATE_WRITE_CTRL_09_TYPE  = STATE_WRITE_CTRL_08_TYPE  + 1,
        STATE_WRITE_CTRL_10_TYPE  = STATE_WRITE_CTRL_09_TYPE  + 1,
        STATE_WRITE_CTRL_11_TYPE  = STATE_WRITE_CTRL_10_TYPE  + 1,
        STATE_WRITE_CTRL_12_TYPE  = STATE_WRITE_CTRL_11_TYPE  + 1,
        STATE_WRITE_CTRL_01_RANGE = STATE_WRITE_CTRL_12_TYPE  + 1,
        STATE_WRITE_CTRL_02_RANGE = STATE_WRITE_CTRL_01_RANGE + 1,
        STATE_WRITE_CTRL_03_RANGE = STATE_WRITE_CTRL_02_RANGE + 1,
        STATE_WRITE_CTRL_04_RANGE = STATE_WRITE_CTRL_03_RANGE + 1,
        STATE_WRITE_CTRL_05_RANGE = STATE_WRITE_CTRL_04_RANGE + 1,
        STATE_WRITE_CTRL_06_RANGE = STATE_WRITE_CTRL_05_RANGE + 1,
        STATE_WRITE_CTRL_07_RANGE = STATE_WRITE_CTRL_06_RANGE + 1,
        STATE_WRITE_CTRL_08_RANGE = STATE_WRITE_CTRL_07_RANGE + 1,
        STATE_WRITE_CTRL_09_RANGE = STATE_WRITE_CTRL_08_RANGE + 1,
        STATE_WRITE_CTRL_10_RANGE = STATE_WRITE_CTRL_09_RANGE + 1,
        STATE_WRITE_CTRL_11_RANGE = STATE_WRITE_CTRL_10_RANGE + 1,
        STATE_WRITE_CTRL_12_RANGE = STATE_WRITE_CTRL_11_RANGE + 1,
        STATE_READ_CTRL_01_TYPE   = STATE_WRITE_CTRL_12_RANGE + 1,
        STATE_READ_CTRL_02_TYPE   = STATE_READ_CTRL_01_TYPE   + 1,
        STATE_READ_CTRL_03_TYPE   = STATE_READ_CTRL_02_TYPE   + 1,
        STATE_READ_CTRL_04_TYPE   = STATE_READ_CTRL_03_TYPE   + 1,
        STATE_READ_CTRL_05_TYPE   = STATE_READ_CTRL_04_TYPE   + 1,
        STATE_READ_CTRL_06_TYPE   = STATE_READ_CTRL_05_TYPE   + 1,
        STATE_READ_CTRL_07_TYPE   = STATE_READ_CTRL_06_TYPE   + 1,
        STATE_READ_CTRL_08_TYPE   = STATE_READ_CTRL_07_TYPE   + 1,
        STATE_READ_CTRL_09_TYPE   = STATE_READ_CTRL_08_TYPE   + 1,
        STATE_READ_CTRL_10_TYPE   = STATE_READ_CTRL_09_TYPE   + 1,
        STATE_READ_CTRL_11_TYPE   = STATE_READ_CTRL_10_TYPE   + 1,
        STATE_READ_CTRL_12_TYPE   = STATE_READ_CTRL_11_TYPE   + 1,
        STATE_READ_CTRL_01_RANGE  = STATE_READ_CTRL_12_TYPE   + 1,
        STATE_READ_CTRL_02_RANGE  = STATE_READ_CTRL_01_RANGE  + 1,
        STATE_READ_CTRL_03_RANGE  = STATE_READ_CTRL_02_RANGE  + 1,
        STATE_READ_CTRL_04_RANGE  = STATE_READ_CTRL_03_RANGE  + 1,
        STATE_READ_CTRL_05_RANGE  = STATE_READ_CTRL_04_RANGE  + 1,
        STATE_READ_CTRL_06_RANGE  = STATE_READ_CTRL_05_RANGE  + 1,
        STATE_READ_CTRL_07_RANGE  = STATE_READ_CTRL_06_RANGE  + 1,
        STATE_READ_CTRL_08_RANGE  = STATE_READ_CTRL_07_RANGE  + 1,
        STATE_READ_CTRL_09_RANGE  = STATE_READ_CTRL_08_RANGE  + 1,
        STATE_READ_CTRL_10_RANGE  = STATE_READ_CTRL_09_RANGE  + 1,
        STATE_READ_CTRL_11_RANGE  = STATE_READ_CTRL_10_RANGE  + 1,
        STATE_READ_CTRL_12_RANGE  = STATE_READ_CTRL_11_RANGE  + 1,
        STATE_OVER                = STATE_READ_CTRL_12_RANGE  + 1
    };

    QTimer mTimer;
    bool   mIsWritten     = false;

    eState mState         = eState::STATE_INIT;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(20);
    }

    void setState(eState state, bool immediately = false)
    {
        if(!mIsWritten && state == eState::STATE_OVER)
        {
            for(int i = 0; i < mPDOItemList.count(); i ++)
            {
                mPDOItemList[i]->initWriteValue();
            }
            setTotalEditReset();
        }

        mState = state;

        if(state >= STATE_READ_CTRL_01_TYPE && state < STATE_OVER)
        {
            setStrStatus("Loading");
        }
        else if(state >= STATE_WRITE_POSI_UNIT && state < STATE_READ_CTRL_01_TYPE)
        {
            setStrStatus("writting");
        }
        else
        {
            setStrStatus("ready");
        }

        if(state > eState::STATE_INIT && state < eState::STATE_OVER)
        {
            setProgress(qFloor((state * 100) / eState::STATE_OVER));
        }
        else
        {
            setProgress(100);
        }

        if(state != eState::STATE_OVER)
        {
            if(immediately)
                onTimeout();
            else
                startTimer();
        }
    }

public slots:
    void onTimeout()
    {
        if(mState == STATE_WRITE_POSI_UNIT)
        {
            pValveSP->setInterfaceConfigDNetPosUnit("0", this);
        }
        else if(mState == STATE_WRITE_PRES_UNIT)
        {
            pValveSP->setInterfaceConfigDNetPressureUnit("0", this);
        }
        else if(mState >= STATE_READ_CTRL_01_TYPE && mState <= STATE_READ_CTRL_12_TYPE)
        {
            int index = mState - STATE_READ_CTRL_01_TYPE;

            if(mPDOItemList[index]->IsNeedWriteType() || mIsWritten == false)
            {
                pValveSP->readInterfaceConfigEthCATPDODataType(index, this);
            }
            else
            {
                setState((eState)(mState + 1), true);
                return;
            }
        }
        else if(mState >= STATE_READ_CTRL_01_RANGE && mState <= STATE_READ_CTRL_12_RANGE)
        {
            int index = mState - STATE_READ_CTRL_01_RANGE;

            if((mPDOItemList[index]->IsNeedWriteFrom() || mPDOItemList[index]->IsNeedWriteTo())|| mIsWritten == false)
            {
                //qDebug() << "[" << Q_FUNC_INFO << "]index = "<< index << ", is need write from ?" << mPDOItemList[index]->IsNeedWriteFrom() << ", is need write to ?" << mPDOItemList[index]->IsNeedWriteTo();
                pValveSP->readInterfaceConfigEthCATPDORange(index, this);
            }
            else
            {
                if(mState == STATE_READ_CTRL_12_RANGE)
                    checkTotalWriteValue();

                setState((eState)(mState + 1), true);
                return;
            }
        }
        else if(mState >= STATE_WRITE_CTRL_01_TYPE && mState <= STATE_WRITE_CTRL_12_TYPE)
        {
            int index = mState - STATE_WRITE_CTRL_01_TYPE;

            if(mPDOItemList[index]->IsNeedWriteType())
            {
                int type = mPDOItemList[index]->mWriteType;
                pValveSP->setInterfaceConfigEthCATPDODataType(mState - STATE_WRITE_CTRL_01_TYPE, type,this);
            }
            else
            {
                setState((eState)(mState + 1), true);
                return;
            }
        }
        else if(mState >= STATE_WRITE_CTRL_01_RANGE && mState <= STATE_WRITE_CTRL_12_RANGE)
        {
            int     index = mState - STATE_WRITE_CTRL_01_RANGE;

            if(mPDOItemList[index]->IsNeedWriteFrom() || mPDOItemList[index]->IsNeedWriteTo())
            {
                QString from  = mPDOItemList[index]->mWriteFrom;
                QString to    = mPDOItemList[index]->mWriteTo  ;
                QString range = QString("%1to%2").arg(from).arg(to);
                pValveSP->setInterfaceConfigEthCATPDORange(mState - STATE_WRITE_CTRL_01_RANGE, range,this);
            }
            else
            {
                setState((eState)(mState + 1), true);
                return;
            }
        }
    }

    void checkTotalWriteValue()
    {
        if(mIsWritten)
        {
            bool isEdit = false;
            setTotalEditReset();

            for(int i = 0; i < mPDOItemList.count(); i ++)
            {
                isEdit = isEdit || mPDOItemList[i]->getError();
            }
            setIsEdit( isEdit );
            return;
        }
    }

    void checkTotalErrState(eState state, ValveResponseDto dto)
    {
        if(state >= STATE_READ_CTRL_01_TYPE && state <= STATE_READ_CTRL_12_TYPE)
        {
            ValveResponseInterfaceConfigEthCATPDODataTypeDto realDto = dto;
            mPDOItemList[state - STATE_READ_CTRL_01_TYPE]->checkErrType(realDto.mDataType);
        }
        else if(mState >= STATE_READ_CTRL_01_RANGE && state <= STATE_READ_CTRL_12_RANGE)
        {
            QStringList formTo = dto.mResData.mid(dto.mReqDto.mReqCommand.length()).split("to");
            mPDOItemList[state - STATE_READ_CTRL_01_RANGE]->checkErrFrom(formTo[0]); mPDOItemList[state - STATE_READ_CTRL_01_RANGE]->checkErrTo(formTo[1]);
        }
    }

    void setTotalValue(eState state, ValveResponseDto dto)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        if(state >= STATE_READ_CTRL_01_TYPE && state <= STATE_READ_CTRL_12_TYPE)
        {
            ValveResponseInterfaceConfigEthCATPDODataTypeDto realDto = dto;
            qDebug() << "[" << Q_FUNC_INFO << "] set Type";

            mPDOItemList[state - STATE_READ_CTRL_01_TYPE]->setValueType(realDto.mDataType);
        }
        else if(state >= STATE_READ_CTRL_01_RANGE && state <= STATE_READ_CTRL_12_RANGE)
        {
            QStringList formTo = dto.mResData.mid(dto.mReqDto.mReqCommand.length()).split("to");
            qDebug() << "[" << Q_FUNC_INFO << "] set Range";
            mPDOItemList[state - STATE_READ_CTRL_01_RANGE]->setValueFrom(formTo[0]); mPDOItemList[state - STATE_READ_CTRL_01_RANGE]->setValueTo(formTo[1]);
        }
    }

    void setTotalEditReset()
    {
        for(int i = 0; i < mPDOItemList.count(); i ++)
        {
            mPDOItemList[i]->setIsEditReset();
        }

        setIsEdit(false);
    }

    bool checkState(eState state, ValveResponseDto dto)
    {
        switch((int)state)
        {
        case (int)STATE_WRITE_CTRL_01_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2300") == false) return false; break;
        case (int)STATE_WRITE_CTRL_02_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2301") == false) return false; break;
        case (int)STATE_WRITE_CTRL_03_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2302") == false) return false; break;
        case (int)STATE_WRITE_CTRL_04_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2303") == false) return false; break;
        case (int)STATE_WRITE_CTRL_05_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2304") == false) return false; break;
        case (int)STATE_WRITE_CTRL_06_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2305") == false) return false; break;
        case (int)STATE_WRITE_CTRL_07_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2306") == false) return false; break;
        case (int)STATE_WRITE_CTRL_08_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2307") == false) return false; break;
        case (int)STATE_WRITE_CTRL_09_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2308") == false) return false; break;
        case (int)STATE_WRITE_CTRL_10_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2309") == false) return false; break;
        case (int)STATE_WRITE_CTRL_11_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2310") == false) return false; break;
        case (int)STATE_WRITE_CTRL_12_TYPE  : if(dto.mReqDto.mReqCommand.startsWith("s:2311") == false) return false; break;
        case (int)STATE_WRITE_CTRL_01_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2400") == false) return false; break;
        case (int)STATE_WRITE_CTRL_02_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2401") == false) return false; break;
        case (int)STATE_WRITE_CTRL_03_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2402") == false) return false; break;
        case (int)STATE_WRITE_CTRL_04_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2403") == false) return false; break;
        case (int)STATE_WRITE_CTRL_05_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2404") == false) return false; break;
        case (int)STATE_WRITE_CTRL_06_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2405") == false) return false; break;
        case (int)STATE_WRITE_CTRL_07_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2406") == false) return false; break;
        case (int)STATE_WRITE_CTRL_08_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2407") == false) return false; break;
        case (int)STATE_WRITE_CTRL_09_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2408") == false) return false; break;
        case (int)STATE_WRITE_CTRL_10_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2409") == false) return false; break;
        case (int)STATE_WRITE_CTRL_11_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2410") == false) return false; break;
        case (int)STATE_WRITE_CTRL_12_RANGE : if(dto.mReqDto.mReqCommand.startsWith("s:2411") == false) return false; break;
        case (int)STATE_READ_CTRL_01_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2300") == false) return false; break;
        case (int)STATE_READ_CTRL_02_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2301") == false) return false; break;
        case (int)STATE_READ_CTRL_03_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2302") == false) return false; break;
        case (int)STATE_READ_CTRL_04_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2303") == false) return false; break;
        case (int)STATE_READ_CTRL_05_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2304") == false) return false; break;
        case (int)STATE_READ_CTRL_06_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2305") == false) return false; break;
        case (int)STATE_READ_CTRL_07_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2306") == false) return false; break;
        case (int)STATE_READ_CTRL_08_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2307") == false) return false; break;
        case (int)STATE_READ_CTRL_09_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2308") == false) return false; break;
        case (int)STATE_READ_CTRL_10_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2309") == false) return false; break;
        case (int)STATE_READ_CTRL_11_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2310") == false) return false; break;
        case (int)STATE_READ_CTRL_12_TYPE   : if(dto.mReqDto.mReqCommand.startsWith("i:2311") == false) return false; break;
        case (int)STATE_READ_CTRL_01_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2400") == false) return false; break;
        case (int)STATE_READ_CTRL_02_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2401") == false) return false; break;
        case (int)STATE_READ_CTRL_03_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2402") == false) return false; break;
        case (int)STATE_READ_CTRL_04_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2403") == false) return false; break;
        case (int)STATE_READ_CTRL_05_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2404") == false) return false; break;
        case (int)STATE_READ_CTRL_06_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2405") == false) return false; break;
        case (int)STATE_READ_CTRL_07_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2406") == false) return false; break;
        case (int)STATE_READ_CTRL_08_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2407") == false) return false; break;
        case (int)STATE_READ_CTRL_09_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2408") == false) return false; break;
        case (int)STATE_READ_CTRL_10_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2409") == false) return false; break;
        case (int)STATE_READ_CTRL_11_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2410") == false) return false; break;
        case (int)STATE_READ_CTRL_12_RANGE  : if(dto.mReqDto.mReqCommand.startsWith("i:2411") == false) return false; break;
        }

        return true;
    }

    double calFullScale(int dnetUnit)
    {
        double fullScale = 0;
        int    unit = 0;
        if(pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT || pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01)
        {
            fullScale = pValveSP->getS01FullScale();
            unit = pValveSP->getS01SullScaleUnit();
        }
        else if(pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT || pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02)
        {
            fullScale = pValveSP->getS02FullScale();
            unit = pValveSP->getS02SullScaleUnit();
        }
        else
        {
            double s02Scale = UnitUtil::getInstance()->convert(pValveSP->getS02SullScaleUnit(), pValveSP->getS02FullScale(), pValveSP->getS01SullScaleUnit());

            if(s02Scale < pValveSP->getS01FullScale())
            {
                fullScale = pValveSP->getS01FullScale();
                unit = pValveSP->getS01SullScaleUnit();
            }
            else
            {
                fullScale = pValveSP->getS02FullScale();
                unit = pValveSP->getS02SullScaleUnit();
            }
        }

        return UnitUtil::getInstance()->convert(unit, fullScale, dnetUnit);
    }
};
#endif // INTERFACESETUPDEVNETRANGEDLGMODEL_H
