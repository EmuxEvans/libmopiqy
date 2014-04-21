#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

#include "mopidyclient.h"

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    // GUI slots
    void on_btConnect_clicked();
    void on_btDescribe_clicked();
    void on_btDisconnect_clicked();
    void on_btGetPlaylists_clicked();
    void on_btSetAsCurrentPlaylist_clicked();
    void on_lwPlaylists_currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);

    void on_btRefreshTracklist_clicked();

    void on_tbPlay_clicked();
    void on_tbStop_clicked();
    void on_tbNext_clicked();

    // MopidyClient slots
    void onMC_Connected();
    void onMC_Describe(const QJsonObject &desc);
    void onMC_Disconnected();
    void onMC_ConnectionError(const int &code, const QString &message);
    void onMC_MessageError(const int &code, const QString &message);

    // EventListener slots
    void onEL_TrackPlaybackEnded(const Mopidy::Models::TlTrack &tl_track, const int &time_position);
    void onEL_TrackPlaybackStarted(const Mopidy::Models::TlTrack &tl_track);

    // Controllers slots
    void onPlaylistsController_GetPlaylists(const Mopidy::Models::Playlists &pls);
    void onPlaylistsController_Lookup(const Mopidy::Models::Playlist &pl);
    void onTracklistController_Add(const Mopidy::Models::TlTracks &);
    void onTracklistController_GetTlTracks(const Mopidy::Models::TlTracks &);


private:
    void setControlsState(const bool &isConnected);

private:
    Ui::MainWidget *m_ui;

    // entry point to mopidy server
    Mopidy::MopidyClient *m_client;

    // Tracklist for managing playback
    Mopidy::Models::TlTracks m_currentTltracks;
};

#endif //MAINWIDGET_H
