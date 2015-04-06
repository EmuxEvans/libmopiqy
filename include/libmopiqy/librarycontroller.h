#ifndef LIBRARYCONTROLLER_H
#define LIBRARYCONTROLLER_H

#include <QObject>
#include <libmopiqy/mopidymodels.h>

class LIBMOPIQY_EXPORT LibraryController : public QObject
{
    Q_OBJECT

public slots:
    virtual void browse(const QString &uri = "") = 0;
    virtual void lookup(const QStringList &uris = QStringList()) = 0;
    virtual void refresh(const QString &uri = "") = 0;
    virtual void search(const QHash<QString, QStringList> &query, const QStringList &uris = QStringList(), bool exact = false) = 0;
    virtual void getImages(const QStringList &uris) = 0;

signals:
    void lookupResult(const Mopidy::Tracks &);
    void searchResult(const Mopidy::SearchResult &);
    void browseResult(const Mopidy::Refs &);
    void imagesResult(const Mopidy::Images &);
};

#endif //LIBRARYCONTROLLER_H
