#ifndef INTERFACESETUPETHERNETDLGMODEL_H
#define INTERFACESETUPETHERNETDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceSetupEtherNETDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(int      mInterface           READ getInterface           NOTIFY signalEventChangedInterface          )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test        )

    Q_PROPERTY(int      mIp01                READ getIp01                NOTIFY signalEventChangedIp01               )
    Q_PROPERTY(int      mIp02                READ getIp02                NOTIFY signalEventChangedIp02               )
    Q_PROPERTY(int      mIp03                READ getIp03                NOTIFY signalEventChangedIp03               )
    Q_PROPERTY(int      mIp04                READ getIp04                NOTIFY signalEventChangedIp04               )
    Q_PROPERTY(int      mSubNet01            READ getSubNet01            NOTIFY signalEventChangedSubNet01           )
    Q_PROPERTY(int      mSubNet02            READ getSubNet02            NOTIFY signalEventChangedSubNet02           )
    Q_PROPERTY(int      mSubNet03            READ getSubNet03            NOTIFY signalEventChangedSubNet03           )
    Q_PROPERTY(int      mSubNet04            READ getSubNet04            NOTIFY signalEventChangedSubNet04           )
    Q_PROPERTY(int      mGateway01           READ getGateway01           NOTIFY signalEventChangedGateway01          )
    Q_PROPERTY(int      mGateway02           READ getGateway02           NOTIFY signalEventChangedGateway02          )
    Q_PROPERTY(int      mGateway03           READ getGateway03           NOTIFY signalEventChangedGateway03          )
    Q_PROPERTY(int      mGateway04           READ getGateway04           NOTIFY signalEventChangedGateway04          )
    Q_PROPERTY(int      mDHCPIdx             READ getDHCPIdx             NOTIFY signalEventChangedDHCPIdx            )
    Q_PROPERTY(int      mPort01              READ getPort01              NOTIFY signalEventChangedPort01             )
    Q_PROPERTY(int      mPort02              READ getPort02              NOTIFY signalEventChangedPort02             )
    Q_PROPERTY(int      mTerminationIdx      READ getTerminationIdx      NOTIFY signalEventChangedTerminationIdx     )
    Q_PROPERTY(int      mPosRangeIdx         READ getPosRangeIdx         NOTIFY signalEventChangedPosRangeIdx        )
    Q_PROPERTY(int      mPressureRange       READ getPressureRange       NOTIFY signalEventChangedPressureRange      )
    Q_PROPERTY(int      mCommandSetIdx       READ getCommandSetIdx       NOTIFY signalEventChangedCommandSetIdx      )
    Q_PROPERTY(int      mSecondAnswerIdx     READ getSecondAnswerIdx     NOTIFY signalEventChangedSecondAnswerIdx    )
    Q_PROPERTY(int      mDIOpenValveIdx      READ getDIOpenValveIdx      NOTIFY signalEventChangedDIOpenValveIdx     )
    Q_PROPERTY(int      mDICloseValveIdx     READ getDICloseValveIdx     NOTIFY signalEventChangedDICloseValveIdx    )
    Q_PROPERTY(bool     mErrIp               READ getErrIp               NOTIFY signalEventChangedErrIp              )
    Q_PROPERTY(bool     mErrSubNet           READ getErrSubNet           NOTIFY signalEventChangedErrSubNet          )
    Q_PROPERTY(bool     mErrGateway          READ getErrGateway          NOTIFY signalEventChangedErrGateway         )
    Q_PROPERTY(bool     mErrDHCP             READ getErrDHCP             NOTIFY signalEventChangedErrDHCP            )
    Q_PROPERTY(bool     mErrPort01           READ getErrPort01           NOTIFY signalEventChangedErrPort01          )
    Q_PROPERTY(bool     mErrPort02           READ getErrPort02           NOTIFY signalEventChangedErrPort02          )
    Q_PROPERTY(bool     mErrTerminationIdx   READ getErrTerminationIdx   NOTIFY signalEventChangedErrTerminationIdx  )
    Q_PROPERTY(bool     mErrPosRangeIdx      READ getErrPosRangeIdx      NOTIFY signalEventChangedErrPosRangeIdx     )
    Q_PROPERTY(bool     mErrPressureRange    READ getErrPressureRange    NOTIFY signalEventChangedErrPressureRange   )
    Q_PROPERTY(bool     mErrCommandSetIdx    READ getErrCommandSetIdx    NOTIFY signalEventChangedErrCommandSetIdx   )
    Q_PROPERTY(bool     mErrSecondAnswerIdx  READ getErrSecondAnswerIdx  NOTIFY signalEventChangedErrSecondAnswerIdx )
    Q_PROPERTY(bool     mErrDIOpenValveIdx   READ getErrDIOpenValveIdx   NOTIFY signalEventChangedErrDIOpenValveIdx  )
    Q_PROPERTY(bool     mErrDICloseValveIdx  READ getErrDICloseValveIdx  NOTIFY signalEventChangedErrDICloseValveIdx )
    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit             )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2            )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress           )

