#ifndef PLAYBACKCONTROLLERIMPL_H
#define PLAYBACKCONTROLLERIMPL_H

#include "libmopiqy/playbackcontroller.h"

class MopidyClientPrivate;

class PlaybackControllerImpl : public PlaybackController
{
    Q_OBJECT

public:
    PlaybackControllerImpl(MopidyClientPrivate *parent);
    ~PlaybackControllerImpl();

    // process responses

public slots:

private:
    MopidyClientPrivate *m_mcp;
};

#endif //PLAYBACKCONTROLLERIMPL_H
