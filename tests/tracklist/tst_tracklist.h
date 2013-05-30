#ifndef TST_TRACKLIST_H
#define TST_TRACKLIST_H

#include <QObject>
#include <mopiqy_core/mopidyclient.h>

class tst_tracklist : public QObject
{
	Q_OBJECT

public:
	tst_tracklist(QObject *parent = 0);
	~tst_tracklist();

	void run();

private slots:
    void client_connected();
    void client_disconnected();
    void client_error(const int &code, const QString &message);

private:
    Mopidy::MopidyClient *m_client;
};

#endif //TST_TRACKLIST_H