public:
    int     mAccessMode          = ValveEnumDef::ACCESS_LOCAL;
    int     mInterface           = ValveEnumDef::INTERFACE_ETHERNET;
    bool    mIsRS232Test         = false;

    int     mIp01                = 0;
    int     mIp02                = 0;
    int     mIp03                = 0;
    int     mIp04                = 0;
    int     mSubNet01            = 0;
    int     mSubNet02            = 0;
    int     mSubNet03            = 0;
    int     mSubNet04            = 0;
    int     mGateway01           = 0;
    int     mGateway02           = 0;
    int     mGateway03           = 0;
    int     mGateway04           = 0;
    int     mDHCPIdx             = 0;
    int     mPort01              = 0;
    int     mPort02              = 0;
    int     mTerminationIdx      = 0;
    int     mPosRangeIdx         = 0;
    int     mPressureRange       = 0;
    int     mCommandSetIdx       = 0;
    int     mSecondAnswerIdx     = 0;
    int     mDIOpenValveIdx      = 0;
    int     mDICloseValveIdx     = 0;
    bool    mErrIp               = false;
    bool    mErrSubNet           = false;
    bool    mErrGateway          = false;
    bool    mErrDHCP             = false;
    bool    mErrPort01           = false;
    bool    mErrPort02           = false;
    bool    mErrTerminationIdx   = false;
    bool    mErrPosRangeIdx      = false;
    bool    mErrPressureRange    = false;
    bool    mErrCommandSetIdx    = false;
    bool    mErrSecondAnswerIdx  = false;
    bool    mErrDIOpenValveIdx   = false;
    bool    mErrDICloseValveIdx  = false;

    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    int     getInterface              (){ return mInterface              ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}

    int     getIp01                   (){ return mIp01                   ;}
    int     getIp02                   (){ return mIp02                   ;}
    int     getIp03                   (){ return mIp03                   ;}
    int     getIp04                   (){ return mIp04                   ;}
    int     getSubNet01               (){ return mSubNet01               ;}
    int     getSubNet02               (){ return mSubNet02               ;}
    int     getSubNet03               (){ return mSubNet03               ;}
    int     getSubNet04               (){ return mSubNet04               ;}
    int     getGateway01              (){ return mGateway01              ;}
    int     getGateway02              (){ return mGateway02              ;}
    int     getGateway03              (){ return mGateway03              ;}
    int     getGateway04              (){ return mGateway04              ;}
    int     getDHCPIdx                (){ return mDHCPIdx                ;}
    int     getPort01                 (){ return mPort01                 ;}
    int     getPort02                 (){ return mPort02                 ;}
    int     getTerminationIdx         (){ return mTerminationIdx         ;}
    int     getPosRangeIdx            (){ return mPosRangeIdx            ;}
    int     getPressureRange          (){ return mPressureRange          ;}
    int     getCommandSetIdx          (){ return mCommandSetIdx          ;}
    int     getSecondAnswerIdx        (){ return mSecondAnswerIdx        ;}
    int     getDIOpenValveIdx         (){ return mDIOpenValveIdx         ;}
    int     getDICloseValveIdx        (){ return mDICloseValveIdx        ;}
    bool    getErrIp                  (){ return mErrIp                  ;}
    bool    getErrSubNet              (){ return mErrSubNet              ;}
    bool    getErrGateway             (){ return mErrGateway             ;}
    bool    getErrDHCP                (){ return mErrDHCP                ;}
    bool    getErrPort01              (){ return mErrPort01              ;}
    bool    getErrPort02              (){ return mErrPort02              ;}
    bool    getErrTerminationIdx      (){ return mErrTerminationIdx      ;}
    bool    getErrPosRangeIdx         (){ return mErrPosRangeIdx         ;}
    bool    getErrPressureRange       (){ return mErrPressureRange       ;}
    bool    getErrCommandSetIdx       (){ return mErrCommandSetIdx       ;}
    bool    getErrSecondAnswerIdx     (){ return mErrSecondAnswerIdx     ;}
    bool    getErrDIOpenValveIdx      (){ return mErrDIOpenValveIdx      ;}
    bool    getErrDICloseValveIdx     (){ return mErrDICloseValveIdx     ;}

    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode          == value)return; mAccessMode          = value; emit signalEventChangedAccessMode         (value);}
    void    setInterface              (int     value){ if(mInterface           == value)return; mInterface           = value; emit signalEventChangedInterface          (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test         == value)return; mIsRS232Test         = value; emit signalEventChangedIsRS232Test        (value);}

    void    setIp01                   (int     value){ if(mIp01                == value)return; mIp01                = value; emit signalEventChangedIp01               (value);}
    void    setIp02                   (int     value){ if(mIp02                == value)return; mIp02                = value; emit signalEventChangedIp02               (value);}
    void    setIp03                   (int     value){ if(mIp03                == value)return; mIp03                = value; emit signalEventChangedIp03               (value);}
    void    setIp04                   (int     value){ if(mIp04                == value)return; mIp04                = value; emit signalEventChangedIp04               (value);}
    void    setSubNet01               (int     value){ if(mSubNet01            == value)return; mSubNet01            = value; emit signalEventChangedSubNet01           (value);}
    void    setSubNet02               (int     value){ if(mSubNet02            == value)return; mSubNet02            = value; emit signalEventChangedSubNet02           (value);}
    void    setSubNet03               (int     value){ if(mSubNet03            == value)return; mSubNet03            = value; emit signalEventChangedSubNet03           (value);}
    void    setSubNet04               (int     value){ if(mSubNet04            == value)return; mSubNet04            = value; emit signalEventChangedSubNet04           (value);}
    void    setGateway01              (int     value){ if(mGateway01           == value)return; mGateway01           = value; emit signalEventChangedGateway01          (value);}
    void    setGateway02              (int     value){ if(mGateway02           == value)return; mGateway02           = value; emit signalEventChangedGateway02          (value);}
    void    setGateway03              (int     value){ if(mGateway03           == value)return; mGateway03           = value; emit signalEventChangedGateway03          (value);}
    void    setGateway04              (int     value){ if(mGateway04           == value)return; mGateway04           = value; emit signalEventChangedGateway04          (value);}
    void    setDHCPIdx                (int     value){ if(mDHCPIdx             == value)return; mDHCPIdx             = value; emit signalEventChangedDHCPIdx            (value);}
    void    setPort01                 (int     value){ if(mPort01              == value)return; mPort01              = value; emit signalEventChangedPort01             (value);}
    void    setPort02                 (int     value){ if(mPort02              == value)return; mPort02              = value; emit signalEventChangedPort02             (value);}
    void    setTerminationIdx         (int     value){ if(mTerminationIdx      == value)return; mTerminationIdx      = value; emit signalEventChangedTerminationIdx     (value);}
    void    setPosRangeIdx            (int     value){ if(mPosRangeIdx         == value)return; mPosRangeIdx         = value; emit signalEventChangedPosRangeIdx        (value);}
    void    setPressureRange          (int     value){ if(mPressureRange       == value)return; mPressureRange       = value; emit signalEventChangedPressureRange      (value);}
    void    setCommandSetIdx          (int     value){ if(mCommandSetIdx       == value)return; mCommandSetIdx       = value; emit signalEventChangedCommandSetIdx      (value);}
    void    setSecondAnswerIdx        (int     value){ if(mSecondAnswerIdx     == value)return; mSecondAnswerIdx     = value; emit signalEventChangedSecondAnswerIdx    (value);}
    void    setDIOpenValveIdx         (int     value){ if(mDIOpenValveIdx      == value)return; mDIOpenValveIdx      = value; emit signalEventChangedDIOpenValveIdx     (value);}
    void    setDICloseValveIdx        (int     value){ if(mDICloseValveIdx     == value)return; mDICloseValveIdx     = value; emit signalEventChangedDICloseValveIdx    (value);}
    void    setErrIp                  (bool    value){ if(mErrIp               == value)return; mErrIp               = value; emit signalEventChangedErrIp              (value);}
    void    setErrSubNet              (bool    value){ if(mErrSubNet           == value)return; mErrSubNet           = value; emit signalEventChangedErrSubNet          (value);}
    void    setErrGateway             (bool    value){ if(mErrGateway          == value)return; mErrGateway          = value; emit signalEventChangedErrGateway         (value);}
    void    setErrDHCP                (bool    value){ if(mErrDHCP             == value)return; mErrDHCP             = value; emit signalEventChangedErrDHCP            (value);}
    void    setErrPort01              (bool    value){ if(mErrPort01           == value)return; mErrPort01           = value; emit signalEventChangedErrPort01          (value);}
    void    setErrPort02              (bool    value){ if(mErrPort02           == value)return; mErrPort02           = value; emit signalEventChangedErrPort02          (value);}
    void    setErrTerminationIdx      (bool    value){ if(mErrTerminationIdx   == value)return; mErrTerminationIdx   = value; emit signalEventChangedErrTerminationIdx  (value);}
    void    setErrPosRangeIdx         (bool    value){ if(mErrPosRangeIdx      == value)return; mErrPosRangeIdx      = value; emit signalEventChangedErrPosRangeIdx     (value);}
    void    setErrPressureRange       (bool    value){ if(mErrPressureRange    == value)return; mErrPressureRange    = value; emit signalEventChangedErrPressureRange   (value);}
    void    setErrCommandSetIdx       (bool    value){ if(mErrCommandSetIdx    == value)return; mErrCommandSetIdx    = value; emit signalEventChangedErrCommandSetIdx   (value);}
    void    setErrSecondAnswerIdx     (bool    value){ if(mErrSecondAnswerIdx  == value)return; mErrSecondAnswerIdx  = value; emit signalEventChangedErrSecondAnswerIdx (value);}
    void    setErrDIOpenValveIdx      (bool    value){ if(mErrDIOpenValveIdx   == value)return; mErrDIOpenValveIdx   = value; emit signalEventChangedErrDIOpenValveIdx  (value);}
    void    setErrDICloseValveIdx     (bool    value){ if(mErrDICloseValveIdx  == value)return; mErrDICloseValveIdx  = value; emit signalEventChangedErrDICloseValveIdx (value);}

    void    setIsEdit                 (bool    value){ if(mIsEdit              == value)return; mIsEdit              = value; emit signalEventChangedIsEdit             (value);}
    void    setStrStatus              (QString value){ if(mStrStatus           == value)return; mStrStatus           = value; emit signalEventChangedStrStatus          (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg              == value)return; mErrMsg              = value; emit signalEventChangedErrMsg             (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2             == value)return; mErrMsg2             = value; emit signalEventChangedErrMsg2            (value);}
    void    setProgress               (int     value){ if(mProgress            == value)return; mProgress            = value; emit signalEventChangedProgress           (value);}

