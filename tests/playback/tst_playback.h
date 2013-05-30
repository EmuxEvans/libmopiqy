#ifndef TST_PLAYBACK_H
#define TST_PLAYBACK_H

#include <QObject>
#include <mopiqy_core/mopidyclient.h>

class tst_playback : public QObject
{
	Q_OBJECT

public:
	tst_playback(QObject *parent = 0);
	~tst_playback();

	void run();

private slots:
    void client_connected();
    void client_disconnected();
    void client_error(const int &code, const QString &message);

private:
    Mopidy::MopidyClient *m_client;
};

#endif //TST_PLAYBACK_H
