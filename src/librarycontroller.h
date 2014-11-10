#ifndef LIBRARYCONTROLLER_H
#define LIBRARYCONTROLLER_H

#include "controllerinterface.h"
#include "mopidymodels.h"
#include "mopiqy_export.h"

namespace Mopiqy {
class LIBMOPIQY_EXPORT LibraryController : public ControllerInterface
{
    Q_OBJECT

public:
    LibraryController(RemoteClient *remoteClient);
    ~LibraryController();

public slots:
    /*
             * functions from Core API
             */
    void browse(const QString &uri = "");
    void find_exact(const QHash<QString, QString> &query, const QStringList &uris = QStringList());
    void lookup(const QString &uri);
    void refresh(const QString &uri = "");
    void search(const QHash<QString, QString> &query, const QStringList &uris = QStringList());

signals:
    void onFindExact(const Models::SearchResult &);
    void onLookup(const Models::Tracks &);
    void onSearch(const Models::SearchResult &);
    void onBrowse(const Models::Refs &);

protected:
    void processJsonResponse(const int &idt, const QJsonValue &jv);

private:
    enum LCEnum
    {
        LC_FINDEXACT,
        LC_LOOKUP,
        LC_SEARCH,
        LC_BROWSE
    };
};
}

#endif //LIBRARYCONTROLLER_H
