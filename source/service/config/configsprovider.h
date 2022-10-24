#ifndef CONFIGSPROVIDER_H
#define CONFIGSPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


#define pConfigSP ConfigSProvider::getInstance()

class DNetAssemblyItem
{
public:
    int     mSeq    = 0;
    QString mName   ;
    int     mLength ;
    QString mType   ;
    QString mAddInfo;
    int     mDepSeq ;

    DNetAssemblyItem(){}
    DNetAssemblyItem(const DNetAssemblyItem& copy):
        mSeq    (copy.mSeq    ),
        mName   (copy.mName   ),
        mLength (copy.mLength ),
        mType   (copy.mType   ),
        mAddInfo(copy.mAddInfo),
        mDepSeq (copy.mDepSeq ){}

    ~DNetAssemblyItem(){}

    DNetAssemblyItem& operator=(const DNetAssemblyItem& other)
    {
        mSeq     = other.mSeq    ;
        mName    = other.mName   ;
        mLength  = other.mLength ;
        mType    = other.mType   ;
        mAddInfo = other.mAddInfo;
        mDepSeq  = other.mDepSeq ;

        return *this;
    }
};

Q_DECLARE_METATYPE(DNetAssemblyItem);

class ConfigSProvider : public QObject
{
    Q_OBJECT
public:
    static ConfigSProvider * getInstance()
    {
        static ConfigSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ConfigSProvider();
        }

        return mpSelf;
    }

    explicit ConfigSProvider(QObject *parent = nullptr):QObject(parent)
    {
    }

    ~ConfigSProvider()
    {
    }

public:
    QList<DNetAssemblyItem> mInputAssemblyTable;
    QList<DNetAssemblyItem> mOutputAssemblyTable;

    void loadInterfaceDNetAssembly()
    {
        QFile file;
        QJsonDocument doc;

        file.setFileName(QString("%1/config/dnet/assembly.json").arg(QApplication::applicationDirPath()));
        file.open(QFile::ReadOnly);

        mInputAssemblyTable.clear();
        mOutputAssemblyTable.clear();

        if(file.isOpen() == false)
        {
            qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]fail";
            return;
        }

        QByteArray loadData = file.readAll();

        file.close();

        try{
            doc = QJsonDocument::fromJson(loadData);

            QJsonObject obj = doc.object();

            QJsonArray inputAssemblyItemList  = obj.value("Input Assembly").toArray();
            QJsonArray outputAssemblyItemList = obj.value("Output Assembly").toArray();

            for(int i = 0; i < inputAssemblyItemList.size(); i ++)
            {
                DNetAssemblyItem item;
                item.mSeq     = inputAssemblyItemList.at(i).toObject().value("seq").toInt();
                item.mLength  = inputAssemblyItemList.at(i).toObject().value("length").toInt();
                item.mName    = inputAssemblyItemList.at(i).toObject().value("name").toString();
                item.mType    = inputAssemblyItemList.at(i).toObject().value("type").toString();
                item.mAddInfo = inputAssemblyItemList.at(i).toObject().value("additional infomation").toString();
                item.mDepSeq  = inputAssemblyItemList.at(i).toObject().value("dependent seq").toInt();

                mInputAssemblyTable.append(item);
            }

            for(int i = 0; i < outputAssemblyItemList.size(); i ++)
            {
                DNetAssemblyItem item;
                item.mSeq     = outputAssemblyItemList.at(i).toObject().value("seq").toInt();
                item.mLength  = outputAssemblyItemList.at(i).toObject().value("length").toInt();
                item.mName    = outputAssemblyItemList.at(i).toObject().value("name").toString();
                item.mType    = outputAssemblyItemList.at(i).toObject().value("type").toString();
                item.mAddInfo = outputAssemblyItemList.at(i).toObject().value("additional infomation").toString();
                item.mDepSeq  = outputAssemblyItemList.at(i).toObject().value("dependent seq").toInt();

                mOutputAssemblyTable.append(item);
            }
        }
        catch (int ex)
        {
            qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]exception";
        }
        return;
    }

};
#endif // CONFIGSPROVIDER_H
