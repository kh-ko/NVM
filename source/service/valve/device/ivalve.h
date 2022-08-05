#ifndef IVALVE_H
#define IVALVE_H

#include <QObject>

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
    virtual QStringList searchDevice(QString cmd, QString value, QString checkPreFix, int checkLength, QString additionalInfo = "") = 0;
    virtual bool connectValve(QString valveAddr) = 0;
    virtual void disconnectValve() = 0;
    virtual bool sendCmd(QString cmd, QString value, QString checkPreFix, int checkLength, QString & resValue, qint64 timeout, eValveError *oErr = nullptr) = 0;
};

Q_DECLARE_INTERFACE(IValve, "NCPA.IValve/1.0")
#endif // IVALVE_H
