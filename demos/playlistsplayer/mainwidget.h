#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

#include "mopiqy.h"

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
    void onEL_TrackPlaybackEnded(const Mopiqy::Models::TlTrack &tl_track, const int &time_position);
    void onEL_TrackPlaybackStarted(const Mopiqy::Models::TlTrack &tl_track);

    // Controllers slots
    void onPlaylistsController_GetPlaylists(const Mopiqy::Models::Playlists &pls);
    void onPlaylistsController_Lookup(const Mopiqy::Models::Playlist &pl);
    void onTracklistController_Add(const Mopiqy::Models::TlTracks &);
    void onTracklistController_GetTlTracks(const Mopiqy::Models::TlTracks &);


private:
    void setControlsState(const bool &isConnected);

private:
    Ui::MainWidget *m_ui;

    // Tracklist for managing playback
    Mopiqy::Models::TlTracks m_currentTltracks;
};

#endif //MAINWIDGET_H
