#ifndef PLAYLISTSCONTROLLER_H
#define PLAYLISTSCONTROLLER_H

#include <QObject>
#include <QString>

#include "mopidymodels.h"
#include "controllerinterface.h"
#include "mopiqy_export.h"

namespace Mopidy {
    namespace Core {
        class LIBMOPIQY_EXPORT PlaylistsController : public ControllerInterface
        {
            Q_OBJECT

        public:
            PlaylistsController(Mopidy::MopidyClient *mopidyClient);
            ~PlaylistsController();

        public slots:
            /*
             * functions from Core API
             */
            void create(const QString &name, const QString &uri_scheme = "");
            void deletePl(const QString &uri);
            void filter(const QHash<QString, QString> &criteria);
            void lookup(const QString &uri);
            void refresh(const QString &uri = "");
            void save(const Mopidy::Models::Playlist &pl);
            void get_playlists(const bool &include_tracks = false);

        signals:
            void onCreate(const Mopidy::Models::Playlist &pl);
            void onFilter(const Mopidy::Models::Playlists &pls);
            void onLookup(const Mopidy::Models::Playlist &pl);
            void onGetPlaylists(const Mopidy::Models::Playlists &pls);
            void onSave(const Mopidy::Models::Playlist &pl);

        protected:
            void processJsonResponse(const int &idt, const QJsonValue &jv);

        private:
            enum PLSEnum
            {
                PLS_CREATE,
                PLS_FILTER,
                PLS_LOOKUP,
                PLS_GETPLAYLISTS,
                PLS_SAVE
            };
        };
    }
}

#endif //PLAYLISTSCONTROLLER_H
