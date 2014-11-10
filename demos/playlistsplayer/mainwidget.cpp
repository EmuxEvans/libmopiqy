#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QTime>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), m_ui(new Ui::MainWidget)
{
    m_ui->setupUi(this);

    Mopiqy::RemoteClient *client = Mopiqy::MopiqyHelper::instance()->remoteClient();

    // connection to client signals
    connect(client, &Mopiqy::RemoteClient::clientConnected, this, &MainWidget::onMC_Connected);
    connect(client, &Mopiqy::RemoteClient::clientDisconnected, this, &MainWidget::onMC_Disconnected);
    connect(client, &Mopiqy::RemoteClient::connectionError, this, &MainWidget::onMC_ConnectionError);
    connect(client, &Mopiqy::RemoteClient::messageError, this, &MainWidget::onMC_MessageError);

    // connection to events
    connect(client, &Mopiqy::RemoteClient::track_playback_ended,
            this, &MainWidget::onEL_TrackPlaybackEnded);
    connect(client, &Mopiqy::RemoteClient::track_playback_started,
            this, &MainWidget::onEL_TrackPlaybackStarted);

    // connect to controllers signals
    connect(Mopiqy::MopiqyHelper::instance()->coreController(), &Mopiqy::CoreController::onDescribe,
            this, &MainWidget::onMC_Describe);
    connect(Mopiqy::MopiqyHelper::instance()->coreController(), &Mopiqy::CoreController::onVersion,
            [=](const QString &v) { m_ui->lbMopidyVersion->setText(v); });

    connect(Mopiqy::MopiqyHelper::instance()->playlistsController(), &Mopiqy::PlaylistsController::onGetPlaylists,
            this, &MainWidget::onPlaylistsController_GetPlaylists);
    connect(Mopiqy::MopiqyHelper::instance()->playlistsController(), &Mopiqy::PlaylistsController::onLookup,
            this, &MainWidget::onPlaylistsController_Lookup);
    connect(Mopiqy::MopiqyHelper::instance()->tracklistController(), &Mopiqy::TracklistController::onAdd,
            this, &MainWidget::onTracklistController_Add);
    connect(Mopiqy::MopiqyHelper::instance()->tracklistController(), &Mopiqy::TracklistController::onGetTlTracks,
            this, &MainWidget::onTracklistController_GetTlTracks);

    //
    qWarning() << "Using libmopiqy" << client->clientVersion();
}

MainWidget::~MainWidget()
{
    delete m_ui;
}

void MainWidget::on_btConnect_clicked()
{
    qWarning() << "connecting client request";
    Mopiqy::MopiqyHelper::instance()->remoteClient()->connectTo(m_ui->leHost->text(), m_ui->sbPort->value(), m_ui->lePath->text());
}

void MainWidget::on_btDescribe_clicked()
{
    qWarning() << "describe request";
    Mopiqy::MopiqyHelper::instance()->coreController()->describe();
}

void MainWidget::on_btDisconnect_clicked()
{
    qWarning() << "disconnecting client request";
    Mopiqy::MopiqyHelper::instance()->remoteClient()->disconnectClient();
}

void MainWidget::on_btGetPlaylists_clicked()
{
    qWarning() << "get playlists request";
    //
    // Controllers functions are thoses defined from
    // http://docs.mopidy.com/en/latest/api/core/
    //
    Mopiqy::MopiqyHelper::instance()->playlistsController()->get_playlists();
}