signals:
    void signalEventChangedAccessMode         (int     value);
    void signalEventChangedInterface          (int     value);
    void signalEventChangedIsRS232Test        (bool    value);

    void signalEventChangedIp01               (int     value);
    void signalEventChangedIp02               (int     value);
    void signalEventChangedIp03               (int     value);
    void signalEventChangedIp04               (int     value);
    void signalEventChangedSubNet01           (int     value);
    void signalEventChangedSubNet02           (int     value);
    void signalEventChangedSubNet03           (int     value);
    void signalEventChangedSubNet04           (int     value);
    void signalEventChangedGateway01          (int     value);
    void signalEventChangedGateway02          (int     value);
    void signalEventChangedGateway03          (int     value);
    void signalEventChangedGateway04          (int     value);
    void signalEventChangedDHCPIdx            (int     value);
    void signalEventChangedPort01             (int     value);
    void signalEventChangedPort02             (int     value);
    void signalEventChangedTerminationIdx     (int     value);
    void signalEventChangedPosRangeIdx        (int     value);
    void signalEventChangedPressureRange      (int     value);
    void signalEventChangedCommandSetIdx      (int     value);
    void signalEventChangedSecondAnswerIdx    (int     value);
    void signalEventChangedDIOpenValveIdx     (int     value);
    void signalEventChangedDICloseValveIdx    (int     value);
    void signalEventChangedErrIp              (bool    value);
    void signalEventChangedErrSubNet          (bool    value);
    void signalEventChangedErrGateway         (bool    value);
    void signalEventChangedErrDHCP            (bool    value);
    void signalEventChangedErrPort01          (bool    value);
    void signalEventChangedErrPort02          (bool    value);
    void signalEventChangedErrTerminationIdx  (bool    value);
    void signalEventChangedErrPosRangeIdx     (bool    value);
    void signalEventChangedErrPressureRange   (bool    value);
    void signalEventChangedErrCommandSetIdx   (bool    value);
    void signalEventChangedErrSecondAnswerIdx (bool    value);
    void signalEventChangedErrDIOpenValveIdx  (bool    value);
    void signalEventChangedErrDICloseValveIdx (bool    value);

    void signalEventChangedIsEdit            (bool    value);
    void signalEventChangedStrStatus         (QString value);
    void signalEventChangedErrMsg            (QString value);
    void signalEventChangedErrMsg2           (QString value);
    void signalEventChangedProgress          (int     value);
    void signalEventCompletedLoad            (             );

