#ifndef GRAPHANALYZEDLGMODEL_H
#define GRAPHANALYZEDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QDir>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/unitutil.h"
#include "source/service/util/filewriterex.h"
#include "source/service/coreservice.h"
#include "source/nchart/nchartview.h"


class GraphAnalyzeDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mIsAutoLoad           READ getIsAutoLoad           NOTIFY signalEventChangedIsAutoLoad          )
    Q_PROPERTY(int  mAutoRecordFileIdx    READ getAutoRecordFileIdx    NOTIFY signalEventChangedAutoRecordFileIdx   )
    Q_PROPERTY(int  mSelAutoRecordFileIdx READ getSelAutoRecordFileIdx NOTIFY signalEventChangedSelAutoRecordFileIdx)


public:
    QStringList mAutoRecordFileList;
    bool mIsAutoLoad = false;
    int  mAutoRecordFileIdx = 0;
    int  mSelAutoRecordFileIdx = -1;

    bool getIsAutoLoad          (){return mIsAutoLoad          ;}
    int  getAutoRecordFileIdx   (){return mAutoRecordFileIdx   ;}
    int  getSelAutoRecordFileIdx(){return mSelAutoRecordFileIdx;}

    void setIsAutoLoad          (bool value){if(mIsAutoLoad           == value)return; mIsAutoLoad           = value; emit signalEventChangedIsAutoLoad          (value); }
    void setAutoRecordFileIdx   (int  value){if(mAutoRecordFileIdx    == value)return; mAutoRecordFileIdx    = value; emit signalEventChangedAutoRecordFileIdx   (value); }
    void setSelAutoRecordFileIdx(int  value){if(mSelAutoRecordFileIdx == value)return; mSelAutoRecordFileIdx = value; emit signalEventChangedSelAutoRecordFileIdx(value); }

    explicit GraphAnalyzeDlgModel(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~GraphAnalyzeDlgModel()
    {
    }

signals:
    void signalEventChangedIsAutoLoad          (bool value);
    void signalEventChangedAutoRecordFileIdx   (int  value);
    void signalEventChangedSelAutoRecordFileIdx(int  value);

public slots:    
    Q_INVOKABLE QString onCommandGetAutoRecordFileName(int idx)
    {
        if((idx > (mAutoRecordFileList.count() - 1)) || idx < 0)
            return "";

        return mAutoRecordFileList.at(idx);
    }

    Q_INVOKABLE void onCommandPre()
    {
        if(mAutoRecordFileIdx < 1)
            return;

        setAutoRecordFileIdx(mAutoRecordFileIdx - 1);
    }

    Q_INVOKABLE void onCommandNext()
    {
        if((mAutoRecordFileIdx + 1) > (mAutoRecordFileList.count() - 1))
            return;

        setAutoRecordFileIdx(mAutoRecordFileIdx + 1);
    }

    Q_INVOKABLE void onCommandLoadAutoRecordFolder()
    {
        setAutoRecordFileIdx(-1);
        setSelAutoRecordFileIdx(-1);
        mAutoRecordFileList.clear();
        setIsAutoLoad(true);

        if (QDir(QString("%1/autosave").arg(QApplication::applicationDirPath())).exists() == false)
        {
            return;
        }
        else
        {
            QDir dir(QString("%1/autosave").arg(QApplication::applicationDirPath()));
            QStringList fileList = dir.entryList(QStringList() << "*.txt",QDir::Files,QDir::SortFlag::Name);

            for(int i = 0; i < fileList.size(); i++)
            {
                mAutoRecordFileList.append(fileList.at(i));
            }
        }

        if(mAutoRecordFileList.count() > 0)
            setAutoRecordFileIdx(0);
    }

    Q_INVOKABLE void onCommandLoadAutoRecord(int idx, NChartView * dstChart)
    {
        if((idx > (mAutoRecordFileList.count() - 1)) || idx < 0)
            return;

        setSelAutoRecordFileIdx(idx);

        loadFromFile(QString("%1/autosave/%2").arg(QApplication::applicationDirPath()).arg(mAutoRecordFileList.at(idx)), dstChart);
    }

    Q_INVOKABLE QString onCommandLoadFromFile(QString filePath, NChartView * dstChart)
    {
        if(filePath.startsWith(QString("%1/autosave").arg(QApplication::applicationDirPath())))
        {
            onCommandLoadAutoRecordFolder();

            for(int i = 0; i < mAutoRecordFileList.count(); i ++)
            {
                if(QString("%1/autosave/%2").arg(QApplication::applicationDirPath()).arg(mAutoRecordFileList.at(i)) == filePath)
                {
                    setAutoRecordFileIdx(i);
                    onCommandLoadAutoRecord(i, dstChart);
                    break;
                }
            }

            return "";
        }
        else
        {
            setIsAutoLoad(false);
            setSelAutoRecordFileIdx(-1);
            return loadFromFile(filePath, dstChart);
        }
    }

private:
    QString loadFromFile(QString filePath, NChartView * dstChart)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] file name = " << filePath;

        QString result = "";
        double  sensorFullScale;
        int     sensorUnit;
        int     dpUnit;
        int     pointStartLine = -1;

        bool    foundPosResolution = false;
        bool    foundSensorFullScale = false;
        bool    foundDpUnit = false;

        double  posMax;
        QString pressureTitle = QString("Pressure(%1)");
        double  pressureMax;

        double  firstSec      = -1;;
        double  sec           ;
        double  posCurr       ;
        double  posTarget     ;
        double  pressureCurr  ;
        double  pressureTarget;

        int lineIdx = 0;
        QFile file;
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)return "File open failed!";

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            QString line = out.readLine();
            QStringList value;

            if(line.startsWith("Position resolution"))
            {
                if(getDoubleByLine(line, posMax) == false)
                {
                    result = "file format error(resolution)";
                    break;
                }
                foundPosResolution = true;
            }
            else if(line.startsWith("Sensor full scale"))
            {
                if(getSensorFullScaleNUnitByLine(line, sensorFullScale, sensorUnit) == false)
                {
                    result = "file format error(full scale)";
                    break;
                }
                foundSensorFullScale = true;
            }
            else if(line.startsWith("pressure display unit"))
            {
                if(getDpUnitByLine(line, dpUnit) == false)
                {
                    result = "file format error(dp unit)";
                    break;
                }
                foundDpUnit = true;
            }
            else if(line.startsWith("Record data"))
            {
                if(!foundPosResolution || !foundSensorFullScale || !foundDpUnit)
                {
                    result = "file format error(can't found header)";
                    break;
                }
                pressureMax = UNITUTIL_CONVERT(sensorUnit, sensorFullScale, dpUnit);
                pointStartLine = lineIdx + 2;

                dstChart->onCommandClearGraph();
                dstChart->setYAxis01Title("Position");
                dstChart->setYAxis01Min(0);
                dstChart->setYAxis01Max(posMax);
                dstChart->setYAxis01Factor(1);
                dstChart->setYAxis02Title(pressureTitle.arg(UNITUTIL_TO_STR(dpUnit)));
                dstChart->setYAxis02Min(0);
                dstChart->setYAxis02Max(pressureMax);
                dstChart->setYAxis02Factor(1);
                dstChart->setPause(false);

                //dstChart->setYAxis01AutoScale (true );
                //dstChart->setYAxis01Log       (false);
                //dstChart->setY01Draw          (true );
                //dstChart->setY01DashDraw      (true );
                //
                //dstChart->setYAxis02AutoScale (true );
                //dstChart->setYAxis02Log       (false);
                //dstChart->setY02Draw          (true );
                //dstChart->setY02DashDraw      (true );
            }

            if((lineIdx >= pointStartLine) && pointStartLine != -1)
            {
                line = line.trimmed();
                QStringList col = line.split(QRegExp("[\\s]+"));

                if(col.size() != 5)
                {
                    result = "file format error(point data)";
                    break;
                }

                sec           = col[0].trimmed().toDouble();// / 1000;
                posCurr        = col[1].trimmed().toDouble();
                posTarget      = col[2].trimmed().toDouble();
                pressureCurr   = col[3].trimmed().toDouble();
                pressureTarget = col[4].trimmed().toDouble();

                if(firstSec < 0)
                    firstSec = sec;

                dstChart->setXRange(sec - firstSec);
                dstChart->onCommandAddPoint(sec - firstSec, posCurr, posTarget, pressureCurr, pressureTarget);
            }

            lineIdx++;

        }while(!out.atEnd());

        file.close();
        return "";
    }

    bool getDoubleByLine(QString line, double &value)
    {
        QStringList col = line.split(":");

        if(col.size() != 2)
        {
            return false;
        }

        value = col[1].toDouble();
        return true;
    }

    bool getSensorFullScaleNUnitByLine(QString line, double &fullScale, int &unit)
    {
        QStringList col = line.split(":");
        QStringList scaleNUnit;
        if(col.size() != 2)
        {
            return false;
        }

        scaleNUnit = col[1].trimmed().split(" ");

        if(scaleNUnit.size() != 2)
        {
            return false;
        }

        fullScale = scaleNUnit[0].toDouble();
        unit      = UNITUTIL_STR_TO_INT((scaleNUnit[1].trimmed()));

        return true;
    }

    bool getDpUnitByLine(QString line, int &value)
    {
        QStringList col = line.split(":");

        if(col.size() != 2)
        {
            return false;
        }

        value = UNITUTIL_STR_TO_INT((col[1].trimmed()));
        return true;
    }
};
#endif // GRAPHANALYZEDLGMODEL_H
