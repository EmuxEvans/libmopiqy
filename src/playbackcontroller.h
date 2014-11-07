#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include <QObject>

#include "mopidymodels.h"
#include "controllerinterface.h"
#include "mopiqy_export.h"

namespace Mopidy {
    namespace Core {
        class LIBMOPIQY_EXPORT PlaybackController : public ControllerInterface
        {
            Q_OBJECT

        public:

            PlaybackController(Mopidy::MopidyClient *mopidyClient);
            ~PlaybackController();

        public slots:
            /*
             * functions from Core API
             */
            void change_track(const Mopidy::Models::TlTrack &track, const int &on_error_step = 1);
            void get_current_tltrack();
            void get_current_track();
            void set_mute(const bool &mute);
            void get_mute();
            void next();
            void pause();
            void play(const Mopidy::Models::TlTrack &tltrack, const int &on_error_step = 1);
            void previous();
            void resume();
            void seek(const int &time_position);
            void get_state();
            void stop(const bool &clear_current_track = false);
            void get_time_position();
            void set_volume(const int &volume);
            void get_volume();

        signals:
            void onGetCurrentTlTrack(const Mopidy::Models::TlTrack &);
            void onGetCurrentTrack(const Mopidy::Models::Track &);
            void onSeek(const bool &);
            void onGetState(const Core::PlaybackState &);
            void onGetTimePosition(const int &);
            void onGetVolume(const int &);

        protected:
            void processJsonResponse(const int &idt, const QJsonValue &jo);

        private:
            enum PCEnum {
                PC_NONE,
                PC_GETCURRENTTLTRACK,
                PC_GETCURRENTTRACK,
                PC_SEEK,
                PC_GETSTATE,
                PC_GETTIMEPOSITION,
                PC_GETVOLUME,
                PC_GETMUTE
            };
        };
    }
}

#endif //PLAYBACKCONTROLLER_H
