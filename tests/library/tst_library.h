#ifndef TST_LIBRARY_H
#define TST_LIBRARY_H

#include <QObject>
#include <mopiqy_core/mopidyclient.h>

class tst_library : public QObject
{
	Q_OBJECT

public:
	tst_library(QObject *parent = 0);
	~tst_library();

	void run();

private slots:
    void client_connected();
    void client_disconnected();
    void client_error(const int &code, const QString &message);

    void lc_onFindExact(const Mopidy::Models::SearchResult &);
    void lc_onLookup(const Mopidy::Models::Tracks &);
    void lc_onSearch(const Mopidy::Models::SearchResult &);

private:
    Mopidy::MopidyClient *m_client;
};

#endif //TST_LIBRARY_H
