#ifndef TAGENUM_H
#define TAGENUM_H

#include <QAbstractListModel>
#include <QList>

struct TagEnumItem {
    int value;
    QString text;
};

class TagEnumListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // QML에서 사용할 Role 정의
    enum EnumRoles {
        TextRole = Qt::UserRole + 1,
        ValueRole
    };

    QString Name;

    explicit TagEnumListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    explicit TagEnumListModel(QString name, QObject *parent = nullptr) : QAbstractListModel(parent)
    {
        Name = name;
        addPair(-2, "-");
        addPair(-1, "Unknown");
    }

    // 데이터를 추가하는 함수
    void addPair(int value, const QString &text) {
        beginInsertRows(QModelIndex(), m_items.count(), m_items.count());
        m_items.append({value, text});
        endInsertRows();
    }

    // [필수] 리스트의 길이 반환
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_items.count();
    }

    // [필수] 데이터 반환 로직
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= m_items.count())
            return QVariant();

        const TagEnumItem &item = m_items[index.row()];

        switch (role) {
        case TextRole:
            return item.text;
        case ValueRole:
            return item.value;
        default:
            return QVariant();
        }
    }

    // [필수] Role 이름 매핑 (QML에서 이 이름을 사용함)
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[TextRole] = "text";   // QML에서 model.text 로 접근
        roles[ValueRole] = "value"; // QML에서 model.value 로 접근
        return roles;
    }

    Q_INVOKABLE QString getTextByValue(int value) const {
        for (const auto &item : m_items) {
            if (item.value == value) {
                return item.text;
            }
        }
        // 값을 찾지 못했을 때 반환할 값 (빈 문자열 또는 "Unknown")
        return "";
    }

    Q_INVOKABLE QString getTextByValue(QString value) const {
        int intValue = value.toInt();

        for (const auto &item : m_items) {
            if (item.value == intValue) {
                return item.text;
            }
        }
        // 값을 찾지 못했을 때 반환할 값 (빈 문자열 또는 "Unknown")
        return "Unkonwn";
    }
private:
    QList<TagEnumItem> m_items;
};

class TagEnumDefine: QObject{
    Q_OBJECT

public:
    QList<TagEnumListModel *> EnumList;

    static TagEnumDefine * getInstance()
    {
        static TagEnumDefine *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new TagEnumDefine();
        }

