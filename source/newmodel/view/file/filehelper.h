#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QObject>
#include <QList>

#include "source/service/coreservice.h"
#include "source/newmodel/protocol/protocolmanager.h"

class FileHelper : public QObject
{
    Q_OBJECT

public:
    explicit FileHelper(QObject *parent = nullptr): QObject(parent){
        pProtocolManager = ProtocolManager::getInstance();
    }
    ~FileHelper(){}

public slots:
    Q_INVOKABLE void createDNetEdsFile(QString path){

        QStringList contents;
        QFile file;
        int outputLength = 0;
        int inputLength = 0;
        QString outputObjectNames = "";
        QString inputObjectNames = "";

        TagModel * pProfile     = pProtocolManager->FindTag("Interface DeviceNet.Connection Object.Profile.Profile"    );
        TagModel * pValveType   = pProtocolManager->FindTag("System.Identification.ID: Valve Type"                     );

        TagModel * pVenderId    = pProtocolManager->FindTag("Interface DeviceNet.Identity Object.Instance.Vendor ID"   );
        TagModel * pProdType    = pProtocolManager->FindTag("Interface DeviceNet.Identity Object.Instance.Device Type" );  /*화면에서는 'Device Type' */
        TagModel * pProdCode    = pProtocolManager->FindTag("Interface DeviceNet.Identity Object.Instance.Product Code");
        TagModel * pProdName    = pProtocolManager->FindTag("Interface DeviceNet.Identity Object.Instance.Product Name");
        TagModel * pDNetRev     = pProtocolManager->FindTag("Interface DeviceNet.Identity Object.Instance.Revision"    );

        if (!pProfile || !pVenderId || !pProdType || !pProdCode || !pProdName || !pDNetRev) {
            qDebug() << "Critical Tags are missing in DeviceNet EDS creation.";
            return;
        }

        if(pProfile->getIsSupport() == false || (pProfile->getIsSupport() && pProfile->Value == "2"))
        {
            ProtocolParamSlot * pV1OutBitmapSlot = pProtocolManager->FindSlot("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.DNet Out Assembly v1","Read");
            ProtocolParamSlot * pV1InBitmapSlot  = pProtocolManager->FindSlot("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.DNet In Assembly v1"   ,"Read");

            if (pV1OutBitmapSlot) {
                for(int i = 0; i < pV1OutBitmapSlot->TagList.size(); i ++) {
                    TagModel* pTag = pV1OutBitmapSlot->TagList.at(i); // 임시 변수 사용
                    if(pTag && pTag->Value == "1") {
                        outputLength += pTag->getLengthInfo();
                        if(!outputObjectNames.isEmpty()) outputObjectNames.append(",");
                        outputObjectNames.append(pTag->Name);
                    }
                }
            }

            if (pV1InBitmapSlot) {
                for(int i = 0; i < pV1InBitmapSlot->TagList.size(); i ++) {
                    TagModel* pTag = pV1InBitmapSlot->TagList.at(i);
                    if(pTag && pTag->Value == "1") {
                        inputLength += pTag->getLengthInfo();
                        if(!inputObjectNames.isEmpty()) inputObjectNames.append(",");
                        inputObjectNames.append(pTag->Name);
                    }
                }
            }
        }
        else
        {
            TagModel * pOutputNames = pProtocolManager->FindTag("Interface DeviceNet.Connection Object.Output.Output Name");
            TagModel * pInputNames  = pProtocolManager->FindTag("Interface DeviceNet.Connection Object.Input.Input Name");

            static const QRegularExpression re("(.*?)\\((\\d+)\\)"); // static const 권장

            if(pOutputNames && !pOutputNames->Value.isEmpty())
            {
                QStringList itemList = pOutputNames->Value.split('/');
                QStringList namesList;
                for(const QString& item : qAsConst(itemList))
                {
                    QRegularExpressionMatch match = re.match(item.trimmed());
                    if(match.hasMatch()) {
                        outputLength += match.captured(2).toInt();
                        namesList.append(match.captured(1).trimmed());
                    }
                }
                outputObjectNames = namesList.join(",");
            }

            if(pInputNames && !pInputNames->Value.isEmpty())
            {
                QStringList itemList = pInputNames->Value.split('/');
                QStringList namesList;
                for(const QString& item : qAsConst(itemList))
                {
                    QRegularExpressionMatch match = re.match(item.trimmed());
                    if(match.hasMatch()) {
                        inputLength += match.captured(2).toInt();
                        namesList.append(match.captured(1).trimmed());
                    }
                }
                inputObjectNames = namesList.join(",");
            }
        }

        // [4] 템플릿 파일 읽기
        file.setFileName(QString("%1/ref_sample/eds_sample.txt").arg(QApplication::applicationDirPath()));
        if(!file.open(QFile::ReadOnly | QIODevice::Text)) // Text 모드 추가 권장
        {
            qDebug() << "Failed to open EDS template file:" << file.fileName();
            return;
        }

        QTextStream out(&file);
        out.setCodec("UTF-8");

        QString venderName  = "NOVASEN"       ;
        QString prodTypeStr = ""              ;
        QString prodName    = pProdName->Value;
        int     devMajRev   = 1;
        int     devMinRev   = 1;

        if(pProdName->IsSupport == false)
        {
            int valveTypeValue = pValveType->Value.toInt();
            switch(valveTypeValue)
            {
            case 1:  prodName= "NOVASEN_APC_BUTTERFLY_VALVE"; break;
            case 2:  prodName= "NOVASEN_APC_PENDULUM_VALVE" ; break;
            default: prodName= "NOVASEN_APC_VALVE"          ; break;
            }
        }

        if(pDNetRev->IsSupport)
        {
            devMajRev = pDNetRev->getMajRev();
            devMinRev = pDNetRev->getMinRev();
        }

        // m_modeOptions Null 체크
        if (pProdType->m_modeOptions) {
            prodTypeStr = pProdType->m_modeOptions->getTextByValue(pProdType->Value);
        } else {
            prodTypeStr = "Unknown Type"; // 기본값 처리
        }

        // [5] 템플릿 파싱 및 데이터 삽입
        while(!out.atEnd())
        {
            QString line = out.readLine();

            if      (line.contains("DescText"   )){line.append(QString(" %1;"    ).arg("\"NOVASEN EDS FILE\""                          ));}
            else if (line.contains("CreateDate" )){line.append(QString(" %1;"    ).arg(QDate::currentDate().toString(EDS_FILE_DATE_FMT)));}
            else if (line.contains("CreateTime" )){line.append(QString(" %1;"    ).arg(QDateTime::currentDateTime().toString(TIME_FMT) ));}
            else if (line.contains("ModDate"    )){line.append(QString(" %1;"    ).arg(QDate::currentDate().toString(EDS_FILE_DATE_FMT)));}
            else if (line.contains("ModTime"    )){line.append(QString(" %1;"    ).arg(QDateTime::currentDateTime().toString(TIME_FMT) ));}
            else if (line.contains("Revision"   )){line.append(QString(" %1;"    ).arg("1.0"                                           ));}
            else if (line.contains("VendCode"   )){line.append(QString(" %1;"    ).arg(pVenderId->Value                                ));}
            else if (line.contains("VendName"   )){line.append(QString(" \"%1\";").arg(venderName                                      ));}
            else if (line.contains("ProdTypeStr")){line.append(QString(" \"%1\";").arg(prodTypeStr                                     ));}
            else if (line.contains("ProdType"   )){line.append(QString(" %1;"    ).arg(pProdType->Value                                ));}
            else if (line.contains("ProdCode"   )){line.append(QString(" %1;"    ).arg(pProdCode->Value                                ));}
            else if (line.contains("MajRev"     )){line.append(QString(" %1;"    ).arg(devMajRev                                       ));}
            else if (line.contains("MinRev"     )){line.append(QString(" %1;"    ).arg(devMinRev                                       ));}
            else if (line.contains("ProdName"   )){line.append(QString(" \"%1\";").arg(prodName                                        ));}
            else if (line.contains("Catalog"    )){line.append(QString(" %1;"    ).arg("\"0\""                                         ));}
            else if (line.contains("Default"    )){line.append(QString(" %1;"    ).arg("0x0001"                                        ));}
            else if (line.contains("PollInfo"   )){line.append(QString(" %1;"    ).arg("0x0001,1,1"                                    ));}
            else if (line.contains("Input1"     )){line.append(QString(" %1,0,0x000F,\"Input Assembly 1\",6,\"20 04 24 64 30 03\",\"%2\";").arg(inputLength).arg(inputObjectNames));}
            else if (line.contains("Output1"    )){line.append(QString(" %1,0,0x000F,\"Output Assembly 2\",6,\"20 04 24 96 30 03\",\"%2\";").arg(outputLength).arg(outputObjectNames));}

            contents.append(line);
        }
        file.close();

        // [6] TODO 구현: 파일 저장 (Write)
        QFile saveFile(path);
        if(saveFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            QTextStream saveStream(&saveFile);
            saveStream.setCodec("UTF-8"); // 인코딩 설정 (필요시 "ISO-8859-1" 등으로 변경)

            for(const QString& contentLine : qAsConst(contents)) {
                saveStream << contentLine << "\n"; // 줄바꿈 추가
            }
            saveFile.close();
            qDebug() << "EDS File created successfully at:" << path;
        }
        else
        {
            qDebug() << "Failed to save EDS file at:" << path;
        }
    }

private:
    ProtocolManager * pProtocolManager;
};
#endif // FILEHELPER_H
