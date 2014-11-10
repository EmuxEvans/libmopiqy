#ifndef TRACKLISTCONTROLLER_H
#define TRACKLISTCONTROLLER_H

#include "controllerinterface.h"
#include "mopidymodels.h"
#include "mopiqy_export.h"

namespace Mopiqy {
class LIBMOPIQY_EXPORT TracklistController : public ControllerInterface
{
    Q_OBJECT

public:
    TracklistController(RemoteClient *remoteClient);
    ~TracklistController();

public slots:
    /*
             * functions from Core API
             */
    void add(const Models::Tracks &tracks, const int &at_position = -1);
    void add(const QString &uri, const int &at_position = -1);
    void clear();
    void filter(const QHash<QString, QString> &criteria);
    void index(const Models::TlTrack &);
    void get_length();
    void move(const int &start, const int &end, const int &to_position);
    void remove(const QHash<QString, QString> &criteria);
    void shuffle(const int &start = -1, const int &end = -1);
    void slice(const int &start, const int &end);
    void get_tltracks();
    void get_tracks();
    void get_version();

    /*
             * Since mopidy 0.16
             */
    void get_consume();
    void set_consume(const bool &);
    void get_random();
    void set_random(const bool &);
    void get_repeat();
    void set_repeat(const bool &);
    void get_single();
    void set_single(const bool &);
    void eot_track(const Models::TlTrack &tltrack = Models::TlTrack());
    void next_track(const Models::TlTrack &tltrack = Models::TlTrack());
    void previous_track(const Models::TlTrack &tltrack = Models::TlTrack());

signals:
    void onAdd(const Models::TlTracks &);
    void onFilter(const Models::TlTracks &);
    void onIndex(const int &);
    void onGetLength(const int &);
    void onRemove(const Models::TlTracks &);
    void onSlice(const Models::TlTrack &);
    void onGetTlTracks(const Models::TlTracks &);
    void onGetTracks(const Models::Tracks &);
    void onGetVersion(const int &);
    void onGetConsume(const bool &);
    void onGetRandom(const bool &);
    void onGetRepeat(const bool &);
    void onGetSingle(const bool &);
    void onEotTrack(const Models::TlTrack &);
    void onNextTrack(const Models::TlTrack &);
    void onPreviousTrack(const Models::TlTrack &);

protected:
    void processJsonResponse(const int &idt, const QJsonValue &jv);

private:
    enum TCEnum
    {
        TC_ADD,
        TC_FILTER,
        TC_INDEX,
        TC_GETLENGTH,
        TC_REMOVE,
        TC_SLICE,
        TC_GETTLTRACKS,
        TC_GETTRACKS,
        TC_GETVERSION,
        TC_GETCONSUME,
        TC_GETRANDOM,
        TC_GETREPEAT,
        TC_GETSINGLE,
        TC_EOTTRACK,
        TC_NEXTTRACK,
        TC_PREVIOUSTRACK
    };
};
}

#endif //TRACKLISTCONTROLLER_H
