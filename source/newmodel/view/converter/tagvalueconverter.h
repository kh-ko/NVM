#ifndef TAGVALUECONVERTER_H
#define TAGVALUECONVERTER_H

#include <QObject>

class TagValueConverter: public QObject{
    Q_OBJECT

public:
    explicit TagValueConverter(QObject *parent = nullptr):QObject(parent)
    {

    }

    virtual QString convertToTagValue(QString inValue, double gain)
    {
        Q_UNUSED(inValue)
        Q_UNUSED(gain)
        return "";
    }

    virtual QString convertToProtocolValue(QString inValue, double gain, int length)
    {
        Q_UNUSED(inValue)
        Q_UNUSED(gain)
        Q_UNUSED(length)
        return "";
    }

    void regSignal(QObject * regObj, const char * pMemberFunc)
    {
        connect(this, SIGNAL(signalEventValueChanged()), regObj, pMemberFunc);
    }

    void unRegSignal(QObject * regObj)
    {
        disconnect(this, SIGNAL(signalEventValueChanged()), regObj, nullptr);
    }

signals:
    void signalEventValueChanged();

protected:
    QString applyLengthConstraint(QString result, int length)
    {
        if (length == -1) {
            return result;
        }

        if (result.length() > length) {
            // 결과가 length보다 길면 앞에서부터 자름 (오른쪽에서 length만큼 남김)
            // 예: "12345", length=3 -> "345"
            return result.right(length);
        } else {
            // 결과가 length보다 짧으면 앞에 '0'을 채움
            // 예: "12", length=4 -> "0012"
            return result.rightJustified(length, '0');
        }
    }

    void trimeZero(QString * pValue)
    {
        if (pValue->contains('.'))
        {
            while (pValue->endsWith('0'))
            {
                pValue->chop(1);
            }

            if (pValue->endsWith('.'))
            {
                pValue->chop(1);
            }
        }
    }
};
#endif // TAGVALUECONVERTER_H
