#ifndef TRACKLISTCONTROLLERIMPL_H
#define TRACKLISTCONTROLLERIMPL_H

#include "libmopiqy/tracklistcontroller.h"

class MopidyClientPrivate;

class TracklistControllerImpl : public TracklistController
{
    Q_OBJECT

public:
    TracklistControllerImpl(MopidyClientPrivate *parent);
    ~TracklistControllerImpl();

    // process responses
    void pr_add(const QJsonValue &response);
    void pr_eotTrack(const QJsonValue &response);
    void pr_filter(const QJsonValue &response);
    void pr_consume(const QJsonValue &response);
    void pr_length(const QJsonValue &response);
    void pr_random(const QJsonValue &response);
    void pr_repeat(const QJsonValue &response);
    void pr_single(const QJsonValue &response);
    void pr_tlTracks(const QJsonValue &response);
    void pr_tracks(const QJsonValue &response);
    void pr_version(const QJsonValue &response);
    void pr_index(const QJsonValue &response);
    void pr_nextTrack(const QJsonValue &response);
    void pr_previousTrack(const QJsonValue &response);
    void pr_remove(const QJsonValue &response);
    void pr_slice(const QJsonValue &response);

    // TracklistController interface
public slots:
    void add(const QStringList &uris, const int &atPosition);
    void clear();
    void eotTrack(const Mopidy::TlTrack &tltrack);
    void getConsume();
    void getLength();
    void getRandom();
    void getRepeat();
    void getSingle();
    void getTlTracks();
    void getTracks();
    void getVersion();
    void index(const Mopidy::TlTrack &tltrack);
    void move(const int &start, const int &end, const int &toPosition);
    void nextTrack(const Mopidy::TlTrack &tltrack);
    void previousTrack(const Mopidy::TlTrack &tltrack);
    void setConsume(const bool &consume);
    void setRandom(const bool &random);
    void setRepeat(const bool &repeat);
    void setSingle(const bool &single);
    void shuffle(const int &start, const int &stop);
    void slice(const int &start, const int &stop);

private:
    MopidyClientPrivate *m_mcp;
};

#endif //TRACKLISTCONTROLLERIMPL_H
