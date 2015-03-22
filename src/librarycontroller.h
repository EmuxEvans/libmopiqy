#ifndef LIBRARYCONTROLLER_H
#define LIBRARYCONTROLLER_H

#include <QObject>
#include "libmopiqy_export.h"
#include "mopidymodels.h"

class LIBMOPIQY_EXPORT LibraryController : public QObject
{
    Q_OBJECT

public:
    ~LibraryController();

public slots:
    virtual void browse(const QString &uri = "");
    virtual void findExact(const QHash<QString, QString> &query, const QStringList &uris = QStringList());
    virtual void lookup(const QString &uri);
    virtual void refresh(const QString &uri = "");
    virtual void search(const QHash<QString, QString> &query, const QStringList &uris = QStringList());

signals:
    void findResult(const Mopidy::SearchResult &);
    void lookupResult(const Mopidy::Tracks &);
    void searchResult(const Mopidy::SearchResult &);
    void browseResult(const Mopidy::Refs &);

protected:
    LibraryController(QObject *parent = 0);
};

#endif //LIBRARYCONTROLLER_H
