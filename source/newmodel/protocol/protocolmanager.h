#ifndef PROTOCOLMANAGER_H
#define PROTOCOLMANAGER_H
#include <QObject>
#include <QList>

#include "source/newmodel/protocol/protocolmodel.h"
#include "source/newmodel/protocol/versionchecker.h"

class ProtocolParamSlotFolder{
public:
    QString Name = "root";
    QList<ProtocolParamSlotFolder *> pFolderList;
    QList<ProtocolParamSlot *> pSlotList;
    QList<TagModel *> pTagList;

    ProtocolParamSlotFolder(){}
    ProtocolParamSlotFolder(QString name){ Name = name; }
    ~ProtocolParamSlotFolder() {
        qDeleteAll(pFolderList);
        pFolderList.clear();
        qDeleteAll(pSlotList);
        pSlotList.clear();
    }

    ProtocolParamSlotFolder * appendFolder(ProtocolParamSlotFolder * pFolder){pFolderList.append(pFolder); return pFolder;}
    void appendSlot(ProtocolParamSlot * pSlot){ if(pSlotList.contains(pSlot)) return; pSlotList.append(pSlot);}
    void appendTag(TagModel * pTag){pTagList.append(pTag);}

    ProtocolParamSlotFolder * createFolder(QString path)
    {
        if (path.isEmpty()) {
            return nullptr;
        }

        QStringList pathParts = path.split('.');
        ProtocolParamSlotFolder *currentFolder = this;

        for(int pathIdx = 0; pathIdx < pathParts.size(); pathIdx++)
        {
            bool found = false;

            QString targetName = pathParts[pathIdx];
            ProtocolParamSlotFolder * subFolder;

            for(int subIdx = 0; subIdx < currentFolder->pFolderList.size(); subIdx++)
            {
                subFolder = currentFolder->pFolderList[subIdx];

                if (subFolder && subFolder->Name == targetName) {
                    // 이름을 찾으면 현재 폴더를 갱신하고 다음 경로로 넘어감
                    currentFolder = subFolder;
                    found = true;
                    break;
                }
            }

            if (!found) {
                ProtocolParamSlotFolder * pNewFolder = new ProtocolParamSlotFolder(targetName);
                currentFolder->appendFolder(pNewFolder);
                currentFolder = pNewFolder;
            }
        }

        return currentFolder;
    }

    ProtocolParamSlotFolder * findFolder(QString path)
    {
        if (path.isEmpty()) {
            return nullptr;
        }

        QStringList pathParts = path.split('.');

        ProtocolParamSlotFolder *currentFolder = this;

        for(int pathIdx = 0; pathIdx < pathParts.size(); pathIdx++)
        {
            QString targetName = pathParts[pathIdx];
            bool found = false;

            for(int subIdx = 0; subIdx < currentFolder->pFolderList.size(); subIdx++)
            {
                ProtocolParamSlotFolder * subFolder = currentFolder->pFolderList[subIdx];

                if (subFolder && subFolder->Name == targetName) {
                    // 이름을 찾으면 현재 폴더를 갱신하고 다음 경로로 넘어감
                    currentFolder = subFolder;
                    found = true;
                    break;
                }
            }

            if (!found) {
                qDebug() << "[" << Q_FUNC_INFO << "]not found path = " << path;
                return nullptr;
            }
        }
        return currentFolder;
    }

    ProtocolParamSlot * findSlot(QString path, QString accType)
    {
        if (path.isEmpty()) return nullptr;

        // 1. 경로 분리
        int lastDotIndex = path.lastIndexOf('.');

        ProtocolParamSlotFolder* targetFolder = this;
        QString slotName = path;

        // 점(.)이 있다면 폴더 경로와 슬롯 이름을 분리
        if (lastDotIndex != -1) {
            QString folderPath = path.left(lastDotIndex); // "abc.dgd"
            slotName = path.mid(lastDotIndex + 1);        // "aaa"

            // 이미 만들어둔 findFolder 함수 재사용!
            targetFolder = this->findFolder(folderPath);
        }

        if (!targetFolder)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]not found path = " << path;
            return nullptr;
        }

        // 2. 해당 폴더에서 슬롯 찾기
        for(int i = 0; i < targetFolder->pSlotList.size(); i ++)
        {
            ProtocolParamSlot *slot = targetFolder->pSlotList[i];

            if (slot->Name == slotName && slot->AccType == accType) {
                return slot;
            }
        }

        qDebug() << "[" << Q_FUNC_INFO << "]not found path = " << path;
        return nullptr;
    }

    TagModel * findTag(QString path)
    {
        if (path.isEmpty()) return nullptr;

        // 1. 경로 분리
        int lastDotIndex = path.lastIndexOf('.');

        ProtocolParamSlotFolder* targetFolder = this;
        QString tagName = path;

        // 점(.)이 있다면 폴더 경로와 슬롯 이름을 분리
        if (lastDotIndex != -1) {
            QString folderPath = path.left(lastDotIndex); // "abc.dgd"
            tagName = path.mid(lastDotIndex + 1);        // "aaa"

            // 이미 만들어둔 findFolder 함수 재사용!
            targetFolder = this->findFolder(folderPath);
        }

        if (!targetFolder)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]not found path = " << path;
            return nullptr;
        }

        // 2. 해당 폴더에서 슬롯 찾기
        for(int i = 0; i < targetFolder->pTagList.size(); i ++)
        {
            TagModel *pTag = targetFolder->pTagList[i];

            if (pTag->Name == tagName) {
                return pTag;
            }
        }

        qDebug() << "[" << Q_FUNC_INFO << "]not found path = " << path;
        return nullptr;
    }
};

class ProtocolManager: QObject
{
    Q_OBJECT
public:
    TagEnumDefine * pEnumDefine;
    ProtocolParamSlotFolder * pRootFolder;
    ProtocolModel * pParamWriteStartProtocol;
    ProtocolModel * pParamWriteEndProtocol;

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
        // param // a:9901 a:9900
        // ID : firmware id, firmware version, serial number : 문자 타입이다...

        pEnumDefine = TagEnumDefine::getInstance();
        pRootFolder = new ProtocolParamSlotFolder("root");
        ProtocolParamSlotFolder * pFolder;

        ProtocolParamSlot * pSlot;
        TagModel *  pTag;

        createICProtocol("Param Write Start", "", "", "a:9901", "a:9901"); pParamWriteStartProtocol = pLastCreateWriteProtocol;
        createICProtocol("Param Write End"  , "", "", "a:9900", "a:9900"); pParamWriteEndProtocol   = pLastCreateWriteProtocol;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// System
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        pFolder = pRootFolder->createFolder("System.Identification.Firmware");

        pTag = createTag("Valve Firmware Version", "RO", TagModel::TypeFirmwareVersion(), nullptr, 0, pFolder);
        createICProtocol("Valve Firmware Version", "i:82", "i:82", "", ""); createSlot("Valve Firmware Version", 4, -1, 0, 0, ProtocolParamSlot::TypeString(), 1, pFolder); setTag(pTag);


