#ifndef MOPIDY_CLIENT_P_H
#define MOPIDY_CLIENT_P_H

#include <QObject>
#include <QWebSocket>

class MopidyClient;
class MopidyClientPrivate : public QObject
{
    Q_OBJECT

public:
    MopidyClientPrivate(QObject * parent = 0);
    ~MopidyClientPrivate();

    QWebSocket *webSocket;

public slots:
    void onTextMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError socketError);

private:
    MopidyClient const *q_ptr;
    Q_DECLARE_PUBLIC(MopidyClient)
};

#endif //MOPIDY_CLIENT_P_H
