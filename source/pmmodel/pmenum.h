#ifndef PMENUM_H
#define PMENUM_H

#include <QAbstractListModel>
#include <QList>

struct PmEnumItem {
    int value;
    QString text;
};

class PmEnumListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    // QML에서 사용할 Role 정의
    enum EnumRoles {
        TextRole = Qt::UserRole + 1,
        ValueRole
    };

    QString Name;

    explicit PmEnumListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    explicit PmEnumListModel(QString name, QObject *parent = nullptr) : QAbstractListModel(parent)
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

        const PmEnumItem &item = m_items[index.row()];

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
    QList<PmEnumItem> m_items;
};
#endif // PMENUM_H
