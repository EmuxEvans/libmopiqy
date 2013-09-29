#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QTime>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), m_ui(new Ui::MainWidget)
{
    m_ui->setupUi(this);
    m_client = new Mopidy::MopidyClient(this);

    // connection to client signals
    connect(m_client, &Mopidy::MopidyClient::connected, this, &MainWidget::onMC_Connected);
    connect(m_client, &Mopidy::MopidyClient::disconnected, this, &MainWidget::onMC_Disconnected);
    connect(m_client, &Mopidy::MopidyClient::connectionError, this, &MainWidget::onMC_ConnectionError);
    connect(m_client, &Mopidy::MopidyClient::messageError, this, &MainWidget::onMC_MessageError);

    // connection to eventlistener
    connect(m_client->eventListener(), &Mopidy::Core::EventListener::track_playback_ended,
            this, &MainWidget::onEL_TrackPlaybackEnded);
    connect(m_client->eventListener(), &Mopidy::Core::EventListener::track_playback_started,
            this, &MainWidget::onEL_TrackPlaybackStarted);

    // connect to controllers signals
    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onGetPlaylists,
            this, &MainWidget::onPlaylistsController_GetPlaylists);
    connect(m_client->playlistsController(), &Mopidy::Core::PlaylistsController::onLookup,
            this, &MainWidget::onPlaylistsController_Lookup);
    connect(m_client->tracklistController(), &Mopidy::Core::TracklistController::onAdd,
            this, &MainWidget::onTracklistController_Add);
    connect(m_client->tracklistController(), &Mopidy::Core::TracklistController::onGetTlTracks,
            this, &MainWidget::onTracklistController_GetTlTracks);

    //
    qWarning() << "Using libmopiqy" << m_client->clientVersion();
}

MainWidget::~MainWidget()
{
    delete m_ui;
}

void MainWidget::on_btConnect_clicked()
{
    qWarning() << "connecting client request";
    m_client->connectTo(m_ui->leHost->text(), m_ui->sbPort->value(), m_ui->lePath->text());
}

void MainWidget::on_btDisconnect_clicked()
{
    qWarning() << "disconnecting client request";
    m_client->disconnectClient();
}

void MainWidget::on_btGetPlaylists_clicked()
{
    qWarning() << "get playlists request";
    //
    // Controllers functions are thoses defined from
    // http://docs.mopidy.com/en/latest/api/core/
    //
    m_client->playlistsController()->get_playlists();
}

void MainWidget::on_btSetAsCurrentPlaylist_clicked()
{
    if(m_ui->lwPlaylists->selectedItems().count() > 0)
    {
        QListWidgetItem *selItem = m_ui->lwPlaylists->selectedItems().at(0);
        QVariant vData = selItem->data(Qt::UserRole);

        //
        // Mopidy::Models can be casted from QVariant
        //
        if(vData.canConvert<Mopidy::Models::Playlist>())
        {
            Mopidy::Models::Playlist pl = qvariant_cast<Mopidy::Models::Playlist>(vData);

            qWarning() << "set current playlist" << pl.name << "[" << pl.tracks.count() << " tracks] @" << pl.uri;
            m_client->tracklistController()->clear();
            m_client->tracklistController()->add(pl.uri);
        }
    }
}

void MainWidget::on_lwPlaylists_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)

    if(current)
    {
        QVariant vData = current->data(Qt::UserRole);

        //
        // Mopidy::Models can be casted from QVariant
        //
        if(vData.canConvert<Mopidy::Models::Playlist>())
        {
            Mopidy::Models::Playlist pl = qvariant_cast<Mopidy::Models::Playlist>(vData);

            qWarning() << "request lookup for playlist" << pl.name;
            m_client->playlistsController()->lookup(pl.uri);
        }
    }
}

void MainWidget::on_btRefreshTracklist_clicked()
{
    qWarning() << "get current tracklist request";
    m_client->tracklistController()->get_tltracks();
}

void MainWidget::on_tbPlay_clicked()
{
    if(m_currentTltracks.count() > 0)
    {
        qWarning() << "play request";
        m_client->playbackController()->play(m_currentTltracks.at(0));
    }
}

void MainWidget::on_tbStop_clicked()
{
    qWarning() << "stop request";
    m_client->playbackController()->stop();
}

void MainWidget::on_tbNext_clicked()
{
    qWarning() << "next request";
    m_client->playbackController()->next();
}

/*
 * MopidyClient slots
 */
void MainWidget::onMC_Connected()
{
    qWarning() << "mopidy client connected";

    // Enable controls
    setControlsState(true);
}

void MainWidget::onMC_Disconnected()
{
    qWarning() << "mopidy client disconnected";

    // Disable controls
    setControlsState(false);
}

