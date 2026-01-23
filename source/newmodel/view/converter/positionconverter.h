#ifndef POSITIONCONVERTER_H
#define POSITIONCONVERTER_H

#include "source/service/coreservice.h"
#include "source/newmodel/view/converter/tagvalueconverter.h"

class PositionConverter: public TagValueConverter
{
    Q_OBJECT

public:
    int    PosiResolution  = 10000 ;

    static PositionConverter * getInstance()
    {
        static PositionConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new PositionConverter();
        }

        return mpSelf;
    }

    explicit PositionConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_POS_RESOLUTION;

        Name = "PositionConverter";
        PosiResolution = pValveSP->getPositionResolution();
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        TagModel * pTag = pTagList->at(0);

        bool ok;

        double value = inValue.toDouble(&ok);

        if (ok) {
            // 2. 변환 성공 시: 포지션 해상도로 다시 변환
            gain = 100000 / PosiResolution;

            double result = value / gain;

            if (value == 0.0)
            {
                pTag->setValue("0");
            }

            int magnitude = qFloor(qLn(gain)/ qLn(10));

            // 3. 'f' 포맷으로 문자열 변환
            QString str = QString::number(result, 'f', magnitude);

            trimeZero(&str);

            pTag->setValue(str);
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
            value = pTag->Value.toDouble(&ok);
        }
        else{
            value = pTag->GetWriteValue().toDouble(&ok);
        }

        if (ok) {
            // 2. Gain 계산 (pGV 포인터가 클래스 멤버라고 가정)
            // 기존 함수와 동일한 로직으로 Gain을 구합니다.
            double calcGain = 100000 / PosiResolution;
            int result = value * calcGain;

            return QString::number(result, 'f', 0);
        }
        else {
            // 변환 실패 시 기본값 (상황에 따라 "0" 또는 원본 리턴)
            return "0";
        }
    }

public slots:
    void onValveChangedPositionResolution(){
        PosiResolution = pValveSP->getPositionResolution();
        emit signalEventValueChanged();
    }
};

#endif // POSITIONCONVERTER_H
