#ifndef VIEWTAGMANAGER_H
#define VIEWTAGMANAGER_H
#include <QObject>
#include <QList>
#include <QDebug>

#include "source/newmodel/view/tag/viewtagmodel.h"
#include "source/newmodel/protocol/protocolmanager.h"
#include "source/newmodel/view/converter/positionconverter.h"
#include "source/newmodel/view/converter/userpositionconverter.h"
#include "source/newmodel/view/converter/base10tofloatconverter.h"
#include "source/newmodel/view/converter/base36converter.h"

class ViewTagManager:QObject
{
    Q_OBJECT

public:
    static ViewTagManager * getInstance()
    {
        static ViewTagManager *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ViewTagManager();
        }

        return mpSelf;
    }

    explicit ViewTagManager(QObject *parent = nullptr):QObject(parent)
    {
        pProtocolManager = ProtocolManager::getInstance();
        pPosiConvert     = PositionConverter::getInstance();
        pUserPosiConvert = UserPositionConverter::getInstance();
        pBase36Convert   = Base36Converter::getInstance();
        pBase10ToFloatConverter = Base10ToFloatConverter::getInstance();

        initEnumList();
        InitializeTag();
        ProcMatchProtocol();
    }

    ViewTagModel * CopyTag(QObject * parent, QString fullPath)
    {
        foreach(ViewTagModel * src, TagList)
        {
            if(fullPath == src->Path)
            {
                return src->CopyTo(parent);
            }
        }

        return nullptr;
    }

    ViewTagModel * GetTag(QString fullPath)
    {
        foreach(ViewTagModel * src, TagList)
        {
            if(fullPath == src->Path)
            {
                return src;
            }
        }

        return nullptr;
    }

