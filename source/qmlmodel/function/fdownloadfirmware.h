#ifndef FDOWNLOADFIRMWARE_H
#define FDOWNLOADFIRMWARE_H
#include <QObject>
#include <QtMath>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class FDownloadFirmware : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(qint64  mFtpProgressCpu1Kernel READ getFtpProgressCpu1Kernel NOTIFY signalEventChangedFtpProgressCpu1Kernel)
    //Q_PROPERTY(qint64  mFtpProgressCpu2Kernel READ getFtpProgressCpu2Kernel NOTIFY signalEventChangedFtpProgressCpu2Kernel)
    Q_PROPERTY(qint64  mFtpProgressCpu1App    READ getFtpProgressCpu1App    NOTIFY signalEventChangedFtpProgressCpu1App   )
    Q_PROPERTY(qint64  mFtpProgressCpu2App    READ getFtpProgressCpu2App    NOTIFY signalEventChangedFtpProgressCpu2App   )
    Q_PROPERTY(int     mDownloadStep          READ getDownloadStep          NOTIFY signalEventChangedDownloadStep         )

public:
    //qint64      mFtpProgressCpu1Kernel = 0;
    //qint64      mFtpProgressCpu2Kernel = 0;
    qint64      mFtpProgressCpu1App    = 0;
    qint64      mFtpProgressCpu2App    = 0;
    int         mDownloadStep          = 0;

    //qint64  getFtpProgressCpu1Kernel(){ return mFtpProgressCpu1Kernel;}
    //qint64  getFtpProgressCpu2Kernel(){ return mFtpProgressCpu2Kernel;}
    qint64  getFtpProgressCpu1App   (){ return mFtpProgressCpu1App   ;}
    qint64  getFtpProgressCpu2App   (){ return mFtpProgressCpu2App   ;}
    int     getDownloadStep         (){ return mDownloadStep         ;}

    //void    setFtpProgressCpu1Kernel(qint64  value){ if(mFtpProgressCpu1Kernel == value) return; mFtpProgressCpu1Kernel = value; emit signalEventChangedFtpProgressCpu1Kernel(value);}
    //void    setFtpProgressCpu2Kernel(qint64  value){ if(mFtpProgressCpu2Kernel == value) return; mFtpProgressCpu2Kernel = value; emit signalEventChangedFtpProgressCpu2Kernel(value);}
    void    setFtpProgressCpu1App   (qint64  value){ if(mFtpProgressCpu1App    == value) return; mFtpProgressCpu1App    = value; emit signalEventChangedFtpProgressCpu1App   (value);}
    void    setFtpProgressCpu2App   (qint64  value){ if(mFtpProgressCpu2App    == value) return; mFtpProgressCpu2App    = value; emit signalEventChangedFtpProgressCpu2App   (value);}
    void    setDownloadStep         (int     value){ if(mDownloadStep          == value) return; mDownloadStep          = value; emit signalEventChangedDownloadStep         (value);}

signals:
    //void signalEventChangedFtpProgressCpu1Kernel(qint64  value);
    //void signalEventChangedFtpProgressCpu2Kernel(qint64  value);
    void signalEventChangedFtpProgressCpu1App   (qint64  value);
    void signalEventChangedFtpProgressCpu2App   (qint64  value);
    void signalEventChangedDownloadStep         (int     value);
    void signalEventReadedVer(QStringList verList);
    void signalEventCompleted(bool bErr, QString errMsg);

private:
    QString mRemoteFileBasePath = "/HDD1/FIRMWARE/VALVE/BASIC";
    QString mRemoteFilePath = "";
    QString mLocalFileBasePath = "";
    QStringList mDownFileList = {"VALVE_CPU1_%1_FLASH.txt","VALVE_CPU2_%1_FLASH.txt"};

    QNetworkAccessManager mAaccessManager;
    QNetworkReply * mpReply = nullptr;

    QString mTempVerList;
    QFile * mpFile = nullptr;

public:
    explicit FDownloadFirmware(QObject *parent = nullptr): QObject(parent)
    {
        mLocalFileBasePath = QString("%1/ftp").arg(QApplication::applicationDirPath());
        mAaccessManager.setNetworkAccessible(QNetworkAccessManager::Accessible);
    }
    ~FDownloadFirmware()
    {
        foreach(QString remItem, mDownFileList)
        {
            QFile::remove(QString("%1/%2").arg(mLocalFileBasePath).arg(remItem));
        }
    }

    void getVerList()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        mTempVerList.clear();

        if(mpReply != nullptr)
        {
            mpReply->deleteLater();
            mpReply = nullptr;
        }

        QUrl url;  //ftp 설정 부분
        url.setScheme("ftp");
        url.setHost("121.175.173.236");
        url.setPath(QString("%1/version.txt").arg(mRemoteFileBasePath));
        url.setPort(10021);
        url.setUserName("novasen");
        url.setPassword("nova1002");

        QNetworkRequest request(url);
        mpReply = mAaccessManager.get(request);

        connect((QObject *)mpReply, SIGNAL(readyRead()), this, SLOT(readyReadVer()));
        connect((QObject *)mpReply, SIGNAL(finished()), this, SLOT(finishedVer()));
    }

    QString getCpu01FilePath()
    {
        if(mDownFileList.size() < 1)
            return "";
        return QString("%1/%2").arg(mLocalFileBasePath).arg(mDownFileList.at(0));
    }

    QString getCpu02FilePath()
    {
        if(mDownFileList.size() < 2)
            return "";

        return QString("%1/%2").arg(mLocalFileBasePath).arg(mDownFileList.at(1));
    }
