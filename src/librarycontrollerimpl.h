#ifndef LIBRARYCONTROLLERIMPL_P_H
#define LIBRARYCONTROLLERIMPL_P_H

#include "librarycontroller.h"

class MopidyClientPrivate;

class LibraryControllerImpl : public LibraryController
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
    void findExact(const QHash<QString, QString> &query, const QStringList &uris = QStringList());
    void lookup(const QString &uri);
    void refresh(const QString &uri = "");
    void search(const QHash<QString, QString> &query, const QStringList &uris = QStringList());

private:
    MopidyClientPrivate *m_mcp;
};

#endif //LIBRARYCONTROLLER_P_H
