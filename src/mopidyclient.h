#ifndef MOPIDYCLIENT_H
#define MOPIDYCLIENT_H

#include <QJsonValue>
#include <QJsonObject>

#include <QHash>
#include <QObject>

#include "mopidymodels.h"
#include "eventlistener.h"

#include "playbackcontroller.h"
#include "playlistscontroller.h"
#include "tracklistcontroller.h"
#include "librarycontroller.h"

#include "mopiqy_export.h"

namespace Mopidy {

    namespace Internal {
        class JsonWebSocket;
        class JsonRpcHandler;
    }

    class LIBMOPIQY_EXPORT MopidyClient : public QObject
    {
        Q_OBJECT

    public:
        MopidyClient(QObject *parent = 0);
        ~MopidyClient();

        QString clientVersion() const;

        /*
         * Connection handling
         */
        bool connectTo(const QString &host, const qint16 &port, const QString &path);
        void disconnectClient();

        // access to controllers and listener
        Mopidy::Core::EventListener *coreListener() const;

        Mopidy::Core::PlaybackController *playbackController() const;
        Mopidy::Core::PlaylistsController *playlistsController() const;
        Mopidy::Core::TracklistController *tracklistController() const;
        Mopidy::Core::LibraryController *libraryController() const;

    signals:
        /*
         * Connection handling
         */
        void connected();
        void disconnected();
        void connectionError(const int &code, const QString &message);
        void messageError(const int &code, const QString &message);

    private slots:
        void onJwsConnected();
        void onJwsDisconnected();

    private:
        void deleteAll();
        void createAll();

    private:
        Mopidy::Internal::JsonWebSocket *m_jwSocket;
        Mopidy::Internal::JsonRpcHandler *m_jrHandler;

        Mopidy::Core::EventListener *m_coreListener;
        Mopidy::Core::PlaybackController *m_playbackController;
        Mopidy::Core::PlaylistsController *m_playlistsController;
        Mopidy::Core::TracklistController *m_tracklistController;
        Mopidy::Core::LibraryController *m_libraryController;
    };
}

#endif // MOPIDYCLIENT_H
