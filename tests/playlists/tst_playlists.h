#ifndef TST_PLAYLISTS_H
#define TST_PLAYLISTS_H

#include <QObject>
#include <mopiqy_core/mopidyclient.h>

class tst_playlists : public QObject
{
	Q_OBJECT

public:
	tst_playlists(QObject *parent = 0);
	~tst_playlists();

	void run();

private slots:
    void client_connected();
    void client_disconnected();
    void client_error(const int &code, const QString &message);

    void pc_onCreate(const Mopidy::Models::Playlist &pl);
    void pc_onFilter(const Mopidy::Models::Playlists &pls);
    void pc_onLookup(const Mopidy::Models::Playlist &pl);
    void pc_onGetPlaylists(const Mopidy::Models::Playlists &pls);
    void pc_onSave(const Mopidy::Models::Playlist &pl);

private:
    Mopidy::MopidyClient *m_client;
};

#endif //TST_PLAYLISTS_H
