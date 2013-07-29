#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include <QObject>

#include "mopidymodels.h"
#include "controllerinterface.h"
#include "mopiqy_export.h"

namespace Mopidy {
    namespace Core {
        class MOPIQY_CORE_EXPORT PlaybackController : public QObject, public ControllerInterface
        {
            Q_OBJECT

        public:

            PlaybackController(Mopidy::Internal::JsonRpcHandler *jrHandler, QObject *parent = 0);
            ~PlaybackController();

            /*
             * functions from Core API
             */
            void change_track(const Mopidy::Models::TlTrack &track, const int &on_error_step = 1);

            void get_consume();
            void set_consume(const bool &);

            void get_current_tltrack();
            void get_current_track();

            void next();
            void pause();
            void play(const Mopidy::Models::TlTrack &tltrack, const int &on_error_step = 1);

            void get_random();
            void set_random(const bool &);

            void get_repeat();
            void set_repeat(const bool &);

            void resume();

            void seek(const int &time_position);

            void get_single();
            void set_single(const bool &);

            void get_state();

            void stop(const bool &clear_current_track = false);

            void get_time_position();

            void get_tltrack_at_eot();
            void get_tltrack_at_next();
            void get_tltrack_at_previous();

            void get_tracklist_position();

            void set_volume(const int &volume);
            void get_volume();

        signals:
            void onGetConsume(const bool &);
            void onGetCurrentTlTrack(const Mopidy::Models::TlTrack &);
            void onGetCurrentTrack(const Mopidy::Models::Track &);
            void onGetRandom(const bool &);
            void onGetRepeat(const bool &);
            void onSeek(const bool &);
            void onGetSingle(const bool &);
            void onGetState(const Core::PlaybackState &);
            void onGetTimePosition(const int &);
            void onGetTlTrackAtEot(const Mopidy::Models::TlTrack &);
            void onGetTlTrackAtNext(const Mopidy::Models::TlTrack &);
            void onGetTlTrackAtPrevious(const Mopidy::Models::TlTrack &);
            void onGetTracklistPosition(const int &);
            void onGetVolume(const int &);

        protected:
            void processJsonResponse(const int &id, const QJsonValue &jo);

        private:
            enum PCEnum {
                PC_GETCONSUME,
                PC_GETCURRENTTLTRACK,
                PC_GETCURRENTTRACK,
                PC_GETRANDOM,
                PC_GETREPEAT,
                PC_GETSINGLE,
                PC_SEEK,
                PC_GETSTATE,
                PC_GETTIMEPOSITION,
                PC_GETTLTRACKATEOT,
                PC_GETTLTRACKATNEXT,
                PC_GETTLTRACKATPREVIOUS,
                PC_GETTRACKLISTPOSITION,
                PC_GETVOLUME
            };
        };
    }
}

#endif //PLAYBACKCONTROLLER_H