        pFolder = pRootFolder->findFolder("System.Identification");
        {
            TagModel * pValveType = createTag("ID: Valve Type"    , "RW", TagModel::TypeEnum(), pEnumDefine->Find("IdValveType"), 0, pFolder);
            TagModel * pValveRev1 = createTag("Valve Revision (1)", "RW", TagModel::TypeEnum(), pEnumDefine->Find("Base36"     ), 0, pFolder);
            TagModel * pValveRev2 = createTag("Valve Revision (2)", "RW", TagModel::TypeEnum(), pEnumDefine->Find("Base36"     ), 0, pFolder);
            TagModel * pValveRev3 = createTag("Valve Revision (3)", "RW", TagModel::TypeEnum(), pEnumDefine->Find("Base36"     ), 0, pFolder);

            createICProtocol("ID: Valve Type"    , "b:1001", "b:1001", "a:1001", "a:1001"); createSlot(pValveType->Name, 6, 6, 6, 6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(pValveType);
            createICProtocol("Valve Revision (1)", "b:1009", "b:1009", "a:1009", "a:1009"); createSlot(pValveRev1->Name, 6, 6, 6, 6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(pValveRev1);
            createICProtocol("Valve Revision (2)", "b:1010", "b:1010", "a:1010", "a:1010"); createSlot(pValveRev2->Name, 6, 6, 6, 6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(pValveRev2);
            createICProtocol("Valve Revision (3)", "b:1011", "b:1011", "a:1011", "a:1011"); createSlot(pValveRev3->Name, 6, 6, 6, 6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(pValveRev3);
        }


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Interface RS232
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        pFolder = pRootFolder->createFolder("Interface RS232/RS485.Scaling.Position");
        {
            TagModel * posiUnit    = createTag("Position Unit"         , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("PosiScaling"), 0, pFolder);
            TagModel * closestPosi = createTag("Value Closest Position", "RW", TagModel::TypeBase10(), nullptr                         , 0, pFolder);
            TagModel * openPosi    = createTag("Value Open Position"   , "RW", TagModel::TypeBase10(), nullptr                         , 0, pFolder);

            createPMProtocol("RS232 Interface - Posi Scaling Unit", "A1120101", "00", "RW"); createSlot("Position Unit"         , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(posiUnit   );
            createPMProtocol("RS232 Interface - Posi Closest"     , "A1120102", "00", "RW"); createSlot("Value Closest Position", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(closestPosi);
            createPMProtocol("RS232 Interface - Posi Open"        , "A1120103", "00", "RW"); createSlot("Value Open Position"   , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(openPosi   );
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Interface Device Net
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Identity Object.Instance");
        {
            TagModel * sNum    = createTag("Serial Number(Hex)", "RO", TagModel::TypeBase16()      , nullptr                         , 0, pFolder);
            TagModel * pdName  = createTag("Product Name"      , "RO", TagModel::TypeString()      , nullptr                         , 0, pFolder);
            TagModel * rev     = createTag("Revision"          , "RW", TagModel::TypeDNetRevision(), nullptr                         , 0, pFolder);
            TagModel * vId     = createTag("Vendor ID"         , "RW", TagModel::TypeBase10()      , nullptr                         , 0, pFolder);
            TagModel * devType = createTag("Device Type"       , "RW", TagModel::TypeEnum()        , pEnumDefine->Find("DNetDevType"), 0, pFolder);
            TagModel * pdCode  = createTag("Product Code"      , "RW", TagModel::TypeBase10()      , nullptr                         , 0, pFolder);

            createPMProtocol("DNet Serial Number", "A4010106", "00"    , "RO"              ); createSlot("Serial Number", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(sNum   );
            createPMProtocol("DNet Product Name" , "A4010107", "00"    , "RO"              ); createSlot("Product Name" , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeString(), 1, pFolder); setTag(pdName );
            createPMProtocol("DNet Revision"     , "B0000100", "67"    , "RW"              ); createSlot("Revision"     , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(rev    );
            createICProtocol("DNet Vendor ID"    , "b:1025"  , "b:1025", "a:1025", "a:1025"); createSlot("Vendor ID"    ,           6,           6,           6,           6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(vId    );
            createICProtocol("DNet Device Type"  , "b:1034"  , "b:1034", "a:1034", "a:1034"); createSlot("Device Type"  ,           6,           6,           6,           6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(devType);
            createICProtocol("DNet Product Code" , "b:1033"  , "b:1033", "a:1033", "a:1033"); createSlot("Product Code" ,           6,           6,           6,           6, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(pdCode );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.DeviceNet Object.Instance");
        {
            TagModel * macSwitch = createTag("MAC ID Switch", "RO", TagModel::TypeBase10(), nullptr                          , 0, pFolder);
            TagModel * mac       = createTag("MAC ID"       , "RW", TagModel::TypeBase10(), nullptr                          , 0, pFolder);
            TagModel * baudrate  = createTag("Baud Rate"    , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("DNetBaudRate"), 0, pFolder);

            createPMProtocol("DNet MAC ID Switch", "A4030300"  , "00"        , "RO"                    ); createSlot("MAC ID Switch", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(macSwitch);
            createICProtocol("DNet MAC ID"       , "a:72500001", "a:72500001", "a:72500101", "72500101"); createSlot("MAC ID"       ,          10,           2,          10,           2, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(mac      );
            createICProtocol("DNet Baud Rate"    , "a:72500002", "a:72500002", "a:72500102", "72500102"); createSlot("Baud Rate"    ,          10,           2,          10,           2, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(baudrate );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Profile");
        {
            TagModel * profile  = createTag("Profile"  , "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetProfile" ), 0, pFolder);
            TagModel * dataType = createTag("Data Type", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetDataType"), 0, pFolder);

            createPMProtocol("DNet Profile"  , "A4056600", "00","RW"); createSlot("Profile"  , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(profile);
            createPMProtocol("DNet Data Type", "A4056700", "00","RW"); createSlot("Data Type", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(dataType);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Output");
        {
            TagModel * consumedAssy  = createTag("Output IO Consumed Assembly", "RW", TagModel::TypeEnum()  , pEnumDefine->Find("DNetOutputIOConsumedAssy" ), 0, pFolder);
            TagModel * length        = createTag("Output length (Byte)"       , "RO", TagModel::TypeBase10(), nullptr                                       , 0, pFolder); // 20260119 화면에서 실시간 편집 내용으로 표시 하든 안하든 상관 없음. : 김부장님 의견
            TagModel * name          = createTag("Output Name"                , "RO", TagModel::TypeString(), nullptr                                       , 0, pFolder);

            createPMProtocol("DNet Out Consumed Assy", "A4056400", "00", "RW"); createSlot("Output IO Consumed Assembly", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(consumedAssy);
            createPMProtocol("DNet Out Length"       , "A4056100", "00", "RO"); createSlot("Output length (Byte)"       , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(length      );
            createPMProtocol("DNet Out Name  "       , "A4066300", "00", "RO"); createSlot("Output Name"                , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeString(), 1, pFolder); setTag(name        );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1");
        {
            TagModel * ctrlMode          = createTag("Control Model(1)"             , "RW", TagModel::TypeBitmap(), nullptr,  0, pFolder); ctrlMode         ->setLengthInfo(1);
            TagModel * setPointInt       = createTag("Setpoint-INT(2)"              , "RW", TagModel::TypeBitmap(), nullptr,  1, pFolder); setPointInt      ->setLengthInfo(2);
            TagModel * setPointFloat     = createTag("Setpoint-FLOAT(4)"            , "RW", TagModel::TypeBitmap(), nullptr,  2, pFolder); setPointFloat    ->setLengthInfo(4);
            TagModel * setPointType      = createTag("Setpoint type(1)"             , "RW", TagModel::TypeBitmap(), nullptr,  3, pFolder); setPointType     ->setLengthInfo(1);
            TagModel * learn             = createTag("Learn(1)"                     , "RW", TagModel::TypeBitmap(), nullptr,  4, pFolder); learn            ->setLengthInfo(1);
            TagModel * learnPresLimInt   = createTag("Learn pressure limit-INT(2)"  , "RW", TagModel::TypeBitmap(), nullptr,  5, pFolder); learnPresLimInt  ->setLengthInfo(2);
            TagModel * learnPresLimFloat = createTag("Learn pressure limit-FLOAT(4)", "RW", TagModel::TypeBitmap(), nullptr,  6, pFolder); learnPresLimFloat->setLengthInfo(4);
            TagModel * zero              = createTag("Zero(1)"                      , "RW", TagModel::TypeBitmap(), nullptr,  7, pFolder); zero             ->setLengthInfo(1);
            TagModel * presCtrlMode      = createTag("Pressure control mode(1)"     , "RW", TagModel::TypeBitmap(), nullptr,  8, pFolder); presCtrlMode     ->setLengthInfo(1);
            TagModel * writeCtrlParam    = createTag("Write control parameter(1)"   , "RW", TagModel::TypeBitmap(), nullptr,  9, pFolder); writeCtrlParam   ->setLengthInfo(1);
            TagModel * adaptiveGain      = createTag("Adaptive gain(4)"             , "RW", TagModel::TypeBitmap(), nullptr, 10, pFolder); adaptiveGain     ->setLengthInfo(4);
            TagModel * adaptiveSensDelay = createTag("Adaptive sensor delay(4)"     , "RW", TagModel::TypeBitmap(), nullptr, 11, pFolder); adaptiveSensDelay->setLengthInfo(4);
            TagModel * adaptiveRampTime  = createTag("Adaptive ramp time(4)"        , "RW", TagModel::TypeBitmap(), nullptr, 12, pFolder); adaptiveRampTime ->setLengthInfo(4);
            TagModel * adaptiveRampMode  = createTag("Adaptive ramp mode(1)"        , "RW", TagModel::TypeBitmap(), nullptr, 13, pFolder); adaptiveRampMode ->setLengthInfo(1);
            TagModel * fixedPGain        = createTag("Fixed P-gain(4)"              , "RW", TagModel::TypeBitmap(), nullptr, 14, pFolder); fixedPGain       ->setLengthInfo(4);
            TagModel * fixedIGain        = createTag("Fixed I-Gain(4)"              , "RW", TagModel::TypeBitmap(), nullptr, 15, pFolder); fixedIGain       ->setLengthInfo(4);
            TagModel * fixedRampTime     = createTag("Fixed ramp time(4)"           , "RW", TagModel::TypeBitmap(), nullptr, 16, pFolder); fixedRampTime    ->setLengthInfo(4);
            TagModel * fixedRampMode     = createTag("Fixed ramp mode(1)"           , "RW", TagModel::TypeBitmap(), nullptr, 17, pFolder); fixedRampMode    ->setLengthInfo(1);
            TagModel * fixedDir          = createTag("Fixed direction mode(1)"      , "RW", TagModel::TypeBitmap(), nullptr, 18, pFolder); fixedDir         ->setLengthInfo(1);
            TagModel * adaptiveDeltaGain = createTag("Adaptive delta gain(4)"       , "RW", TagModel::TypeBitmap(), nullptr, 19, pFolder); adaptiveDeltaGain->setLengthInfo(4);
            TagModel * calibration       = createTag("Calibration(1)"               , "RW", TagModel::TypeBitmap(), nullptr, 20, pFolder); calibration      ->setLengthInfo(1);
            TagModel * dummy             = createTag("Dummy(1)"                     , "RW", TagModel::TypeBitmap(), nullptr, 21, pFolder); dummy            ->setLengthInfo(1);

            createICProtocol("DNet Out Assembly v1", "a:72500004", "a:72500004", "a:72500104", "a:72500104"); createSlot("DNet Out Assembly v1", 10, 8, 10, 8, ProtocolParamSlot::TypeBase16()  , 1, pFolder);
            setTag(ctrlMode         );
            setTag(setPointInt      );
            setTag(setPointFloat    );
            setTag(setPointType     );
            setTag(learn            );
            setTag(learnPresLimInt  );
            setTag(learnPresLimFloat);
            setTag(zero             );
            setTag(presCtrlMode     );
            setTag(writeCtrlParam   );
            setTag(adaptiveGain     );
            setTag(adaptiveSensDelay);
            setTag(adaptiveRampTime );
            setTag(adaptiveRampMode );
            setTag(fixedPGain       );
            setTag(fixedIGain       );
            setTag(fixedRampTime    );
            setTag(fixedRampMode    );
            setTag(fixedDir         );
            setTag(adaptiveDeltaGain);
            setTag(calibration      );
            setTag(dummy            );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Output");
        {
            TagModel * selector01 = createTag("Output Selector 01", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector02 = createTag("Output Selector 02", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector03 = createTag("Output Selector 03", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector04 = createTag("Output Selector 04", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector05 = createTag("Output Selector 05", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector06 = createTag("Output Selector 06", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector07 = createTag("Output Selector 07", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector08 = createTag("Output Selector 08", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector09 = createTag("Output Selector 09", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector10 = createTag("Output Selector 10", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector11 = createTag("Output Selector 11", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector12 = createTag("Output Selector 12", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector13 = createTag("Output Selector 13", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector14 = createTag("Output Selector 14", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector15 = createTag("Output Selector 15", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector16 = createTag("Output Selector 16", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector17 = createTag("Output Selector 17", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector18 = createTag("Output Selector 18", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector19 = createTag("Output Selector 19", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);
            TagModel * selector20 = createTag("Output Selector 20", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetOutputSelector"),  0, pFolder);

            createPMProtocol("DNet Out Selector 01", "A4066500", "00", "RW"); createSlot(selector01->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector01);
            createPMProtocol("DNet Out Selector 02", "A4066500", "01", "RW"); createSlot(selector02->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector02);
            createPMProtocol("DNet Out Selector 03", "A4066500", "02", "RW"); createSlot(selector03->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector03);
            createPMProtocol("DNet Out Selector 04", "A4066500", "03", "RW"); createSlot(selector04->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector04);
            createPMProtocol("DNet Out Selector 05", "A4066500", "04", "RW"); createSlot(selector05->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector05);
            createPMProtocol("DNet Out Selector 06", "A4066500", "05", "RW"); createSlot(selector06->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector06);
            createPMProtocol("DNet Out Selector 07", "A4066500", "06", "RW"); createSlot(selector07->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector07);
            createPMProtocol("DNet Out Selector 08", "A4066500", "07", "RW"); createSlot(selector08->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector08);
            createPMProtocol("DNet Out Selector 09", "A4066500", "08", "RW"); createSlot(selector09->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector09);
            createPMProtocol("DNet Out Selector 10", "A4066500", "09", "RW"); createSlot(selector10->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector10);
            createPMProtocol("DNet Out Selector 11", "A4066500", "10", "RW"); createSlot(selector11->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector11);
            createPMProtocol("DNet Out Selector 12", "A4066500", "11", "RW"); createSlot(selector12->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector12);
            createPMProtocol("DNet Out Selector 13", "A4066500", "12", "RW"); createSlot(selector13->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector13);
            createPMProtocol("DNet Out Selector 14", "A4066500", "13", "RW"); createSlot(selector14->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector14);
            createPMProtocol("DNet Out Selector 15", "A4066500", "14", "RW"); createSlot(selector15->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector15);
            createPMProtocol("DNet Out Selector 16", "A4066500", "15", "RW"); createSlot(selector16->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector16);
            createPMProtocol("DNet Out Selector 17", "A4066500", "16", "RW"); createSlot(selector17->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector17);
            createPMProtocol("DNet Out Selector 18", "A4066500", "17", "RW"); createSlot(selector18->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector18);
            createPMProtocol("DNet Out Selector 19", "A4066500", "18", "RW"); createSlot(selector19->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector19);
            createPMProtocol("DNet Out Selector 20", "A4066500", "19", "RW"); createSlot(selector20->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector20);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Input");
        {
            TagModel * consumedAssy  = createTag("Input IO Produced Assembly", "RW", TagModel::TypeEnum()  , pEnumDefine->Find("DNetInputIOProducedAssy"), 0, pFolder);
            TagModel * length        = createTag("Input length (Byte)"       , "RO", TagModel::TypeBase10(), nullptr                                     , 0, pFolder); // 20260119 화면에서 실시간 편집 내용으로 표시 하든 안하든 상관 없음. : 김부장님 의견
            TagModel * name          = createTag("Input Name"                , "RO", TagModel::TypeString(), nullptr                                     , 0, pFolder);

            createPMProtocol("DNet In Produced Assy", "A4056500", "00", "RW"); createSlot("Input IO Produced Assembly", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(consumedAssy);
            createPMProtocol("DNet In Length"       , "A4056200", "00", "RO"); createSlot("Input length (Byte)"       , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(length      );
            createPMProtocol("DNet In Name  "       , "A4066400", "00", "RO"); createSlot("Input Name"                , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeString(), 1, pFolder); setTag(name        );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1");
        {
            TagModel * exStatus              = createTag("Exception Status(1)"               , "RW", TagModel::TypeBitmap(), nullptr,  0, pFolder); exStatus             ->setLengthInfo( 1);
            TagModel * presInt               = createTag("Pressure-INT(2)"                   , "RW", TagModel::TypeBitmap(), nullptr,  1, pFolder); presInt              ->setLengthInfo( 2);
            TagModel * presFloat             = createTag("Pressure-FLOAT(4)"                 , "RW", TagModel::TypeBitmap(), nullptr,  2, pFolder); presFloat            ->setLengthInfo( 4);
            TagModel * setPointInt           = createTag("Setpoint-INT(2)"                   , "RW", TagModel::TypeBitmap(), nullptr,  3, pFolder); setPointInt          ->setLengthInfo( 2);
            TagModel * setPointFloat         = createTag("Setpoint-FLOAT(4)"                 , "RW", TagModel::TypeBitmap(), nullptr,  4, pFolder); setPointFloat        ->setLengthInfo( 4);
            TagModel * posiInt               = createTag("Position-INT(2)"                   , "RW", TagModel::TypeBitmap(), nullptr,  5, pFolder); posiInt              ->setLengthInfo( 2);
            TagModel * posiFloat             = createTag("Position-FLOAT(4)"                 , "RW", TagModel::TypeBitmap(), nullptr,  6, pFolder); posiFloat            ->setLengthInfo( 4);
            TagModel * exDetailAlarm         = createTag("Exception Detail Alarm(15)"        , "RW", TagModel::TypeBitmap(), nullptr,  7, pFolder); exDetailAlarm        ->setLengthInfo(15);
            TagModel * exDetailWarn          = createTag("Exception Detail Warning(15)"      , "RW", TagModel::TypeBitmap(), nullptr,  8, pFolder); exDetailWarn         ->setLengthInfo(15);
            TagModel * valveCloseOpenCheck   = createTag("Valve Close/Open Check(1)"         , "RW", TagModel::TypeBitmap(), nullptr,  9, pFolder); valveCloseOpenCheck  ->setLengthInfo( 1);
            TagModel * devStatus2            = createTag("Device Status 2(1)"                , "RW", TagModel::TypeBitmap(), nullptr, 10, pFolder); devStatus2           ->setLengthInfo( 1);
            TagModel * accMode               = createTag("Access Mode(1)"                    , "RW", TagModel::TypeBitmap(), nullptr, 11, pFolder); accMode              ->setLengthInfo( 1);
            TagModel * presCtrlMode          = createTag("Pressure control Mode(1)"          , "RW", TagModel::TypeBitmap(), nullptr, 12, pFolder); presCtrlMode         ->setLengthInfo( 1);
            TagModel * writeCtrlParamAnalyze = createTag("Write Control Parameter Analyze(1)", "RW", TagModel::TypeBitmap(), nullptr, 13, pFolder); writeCtrlParamAnalyze->setLengthInfo( 1);
            TagModel * adaptiveGain          = createTag("Adaptive Gain(4)"                  , "RW", TagModel::TypeBitmap(), nullptr, 14, pFolder); adaptiveGain         ->setLengthInfo( 4);
            TagModel * adaptiveSensDelay     = createTag("Adaptive Sensor Delay(4)"          , "RW", TagModel::TypeBitmap(), nullptr, 15, pFolder); adaptiveSensDelay    ->setLengthInfo( 4);
            TagModel * adaptiveRampTime      = createTag("Adaptive Ramp Time(4)"             , "RW", TagModel::TypeBitmap(), nullptr, 16, pFolder); adaptiveRampTime     ->setLengthInfo( 4);
            TagModel * adaptiveRampMode      = createTag("Adaptive Ramp Mode(1)"             , "RW", TagModel::TypeBitmap(), nullptr, 17, pFolder); adaptiveRampMode     ->setLengthInfo( 1);
            TagModel * fixedPGain            = createTag("Fixed P-Gain(4)"                   , "RW", TagModel::TypeBitmap(), nullptr, 18, pFolder); fixedPGain           ->setLengthInfo( 4);
            TagModel * fixedIGain            = createTag("Fixed I-Gain(4)"                   , "RW", TagModel::TypeBitmap(), nullptr, 19, pFolder); fixedIGain           ->setLengthInfo( 4);
            TagModel * fixedRampTime         = createTag("Fixed Ramp Time(4)"                , "RW", TagModel::TypeBitmap(), nullptr, 20, pFolder); fixedRampTime        ->setLengthInfo( 4);
            TagModel * fixedRampMode         = createTag("Fixed Ramp Mode(1)"                , "RW", TagModel::TypeBitmap(), nullptr, 21, pFolder); fixedRampMode        ->setLengthInfo( 1);
            TagModel * fixedDir              = createTag("Fixed Direction Mode(1)"           , "RW", TagModel::TypeBitmap(), nullptr, 22, pFolder); fixedDir             ->setLengthInfo( 1);
            TagModel * adaptiveDeltaGain     = createTag("Adaptive Delta Gain(4)"            , "RW", TagModel::TypeBitmap(), nullptr, 23, pFolder); adaptiveDeltaGain    ->setLengthInfo( 4);
            TagModel * sens1PresInt          = createTag("Sensor1 Pressure-INT(2)"           , "RW", TagModel::TypeBitmap(), nullptr, 24, pFolder); sens1PresInt         ->setLengthInfo( 2);
            TagModel * sens1PresFloat        = createTag("Sensor1 Pressure-FLOAT(4)"         , "RW", TagModel::TypeBitmap(), nullptr, 25, pFolder); sens1PresFloat       ->setLengthInfo( 4);
            TagModel * sens2PresInt          = createTag("Sensor2 Pressure-INT(2)"           , "RW", TagModel::TypeBitmap(), nullptr, 26, pFolder); sens2PresInt         ->setLengthInfo( 2);
            TagModel * sens2PresFloat        = createTag("Sensor2 Pressure-FLOAT(4)"         , "RW", TagModel::TypeBitmap(), nullptr, 27, pFolder); sens2PresFloat       ->setLengthInfo( 4);
            TagModel * dummy                 = createTag("Dummy(1)"                          , "RW", TagModel::TypeBitmap(), nullptr, 28, pFolder); dummy                ->setLengthInfo( 1);

            createICProtocol("DNet In Assembly v1", "a:72500005", "a:72500005", "a:72500105", "a:72500105"); createSlot("DNet In Assembly v1", 10, 8, 10, 8, ProtocolParamSlot::TypeBase16()  , 1, pFolder);
            setTag(exStatus             );
            setTag(presInt              );
            setTag(presFloat            );
            setTag(setPointInt          );
            setTag(setPointFloat        );
            setTag(posiInt              );
            setTag(posiFloat            );
            setTag(exDetailAlarm        );
            setTag(exDetailWarn         );
            setTag(valveCloseOpenCheck  );
            setTag(devStatus2           );
            setTag(accMode              );
            setTag(presCtrlMode         );
            setTag(writeCtrlParamAnalyze);
            setTag(adaptiveGain         );
            setTag(adaptiveSensDelay    );
            setTag(adaptiveRampTime     );
            setTag(adaptiveRampMode     );
            setTag(fixedPGain           );
            setTag(fixedIGain           );
            setTag(fixedRampTime        );
            setTag(fixedRampMode        );
            setTag(fixedDir             );
            setTag(adaptiveDeltaGain    );
            setTag(sens1PresInt         );
            setTag(sens1PresFloat       );
            setTag(sens2PresInt         );
            setTag(sens2PresFloat       );
            setTag(dummy                );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Object.Input");
        {
            TagModel * selector01 = createTag("Input Selector 01", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector02 = createTag("Input Selector 02", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector03 = createTag("Input Selector 03", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector04 = createTag("Input Selector 04", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector05 = createTag("Input Selector 05", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector06 = createTag("Input Selector 06", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector07 = createTag("Input Selector 07", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector08 = createTag("Input Selector 08", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector09 = createTag("Input Selector 09", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector10 = createTag("Input Selector 10", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector11 = createTag("Input Selector 11", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector12 = createTag("Input Selector 12", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector13 = createTag("Input Selector 13", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector14 = createTag("Input Selector 14", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector15 = createTag("Input Selector 15", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector16 = createTag("Input Selector 16", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector17 = createTag("Input Selector 17", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector18 = createTag("Input Selector 18", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector19 = createTag("Input Selector 19", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);
            TagModel * selector20 = createTag("Input Selector 20", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetInputSelector"),  0, pFolder);

            createPMProtocol("DNet In Selector 01", "A4066600", "00", "RW"); createSlot(selector01->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector01);
            createPMProtocol("DNet In Selector 02", "A4066600", "01", "RW"); createSlot(selector02->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector02);
            createPMProtocol("DNet In Selector 03", "A4066600", "02", "RW"); createSlot(selector03->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector03);
            createPMProtocol("DNet In Selector 04", "A4066600", "03", "RW"); createSlot(selector04->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector04);
            createPMProtocol("DNet In Selector 05", "A4066600", "04", "RW"); createSlot(selector05->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector05);
            createPMProtocol("DNet In Selector 06", "A4066600", "05", "RW"); createSlot(selector06->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector06);
            createPMProtocol("DNet In Selector 07", "A4066600", "06", "RW"); createSlot(selector07->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector07);
            createPMProtocol("DNet In Selector 08", "A4066600", "07", "RW"); createSlot(selector08->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector08);
            createPMProtocol("DNet In Selector 09", "A4066600", "08", "RW"); createSlot(selector09->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector09);
            createPMProtocol("DNet In Selector 10", "A4066600", "09", "RW"); createSlot(selector10->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector10);
            createPMProtocol("DNet In Selector 11", "A4066600", "10", "RW"); createSlot(selector11->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector11);
            createPMProtocol("DNet In Selector 12", "A4066600", "11", "RW"); createSlot(selector12->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector12);
            createPMProtocol("DNet In Selector 13", "A4066600", "12", "RW"); createSlot(selector13->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector13);
            createPMProtocol("DNet In Selector 14", "A4066600", "13", "RW"); createSlot(selector14->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector14);
            createPMProtocol("DNet In Selector 15", "A4066600", "14", "RW"); createSlot(selector15->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector15);
            createPMProtocol("DNet In Selector 16", "A4066600", "15", "RW"); createSlot(selector16->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector16);
            createPMProtocol("DNet In Selector 17", "A4066600", "16", "RW"); createSlot(selector17->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector17);
            createPMProtocol("DNet In Selector 18", "A4066600", "17", "RW"); createSlot(selector18->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector18);
            createPMProtocol("DNet In Selector 19", "A4066600", "18", "RW"); createSlot(selector19->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector19);
            createPMProtocol("DNet In Selector 20", "A4066600", "19", "RW"); createSlot(selector20->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(selector20);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Scaling.Output");
        {
            TagModel * posiUnit  = createTag("Position Setpoint Unit"        , "RW", TagModel::TypeEnum() , pEnumDefine->Find("DNetPosiUnit"),  0, pFolder);
            TagModel * posiGain  = createTag("Position Setpoint Gain"        , "RW", TagModel::TypeFloat(), nullptr,  0, pFolder);
            TagModel * presUnit  = createTag("Pressure Setpoint Unit"        , "RW", TagModel::TypeEnum() , pEnumDefine->Find("DNetPresUnit"),  0, pFolder);
            TagModel * sens1Gain = createTag("Pressure Setpoint Sensor1 Gain", "RW", TagModel::TypeFloat(), nullptr,  0, pFolder);
            TagModel * sens2Gain = createTag("Pressure Setpoint Sensor2 Gain", "RW", TagModel::TypeFloat(), nullptr,  0, pFolder);

            createICProtocol("DNet Position Setpoint Unit"        , "a:7250001B", "a:7250001B", "a:7250011B", "a:7250011B"); createSlot(posiUnit ->Name, 10, 4, 10, 4, ProtocolParamSlot::TypeBase16()  , 1, pFolder); setTag(posiUnit );
            createICProtocol("DNet Position Setpoint Gain"        , "a:7250001F", "a:7250001F", "a:7250011F", "a:7250011F"); createSlot(posiGain ->Name, 10, 8, 10, 8, ProtocolParamSlot::TypeBaseFHex(), 1, pFolder); setTag(posiGain );
            createICProtocol("DNet Pressure Setpoint Unit"        , "a:7250001A", "a:7250001A", "a:7250011A", "a:7250011A"); createSlot(presUnit ->Name, 10, 4, 10, 4, ProtocolParamSlot::TypeBase16()  , 1, pFolder); setTag(presUnit );
            createICProtocol("DNet Pressure Setpoint Sensor1 Gain", "a:7250001D", "a:7250001D", "a:7250011D", "a:7250011D"); createSlot(sens1Gain->Name, 10, 8, 10, 8, ProtocolParamSlot::TypeBaseFHex(), 1, pFolder); setTag(sens1Gain);
            createICProtocol("DNet Pressure Setpoint Sensor2 Gain", "a:7250001E", "a:7250001E", "a:7250011E", "a:7250011E"); createSlot(sens2Gain->Name, 10, 8, 10, 8, ProtocolParamSlot::TypeBaseFHex(), 1, pFolder); setTag(sens2Gain);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Scaling.Input");
        {
            TagModel * posiUnit  = createTag("Position Setpoint Unit"        , "RW", TagModel::TypeEnum() , pEnumDefine->Find("DNetPosiUnit"),  0, pFolder);
            TagModel * posiGain  = createTag("Position Setpoint Gain"        , "RW", TagModel::TypeFloat(), nullptr,  0, pFolder);
            TagModel * presUnit  = createTag("Pressure Setpoint Unit"        , "RW", TagModel::TypeEnum() , pEnumDefine->Find("DNetPresUnit"),  0, pFolder);
            TagModel * sens1Gain = createTag("Pressure Setpoint Sensor1 Gain", "RW", TagModel::TypeFloat(), nullptr,  0, pFolder);
            TagModel * sens2Gain = createTag("Pressure Setpoint Sensor2 Gain", "RW", TagModel::TypeFloat(), nullptr,  0, pFolder);

            createICProtocol("DNet Position Setpoint Unit"        , "a:7250000B", "a:7250000B", "a:7250010B", "a:7250010B"); createSlot(posiUnit ->Name, 10, 4, 10, 4, ProtocolParamSlot::TypeBase16()  , 1, pFolder); setTag(posiUnit );
            createICProtocol("DNet Position Setpoint Gain"        , "a:7250000F", "a:7250000F", "a:7250010F", "a:7250010F"); createSlot(posiGain ->Name, 10, 8, 10, 8, ProtocolParamSlot::TypeBaseFHex(), 1, pFolder); setTag(posiGain );
            createICProtocol("DNet Pressure Setpoint Unit"        , "a:7250000A", "a:7250000A", "a:7250010A", "a:7250010A"); createSlot(presUnit ->Name, 10, 4, 10, 4, ProtocolParamSlot::TypeBase16()  , 1, pFolder); setTag(presUnit );
            createICProtocol("DNet Pressure Setpoint Sensor1 Gain", "a:7250000D", "a:7250000D", "a:7250010D", "a:7250010D"); createSlot(sens1Gain->Name, 10, 8, 10, 8, ProtocolParamSlot::TypeBaseFHex(), 1, pFolder); setTag(sens1Gain);
            createICProtocol("DNet Pressure Setpoint Sensor2 Gain", "a:7250000E", "a:7250000E", "a:7250010E", "a:7250010E"); createSlot(sens2Gain->Name, 10, 8, 10, 8, ProtocolParamSlot::TypeBaseFHex(), 1, pFolder); setTag(sens2Gain);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Connection Loss Reaction");
        {
            TagModel * enable = createTag("Enable"       , "RW", TagModel::TypeEnum(), pEnumDefine->Find("DisableEnable"             ),  0, pFolder);
            TagModel * state  = createTag("State"        , "RO", TagModel::TypeEnum(), pEnumDefine->Find("FalseTrue"                 ),  0, pFolder);
            TagModel * func   = createTag("Functionality", "RW", TagModel::TypeEnum(), pEnumDefine->Find("DNetConnectionLossReaction"),  0, pFolder);

            createPMProtocol("DNet Connection Loss Reaction Enable", "A4710100", "00", "RW"); createSlot(enable->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable);
            createPMProtocol("DNet Connection Loss Reaction State" , "A4710200", "00", "RO"); createSlot(state ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(state );
            createPMProtocol("DNet Connection Loss Reaction Func"  , "A4710300", "00", "RW"); createSlot(func  ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func  );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Identity Object.Services");
        {
            TagModel * profile = createTag("Reset", "RW", TagModel::TypeEnum(), pEnumDefine->Find("FalseTrue"), 0, pFolder);

            createPMProtocol("DNet Reset", "A401F005", "00", "RW"); createSlot("Reset", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(profile);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Input Output.DIO Status");
        {
            TagModel * doStatus = createTag("Digital Out Status", "RO", TagModel::TypeEnum(), pEnumDefine->Find("OffOn"), 0, pFolder);
            TagModel * diStatus = createTag("Digital In Status" , "RO", TagModel::TypeEnum(), pEnumDefine->Find("OffOn"), 0, pFolder);

            createICProtocol("DNet DIO Status", "i:40", "i:40", "", "");
            createSlot("Unknown(1)"  , 4, 1, 0, 0, ProtocolParamSlot::TypeString(), 1, pFolder);
            createSlot(diStatus->Name, 5, 1, 0, 0, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(diStatus);
            createSlot("Unknown(2)"  , 6, 1, 0, 0, ProtocolParamSlot::TypeString(), 1, pFolder);
            createSlot(doStatus->Name, 7, 1, 0, 0, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(doStatus);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Input Output.Digital Output");
        {
            TagModel * enable   = createTag("Enable"       , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("EnableDisable"), 0, pFolder);
            TagModel * func     = createTag("Functionality", "RW", TagModel::TypeEnum()  , pEnumDefine->Find("DOFunc"       ), 0, pFolder);
            TagModel * polarity = createTag("Polarity"     , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("Polarity"     ), 0, pFolder);
            TagModel * dummy    = createTag("dummy"        , "RW", TagModel::TypeString(), nullptr                           , 0, pFolder);

            createICProtocol("DNet Digital Output", "i:2611", "i:2611", "s:2611", "s:2611");
            createSlot(enable->Name    , 6, 1, 6, 1, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable  );
            createSlot(func->Name      , 7, 1, 7, 1, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func    );
            createSlot(polarity->Name  , 8, 1, 8, 1, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(polarity);
            createSlot(dummy->Name     , 9, 3, 8, 3, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(dummy   );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Input Output.Digital Input");
        {
            TagModel * enable   = createTag("Enable"       , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("EnableDisable"), 0, pFolder);
            TagModel * func     = createTag("Functionality", "RW", TagModel::TypeEnum()  , pEnumDefine->Find("DIFunc"       ), 0, pFolder);
            TagModel * polarity = createTag("Polarity"     , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("Polarity"     ), 0, pFolder);
            TagModel * dummy    = createTag("dummy"        , "RW", TagModel::TypeString(), nullptr                           , 0, pFolder);

            createICProtocol("DNet Digital Input", "i:2601", "i:2601", "s:2601", "s:2601");
            createSlot(enable->Name    , 6, 1, 6, 1, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable  );
            createSlot(func->Name      , 7, 1, 7, 1, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func    );
            createSlot(polarity->Name  , 8, 1, 8, 1, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(polarity);
            createSlot(dummy->Name     , 9, 3, 8, 3, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(dummy   );
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Status");
        {
            TagModel * status = createTag("Status", "RO", TagModel::TypeEnum()  , pEnumDefine->Find("CtrlMode"), 0, pFolder);
            createICProtocol("DNet Status", "a:72500008", "a:72500008", "", "");
            createSlot(status->Name, 10, -1, 0, 0, ProtocolParamSlot::TypeBase16(), 1, pFolder); setTag(status);
        }

        pFolder = pRootFolder->createFolder("Interface DeviceNet.Exception Status");
        {
            TagModel * alarmDevComm        = createTag("ALARM/device-common"          , "RO", TagModel::TypeBitmap(), nullptr, 0, pFolder);
            TagModel * alarmDevSpecific    = createTag("ALARM/device-specific"        , "RO", TagModel::TypeBitmap(), nullptr, 1, pFolder);
            TagModel * alarmMenuSpecific   = createTag("ALARM/manufacturer-specific"  , "RO", TagModel::TypeBitmap(), nullptr, 2, pFolder);
            TagModel * warningDevComm      = createTag("WARNING/device-common"        , "RO", TagModel::TypeBitmap(), nullptr, 4, pFolder);
            TagModel * warningDevSpecific  = createTag("WARNING/device-specific"      , "RO", TagModel::TypeBitmap(), nullptr, 5, pFolder);
            TagModel * warningMenuSpecific = createTag("WARNING/manufacturer-specific", "RO", TagModel::TypeBitmap(), nullptr, 6, pFolder);
            TagModel * expandedMode        = createTag("expanded mode"                , "RO", TagModel::TypeBitmap(), nullptr, 7, pFolder);

            createICProtocol("DNet Exception Status", "a:72500009", "a:72500009", "", "");
            createSlot("DNet Exception Status", 10, -1, 0, 0, ProtocolParamSlot::TypeBase16(), 1, pFolder);
            setTag(alarmDevComm       );
            setTag(alarmDevSpecific   );
            setTag(alarmMenuSpecific  );
            setTag(warningDevComm     );
            setTag(warningDevSpecific );
            setTag(warningMenuSpecific);
            setTag(expandedMode       );
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Power Connector IO
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        pFolder = pRootFolder->createFolder("Power Connector IO.Digital Input 1");
        {
            TagModel * enable = createTag("Enable"       , "RW", TagModel::TypeEnum(), pEnumDefine->Find("DisableEnable"), 0, pFolder);
            TagModel * func   = createTag("Functionality", "RW", TagModel::TypeEnum(), pEnumDefine->Find("PowerDIFunc"  ), 0, pFolder);
            TagModel * invert = createTag("Inverted"     , "RW", TagModel::TypeEnum(), pEnumDefine->Find("Polarity"     ), 0, pFolder);
            TagModel * state  = createTag("State"        , "RW", TagModel::TypeEnum(), pEnumDefine->Find("OffOn"        ), 0, pFolder);

            createPMProtocol("Power DIO Input 1 Enable", "37010100", "00", "RW"); createSlot(enable->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable);
            createPMProtocol("Power DIO Input 1 Func"  , "37010300", "00", "RW"); createSlot(func  ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func  );
            createPMProtocol("Power DIO Input 1 Invert", "37010400", "00", "RW"); createSlot(invert->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(invert);
            createPMProtocol("Power DIO Input 1 State" , "37010200", "00", "RO"); createSlot(state ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(state );
        }

        pFolder = pRootFolder->createFolder("Power Connector IO.Digital Input 2");
        {
            TagModel * enable = createTag("Enable"       , "RW", TagModel::TypeEnum(), pEnumDefine->Find("DisableEnable"), 0, pFolder);
            TagModel * func   = createTag("Functionality", "RW", TagModel::TypeEnum(), pEnumDefine->Find("PowerDIFunc"  ), 0, pFolder);
            TagModel * invert = createTag("Inverted"     , "RW", TagModel::TypeEnum(), pEnumDefine->Find("Polarity"     ), 0, pFolder);
            TagModel * state  = createTag("State"        , "RW", TagModel::TypeEnum(), pEnumDefine->Find("OffOn"        ), 0, pFolder);

            createPMProtocol("Power DIO Input 2 Enable", "37020100", "00", "RW"); createSlot(enable->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable);
            createPMProtocol("Power DIO Input 2 Func"  , "37020300", "00", "RW"); createSlot(func  ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func  );
            createPMProtocol("Power DIO Input 2 Invert", "37020400", "00", "RW"); createSlot(invert->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(invert);
            createPMProtocol("Power DIO Input 2 State" , "37020200", "00", "RO"); createSlot(state ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(state );
        }

        pFolder = pRootFolder->createFolder("Power Connector IO.Digital Output 1");
        {
            TagModel * enable = createTag("Enable"       , "RW", TagModel::TypeEnum(), pEnumDefine->Find("DisableEnable"), 0, pFolder);
            TagModel * func   = createTag("Functionality", "RW", TagModel::TypeEnum(), pEnumDefine->Find("PowerDOFunc"  ), 0, pFolder);
            TagModel * invert = createTag("Inverted"     , "RW", TagModel::TypeEnum(), pEnumDefine->Find("Polarity"     ), 0, pFolder);
            TagModel * state  = createTag("State"        , "RW", TagModel::TypeEnum(), pEnumDefine->Find("OffOn"        ), 0, pFolder);

            createPMProtocol("Power DIO Output 1 Enable", "37030100", "00", "RW"); createSlot(enable->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable);
            createPMProtocol("Power DIO Output 1 Func"  , "37030300", "00", "RW"); createSlot(func  ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func  );
            createPMProtocol("Power DIO Output 1 Invert", "37030400", "00", "RW"); createSlot(invert->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(invert);
            createPMProtocol("Power DIO Output 1 State" , "37030200", "00", "RO"); createSlot(state ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(state );
        }

        pFolder = pRootFolder->createFolder("Power Connector IO.Digital Output 2");
        {
            TagModel * enable = createTag("Enable"       , "RW", TagModel::TypeEnum(), pEnumDefine->Find("DisableEnable"), 0, pFolder);
            TagModel * func   = createTag("Functionality", "RW", TagModel::TypeEnum(), pEnumDefine->Find("PowerDOFunc"  ), 0, pFolder);
            TagModel * invert = createTag("Inverted"     , "RW", TagModel::TypeEnum(), pEnumDefine->Find("Polarity"     ), 0, pFolder);
            TagModel * state  = createTag("State"        , "RW", TagModel::TypeEnum(), pEnumDefine->Find("OffOn"        ), 0, pFolder);

            createPMProtocol("Power DIO Output 2 Enable", "37040100", "00", "RW"); createSlot(enable->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(enable);
            createPMProtocol("Power DIO Output 2 Func"  , "37040300", "00", "RW"); createSlot(func  ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(func  );
            createPMProtocol("Power DIO Output 2 Invert", "37040400", "00", "RW"); createSlot(invert->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(invert);
            createPMProtocol("Power DIO Output 2 State" , "37040200", "00", "RO"); createSlot(state ->Name, PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(state );
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Cluster
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        pFolder = pRootFolder->createFolder("Cluster.Master.Settings");
        {
            TagModel * numOfValve  = createTag("Number of Valves"           , "RW", TagModel::TypeBase10(), nullptr                                           , 0, pFolder);
            TagModel * addr        = createTag("Cluster Address"            , "RW", TagModel::TypeBase10(), nullptr                                           , 0, pFolder);
            TagModel * showAddr    = createTag("Show Address on Display"    , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("FalseTrue")                    , 0, pFolder);
            TagModel * reaction    = createTag("Connection Loss Reaction"   , "RW", TagModel::TypeEnum()  , pEnumDefine->Find("ClusterConnectionLossReaction"), 0, pFolder);
            TagModel * disableLock = createTag("Disable Interlocks of Slave", "RW", TagModel::TypeEnum()  , pEnumDefine->Find("NotDisableDisable")            , 0, pFolder);

            createPMProtocol("Cluster Number of Valves"           , "200D0100", "00", "RW"); createSlot("Number of Valves"           , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(numOfValve );
            createPMProtocol("Cluster Cluster Address"            , "200D0200", "00", "RW"); createSlot("Cluster Address"            , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(addr       );
            createPMProtocol("Cluster Show Address on Display"    , "200D0300", "00", "RW"); createSlot("Show Address on Display"    , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(showAddr   );
            createPMProtocol("Cluster Connection Loss Reaction"   , "200D0400", "00", "RW"); createSlot("Connection Loss Reaction"   , PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(reaction   );
            createPMProtocol("Cluster Disable Interlocks of Slave", "200D0500", "00", "RW"); createSlot("Disable Interlocks of Slave", PM_R_OFFSET, PM_R_LENGTH, PM_W_OFFSET, PM_W_LENGTH, ProtocolParamSlot::TypeBase10(), 1, pFolder); setTag(disableLock);
        }

        pFolder = pRootFolder->createFolder("Cluster.Slave.Settings");

        QStringList slaveCode = {"0E","0F","10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E", "1F", "20","21","22","23","24","25","26","27","28","29","2A","2B"};

        for(int i = 1; i < 31; i ++)
        {
            TagModel * resetart     = createTag(QString("Device %1 Restart Controller"        ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * target       = createTag(QString("Device %1 Target Position"           ).arg(i), "RW", TagModel::TypePosi()     , nullptr                               , 0, pFolder);
            TagModel * setpointMode = createTag(QString("Device %1 Control Mode SetPoint"     ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("SetPointMode")     , 0, pFolder);
            TagModel * actual       = createTag(QString("Device %1 Actual Position"           ).arg(i), "RW", TagModel::TypePosi()     , nullptr                               , 0, pFolder);
            TagModel * posiOffset   = createTag(QString("Device %1 Position Offset"           ).arg(i), "RW", TagModel::TypePosi()     , nullptr                               , 0, pFolder);
            TagModel * posiSpeed    = createTag(QString("Device %1 Speed Position Control"    ).arg(i), "RW", TagModel::TypeBase10()   , nullptr                               , 0, pFolder);
            TagModel * fressze      = createTag(QString("Device %1 Freeze"                    ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FresszeStatus")    , 0, pFolder);
            TagModel * accMode      = createTag(QString("Device %1 Access Mode"               ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("AccMode")          , 0, pFolder);
            TagModel * ctrlMode     = createTag(QString("Device %1 Control Mode"              ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("CtrlMode")         , 0, pFolder);
            TagModel * svcRequest   = createTag(QString("Device %1 Service Reqeust"           ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * paramErr     = createTag(QString("Device %1 Parameter Error"           ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * PFOErr       = createTag(QString("Device %1 PFO Not Fully Charged"     ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * airErr       = createTag(QString("Device %1 Compressed Air Failure"    ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * sensErr      = createTag(QString("Device %1 Sensor Factor Warning"     ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
          //TagModel * disableLock  = createTag(QString("Device %1 reserved 1"                ).arg(i), "RW", TagModel::TypeEnum()     , nullptr                               , 0, pFolder);
            TagModel * offline      = createTag(QString("Device %1 Offline Mode"              ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
          //TagModel * addr         = createTag(QString("Device %1 reserved 2"                ).arg(i), "RW", TagModel::TypeBase10()   , nullptr                               , 0, pFolder);
            TagModel * romErr       = createTag(QString("Device %1 ROM Error"                 ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * ifErr        = createTag(QString("Device %1 No Interface Found"        ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * adcErr       = createTag(QString("Device %1 No ADC Signal"             ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
            TagModel * logicErr     = createTag(QString("Device %1 No ADC Siganl On Logic"    ).arg(i), "RW", TagModel::TypeEnum()     , pEnumDefine->Find("FalseTrue")        , 0, pFolder);
          //TagModel * reaction     = createTag(QString("Device %1 reserved 3"                ).arg(i), "RW", TagModel::TypeEnum()     , nullptr                               , 0, pFolder);
            TagModel * airPres      = createTag(QString("Device %1 Compressed Air Value(mbar)").arg(i), "RW", TagModel::TypeFloatGain(), nullptr                               , 0, pFolder);

            QString restartReq    = QString("20%1%2").arg(slaveCode[i-1], "2300");
            QString targetPosiReq = QString("20%1%2").arg(slaveCode[i-1], "0600");
            QString setpointReq   = QString("20%1%2").arg(slaveCode[i-1], "0300");

            createPMProtocol(QString("Cluster %1 Restart"      ).arg(i), restartReq   , "00", "RW");createSlot(resetart->Name    , 16, -1, 14, -1, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(resetart    );
            createPMProtocol(QString("Cluster %1 Target Posi"  ).arg(i), targetPosiReq, "00", "RW");createSlot(target->Name      , 16, -1, 14, -1, ProtocolParamSlot::TypeUserPosi(), 1, pFolder); setTag(target      );
            createPMProtocol(QString("Cluster %1 SetPoint Mode").arg(i), setpointReq  , "00", "RW");createSlot(setpointMode->Name, 16, -1, 14, -1, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(setpointMode);

            createICProtocol(QString("Cluster %1 Status").arg(i), QString("i:93%1").arg(i, 2, 16, QChar('0')), QString("i:93%1").arg(i, 2, 16, QChar('0')), "", "");
            createSlot(actual->Name    ,  6, 6, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(actual    );
            createSlot(posiOffset->Name, 12, 6, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(posiOffset);
            createSlot(posiSpeed->Name , 18, 4, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(posiSpeed );
            createSlot(fressze->Name   , 22, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(fressze   );
            createSlot(accMode->Name   , 23, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(accMode   );
            createSlot(ctrlMode->Name  , 24, 1, 0, 0, ProtocolParamSlot::TypeBase36()  , 1, pFolder); setTag(ctrlMode  );
            createSlot(svcRequest->Name, 25, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(svcRequest);
            createSlot(paramErr->Name  , 26, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(paramErr  );
            createSlot(PFOErr->Name    , 27, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(PFOErr    );
            createSlot(airErr->Name    , 28, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(airErr    );
            createSlot(sensErr->Name   , 29, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(sensErr   );
            createSlot("reserved 1"    , 30, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(nullptr   );
            createSlot(offline->Name   , 31, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(offline   );
            createSlot("reserved 2"    , 32, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(nullptr   );
            createSlot(romErr->Name    , 33, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(romErr    );
            createSlot(ifErr->Name     , 34, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(ifErr     );
            createSlot(adcErr->Name    , 35, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(adcErr    );
            createSlot(logicErr->Name  , 36, 1, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(logicErr  );
            createSlot("reserved 3"    , 37, 4, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(nullptr   );
            createSlot(airPres->Name   , 41, 6, 0, 0, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(airPres   );

            QString posiOffsetReq = QString("20%1%2").arg(slaveCode[i-1], "2100");
            QString speedReq      = QString("20%1%2").arg(slaveCode[i-1], "0800");
            QString fresszeReq    = QString("20%1%2").arg(slaveCode[i-1], "0100");

            createPMProtocol(QString("Cluster %1 Posi Offset").arg(i), posiOffsetReq, "00", "WO"); createSlot(posiOffset->Name, 0, 0, 14, -1, ProtocolParamSlot::TypeUserPosi(), 1, pFolder); setTag(posiOffset );
            createPMProtocol(QString("Cluster %1 Valve Speed").arg(i), speedReq     , "00", "WO"); createSlot(posiSpeed->Name , 0, 0, 14, -1, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(posiSpeed  );
            createPMProtocol(QString("Cluster %1 Fressze"    ).arg(i), fresszeReq   , "00", "WO"); createSlot(fressze->Name   , 0, 0, 14, -1, ProtocolParamSlot::TypeBase10()  , 1, pFolder); setTag(fressze    );
        }

        UserPositionConverter::getInstance()->regRS232ScalingTag(FindTag("Interface RS232/RS485.Scaling.Position.Position Unit"));
        UserPositionConverter::getInstance()->regRS232ClosestPosiTag(FindTag("Interface RS232/RS485.Scaling.Position.Value Closest Position"));
        UserPositionConverter::getInstance()->regRS232OpenPosiTag(FindTag("Interface RS232/RS485.Scaling.Position.Value Open Position"));

        VersionChecker::getInstance()->setDNetV1TbSlot( FindSlot("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.DNet Out Assembly v1" ,"Read" ),
                                                        FindSlot("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.DNet Out Assembly v1" ,"Write"),
                                                        FindSlot("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.DNet In Assembly v1" ,"Read" ),
                                                        FindSlot("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.DNet In Assembly v1" ,"Write"));
        VersionChecker::getInstance()->setDNetV1TbDummyTag(FindTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Dummy(1)"), FindTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Dummy(1)"));
        VersionChecker::getInstance()->setDNetDIOTag(FindTag("Interface DeviceNet.Input Output.Digital Output.Enable"        ),
                                                     FindTag("Interface DeviceNet.Input Output.Digital Output.Functionality" ),
                                                     FindTag("Interface DeviceNet.Input Output.Digital Output.Polarity"      ),
                                                     FindTag("Interface DeviceNet.Input Output.DIO Status.Digital Out Status"),
                                                     FindTag("Interface DeviceNet.Input Output.Digital Input.Enable"        ),
                                                     FindTag("Interface DeviceNet.Input Output.Digital Input.Functionality" ),
                                                     FindTag("Interface DeviceNet.Input Output.Digital Input.Polarity"      ),
                                                     FindTag("Interface DeviceNet.Input Output.DIO Status.Digital In Status"));
        VersionChecker::getInstance()->setPwrConnDIOTag(FindTag("Power Connector IO.Digital Input 1.Enable"        ),
                                                        FindTag("Power Connector IO.Digital Input 1.Functionality" ),
                                                        FindTag("Power Connector IO.Digital Input 1.Inverted"      ),
                                                        FindTag("Power Connector IO.Digital Input 1.State"         ),
                                                        FindTag("Power Connector IO.Digital Input 2.Enable"        ),
                                                        FindTag("Power Connector IO.Digital Input 2.Functionality" ),
                                                        FindTag("Power Connector IO.Digital Input 2.Inverted"      ),
                                                        FindTag("Power Connector IO.Digital Input 2.State"         ),
                                                        FindTag("Power Connector IO.Digital Output 1.Enable"       ),
                                                        FindTag("Power Connector IO.Digital Output 1.Functionality"),
                                                        FindTag("Power Connector IO.Digital Output 1.Inverted"     ),
                                                        FindTag("Power Connector IO.Digital Output 1.State"        ),
                                                        FindTag("Power Connector IO.Digital Output 2.Enable"       ),
                                                        FindTag("Power Connector IO.Digital Output 2.Functionality"),
                                                        FindTag("Power Connector IO.Digital Output 2.Inverted"     ),
                                                        FindTag("Power Connector IO.Digital Output 2.State"        ));

        VersionChecker::getInstance()->regIdValveTypeTag(FindTag("System.Identification.ID: Valve Type"                 ));
        VersionChecker::getInstance()->regValveRev1Tag  (FindTag("System.Identification.Valve Revision (1)"             ));
        VersionChecker::getInstance()->regValveRev2Tag  (FindTag("System.Identification.Valve Revision (2)"             ));
        VersionChecker::getInstance()->regValveRev3Tag  (FindTag("System.Identification.Valve Revision (3)"             ));
        VersionChecker::getInstance()->regFirmwareVerTag(FindTag("System.Identification.Firmware.Valve Firmware Version"));

    }

    ProtocolParamSlotFolder * FindSlotFolder(QString path)
    {
        if(pRootFolder == nullptr)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]root is null";
            return nullptr;
        }

        return pRootFolder->findFolder(path);
    }

    ProtocolParamSlot * FindSlot(QString path, QString accType)
    {
        if(pRootFolder == nullptr)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]root is null";
            return nullptr;
        }

        return pRootFolder->findSlot(path, accType);
    }

    TagModel * FindTag(QString path)
    {
        if(pRootFolder == nullptr)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]root is null";
            return nullptr;
        }

        return pRootFolder->findTag(path);
    }

private:
    int PM_R_OFFSET = 16;
    int PM_R_LENGTH = -1;
    int PM_W_OFFSET = 14;
    int PM_W_LENGTH = -1;

    ProtocolModel     * pLastCreateReadProtocol;
    ProtocolModel     * pLastCreateWriteProtocol;
    ProtocolParamSlot * pLastCreateReadSlot;
    ProtocolParamSlot * pLastCreateWriteSlot;

    TagModel * createTag(QString name, QString acc, int tagValueType, TagEnumListModel* modeOptions, int bitOffset, ProtocolParamSlotFolder * pFolder)
    {
        TagModel * pTag = new TagModel(name, acc, tagValueType, modeOptions, bitOffset, this);
        pFolder->appendTag(pTag);
        return pTag;
    }

    void createICProtocol(QString name, QString readReq, QString readResp, QString writeReq, QString writeResp)
    {
        bool isParam = false;

        if(readReq.startsWith("b:10"))
        {
            isParam = true;
        }

        pLastCreateReadProtocol = nullptr;
        pLastCreateWriteProtocol = nullptr;

        if(readReq.length() > 0)
            pLastCreateReadProtocol = new ProtocolModel(name, "Read", false, readReq, readResp, this);

        if(writeReq.length() > 0)
            pLastCreateWriteProtocol = new ProtocolModel(name, "Write", isParam, writeReq, writeResp, this);
    }

    void createPMProtocol(QString name, QString id, QString index,QString accType)
    {
        bool isReadOnly = false;
        bool isWriteOnly = false;

        if(accType== "RO")
        {
            isReadOnly = true;
        }
        else if(accType== "WO")
        {
            isWriteOnly = true;
        }

        pLastCreateReadProtocol = nullptr;
        pLastCreateWriteProtocol = nullptr;

        if(isWriteOnly == false)
            pLastCreateReadProtocol  = new ProtocolModel(name, "Read" , false, QString("p:0B%1%2").arg(id, index), QString("p:000B%1%2").arg(id, index), this);

        if(isReadOnly == false)
            pLastCreateWriteProtocol = new ProtocolModel(name, "Write", false, QString("p:01%1%2").arg(id, index), QString("p:0001%1%2").arg(id, index), this);
    }

    void createSlot(QString name, int r_offset, int r_length, int w_offset, int w_length, int slotDataType, int gain, ProtocolParamSlotFolder * pFolder)
    {
        pLastCreateReadSlot = nullptr;
        pLastCreateWriteSlot = nullptr;

        if(pLastCreateReadProtocol != nullptr)
        {
            pLastCreateReadSlot = pLastCreateReadProtocol->AppendSlot(name, r_offset, r_length, slotDataType, gain);
            pFolder->appendSlot(pLastCreateReadSlot);
        }

        if(pLastCreateWriteProtocol != nullptr)
        {
            pLastCreateWriteSlot = pLastCreateWriteProtocol->AppendSlot(name, w_offset, w_length, slotDataType, gain);
            pFolder->appendSlot(pLastCreateWriteSlot);
        }
    }

    void setTag(TagModel * pTag)
    {
        if(pLastCreateReadSlot != nullptr)
        {
            pLastCreateReadSlot->SetTag(pTag);
        }

        if(pLastCreateWriteSlot != nullptr)
        {
            pLastCreateWriteSlot->SetTag(pTag);
        }
    }
};
#endif // PROTOCOLMANAGER_H
