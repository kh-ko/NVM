#ifndef PMVALVEMODEL_H
#define PMVALVEMODEL_H

#include <QObject>
#include <QList>
#include "source/pmmodel/pmvalveitemmodel.h"

class PmValveModel:QObject
{
    Q_OBJECT

public:
    static PmValveModel * getInstance()
    {
        static PmValveModel *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new PmValveModel();
        }

        return mpSelf;
    }

    explicit PmValveModel(QObject *parent = nullptr):QObject(parent)
    {
        initEnumList();
        initItemModel();
    }

private:
    void initEnumList()
    {
        PmEnumListModel * pTemp = nullptr;

        pTemp = new PmEnumListModel("FalseTrue", this);
        pTemp->addPair(0, "False");
        pTemp->addPair(1, "True");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("ClusterConnectionLossReaction", this);
        pTemp->addPair(0, "Close");
        pTemp->addPair(1, "Open");
        pTemp->addPair(2, "Stay");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("NotDisableDisable", this);
        pTemp->addPair(0, "NotDisable");
        pTemp->addPair(1, "Disable");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("SetPointMode", this);
        pTemp->addPair(2, "Position");
        pTemp->addPair(3, "Close");
        pTemp->addPair(4, "Open");
        pTemp->addPair(5, "Pressure Control");
        pTemp->addPair(6, "Hold");
        pTemp->addPair(7, "Learn");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("CtrlMode", this);
        pTemp->addPair(0, "Init");
        pTemp->addPair(1, "Homing");
        pTemp->addPair(2, "Position");
        pTemp->addPair(3, "Close");
        pTemp->addPair(4, "Open");
        pTemp->addPair(5, "Pressure Control");
        pTemp->addPair(6, "Hold");
        pTemp->addPair(7, "Learn");
        pTemp->addPair(8, "Interlock Open");
        pTemp->addPair(9, "Interlock Close");
        pTemp->addPair(12, "Power Failure");
        pTemp->addPair(13, "Safety");
        pTemp->addPair(14, "Error");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("AccMode", this);
        pTemp->addPair(0, "Local");
        pTemp->addPair(1, "Remote");
        pTemp->addPair(2, "Remote Locked");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("NotIsolated", this);
        pTemp->addPair(0, "Not Isolated");
        pTemp->addPair(1, "Isolated");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("ClusterSlaveWarn", this);
        pTemp->addPair(0, "No Learn Data");
        pTemp->addPair(1, "Isolation valve does not work");
        pTemp->addPair(2, "No Sensor Active");
        pTemp->addPair(3, "PFO Not Ready");
        pTemp->addPair(4, "Cluster Slave Offline");
        pTemp->addPair(6, "Fieldbus Data Not Valid");
        pTemp->addPair(7, "Network failure");
        pTemp->addPair(8, "Compressed Air Not Falling when valve close");
        pTemp->addPair(9, "Compressed Air Too Low");
        pTemp->addPair(10, "Compressed Air Too High");
        pTemp->addPair(12, "Fan stall alarm");
        pTemp->addPair(15, "Storing in NV Memory");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("ClusterSlaveErr", this);
        pTemp->addPair(0, "Homing Position Error");
        pTemp->addPair(1, "Homing Not Running");
        pTemp->addPair(2, "Homing Error State");
        pTemp->addPair(3, "Operation Position Error");
        pTemp->addPair(4, "Operation Not Running");
        pTemp->addPair(5, "Operation Error State");
        pTemp->addPair(12, "Other Component");
        pTemp->addPair(30, "General");
        pTemp->addPair(31, "Internal");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("ClusterSlaveConnStatus", this);
        pTemp->addPair(0, "Online");
        pTemp->addPair(1, "Offline");
        mEnumList.append(pTemp);

        pTemp = new PmEnumListModel("ClusterSlaveAirPres", this);
        pTemp->addPair(0, "Ok");
        pTemp->addPair(1, "Not Ok");
        mEnumList.append(pTemp);
    }

    void initItemModel()
    {
        PmValveItemModel * pTemp = nullptr;

        pTemp = new PmValveItemModel("Cluster.Settings.Number of Valves"           , "p:0B200D010000", "p:000B200D010000", "p:01200D010000", "p:0001200D010000", 0, -1, "IntegerInput", "0", "10", nullptr                                  , "", this); mItemList.append(pTemp);
        pTemp = new PmValveItemModel("Cluster.Settings.Cluster Address"            , "p:0B200D020000", "p:000B200D020000", "p:01200D020000", "p:0001200D020000", 0, -1, "IntegerInput", "0", "10", nullptr                                  , "", this); mItemList.append(pTemp);
        pTemp = new PmValveItemModel("Cluster.Settings.Show Address on Display"    , "p:0B200D030000", "p:000B200D030000", "p:01200D030000", "p:0001200D030000", 0, -1, "ComboBox"    ,  "",   "", findEnum("FalseTrue"                    ), "", this); mItemList.append(pTemp);
        pTemp = new PmValveItemModel("Cluster.Settings.Connection Loss Reaction"   , "p:0B200D040000", "p:000B200D040000", "p:01200D040000", "p:0001200D040000", 0, -1, "ComboBox"    ,  "",   "", findEnum("ClusterConnectionLossReaction"), "", this); mItemList.append(pTemp);
        pTemp = new PmValveItemModel("Cluster.Settings.Disable Interlocks of Slave", "p:0B200D050000", "p:000B200D050000", "p:01200D050000", "p:0001200D050000", 0, -1, "ComboBox"    ,  "",   "", findEnum("NotDisableDisable"            ), "", this); mItemList.append(pTemp);

        QStringList temp = {"0E","0F","10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F","20","21","22"};

        for(int i = 0; i < 20; i++)
        {
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Freeze"               ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("010000"), QString("p:000B20%1%2").arg(temp[i]).arg("010000"), QString("p:0120%1%2").arg(temp[i]).arg("010000"), QString("p:0120%1%2").arg(temp[i]).arg("010000"), 0, -1, "ComboBox"     , "", "", findEnum("FalseTrue"             ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Control Mode Setpoint").arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("030000"), QString("p:000B20%1%2").arg(temp[i]).arg("030000"), QString("p:0120%1%2").arg(temp[i]).arg("030000"), QString("p:0120%1%2").arg(temp[i]).arg("030000"), 0, -1, "ComboBox"     , "", "", findEnum("SetPointMode"          ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Control Mode"         ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("040000"), QString("p:000B20%1%2").arg(temp[i]).arg("040000"), QString("p:0120%1%2").arg(temp[i]).arg("040000"), QString("p:0120%1%2").arg(temp[i]).arg("040000"), 0, -1, "LabelComboBox", "", "", findEnum("CtrlMode"              ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Access Mode"          ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("050000"), QString("p:000B20%1%2").arg(temp[i]).arg("050000"), QString("p:0120%1%2").arg(temp[i]).arg("050000"), QString("p:0120%1%2").arg(temp[i]).arg("050000"), 0, -1, "LabelComboBox", "", "", findEnum("AccMode"               ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Target Position"      ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("060000"), QString("p:000B20%1%2").arg(temp[i]).arg("060000"), QString("p:0120%1%2").arg(temp[i]).arg("060000"), QString("p:0120%1%2").arg(temp[i]).arg("060000"), 0, -1, "Posi"         , "", "", nullptr                           , "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Actual Position"      ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("070000"), QString("p:000B20%1%2").arg(temp[i]).arg("070000"), QString("p:0120%1%2").arg(temp[i]).arg("070000"), QString("p:0120%1%2").arg(temp[i]).arg("070000"), 0, -1, "LabelPosi"    , "", "", nullptr                           , "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Isolated"             ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("090000"), QString("p:000B20%1%2").arg(temp[i]).arg("090000"), QString("p:0120%1%2").arg(temp[i]).arg("090000"), QString("p:0120%1%2").arg(temp[i]).arg("090000"), 0, -1, "LabelComboBox", "", "", findEnum("NotIsolated"           ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Warning Bitmap"       ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("0A0000"), QString("p:000B20%1%2").arg(temp[i]).arg("0A0000"), QString("p:0120%1%2").arg(temp[i]).arg("0A0000"), QString("p:0120%1%2").arg(temp[i]).arg("0A0000"), 0, -1, "LabelBitmap"  , "", "", findEnum("ClusterSlaveWarn"      ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Error Bitmap"         ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("0B0000"), QString("p:000B20%1%2").arg(temp[i]).arg("0B0000"), QString("p:0120%1%2").arg(temp[i]).arg("0B0000"), QString("p:0120%1%2").arg(temp[i]).arg("0B0000"), 0, -1, "LabelBitmap"  , "", "", findEnum("ClusterSlaveErr"       ), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Connection Status"    ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("0D0000"), QString("p:000B20%1%2").arg(temp[i]).arg("0D0000"), QString("p:0120%1%2").arg(temp[i]).arg("0D0000"), QString("p:0120%1%2").arg(temp[i]).arg("0D0000"), 0, -1, "LabelComboBox", "", "", findEnum("ClusterSlaveConnStatus"), "", this); mItemList.append(pTemp);
            pTemp = new PmValveItemModel(QString("Cluster.Slave %1.Air Pressure"         ).arg(i), QString("p:0B20%1%2").arg(temp[i]).arg("220000"), QString("p:000B20%1%2").arg(temp[i]).arg("220000"), QString("p:0120%1%2").arg(temp[i]).arg("220000"), QString("p:0120%1%2").arg(temp[i]).arg("220000"), 0, -1, "LabelComboBox", "", "", findEnum("ClusterSlaveAirPres"   ), "", this); mItemList.append(pTemp);
        }
    }

public:
    Q_INVOKABLE PmValveItemModel *findItem(QString path)
    {
        for(int i = 0; i < mItemList.size(); i ++)
        {
            if(path == mItemList[i]->mPath)
            {
                return mItemList[i];
            }
        }

        return nullptr;
    }

    Q_INVOKABLE PmEnumListModel *findEnum(QString name)
    {
        for(int i = 0; i < mEnumList.size(); i ++)
        {
            if(name == mEnumList[i]->Name)
            {
                return mEnumList[i];
            }
        }

        return nullptr;
    }

private:
    QList<PmValveItemModel *> mItemList;
    QList<PmEnumListModel *> mEnumList;
};

#endif // PMVALVEMODEL_H

