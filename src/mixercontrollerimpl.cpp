#include "mixercontrollerimpl.h"
#include "mopidyclient_p.h"

#include <QJsonValue>
#include <QJsonObject>

MixerControllerImpl::MixerControllerImpl(MopidyClientPrivate *parent)
    : MixerController(), m_mcp(parent)
{ }

MixerControllerImpl::~MixerControllerImpl()
{ }

void MixerControllerImpl::pr_getMute(const QJsonValue &response)
{
    emit getMuteReceived(response.toBool());
}

void MixerControllerImpl::pr_setMute(const QJsonValue &response)
{
    emit setMuteReceived(response.toBool());
}

void MixerControllerImpl::pr_getVolume(const QJsonValue &response)
{
    emit getVolumeReceived(response.toInt());
}

void MixerControllerImpl::pr_setVolume(const QJsonValue &response)
{
    emit setVolumeReceived(response.toBool());
}

void MixerControllerImpl::getMute()
{
    m_mcp->sendRequest(
                std::bind(&MixerControllerImpl::pr_getMute, this, std::placeholders::_1),
                "core.mixer.get_mute");
}

void MixerControllerImpl::setMute(bool mute)
{
    QJsonObject params;
    params.insert("mute", mute);
    m_mcp->sendRequest(
                std::bind(&MixerControllerImpl::pr_setMute, this, std::placeholders::_1),
                "core.mixer.set_mute", params);
}

void MixerControllerImpl::getVolume()
{
    m_mcp->sendRequest(
                std::bind(&MixerControllerImpl::pr_getVolume, this, std::placeholders::_1),
                "core.mixer.get_volume");
}

void MixerControllerImpl::setVolume(int volume)
{
    QJsonObject params;
    params.insert("volume", volume);
    m_mcp->sendRequest(
                std::bind(&MixerControllerImpl::pr_setVolume, this, std::placeholders::_1),
                "core.mixer.set_volume", params);
}