        return mpSelf;
    }

    explicit TagEnumDefine(QObject *parent = nullptr):QObject(parent)
    {
        TagEnumListModel * pTemp = nullptr;

        pTemp = new TagEnumListModel("OffOn", this);
        pTemp->addPair(0, "Off");
        pTemp->addPair(1, "On");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("FalseTrue", this);
        pTemp->addPair(0, "False");
        pTemp->addPair(1, "True");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DisableEnable", this);
        pTemp->addPair(0, "Disable");
        pTemp->addPair(1, "Enable");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("EnableDisable", this);
        pTemp->addPair(0, "Enable");
        pTemp->addPair(1, "Disable");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("Base36", this);
        pTemp->addPair( 0,  "0"); pTemp->addPair( 1,  "1"); pTemp->addPair( 2,  "2"); pTemp->addPair( 3,  "3"); pTemp->addPair( 4,  "4");
        pTemp->addPair( 5,  "5"); pTemp->addPair( 6,  "6"); pTemp->addPair( 7,  "7"); pTemp->addPair( 8,  "8"); pTemp->addPair( 9,  "9");
        pTemp->addPair(10,  "A"); pTemp->addPair(11,  "B"); pTemp->addPair(12,  "C"); pTemp->addPair(13,  "D"); pTemp->addPair(14,  "E");
        pTemp->addPair(15,  "F"); pTemp->addPair(16,  "G"); pTemp->addPair(17,  "H"); pTemp->addPair(18,  "I"); pTemp->addPair(19,  "J");
        pTemp->addPair(20,  "K"); pTemp->addPair(21,  "L"); pTemp->addPair(22,  "M"); pTemp->addPair(23,  "N"); pTemp->addPair(24,  "O");
        pTemp->addPair(25,  "P"); pTemp->addPair(26,  "Q"); pTemp->addPair(27,  "R"); pTemp->addPair(28,  "S"); pTemp->addPair(29,  "T");
        pTemp->addPair(30,  "U"); pTemp->addPair(31,  "V"); pTemp->addPair(32,  "W"); pTemp->addPair(33,  "X"); pTemp->addPair(34,  "Y");
        pTemp->addPair(35,  "Z");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DIFunc", this);
        pTemp->addPair(0, "Interlock Close");
        pTemp->addPair(1, "Interlock Open" );
        pTemp->addPair(2, "Hold"           );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DOFunc", this);
        pTemp->addPair(0, "Close"        );
        pTemp->addPair(1, "Open"         );
        pTemp->addPair(2, "Constantly ON");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("Polarity", this);
        pTemp->addPair(0, "Not Inverted");
        pTemp->addPair(1, "inverted");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("IdValveType", this);
        pTemp->addPair(1, "B : BUTTERFLY");
        pTemp->addPair(2, "P : PENDULUM" );
        pTemp->addPair(3, "C : CIRCULAR" );
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

        pTemp = new TagEnumListModel("PosiScaling", this);
        pTemp->addPair(0, "0-1"                            );
        pTemp->addPair(1, "0-10"                           );
        pTemp->addPair(2, "0-90"                           );
        pTemp->addPair(3, "0-100"                          );
        pTemp->addPair(4, "0-1000"                         );
        pTemp->addPair(5, "0-10000"                        );
        pTemp->addPair(6, "0-100000"                       );
        pTemp->addPair(7, "Defines the User Specific Range");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetDevType", this);
        pTemp->addPair(  0, "Generic Device"        );
        pTemp->addPair( 12, "Communications Adapter");
        pTemp->addPair( 29, "Process Control Device");
        pTemp->addPair( 43, "Generic Device"        );
        pTemp->addPair(100, "Pressure Control Valve");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetBaudRate", this);
        pTemp->addPair(0, "125k");
        pTemp->addPair(1, "250k");
        pTemp->addPair(2, "500k");
        pTemp->addPair(3, "Auto");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetProfile", this);
        pTemp->addPair(0, "Process Control Device");
        pTemp->addPair(1, "Generic Device C(new)" );
        pTemp->addPair(2, "Generic Device B(old)" );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetDataType", this);
        pTemp->addPair(195, "INT16");
        pTemp->addPair(202, "FLOAT32" );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetOutputIOConsumedAssy", this);
        pTemp->addPair(  0, "(0)CUSTOMIZE"                                                                                                                 );
        pTemp->addPair(  7, "(7)SETPOINT/SETPOINT TYPE"                                                                                                    );
        pTemp->addPair(  8, "(8)CONTROL MODE/SETPOINT/SETPOINT TYPE"                                                                                       );
        pTemp->addPair( 23, "(23)SETPOINT/SETPOINT TYPE"                                                                                                   );
        pTemp->addPair( 24, "(24)CONTROL MODE/SETPOINT/SETPOINT TYPE"                                                                                      );
        pTemp->addPair( 32, "(32)CONTROL MODE/SETPOINT/KP/KI/KD"                                                                                           );
        pTemp->addPair(102, "(102)CONTROL MODE/SETPOINT/SETPOINT TYPE/LEARN/LEARN PRES. LIMIT/ZERO"                                                        );
        pTemp->addPair(103, "(103)CONTROL MODE/SETPOINT/SETPOINT TYPE/CLUSTER ADDR./CLUSTER ACTION"                                                        );
        pTemp->addPair(107, "(107)CONTROL MODE/SETPOINT/SETPOINT TYPE/LEARN/LEARN PRES. LIMIT/ZERO"                                                        );
        pTemp->addPair(108, "(108)CONTROL MODE/SETPOINT/SETPOINT TYPE/CLUSTER ADDR./CLUSTER ACTION"                                                        );
        pTemp->addPair(110, "(110)CONTROL MODE/SETPOINT PRESSURE/SETPOINT POSITION/SETPOINT TYPE/LEARN/LEARN PRES. LIMIT/ZERO/CLUSTER ADDR./CLUSTER ACTION");
        pTemp->addPair(112, "(112)CONTROL MODE/SETPOINT PRESSURE/SETPOINT POSITION/SETPOINT TYPE/LEARN/LEARN PRES. LIMIT/ZERO/CLUSTER ADD./CLUSTER ACTION" );
        pTemp->addPair(151, "(151)CONTROL MODE/SETPOINT PRESSURE/SETPOINT POSITION/SETPOINT TYPE/CLUSTER ADDR./CLUSTER ACTION"                             );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetOutputSelector", this);
        pTemp->addPair( 0, "NONE"                );
        pTemp->addPair( 1, "CONTROL MODE"        );
        pTemp->addPair( 2, "SETPOINT"            );
        pTemp->addPair( 3, "SETPOINT PRESSURE"   );
        pTemp->addPair( 4, "SETPOINT POSITION"   );
        pTemp->addPair( 5, "SETPOINT TYPE"       );
        pTemp->addPair( 6, "LEARN"               );
        pTemp->addPair( 7, "LEARN PRESSURE LIMIT");
        pTemp->addPair( 8, "ZERO"                );
        pTemp->addPair( 9, "KP (Gain Factor)"    );
        pTemp->addPair(10, "KI (Delta Factor)"   );
        pTemp->addPair(11, "KD (Ramp Time)"      );
        pTemp->addPair(12, "CLUSTER ADDRESS"     );
        pTemp->addPair(13, "CLUSTER ACTION"      );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetInputIOProducedAssy", this);
        pTemp->addPair(  0, "(0)CUSTOMIZE"                                                                                                                              );
        pTemp->addPair(  1, "(1)PRESSURE"                                                                                                                               );
        pTemp->addPair(  2, "(2)EXCEPTION STATUS/PRESSURE"                                                                                                              );
        pTemp->addPair(  3, "(3)EXCEPTION STATUS/PRESSURE/POSITION"                                                                                                     );
        pTemp->addPair(  4, "(4)EXCEPTION STATUS/PRESSURE/SETPOINT"                                                                                                     );
        pTemp->addPair(  5, "(5)EXCEPTION STATUS/PRESSURE/SETPOINT/POSITION"                                                                                            );
        pTemp->addPair(  6, "(6)EXCEPTION STATUS/PRESSURE/SETPOINT/CONTROL MODE/POSITION"                                                                               );
        pTemp->addPair( 10, "(10)EXCEPTION STATUS"                                                                                                                      );
        pTemp->addPair( 11, "(11)EXCEPTION STATUS/PRESSURE/POSITION/CLOSE OPEN CHECK"                                                                                   );
        pTemp->addPair( 13, "(13)EXCEPTION STATUS/EXCEPTION DETAIL ALARM"                                                                                               );
        pTemp->addPair( 14, "(14)EXCEPTION STATUS/PRESSURE/POSITION/CLOSE OPEN CHECK"                                                                                   );
        pTemp->addPair( 17, "(17)PRESSURE"                                                                                                                              );
        pTemp->addPair( 18, "(18)EXCEPTION STATUS/PRESSURE"                                                                                                             );
        pTemp->addPair( 19, "(19)EXCEPTION STATUS/PRESSURE/POSITION"                                                                                                    );
        pTemp->addPair( 20, "(20)EXCEPTION STATUS/PRESSURE/SETPOINT"                                                                                                    );
        pTemp->addPair( 21, "(21)EXCEPTION STATUS/PRESSURE/SETPOINT/POSITION"                                                                                           );
        pTemp->addPair( 22, "(22)EXCEPTION STATUS/PRESSURE/SETPOINT/CONTROL MODE/POSITION"                                                                              );
        pTemp->addPair( 26, "(26)EXCEPTION STATUS/PRESSURE/POSITION/CLOSE OPEN CHECK"                                                                                   );
        pTemp->addPair(100, "(100)EXCEPTION STATUS/PRESSURE/POSITION/DEVICE STATUS 2/ACCESS MODE"                                                                       );
        pTemp->addPair(101, "(101)EXCEPTION STATUS/PRESSURE/POSITION/CLOSE OPEN CHECK/DEVICE STATUS 2"                                                                  );
        pTemp->addPair(104, "(104)EXCEPTION STATUS/PRESSURE/SENSOR 2 READING/POSITION/ACCESS MODE/DEVICE STATUS 2/CLUSTER INFOMATION"                                   );
        pTemp->addPair(105, "(105)EXCEPTION STATUS/PRESSURE/POSITION/DEVICE STATUS 2/ACCESS MODE"                                                                       );
        pTemp->addPair(106, "(106)EXCEPTION STATUS/PRESSURE/POSITION/SETPOINT/DEVICE STATUS 2"                                                                          );
        pTemp->addPair(109, "(109)EXCEPTION STATUS/PRESSURE/SENSOR 2 READING/POSITION/ACCESS MODE/DEVICE STATUS 2/CLUSTER INFOMATION"                                   );
        pTemp->addPair(111, "(111)EXCEPTION STATUS/PRESSURE/POSITION/SENSOR 1 READING/SENSOR 2 READING/CLOSE OPEN CHECK/DEVICE STATUTS2/ACCESS MODE/CLUSTER INFORMATION");
        pTemp->addPair(113, "(113)EXCEPTION STATUS/PRESSURE/POSITION/SENSOR 1 READING/SENSOR 2 READING/CLOSE OPEN CHECK/DEVICE STATUTS2/ACCESS MODE/CLUSTER INFORMATION");
        pTemp->addPair(150, "(150)EXCEPTION STATUS/SENSOR 1 READING/SENSOR 2 READING/POSITION/READING SENSOR/CLOSE OPEN CHECK"                                          );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetInputSelector", this);
        pTemp->addPair( 0, "NONE"                    );
        pTemp->addPair( 1, "EXCEPTION STATUS"        );
        pTemp->addPair( 2, "EXCEPTION DETAIL ALARM"  );
        pTemp->addPair( 3, "EXCEPTION DETAIL WARNING");
        pTemp->addPair( 4, "PRESSURE"                );
        pTemp->addPair( 5, "POSITION"                );
        pTemp->addPair( 6, "CLOSE/OPEN CHECK"        );
        pTemp->addPair( 7, "DEVICE STATUS 2"         );
        pTemp->addPair( 8, "SENSOR 1 READING"        );
        pTemp->addPair( 9,"SENSOR 2 READING"         );
        pTemp->addPair(10,"READING SENSOR"           );
        pTemp->addPair(11,"CONTROL MODE"             );
        pTemp->addPair(12,"SETPOINT"                 );
        pTemp->addPair(13,"SETPOINT PRESSURE"        );
        pTemp->addPair(14,"SETPOINT POSITION"        );
        pTemp->addPair(15,"SETPOINT TYPE"            );
        pTemp->addPair(16,"ACCESS MODE"              );
        pTemp->addPair(17,"CLUSTER INFORMATION"      );
        pTemp->addPair(18,"CLUSTER ACTION"           );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetPosiUnit", this);
        pTemp->addPair(4097, "Counts" );
        pTemp->addPair(4103, "Percent");
        pTemp->addPair(5891, "Degress");
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetPresUnit", this);
        pTemp->addPair(4097, "Counts" );
        pTemp->addPair(4103, "Percent");
        pTemp->addPair(4864, "psi"    );
        pTemp->addPair(4865, "Torr"   );
        pTemp->addPair(4866, "mTorr"  );
        pTemp->addPair(4871, "bar"    );
        pTemp->addPair(4872, "mbar"   );
        pTemp->addPair(4873, "Pa"     );
        pTemp->addPair(4875, "atm"    );
        EnumList.append(pTemp);

        pTemp = new TagEnumListModel("DNetConnectionLossReaction", this);
        pTemp->addPair(0, "Open"         );
        pTemp->addPair(1, "Close"        );
        pTemp->addPair(2, "Keep Position");
        EnumList.append(pTemp);
    }

    TagEnumListModel * Find(QString name)
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

#endif // TAGENUM_H
