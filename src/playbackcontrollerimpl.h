#ifndef PLAYBACKCONTROLLERIMPL_H
#define PLAYBACKCONTROLLERIMPL_H

#include "libmopiqy/playbackcontroller.h"
#include "basecontrollerimpl.h"

class PlaybackControllerImpl : public PlaybackController, public BaseControllerImpl
{
    Q_OBJECT

public:
    PlaybackControllerImpl(MopidyClientPrivate *parent);
    ~PlaybackControllerImpl();

    // process responses
    void pr_getCurrentTlTrack(const QJsonValue &response);
    void pr_getCurrentTrack(const QJsonValue &response);
    void pr_getState(const QJsonValue &response);
    void pr_getStreamTitle(const QJsonValue &response);
    void pr_getTimePosition(const QJsonValue &response);
    void pr_seek(const QJsonValue &response);

    // PlaybackController interface
public slots:
    void getCurrentTlTrack();
    void getCurrentTrack();
    void getState();
    void getStreamTitle();
    void getTimePosition();
    void next();
    void pause();
    void play(const Mopidy::TlTrack &tltrack);
    void previous();
    void resume();
    void seek(const int &timePosition);
    void stop();
};

#endif //PLAYBACKCONTROLLERIMPL_H
