#ifndef MOPIDY_CLIENT_H
#define MOPIDY_CLIENT_H

#include <QObject>
#include <QHostAddress>
#include "libmopiqy_export.h"

class MopidyClientPrivate;
class MopidyClient : public QObject
{
    Q_OBJECT

public:
    MopidyClient(QObject *parent = 0);
    ~MopidyClient();

    void connectToServer(const QHostAddress &address, const quint16 &port, const QString &path);
    void disconnectFromServer();

signals:
    void clientConnected();
    void clientDisconnected();
    void connectionError(const int &code, const QString &message);

private:
    Q_DECLARE_PRIVATE(MopidyClient)
    QScopedPointer<MopidyClientPrivate> d_ptr;
};

#endif //MOPIDY_CLIENT_H
