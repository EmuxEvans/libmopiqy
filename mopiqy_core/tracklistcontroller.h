#ifndef TRACKLISTCONTROLLER_H
#define TRACKLISTCONTROLLER_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "mopidymodels.h"
#include "controllerinterface.h"
#include "mopiqy_export.h"

namespace Mopidy {
    namespace Core {
        class MOPIQY_CORE_EXPORT TracklistController : public QObject, public ControllerInterface
        {
            Q_OBJECT

        public:
            TracklistController(Mopidy::Internal::JsonRpcHandler *jrHandler, QObject *parent = 0);
            ~TracklistController();

            /*
             * functions from Core API
             */
            void add(const Mopidy::Models::Tracks &tracks, const int &at_position = -1);
            void add(const QString &uri, const int &at_position = -1);
            void clear();
            void filter(const Dict &criteria);
            void index(const Mopidy::Models::TlTrack &);
            void get_length();
            void move(const int &start, const int &end, const int &to_position);
            void remove(const Dict &criteria);
            void shuffle(const int &start = -1, const int &end = -1);
            void slice(const int &start, const int &end);
            void get_tltracks();
            void get_tracks();
            void get_version();

        signals:
            void onAdd(const Mopidy::Models::TlTracks &);
            void onFilter(const Mopidy::Models::TlTracks &);
            void onIndex(const int &);
            void onGetLength(const int &);
            void onRemove(const Mopidy::Models::TlTracks &);
            void onSlice(const Mopidy::Models::TlTrack &);
            void onGetTlTracks(const Mopidy::Models::TlTracks &);
            void onGetTracks(const Mopidy::Models::Tracks &);
            void onGetVersion(const int &);

        protected:
            void processJsonResponse(const int &id, const QJsonValue &jv);

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
                TC_GETVERSION
            };
        };
    }
}

#endif //TRACKLISTCONTROLLER_H
