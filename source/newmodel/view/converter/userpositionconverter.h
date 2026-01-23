#ifndef USERPOSITIONCONVERTER_H
#define USERPOSITIONCONVERTER_H

#include "source/service/coreservice.h"
#include "source/newmodel/view/converter/tagvalueconverter.h"

class UserPositionConverter: public TagValueConverter
{
    Q_OBJECT

public:
    int    PosiResolution  = 10000 ;
    int    ScalingUnit     = 6     ;
    double ClosestPosi     = 0     ;
    double OpenPosi        = 100000;
    double BankClosestPosi = 0     ;
    double BankOpenPosi    = 100000;

    static UserPositionConverter * getInstance()
    {
        static UserPositionConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new UserPositionConverter();
        }

        return mpSelf;
    }

    explicit UserPositionConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_POS_RESOLUTION;

        Name = "PositionConverter";
        PosiResolution = pValveSP->getPositionResolution();
    }

    void regRS232ScalingTag(TagModel * pTag) // todo : reg position resolution tag
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedRS232ScalingUnit(QString)));
    }

    void regRS232ClosestPosiTag(TagModel * pTag) // todo : reg position resolution tag
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedRS232ClosestPosi(QString)));
    }

    void regRS232OpenPosiTag(TagModel * pTag) // todo : reg position resolution tag
    {
        connect(pTag   , SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedRS232OpenPosi   (QString)));
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        TagModel * pTag = pTagList->at(0);

        bool ok;

        // 1. 입력 문자열을 실수(double)로 변환
        double value = inValue.toDouble(&ok);

        if (ok) {
            value = value - ClosestPosi;
            // 2. 변환 성공 시: 포지션 해상도로 다시 변환
            double calcGain = (OpenPosi - ClosestPosi) / PosiResolution;
            double result = (value / calcGain);
            double absResult = qAbs(result);

            if (value == 0.0)
            {
                pTag->setValue("0");
            }

            int magnitude = qFloor(qLn(absResult)/ qLn(10));

            int precision = 6;
            int decimalPlaces = precision - 1 - (int)magnitude;

            QString str;

            if (decimalPlaces > 0) {
                str = QString::number(result, 'f', decimalPlaces);
                trimeZero(&str);

                pTag->setValue(str);
            }
            else {
                pTag->setValue(QString::number(result, 'f', 0));
            }
        }
        else {
            pTag->setValue("");
        }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return "";

        TagModel * pTag = pTagList->at(0);
        bool ok;
        double value;

        if(pTag->IsEdit == false){
            qDebug() << "[" << Q_FUNC_INFO << "]Tag Value = " << pTag->Value;

            value = pTag->Value.toDouble(&ok);
        }
        else{
            qDebug() << "[" << Q_FUNC_INFO << "]Tag Write Value = " << pTag->GetWriteValue();

            value = pTag->GetWriteValue().toDouble(&ok);
        }



        if (ok) {
            // 2. Gain 계산 (pGV 포인터가 클래스 멤버라고 가정)
            // 기존 함수와 동일한 로직으로 Gain을 구합니다.
            qDebug() << "[" << Q_FUNC_INFO << "]OpenPosi = " << OpenPosi << ", ClosestPosi = " << ClosestPosi << ", PosiResolution = " << PosiResolution;

            double calcGain = (OpenPosi - ClosestPosi) / PosiResolution;
            double result = value * calcGain;
            result = result + ClosestPosi;
            double absResult = qAbs(result);

            if (result == 0.0)
            {
                return "0";
            }

            int magnitude = qFloor(qLn(absResult)/ qLn(10));

            int precision = 6;
            int decimalPlaces = precision - 1 - (int)magnitude;

            QString str;

            if (decimalPlaces > 0) {
                str = QString::number(result, 'f', decimalPlaces);
                trimeZero(&str);
            }
            else {
                str = QString::number(result, 'f', 0);
            }
            return str;
        }
        else {
            // 변환 실패 시 기본값 (상황에 따라 "0" 또는 원본 리턴)
            return "0";
        }
    }

public slots:
    void onTagChangedRS232ScalingUnit(QString value){

        bool ok;
        int unit = value.toInt(&ok, 10);

        if(!ok)
        {
            ScalingUnit = 6;
        }
        else
        {
            ScalingUnit = unit;
        }

        switch (ScalingUnit) {
        case 0:
            ClosestPosi = 0.0;
            OpenPosi    = 1.0;
            break;
        case 1:
            ClosestPosi =  0.0;
            OpenPosi    = 10.0;
            break;
        case 2:
            ClosestPosi =  0.0;
            OpenPosi    = 90.0;
            break;
        case 3:
            ClosestPosi =   0.0;
            OpenPosi    = 100.0;
            break;
        case 4:
            ClosestPosi =    0.0;
            OpenPosi    = 1000.0;
            break;
        case 5:
            ClosestPosi =     0.0;
            OpenPosi    = 10000.0;
            break;
        case 6:
            ClosestPosi =      0.0;
            OpenPosi    = 100000.0;
            break;
        case 7:
            ClosestPosi = BankClosestPosi;
            OpenPosi    = BankOpenPosi   ;
            return;
        }
        emit signalEventValueChanged();
    }

    void onTagChangedRS232ClosestPosi(QString value){
        double closestPosiValue;

        bool ok;
        closestPosiValue = value.toDouble(&ok);

        if(!ok)
        {
            closestPosiValue = 0.0;
        }

        BankClosestPosi = closestPosiValue;

        if(ScalingUnit == 7)
        {
            ClosestPosi = BankClosestPosi;
        }
        emit signalEventValueChanged();
    }

    void onTagChangedRS232OpenPosi(QString value)
    {
        double openPosiValue;

        bool ok;
        openPosiValue = value.toDouble(&ok);

        if(!ok)
        {
            openPosiValue = 100000.0;
        }

        BankOpenPosi = openPosiValue;

        if(ScalingUnit == 7)
        {
            OpenPosi = BankOpenPosi;
        }
        emit signalEventValueChanged();
    }

    void onValveChangedPositionResolution(){
        PosiResolution = pValveSP->getPositionResolution();
        emit signalEventValueChanged();
    }
};

#endif // USERPOSITIONCONVERTER_H