public:
    explicit InterfaceSetupEtherNETDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_ETHERNET_IP;
        ENABLE_SLOT_VALVE_READED_ETHERNET_SUBNET;
        ENABLE_SLOT_VALVE_READED_ETHERNET_GATEWAY;
        ENABLE_SLOT_VALVE_READED_ETHERNET_DHCP;
        ENABLE_SLOT_VALVE_READED_ETHERNET_PORT01;
        ENABLE_SLOT_VALVE_READED_ETHERNET_PORT02;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS485;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS232_RANGE;
        ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_IP;
        ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_SUBNET;
        ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_GATEWAY;
        ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_DHCP;
        ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_PORT01;
        ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_PORT02;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS485;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232_RANGE;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_INTERFACE;

        onValveChangedAccess();
        onValveChangedInterface();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_IP);
    }
    ~InterfaceSetupEtherNETDlgModel()
    {
        pValveSP->reLoad();
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedInterface()
    {
        setInterface(pValveSP->getInterface());
    }

    void onValveChangedIsRS232Test()
    {
        setIsRS232Test(pValveSP->getIsRS232Test());
    }

    void onValveReadedInterfaceEthernetIP(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_IP || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrIp(dto.mValue != mWriteIP  );
        }
        else
        {
            QStringList ips = dto.mValue.split(".");

            if(ips.count() > 0) setIp01(ips[0].toInt());
            if(ips.count() > 1) setIp02(ips[1].toInt());
            if(ips.count() > 2) setIp03(ips[2].toInt());
            if(ips.count() > 3) setIp04(ips[3].toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceEthernetSubnet(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_SUBNET || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrSubNet(dto.mValue != mWriteSubnet  );
        }
        else
        {
            QStringList subnet = dto.mValue.split(".");

            if(subnet.count() > 0) setSubNet01(subnet[0].toInt());
            if(subnet.count() > 1) setSubNet02(subnet[1].toInt());
            if(subnet.count() > 2) setSubNet03(subnet[2].toInt());
            if(subnet.count() > 3) setSubNet04(subnet[3].toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceEthernetGateway(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_GATEWAY || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrGateway(dto.mValue != mWriteGateway );
        }
        else
        {
            QStringList gateway = dto.mValue.split(".");

            if(gateway.count() > 0) setGateway01(gateway[0].toInt());
            if(gateway.count() > 1) setGateway02(gateway[1].toInt());
            if(gateway.count() > 2) setGateway03(gateway[2].toInt());
            if(gateway.count() > 3) setGateway04(gateway[3].toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceEthernetDHCP(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_DHCP || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrDHCP(dto.mValue != mWriteDHCP );
        }
        else
        {
            QStringList gateway = dto.mValue.split(".");

            if(dto.mValue == "y")
                setDHCPIdx(1);
            else
                setDHCPIdx(0);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceEthernetPort01(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_PORT01 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrPort01(dto.mValue != mWritePort01 );
        }
        else
        {
            setPort01(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceEthernetPort02(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_PORT02 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrPort02(dto.mValue != mWritePort02 );
        }
        else
        {
            setPort02(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgRS232(ValveResponseInterfaceConfigRS232Dto dto)
    {
        if(mState != eState::STATE_READ_CFG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrCommandSetIdx  (dto.mCommandSetIdx   != mWriteCommandSetIdx  );
            setErrSecondAnswerIdx(dto.mSecondAnswerIdx != mWriteSecondAnswerIdx);
            setErrDIOpenValveIdx (dto.mDIOpenValveIdx  != mWriteDIOpenValveIdx );
            setErrDICloseValveIdx(dto.mDICloseValveIdx != mWriteDICloseValveIdx);
        }
        else
        {
            setCommandSetIdx  (dto.mCommandSetIdx  );
            setSecondAnswerIdx(dto.mSecondAnswerIdx);
            setDIOpenValveIdx (dto.mDIOpenValveIdx );
            setDICloseValveIdx(dto.mDICloseValveIdx);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgRS485(ValveResponseInterfaceConfigRS485Dto dto)
    {
        if(mState != eState::STATE_READ_RS485_CFG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrTerminationIdx  (dto.mTerminationIdx   != mWriteTerminationIdx  );
        }
        else
        {
            setTerminationIdx  (dto.mTerminationIdx  );
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgRS232Range(ValveResponseInterfaceConfigRS232RangeDto dto)
    {
        if(mState != eState::STATE_READ_RANGE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            //setState(mState);
            setState((eState)(mState + 1));
            return;
        }

        if(mIsWritten)
        {
            setErrPosRangeIdx  (dto.mPosRangeIdx   != mWritePosRangeIdx  );
            setErrPressureRange(dto.mPressureRange != mWritePressureRange);

            onCommandSetEdit( getErrIp() || getErrSubNet() || getErrDHCP() || getErrPort01() || getErrPort02() || getErrCommandSetIdx() || getErrSecondAnswerIdx() || getErrDIOpenValveIdx() || getErrDICloseValveIdx() || getErrPosRangeIdx() || getErrPressureRange());
        }
        else
        {
            setPosRangeIdx  (dto.mPosRangeIdx  );
            setPressureRange(dto.mPressureRange);
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int ip01, int ip02, int ip03, int ip04, int subnet01,int subnet02,int subnet03,int subnet04,
                                    int gateway01, int gateway02, int gateway03, int gateway04, int dhcpIdx, int port01, int port02,
                                    int terminationIdx  ,int commandSetIdx, int secondAnswerIdx, int diOpenValveIdx, int diCloseValveIdx, int posRangeIdx, int pressureRange)
    {
        mIsWritten             = true            ;

        mWriteIP               = QString("%1.%2.%3.%4").arg(ip01).arg(ip02).arg(ip03).arg(ip04);
        mWriteSubnet           = QString("%1.%2.%3.%4").arg(subnet01).arg(subnet02).arg(subnet03).arg(subnet04);
        mWriteGateway          = QString("%1.%2.%3.%4").arg(gateway01).arg(gateway02).arg(gateway03).arg(gateway04);
        mWriteDHCP             = dhcpIdx == 0 ? "n" : "y";
        mWritePort01           = QString("%1").arg(port01);
        mWritePort02           = QString("%1").arg(port02);
        mWriteTerminationIdx   = terminationIdx  ;
        mWriteCommandSetIdx    = commandSetIdx   ;
        mWriteSecondAnswerIdx  = secondAnswerIdx ;
        mWriteDIOpenValveIdx   = diOpenValveIdx  ;
        mWriteDICloseValveIdx  = diCloseValveIdx ;
        mWritePosRangeIdx      = posRangeIdx     ;
        mWritePressureRange    = pressureRange   ;

        setIsEdit(false);

        setErrMsg("");
        setErrMsg2("");

        setState(eState::STATE_WRITE_IP);
    }

    void onValveWrittenInterfaceEthernetIP(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_IP || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceEthernetSubnet(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_SUBNET || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceEthernetGateway(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_GATEWAY || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceEthernetDHCP(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DHCP || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceEthernetPort01(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_PORT01 || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceEthernetPort02(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_PORT02 || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceCfgRS232(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_CFG || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceCfgRS485(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_RS485_CFG || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceCfgRS232Range(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_RANGE || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

private:
    enum eState{
        STATE_WRITE_IP        = 0,
        STATE_WRITE_SUBNET    = STATE_WRITE_IP        + 1,
        STATE_WRITE_GATEWAY   = STATE_WRITE_SUBNET    + 1,
        STATE_WRITE_DHCP      = STATE_WRITE_GATEWAY   + 1,
        STATE_WRITE_PORT01    = STATE_WRITE_DHCP      + 1,
        STATE_WRITE_PORT02    = STATE_WRITE_PORT01    + 1,
        STATE_WRITE_CFG       = STATE_WRITE_PORT02    + 1,
        STATE_WRITE_RS485_CFG = STATE_WRITE_CFG       + 1,
        STATE_WRITE_RANGE     = STATE_WRITE_RS485_CFG + 1,
        STATE_READ_IP         = STATE_WRITE_RANGE     + 1,
        STATE_READ_SUBNET     = STATE_READ_IP         + 1,
        STATE_READ_GATEWAY    = STATE_READ_SUBNET     + 1,
        STATE_READ_DHCP       = STATE_READ_GATEWAY    + 1,
        STATE_READ_PORT01     = STATE_READ_DHCP       + 1,
        STATE_READ_PORT02     = STATE_READ_PORT01     + 1,
        STATE_READ_CFG        = STATE_READ_PORT02     + 1,
        STATE_READ_RS485_CFG  = STATE_READ_CFG        + 1,
        STATE_READ_RANGE      = STATE_READ_RS485_CFG  + 1,
        STATE_READY           = STATE_READ_RANGE      + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CFG;

    bool    mIsWritten             = false;
    QString mWriteIP            = "000.000.000.000";
    QString mWriteSubnet        = "000.000.000.000";
    QString mWriteGateway       = "000.000.000.000";
    QString mWriteDHCP          = "n";
    QString mWritePort01        = "501";
    QString mWritePort02        = "501";
    int  mWriteTerminationIdx   = 0;
    int  mWriteCommandSetIdx    = 0;
    int  mWriteSecondAnswerIdx  = 0;
    int  mWriteDIOpenValveIdx   = 0;
    int  mWriteDICloseValveIdx  = 0;
    int  mWritePosRangeIdx      = 0;
    int  mWritePressureRange    = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        int progress = 0;
        QString strStatus;

        mState = state;

        if(mIsWritten == false && mState == STATE_READY)
        {
            onCommandSetEdit(false);

            emit signalEventCompletedLoad();
        }

        progress = ((mState) * 100) / STATE_READY;

        if(mState >= STATE_READ_IP && mState <= STATE_READ_RANGE)
        {
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_IP && mState <= STATE_WRITE_RANGE)
        {
            strStatus = "writting";
        }
        else
        {
            progress = 100;
            strStatus = "ready";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_IP:
            pValveSP->readInterfaceEthernetIP(this);
            break;

        case (int)eState::STATE_READ_SUBNET:
            pValveSP->readInterfaceEthernetSubnet(this);
            break;

        case (int)eState::STATE_READ_GATEWAY:
            pValveSP->readInterfaceEthernetGateway(this);
            break;

        case (int)eState::STATE_READ_DHCP:
            pValveSP->readInterfaceEthernetDHCP(this);
            break;

        case (int)eState::STATE_READ_PORT01:
            pValveSP->readInterfaceEthernetPort01(this);
            break;

        case (int)eState::STATE_READ_PORT02:
            pValveSP->readInterfaceEthernetPort02(this);
            break;

        case (int)eState::STATE_READ_CFG:
            pValveSP->readInterfaceConfigRS232(this);
            break;

        case (int)eState::STATE_READ_RS485_CFG:
            pValveSP->readInterfaceConfigRS485(this);
            break;

        case (int)eState::STATE_READ_RANGE:
            pValveSP->readInterfaceConfigRS232Range(this);
            break;

        case (int)eState::STATE_WRITE_IP:
            pValveSP->setInterfaceEthernetIP(mWriteIP, this);
            break;

        case (int)eState::STATE_WRITE_SUBNET:
            pValveSP->setInterfaceEthernetSubnet(mWriteSubnet, this);
            break;

        case (int)eState::STATE_WRITE_GATEWAY:
            pValveSP->setInterfaceEthernetGateway(mWriteGateway, this);
            break;

        case (int)eState::STATE_WRITE_DHCP:
            pValveSP->setInterfaceEthernetDHCP(mWriteDHCP, this);
            break;

        case (int)eState::STATE_WRITE_PORT01:
            pValveSP->setInterfaceEthernetPort01(mWritePort01, this);
            break;

        case (int)eState::STATE_WRITE_PORT02:
            pValveSP->setInterfaceEthernetPort02(mWritePort02, this);
            break;

        case (int)eState::STATE_WRITE_CFG:
            pValveSP->setInterfaceConfigRS232(0, 0, 0, 0, mWriteCommandSetIdx, mWriteSecondAnswerIdx, mWriteDIOpenValveIdx, mWriteDICloseValveIdx, this);
            break;

        case (int)eState::STATE_WRITE_RS485_CFG:
            pValveSP->setInterfaceConfigRS485(0, 0, 0, mWriteTerminationIdx, this);
            break;
        case (int)eState::STATE_WRITE_RANGE:
            pValveSP->setInterfaceConfigRS232Range(mWritePosRangeIdx, mWritePressureRange, this);
            break;
        }
    }

};
#endif // INTERFACESETUPETHERNETDLGMODEL_H
