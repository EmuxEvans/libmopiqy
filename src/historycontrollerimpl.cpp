#include "historycontrollerimpl.h"
#include "modeltranslator.h"

HistoryControllerImpl::HistoryControllerImpl(MopidyClientPrivate *parent)
    : HistoryController(), BaseControllerImpl(parent)
{ }

HistoryControllerImpl::~HistoryControllerImpl()
{ }

void HistoryControllerImpl::pr_getHistory(const QJsonValue &response)
{
    QMap<unsigned long, Mopidy::Ref> history;
    const QJsonArray &historyArray = response.toArray();
    foreach(const QJsonValue &historyValue, historyArray)
    {
        const QJsonArray &historyValueTuple = historyValue.toArray();
        Mopidy::Ref ref;
        if(ModelTranslator::fromJson(historyValueTuple.at(1).toObject(), ref))
        {
            history.insert(static_cast<unsigned long>(historyValueTuple.at(0).toDouble()), ref);
        }
    }
    emit historyReceived(history);
}

void HistoryControllerImpl::pr_getLength(const QJsonValue &response)
{
    emit lengthReceived(response.toInt());
}

void HistoryControllerImpl::getHistory()
{
    sendRequest(std::bind(&HistoryControllerImpl::pr_getHistory, this, std::placeholders::_1),
                "core.history.get_history");
}

void HistoryControllerImpl::getLength()
{
    sendRequest(std::bind(&HistoryControllerImpl::pr_getLength, this, std::placeholders::_1),
                "core.history.get_length");
}