private:
    QList<ViewTagModel *> TagList;
    QList<TagEnumListModel *> EnumList;
    ProtocolManager * pProtocolManager;
    PositionConverter * pPosiConvert;
    UserPositionConverter * pUserPosiConvert;
    Base36Converter * pBase36Convert;
    Base10ToFloatConverter * pBase10ToFloatConverter;

    void initEnumList()
    {
        TagEnumListModel * pTemp = nullptr;

        pTemp = new TagEnumListModel("FalseTrue", this);
        pTemp->addPair(0, "False");
        pTemp->addPair(1, "True");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("FresszeStatus", this);
        pTemp->addPair(0, "No Fressze");
        pTemp->addPair(1, "Fressze");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("ClusterConnectionLossReaction", this);
        pTemp->addPair(0, "Close");
        pTemp->addPair(1, "Open");
        pTemp->addPair(2, "Stay");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("NotDisableDisable", this);
        pTemp->addPair(0, "NotDisable");
        pTemp->addPair(1, "Disable");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("SetPointMode", this);
        pTemp->addPair(2, "Position");
        pTemp->addPair(3, "Close");
        pTemp->addPair(4, "Open");
        pTemp->addPair(5, "Pressure Control");
        pTemp->addPair(6, "Hold");
        pTemp->addPair(7, "Learn");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("CtrlMode", this);
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
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("CtrlModeSetPoint", this);
        pTemp->addPair(2, "Position");
        pTemp->addPair(3, "Close");
        pTemp->addPair(4, "Open");
        pTemp->addPair(5, "Pressure Control");
        pTemp->addPair(6, "Hold");
        pTemp->addPair(7, "Learn");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("AccMode", this);
        pTemp->addPair(0, "Local");
        pTemp->addPair(1, "Remote");
        pTemp->addPair(2, "Remote Locked");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("NotIsolated", this);
        pTemp->addPair(0, "Not Isolated");
        pTemp->addPair(1, "Isolated");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("ClusterSlaveWarn", this);
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
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("ClusterSlaveErr", this);
        pTemp->addPair(0, "Homing Position Error");
        pTemp->addPair(1, "Homing Not Running");
        pTemp->addPair(2, "Homing Error State");
        pTemp->addPair(3, "Operation Position Error");
        pTemp->addPair(4, "Operation Not Running");
        pTemp->addPair(5, "Operation Error State");
        pTemp->addPair(12, "Other Component");
        pTemp->addPair(30, "General");
        pTemp->addPair(31, "Internal");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("ClusterSlaveConnStatus", this);
        pTemp->addPair(0, "Online");
        pTemp->addPair(1, "Offline");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("ClusterSlaveAirPres", this);
        pTemp->addPair(0, "Ok");
        pTemp->addPair(1, "Not Ok");
        EnumList.append(pTemp);
    }

    void InitializeTag()
    {
        ViewTagModel * pTemp = nullptr;

        pTemp = new ViewTagModel("Cluster.Master.Settings.Number of Valves"               , "IntegerInput", nullptr                                  , this); TagList.append(pTemp);
        pTemp = new ViewTagModel("Cluster.Master.Settings.Cluster Address"                , "IntegerInput", nullptr                                  , this); TagList.append(pTemp);
        pTemp = new ViewTagModel("Cluster.Master.Settings.Show Address on Display"        , "ComboBox"    , FindEnum("FalseTrue"                    ), this); TagList.append(pTemp);
        pTemp = new ViewTagModel("Cluster.Master.Settings.Connection Loss Reaction"       , "ComboBox"    , FindEnum("ClusterConnectionLossReaction"), this); TagList.append(pTemp);
        pTemp = new ViewTagModel("Cluster.Master.Settings.Disable Interlocks of Slave"    , "ComboBox"    , FindEnum("NotDisableDisable"            ), this); TagList.append(pTemp);

        for(int i = 1; i < 31; i ++)  // i = 0 은 Master 이므로 의미 없음
        {
            pTemp = new ViewTagModel(QString("Cluster.Slave.Settings.Device %1 Restart Controller"       ).arg(i), "ComboBox"     , FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Settings.Device %1 Target Position"          ).arg(i), "FloatInput"   , nullptr                     , this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Settings.Device %1 Position Offset"          ).arg(i), "FloatInput"   , nullptr                     , this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Settings.Device %1 Speed Position Control"   ).arg(i), "IntegerInput" , nullptr                     , this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Settings.Device %1 Freeze"                   ).arg(i), "ComboBox"     , FindEnum("FresszeStatus"   ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint"    ).arg(i), "ComboBox"     , FindEnum("CtrlModeSetPoint"), this); TagList.append(pTemp);

            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Actual Position"            ).arg(i), "LabelInteger" , nullptr                     , this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Access Mode"                ).arg(i), "LabelComboBox", FindEnum("AccMode"         ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Control Mode"               ).arg(i), "LabelComboBox", FindEnum("CtrlMode"        ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Service Reqeust"            ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Parameter Error"            ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 PFO Not Fully Charged"      ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Compressed Air Failure"     ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Sensor Factor Warning"      ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Offline Mode"               ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 ROM Error"                  ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 No Interface Found"         ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 No ADC Signal"              ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 No ADC Siganl On Logic"     ).arg(i), "LabelComboBox", FindEnum("FalseTrue"       ), this); TagList.append(pTemp);
            pTemp = new ViewTagModel(QString("Cluster.Slave.Status.Device %1 Compressed Air Value(mbar)" ).arg(i), "LabelCompAir" , nullptr                     , this); TagList.append(pTemp);
        }
    }

    void ProcMatchProtocol()
    {
        ProtocolModel * pWProtocol;
        ProtocolModel * pRProtocol;

        pRProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Number of Valves", "Read" );
        pWProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Number of Valves", "Write");
        pRProtocol->SetTag(GetTag("Cluster.Master.Settings.Number of Valves"), 16, -1, nullptr, 1);
        pWProtocol->SetTag(GetTag("Cluster.Master.Settings.Number of Valves"), 14, -1, nullptr, 1);

        pRProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Cluster Address", "Read" );
        pWProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Cluster Address", "Write");
        pRProtocol->SetTag(GetTag("Cluster.Master.Settings.Cluster Address"), 16, -1, nullptr, 1);
        pWProtocol->SetTag(GetTag("Cluster.Master.Settings.Cluster Address"), 14, -1, nullptr, 1);

        pRProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Show Address on Display", "Read" );
        pWProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Show Address on Display", "Write");
        pRProtocol->SetTag(GetTag("Cluster.Master.Settings.Show Address on Display"), 16, -1, nullptr, 1);
        pWProtocol->SetTag(GetTag("Cluster.Master.Settings.Show Address on Display"), 14, -1, nullptr, 1);

        pRProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Connection Loss Reaction", "Read" );
        pWProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Connection Loss Reaction", "Write");
        pRProtocol->SetTag(GetTag("Cluster.Master.Settings.Connection Loss Reaction"), 16, -1, nullptr, 1);
        pWProtocol->SetTag(GetTag("Cluster.Master.Settings.Connection Loss Reaction"), 14, -1, nullptr, 1);

        pRProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Disable Interlocks of Slave", "Read" );
        pWProtocol = pProtocolManager->FindProtocol("Cluster.Master.Settings.Disable Interlocks of Slave", "Write");
        pRProtocol->SetTag(GetTag("Cluster.Master.Settings.Disable Interlocks of Slave"), 16, -1, nullptr, 1);
        pWProtocol->SetTag(GetTag("Cluster.Master.Settings.Disable Interlocks of Slave"), 14, -1, nullptr, 1);

        for(int i = 1; i < 31; i ++) // i = 0 은 Master 이므로 의미 없음
        {
            pRProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Restart Controller").arg(i), "Read" );
            pWProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Restart Controller").arg(i), "Write");
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Restart Controller").arg(i)), 16, -1, nullptr, 1);
            pWProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Restart Controller").arg(i)), 14, -1, nullptr, 1);

            pRProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Target Position").arg(i), "Read" );
            pWProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Target Position").arg(i), "Write");
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Target Position").arg(i)), 16, -1, pUserPosiConvert, 1);
            pWProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Target Position").arg(i)), 14, -1, pUserPosiConvert, 1);

            pRProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint").arg(i), "Read" );
            pWProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint").arg(i), "Write");
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint").arg(i)), 16, -1, nullptr, 1);
            pWProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Control Mode SetPoint").arg(i)), 14, -1, nullptr, 1);

            pRProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Status.Device %1").arg(i), "Read" );
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Actual Position"           ).arg(i)),  6, 6, pPosiConvert  , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Position Offset"         ).arg(i)), 12, 6, pPosiConvert  , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Speed Position Control"  ).arg(i)), 18, 4, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Freeze"                  ).arg(i)), 22, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Access Mode"               ).arg(i)), 23, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Control Mode"              ).arg(i)), 24, 1, pBase36Convert, 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Service Reqeust"           ).arg(i)), 25, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Parameter Error"           ).arg(i)), 26, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 PFO Not Fully Charged"     ).arg(i)), 27, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Compressed Air Failure"    ).arg(i)), 28, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Sensor Factor Warning"     ).arg(i)), 29, 1, nullptr       , 1);
            // 30, reserved
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Offline Mode"              ).arg(i)), 31, 1, nullptr       , 1);
            // 31, reserved
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 ROM Error"                 ).arg(i)), 33, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 No Interface Found"        ).arg(i)), 34, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 No ADC Signal"             ).arg(i)), 35, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 No ADC Siganl On Logic"    ).arg(i)), 36, 1, nullptr       , 1);
            pRProtocol->SetTag(GetTag(QString("Cluster.Slave.Status.Device %1 Compressed Air Value(mbar)").arg(i)), 41, 6, pBase10ToFloatConverter, 10);

            pWProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Position Offset").arg(i), "Write");
            pWProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Position Offset").arg(i)), 14, -1, pUserPosiConvert, 1);

            pWProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Speed Position Control").arg(i), "Write");
            pWProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Speed Position Control").arg(i)), 14, -1, nullptr, 1);


            pWProtocol = pProtocolManager->FindProtocol(QString("Cluster.Slave.Settings.Device %1 Freeze" ).arg(i), "Write");
            pWProtocol->SetTag(GetTag(QString("Cluster.Slave.Settings.Device %1 Freeze").arg(i)), 14, -1, nullptr, 1);
        }

    }

    TagEnumListModel * FindEnum(QString name)
    {
        foreach (TagEnumListModel * pEnum, EnumList) {
            if(pEnum->Name == name)
            {
                return pEnum;
            }
        }

        return nullptr;
    }
};
#endif // VIEWTAGMANAGER_H
