#ifndef PROTOCOLMANAGER_H
#define PROTOCOLMANAGER_H
#include <QObject>
#include <QList>

#include "source/newmodel/protocol/protocolmodel.h"

class ProtocolManager:QObject
{
    Q_OBJECT
public:
    static ProtocolManager * getInstance()
    {
        static ProtocolManager *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ProtocolManager();
        }

        return mpSelf;
    }

    explicit ProtocolManager(QObject *parent = nullptr):QObject(parent)
    {
        ProtocolModel * protocol;

        protocol = new ProtocolModel("Cluster.Master.Settings.Number of Valves"           , "Read" , "p:0B200D010000", "p:000B200D010000", this); protocolList.append(protocol);
        protocol = new ProtocolModel("Cluster.Master.Settings.Number of Valves"           , "Write", "p:01200D010000", "p:0001200D010000", this); protocolList.append(protocol);

        protocol = new ProtocolModel("Cluster.Master.Settings.Cluster Address"            , "Read" , "p:0B200D020000", "p:000B200D020000", this); protocolList.append(protocol);
        protocol = new ProtocolModel("Cluster.Master.Settings.Cluster Address"            , "Write", "p:01200D020000", "p:0001200D020000", this); protocolList.append(protocol);

        protocol = new ProtocolModel("Cluster.Master.Settings.Show Address on Display"    , "Read" , "p:0B200D030000", "p:000B200D030000", this); protocolList.append(protocol);
        protocol = new ProtocolModel("Cluster.Master.Settings.Show Address on Display"    , "Write", "p:01200D030000", "p:0001200D030000", this); protocolList.append(protocol);

        protocol = new ProtocolModel("Cluster.Master.Settings.Connection Loss Reaction"   , "Read" , "p:0B200D040000", "p:000B200D040000", this); protocolList.append(protocol);
        protocol = new ProtocolModel("Cluster.Master.Settings.Connection Loss Reaction"   , "Write", "p:01200D040000", "p:0001200D040000", this); protocolList.append(protocol);

        protocol = new ProtocolModel("Cluster.Master.Settings.Disable Interlocks of Slave", "Read" , "p:0B200D050000", "p:000B200D050000", this); protocolList.append(protocol);
        protocol = new ProtocolModel("Cluster.Master.Settings.Disable Interlocks of Slave", "Write", "p:01200D050000", "p:0001200D050000", this); protocolList.append(protocol);

        QStringList slaveCode = {"0E","0F","10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E", "1F", "20","21","22","23","24","25","26","27","28","29","2A","2B"};

        for(int i = 1; i < 31; i ++)
        {
            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Restart Controller"    ).arg(i), "Read" , QString("p:0B20%1%2").arg(slaveCode[i-1], "230000"), QString("p:000B20%1%2").arg(slaveCode[i-1], "230000"), this); protocolList.append(protocol);
            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Restart Controller"    ).arg(i), "Write", QString("p:0120%1%2").arg(slaveCode[i-1], "230000"), QString("p:000120%1%2").arg(slaveCode[i-1], "230000"), this); protocolList.append(protocol);

            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Target Position"       ).arg(i), "Read" , QString("p:0B20%1%2").arg(slaveCode[i-1], "060000"), QString("p:000B20%1%2").arg(slaveCode[i-1], "060000"), this); protocolList.append(protocol);
            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Target Position"       ).arg(i), "Write", QString("p:0120%1%2").arg(slaveCode[i-1], "060000"), QString("p:000120%1%2").arg(slaveCode[i-1], "060000"), this); protocolList.append(protocol);

            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint" ).arg(i), "Read" , QString("p:0B20%1%2").arg(slaveCode[i-1], "030000"), QString("p:000B20%1%2").arg(slaveCode[i-1], "030000"), this); protocolList.append(protocol);
            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint" ).arg(i), "Write", QString("p:0120%1%2").arg(slaveCode[i-1], "030000"), QString("p:000120%1%2").arg(slaveCode[i-1], "030000"), this); protocolList.append(protocol);

            protocol = new ProtocolModel(QString("Cluster.Slave.Status.Device %1"                               ).arg(i), "Read" , QString("i:93%1").arg(i, 2, 16, QChar('0'))            , QString("i:93%1").arg(i, 2, 16, QChar('0')), this); protocolList.append(protocol);

            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Position Offset"       ).arg(i), "Write", QString("p:0120%1%2").arg(slaveCode[i-1], "210000"), QString("p:000120%1%2").arg(slaveCode[i-1], "210000"), this); protocolList.append(protocol);
            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Speed Position Control").arg(i), "Write", QString("p:0120%1%2").arg(slaveCode[i-1], "080000"), QString("p:000120%1%2").arg(slaveCode[i-1], "080000"), this); protocolList.append(protocol);
            protocol = new ProtocolModel(QString("Cluster.Slave.Settings.Device %1 Freeze"                ).arg(i), "Write", QString("p:0120%1%2").arg(slaveCode[i-1], "010000"), QString("p:000120%1%2").arg(slaveCode[i-1], "010000"), this); protocolList.append(protocol);
        }
    }

    ProtocolModel * FindProtocol(QString fullPath, QString accType)
    {
        foreach(ProtocolModel * pProtocol, protocolList)
        {
            if(pProtocol->Path == fullPath && pProtocol->AccType == accType)
            {
                return pProtocol;
            }
        }

        return nullptr;
    }

private:
    QList<ProtocolModel *> protocolList;


};
#endif // PROTOCOLMANAGER_H