void MainWidget::onMC_ConnectionError(const int &code, const QString &message)
{
    qWarning() << "mopidy client connection error" << code << message;
}

void MainWidget::onMC_MessageError(const int &code, const QString &message)
{
    qWarning() << "mopidy client message error" << code << message;
}

/*
 * EventListener slots
 */
void MainWidget::onEL_TrackPlaybackEnded(const Mopidy::Models::TlTrack &tl_track, const int &time_position)
{
    Q_UNUSED(time_position)

    qWarning() << "event: playback ended" << tl_track.tlid;
    m_ui->lbCurrentName->clear();
    m_ui->lbCurrentInfos->clear();
    m_ui->lbCurrentLength->clear();
}

void MainWidget::onEL_TrackPlaybackStarted(const Mopidy::Models::TlTrack &tl_track)
{
    qWarning() << "event: playback started" << tl_track.tlid;
    m_ui->lbCurrentName->setText(tl_track.track.name);
    m_ui->lbCurrentInfos->setText(tl_track.track.album.name);

    QTime trackLength(0, 0, 0);
    m_ui->lbCurrentLength->setText(trackLength.addMSecs(tl_track.track.length).toString("[mm:ss]"));
}

/*
 * Controllers slots
 */
void MainWidget::onPlaylistsController_GetPlaylists(const Mopidy::Models::Playlists &pls)
{
    qWarning() << pls.count() << "playlists received";

    m_ui->lwPlaylists->clear();
    foreach(Mopidy::Models::Playlist pl, pls)
    {
        QListWidgetItem *item = new QListWidgetItem;

        //
        // Mopidy::Models are struct corresponding to definition from
        // http://docs.mopidy.com/en/latest/api/models/
        //
        item->setText(pl.name);

        //
        // Every Mopidy::Models structs can be used as QVariant
        //
        QVariant vPlaylist;
        vPlaylist.setValue(pl);
        item->setData(Qt::UserRole, vPlaylist);

        m_ui->lwPlaylists->addItem(item);
    }
}

void MainWidget::onPlaylistsController_Lookup(const Mopidy::Models::Playlist &pl)
{
    qWarning() << "playlist lookup done";
    m_ui->lwTracks->clear();

    foreach(Mopidy::Models::Track track, pl.tracks)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(1, track.name);
        item->setText(2, track.album.name);

        QStringList artistsNames;
        foreach (Mopidy::Models::Artist artist, track.artists) {
            artistsNames << artist.name;
        }
        item->setText(3, artistsNames.join(", "));

        m_ui->lwTracks->addTopLevelItem(item);
    }

    for(int i = 0; i < m_ui->lwTracks->columnCount(); ++i)
        m_ui->lwTracks->resizeColumnToContents(i);
}

void MainWidget::onTracklistController_Add(const Mopidy::Models::TlTracks &tltracks)
{
    qWarning() << tltracks.count() << "Tl_Tracks in tracklist";
    m_currentTltracks = tltracks;
}

void MainWidget::onTracklistController_GetTlTracks(const Mopidy::Models::TlTracks &tltracks)
{
    qWarning() << "playlist lookup done";
    m_ui->lwTlTracks->clear();

    foreach(Mopidy::Models::TlTrack tltrack, tltracks)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString::number(tltrack.tlid));
        item->setText(1, tltrack.track.name);
        item->setText(2, tltrack.track.album.name);

        QStringList artistsNames;
        foreach (Mopidy::Models::Artist artist, tltrack.track.artists) {
            artistsNames << artist.name;
        }
        item->setText(3, artistsNames.join(", "));

        m_ui->lwTlTracks->addTopLevelItem(item);
    }

    for(int i = 0; i < m_ui->lwTracks->columnCount(); ++i)
        m_ui->lwTlTracks->resizeColumnToContents(i);
}

void MainWidget::setControlsState(const bool &isConnected)
{
    // enable stated
    m_ui->leHost->setEnabled(!isConnected);
    m_ui->sbPort->setEnabled(!isConnected);
    m_ui->lePath->setEnabled(!isConnected);
    m_ui->btConnect->setEnabled(!isConnected);
    m_ui->btDisconnect->setEnabled(isConnected);

    m_ui->btGetPlaylists->setEnabled(isConnected);
    m_ui->btSetAsCurrentPlaylist->setEnabled(isConnected);

    m_ui->tabWidget->setEnabled(isConnected);

    m_ui->tbPlay->setEnabled(isConnected);
    m_ui->tbStop->setEnabled(isConnected);
    m_ui->tbNext->setEnabled(isConnected);

    // content
    if(!isConnected)
    {
        m_ui->lwPlaylists->clear();
        m_ui->lwTracks->clear();
        m_ui->lbCurrentName->clear();
        m_ui->lbCurrentInfos->clear();
        m_ui->lbCurrentLength->setText("[00:00]");
    }
}
