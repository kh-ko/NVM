#ifndef TAGVALUECONVERTER_H
#define TAGVALUECONVERTER_H

#include <QObject>
#include "source/newmodel/view/tag/tagmodel.h"

class TagValueConverter: public QObject{
    Q_OBJECT

public:
    QString Name;

    explicit TagValueConverter(QObject *parent = nullptr):QObject(parent)
    {

    }

    virtual void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain)
    {
        Q_UNUSED(pTagList)
        Q_UNUSED(inValue)
        Q_UNUSED(gain)
    }

    virtual QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain)
    {
        Q_UNUSED(pTagList)
        Q_UNUSED(gain)
        Q_UNUSED(pTagList)
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