public slots:
    void readyReadVer()
    {
        mTempVerList.append(mpReply->readAll());
    }

    void finishedVer()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]" << mpReply->error();

        if(mpReply != nullptr)
        {
            mpReply->deleteLater();
            mpReply = nullptr;
        }

        if(mpFile != nullptr)
        {
            mpFile->close();
            mpFile->deleteLater();
            mpFile = nullptr;
        }

        QStringList verList;

        if(mTempVerList.length() > 1)
            verList = mTempVerList.split("\n");

        emit signalEventReadedVer(verList);
    }

public :
    void run(QString ver)
    {
        QStringList verPath;

        qDebug() << "[" << Q_FUNC_INFO << "]";

        if (QDir(mLocalFileBasePath).exists() == false)
        {
            QDir().mkdir(mLocalFileBasePath);
        }

        verPath = ver.split("/");
        mDownFileList.clear();

        if(verPath.at(verPath.size() - 1) == "LASTEST")
        {
            mDownFileList.append(QString("app_cpu01.txt").arg(verPath.at(verPath.size() - 1)));
            mDownFileList.append(QString("app_cpu02.txt").arg(verPath.at(verPath.size() - 1)));
        }
        else
        {
            mDownFileList.append(QString("VALVE_CPU1_%1_FLASH.txt").arg(verPath.at(verPath.size() - 1)));
            mDownFileList.append(QString("VALVE_CPU2_%1_FLASH.txt").arg(verPath.at(verPath.size() - 1)));
        }
        mRemoteFilePath = QString("%1/%2").arg(mRemoteFileBasePath).arg(ver);
        setDownloadStep(0);

        downloadFTP();
    }

    void downloadFTP()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        if(mpReply != nullptr)
        {
            mpReply->deleteLater();
            mpReply = nullptr;
        }

        if(mpFile != nullptr)
        {
            mpFile->close();
            mpFile->deleteLater();
            mpFile = nullptr;
        }

        QUrl url;  //ftp 설정 부분
        url.setScheme("ftp");
        url.setHost("121.175.173.236");
        url.setPath(QString("%1/%2").arg(mRemoteFilePath).arg(mDownFileList.at(mDownloadStep)));
        url.setPort(10021);
        url.setUserName("novasen");
        url.setPassword("nova1002");

        QNetworkRequest request(url);

        mpFile = new QFile(this);
        mpFile = new QFile(QString("%1/%2").arg(mLocalFileBasePath).arg(mDownFileList.at(mDownloadStep)),this);
        mpFile->open(QFile::WriteOnly);
        if(mpFile->isOpen() == false)
        {
            emit signalEventCompleted(true, "file open failed");
            return;
        }

        qDebug() << "["<< Q_FUNC_INFO <<"[debug_khko]" << QString("%1/%2").arg(mLocalFileBasePath).arg(mDownFileList.at(mDownloadStep));

        mpReply = mAaccessManager.get(request);

        connect((QObject *)mpReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect((QObject *)mpReply, SIGNAL(finished()), this, SLOT(replyFinished()));
        connect(mpReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(loadProgress(qint64 ,qint64)));

    }

public slots:
    void readyRead()
    {
        mpFile->write(mpReply->readAll());
        mpFile->flush();
    }

    void replyFinished()
    {
        QNetworkReply::NetworkError err = mpReply->error();

        qDebug() << "[" << Q_FUNC_INFO << "]" << err;

        if(mpFile != nullptr)
        {
            mpFile->close();
            mpFile->deleteLater();
            mpFile = nullptr;
        }

        if(err != QNetworkReply::NoError)
        {
            emit signalEventCompleted(true, "file download failed");
            return;
        }

        if(mDownloadStep < (mDownFileList.size() - 1))
        {
            setDownloadStep(mDownloadStep + 1);
            downloadFTP();
            return;
        }

        emit signalEventCompleted(false, "");
    }

    void loadProgress(qint64 bytesSent, qint64 bytesTotal)    //파일 프로그래스
    {
        qint64 progress = 0;

        if(bytesTotal == 0)
            return;

        qDebug() << "[" << Q_FUNC_INFO << "]" << bytesSent <<"/" << bytesTotal << "=" << progress;

        progress = (bytesSent * 100) /bytesTotal;

        switch(mDownloadStep)
        {
        //case 0:
        //    setFtpProgressCpu1Kernel(progress);
        //    break;
        //case 1:
        //    setFtpProgressCpu2Kernel(progress);
        //    break;
        case 0:
            setFtpProgressCpu1App(progress);
            break;
        case 1:
            setFtpProgressCpu2App(progress);
            break;
        }
    }
};
#endif // FDOWNLOADFIRMWARE_H
