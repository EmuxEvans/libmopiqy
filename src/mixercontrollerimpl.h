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

public slots:
    void getMute();
    void setMute(bool);
    void getVolume();
    void setVolume(int);

private:
    MopidyClientPrivate *m_mcp;
};

#endif //MIXERCONTROLLER_H
