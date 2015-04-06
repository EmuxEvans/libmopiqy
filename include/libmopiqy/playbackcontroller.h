#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include <QObject>
#include <libmopiqy/libmopiqy_export.h>
#include <libmopiqy/mopidymodels.h>

class LIBMOPIQY_EXPORT PlaybackController : public QObject
{
    Q_OBJECT

public slots:
    virtual void getCurrentTlTrack() = 0;
    virtual void getCurrentTrack() = 0;
    virtual void getState() = 0;
    virtual void getStreamTitle() = 0;
    virtual void getTimePosition() = 0;
    virtual void next() = 0;
    virtual void pause() = 0;
    virtual void play(const Mopidy::TlTrack &tltrack = Mopidy::TlTrack()) = 0;
    virtual void previous() = 0;
    virtual void resume() = 0;
    virtual void seek(const int &timePosition) = 0;
    virtual void stop() = 0;

signals:
    void currentTlTrackReceived(const Mopidy::TlTrack &tltrack);
    void currentTrackReceived(const Mopidy::Track &track);
    void stateReceived(const Mopidy::PlaybackState &state);
    void streamTitleReceived(const QString &streamTitle);
    void timePositionReceived(const int &timePosition);
    void seekReceived(const bool &ack);
};

#endif //PLAYBACKCONTROLLER_H
