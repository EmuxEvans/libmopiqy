#ifndef LIBRARYCONTROLLERIMPL_P_H
#define LIBRARYCONTROLLERIMPL_P_H

#include "libmopiqy/librarycontroller.h"
#include "basecontrollerimpl.h"

class LibraryControllerImpl : public LibraryController, public BaseControllerImpl
{
    Q_OBJECT

public:
    LibraryControllerImpl(MopidyClientPrivate *parent);
    ~LibraryControllerImpl();

    // process responses
    void pr_browse(const QJsonValue &response);
    void pr_findExact(const QJsonValue &response);
    void pr_lookup(const QJsonValue &response);
    void pr_search(const QJsonValue &response);

public slots:
    void browse(const QString &uri = "");
    void lookup(const QStringList &uris);
    void refresh(const QString &uri = "");
    void search(const QHash<QString, QString> &query, const QStringList &uris, bool exact);
    void getImages(const QStringList &uris);
};

#endif //LIBRARYCONTROLLER_P_H