void MainWidget::on_btSetAsCurrentPlaylist_clicked()
{
    if(m_ui->lwPlaylists->selectedItems().count() > 0)
    {
        QListWidgetItem *selItem = m_ui->lwPlaylists->selectedItems().at(0);
        QVariant vData = selItem->data(Qt::UserRole);

        //
        // Mopiqy::Models can be casted from QVariant
        //
        if(vData.canConvert<Mopiqy::Models::Playlist>())
        {
            Mopiqy::Models::Playlist pl = qvariant_cast<Mopiqy::Models::Playlist>(vData);

            qWarning() << "set current playlist" << pl.name << "[" << pl.tracks.count() << " tracks] @" << pl.uri;
            Mopiqy::MopiqyHelper::instance()->tracklistController()->clear();
            Mopiqy::MopiqyHelper::instance()->tracklistController()->add(pl.uri);
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
        // Mopiqy::Models can be casted from QVariant
        //
        if(vData.canConvert<Mopiqy::Models::Playlist>())
        {
            Mopiqy::Models::Playlist pl = qvariant_cast<Mopiqy::Models::Playlist>(vData);

            qWarning() << "request lookup for playlist" << pl.name;
            Mopiqy::MopiqyHelper::instance()->playlistsController()->lookup(pl.uri);
        }
    }
}

void MainWidget::on_btRefreshTracklist_clicked()
{
    qWarning() << "get current tracklist request";
    Mopiqy::MopiqyHelper::instance()->tracklistController()->get_tltracks();
}

void MainWidget::on_tbPlay_clicked()
{
    if(m_currentTltracks.count() > 0)
    {
        qWarning() << "play request";
        Mopiqy::MopiqyHelper::instance()->playbackController()->play(m_currentTltracks.at(0));
    }
}

void MainWidget::on_tbStop_clicked()
{
    qWarning() << "stop request";
    Mopiqy::MopiqyHelper::instance()->playbackController()->stop();
}

void MainWidget::on_tbNext_clicked()
{
    qWarning() << "next request";
    Mopiqy::MopiqyHelper::instance()->playbackController()->next();
}

/*
 * MopidyClient slots
 */
void MainWidget::onMC_Connected()
{
    qWarning() << "mopidy client connected";

    // Enable controls
    setControlsState(true);

    // Get Version and URIs
    Mopiqy::MopiqyHelper::instance()->coreController()->get_version();
    Mopiqy::MopiqyHelper::instance()->coreController()->get_uri_schemes();
}

void MainWidget::onMC_Describe(const QJsonObject &desc)
{
    QJsonDocument jdoc(desc);

    QFile fDesc("describe.json");
    if(fDesc.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fDesc.write(jdoc.toJson());
        fDesc.close();
    }

    qWarning() << "Describe file saved at" << QFileInfo(fDesc).absoluteFilePath();
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
void MainWidget::onEL_TrackPlaybackEnded(const Mopiqy::Models::TlTrack &tl_track, const int &time_position)
{
    Q_UNUSED(time_position)

    qWarning() << "event: playback ended" << tl_track.tlid;
    m_ui->lbCurrentName->clear();
    m_ui->lbCurrentInfos->clear();
    m_ui->lbCurrentLength->clear();
}

void MainWidget::onEL_TrackPlaybackStarted(const Mopiqy::Models::TlTrack &tl_track)
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
void MainWidget::onPlaylistsController_GetPlaylists(const Mopiqy::Models::Playlists &pls)
{
    qWarning() << pls.count() << "playlists received";

    m_ui->lwPlaylists->clear();
    foreach(Mopiqy::Models::Playlist pl, pls)
    {
        QListWidgetItem *item = new QListWidgetItem;

        //
        // Mopiqy::Models are struct corresponding to definition from
        // http://docs.mopidy.com/en/latest/api/models/
        //
        item->setText(pl.name);

        //
        // Every Mopiqy::Models structs can be used as QVariant
        //
        QVariant vPlaylist;
        vPlaylist.setValue(pl);
        item->setData(Qt::UserRole, vPlaylist);

        m_ui->lwPlaylists->addItem(item);
    }
}

void MainWidget::onPlaylistsController_Lookup(const Mopiqy::Models::Playlist &pl)
{
    qWarning() << "playlist lookup done";
    m_ui->lwTracks->clear();

    foreach(Mopiqy::Models::Track track, pl.tracks)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(1, track.name);
        item->setText(2, track.album.name);

        QStringList artistsNames;
        foreach (Mopiqy::Models::Artist artist, track.artists) {
            artistsNames << artist.name;
        }
        item->setText(3, artistsNames.join(", "));

        m_ui->lwTracks->addTopLevelItem(item);
    }

    for(int i = 0; i < m_ui->lwTracks->columnCount(); ++i)
        m_ui->lwTracks->resizeColumnToContents(i);
}

void MainWidget::onTracklistController_Add(const Mopiqy::Models::TlTracks &tltracks)
{
    qWarning() << tltracks.count() << "Tl_Tracks in tracklist";
    m_currentTltracks = tltracks;
}

void MainWidget::onTracklistController_GetTlTracks(const Mopiqy::Models::TlTracks &tltracks)
{
    qWarning() << "playlist lookup done";
    m_ui->lwTlTracks->clear();

    foreach(Mopiqy::Models::TlTrack tltrack, tltracks)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString::number(tltrack.tlid));
        item->setText(1, tltrack.track.name);
        item->setText(2, tltrack.track.album.name);

        QStringList artistsNames;
        foreach (Mopiqy::Models::Artist artist, tltrack.track.artists) {
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
    m_ui->btDescribe->setEnabled(isConnected);
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
