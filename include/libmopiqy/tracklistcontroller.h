#ifndef TRACKLISTCONTROLLER_H
#define TRACKLISTCONTROLLER_H

#include <QObject>
#include <libmopiqy/libmopiqy_export.h>
#include <libmopiqy/mopidymodels.h>

class LIBMOPIQY_EXPORT TracklistController : public QObject
{
    Q_OBJECT

public slots:
    virtual void add(const QStringList &uris, const int &atPosition = -1) = 0;
    virtual void clear() = 0;
    virtual void eotTrack(const Mopidy::TlTrack &tltrack) = 0;
    virtual void filter(const QMap<QString, QVariantList> &criteria) = 0;
    virtual void getConsume() = 0;
    virtual void getLength() = 0;
    virtual void getRandom() = 0;
    virtual void getRepeat() = 0;
    virtual void getSingle() = 0;
    virtual void getTlTracks() = 0;
    virtual void getTracks() = 0;
    virtual void getVersion() = 0;
    virtual void index(const Mopidy::TlTrack &tltrack) = 0;
    virtual void move(const int &start, const int &end, const int &toPosition) = 0;
    virtual void nextTrack(const Mopidy::TlTrack &tltrack = Mopidy::TlTrack()) = 0;
    virtual void previousTrack(const Mopidy::TlTrack &tltrack = Mopidy::TlTrack()) = 0;
    virtual void remove(const QMap<QString, QVariantList> &criteria) = 0;
    virtual void setConsume(const bool &consume) = 0;
    virtual void setRandom(const bool &random) = 0;
    virtual void setRepeat(const bool &repeat) = 0;
    virtual void setSingle(const bool &single) = 0;
    virtual void shuffle(const int &start = -1, const int &stop = -1) = 0;
    virtual void slice(const int &start, const int &stop) = 0;

signals:
    void addDone(const Mopidy::TlTracks &tltracks);
    void eotTrackReceived(const Mopidy::TlTrack &tltrack);
    void filterDone(const Mopidy::TlTracks &tltracks);
    void consumeReceived(const bool &consume);
    void lengthReceived(const int &length);
    void randomReceived(const bool &random);
    void repeatReceived(const bool &repeat);
    void singleReceived(const bool &single);
    void tlTracksReceived(const Mopidy::TlTracks &tlTracks);
    void tracksReceived(const Mopidy::Tracks &tracks);
    void versionReceived(const int &version);
    void indexReceived(const int &index);
    void nextTrackReceived(const Mopidy::TlTrack &nextTlTrack);
    void previousTrackReceived(const Mopidy::TlTrack &previousTlTrack);
    void removeDone(const Mopidy::TlTracks &tltracks);
    void sliceDone(const Mopidy::TlTrack &tltrack);
};

#endif //TRACKLISTCONTROLLER_H
