#ifndef MIXERCONTROLLERIMPL_H
#define MIXERCONTROLLERIMPL_H

#include "libmopiqy/mixercontroller.h"
#include "basecontrollerimpl.h"

class MixerControllerImpl : public MixerController, public BaseControllerImpl
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
};

#endif //MIXERCONTROLLER_H
