#ifndef MIXERCONTROLLERIMPL_H
#define MIXERCONTROLLERIMPL_H

#include "libmopiqy/mixercontroller.h"

class MopidyClientPrivate;

class MixerControllerImpl : public MixerController
{
    Q_OBJECT

public:
    MixerControllerImpl(MopidyClientPrivate *parent);
    ~MixerControllerImpl();

    // process responses
    void pr_getMute(const QJsonValue &response);
    void pr_setMute(const QJsonValue &response);
    void pr_getVolume(const QJsonValue &response);
    void pr_setVolume(const QJsonValue &response);

public slots:
    void getMute();
    void setMute(bool);
    void getVolume();
    void setVolume(int);

private:
    MopidyClientPrivate *m_mcp;
};

#endif //MIXERCONTROLLER_H
