#ifndef MOPIDY_CLIENT_H
#define MOPIDY_CLIENT_H

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
};

#endif //MOPIDY_CLIENT_H
