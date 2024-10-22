#ifndef IVALVE_H
#define IVALVE_H

#include <QObject>
#include <QSerialPort>

class SerialConnectionOpt{
public:
    QString mName = "";
    bool mIsSelect = true;
    QSerialPort::BaudRate mBaudRate = QSerialPort::Baud38400 ;
    QSerialPort::DataBits mDataBits = QSerialPort::Data7     ;
    QSerialPort::StopBits mStopBits = QSerialPort::OneStop   ;
    QSerialPort::Parity   mParity   = QSerialPort::EvenParity;

    SerialConnectionOpt(){}
    SerialConnectionOpt(QString               name,
                        bool                  isSelect,
                        QSerialPort::BaudRate baudRate,
                        QSerialPort::DataBits dataBits,
                        QSerialPort::StopBits stopBits,
                        QSerialPort::Parity   parity)
    {
        mName     = name    ;
        mIsSelect = isSelect;
        mBaudRate = baudRate;
        mDataBits = dataBits;
        mStopBits = stopBits;
        mParity   = parity  ;
    }
    SerialConnectionOpt(const SerialConnectionOpt& copy) :
        mName    (copy.mName),
        mIsSelect(copy.mIsSelect),
        mBaudRate(copy.mBaudRate),
        mDataBits(copy.mDataBits),
        mStopBits(copy.mStopBits),
        mParity  (copy.mParity  ){}

    ~SerialConnectionOpt(){}

    SerialConnectionOpt& operator=(const SerialConnectionOpt& other)
    {
        mName     = other.mName    ;
        mIsSelect = other.mIsSelect;
        mBaudRate = other.mBaudRate;
        mDataBits = other.mDataBits;
        mStopBits = other.mStopBits;
        mParity   = other.mParity  ;

        return *this;
    }
};

Q_DECLARE_METATYPE(SerialConnectionOpt);

class IValve{
public:
    enum eValveError {
        NoError,
        DeviceNotFoundError,
        PermissionError,
        OpenError,
        ParityError,
        FramingError,
        BreakConditionError,
        WriteError,
        ReadError,
        ResourceError,
        UnsupportedOperationError,
        UnknownError,
        TimeoutError,
        NotOpenError
    };

public:
    virtual QString getConnectionInfo() = 0;
    virtual QString getConnectTypeNmae() = 0;
    virtual QString getValveAddr() = 0;
    virtual QStringList searchDevice(QList<SerialConnectionOpt>connList, QString cmd, QString value, QString checkPreFix, int checkLength, QString additionalInfo = "") = 0;
    virtual bool connectValve(QString valveAddr) = 0;
    virtual void disconnectValve() = 0;
    virtual bool sendCmd(QString cmd, QString value, QString checkPreFix, int checkLength, QString & resValue, qint64 timeout, eValveError *oErr = nullptr) = 0;
};

Q_DECLARE_INTERFACE(IValve, "NCPA.IValve/1.0")
#endif // IVALVE_H
