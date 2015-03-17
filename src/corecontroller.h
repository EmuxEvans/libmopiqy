

class CoreController : public QObject
{
    Q_OBJECT

public:
    CoreController(RemoteClient *remoteClient);
    ~CoreController();

public slots:
    /*
     * functions from Core API
     */
    void describe();
    void get_uri_schemes();
    void get_version();

signals:
    void describe(const QJsonObject &desc);
    void onVersion(const QString &version);
    void onUriSchemes(const QStringList &uris);
};
