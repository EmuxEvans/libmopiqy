#ifndef LIBRARYCONTROLLER_H
#define LIBRARYCONTROLLER_H

#include <QObject>
#include <QString>

#include "mopidymodels.h"
#include "controllerinterface.h"
#include "mopiqy_export.h"

namespace Mopidy {
    namespace Core {
        class LIBMOPIQY_EXPORT LibraryController : public QObject, public ControllerInterface
        {
            Q_OBJECT

        public:
            LibraryController(Mopidy::Internal::JsonRpcHandler *jrHandler, QObject *parent = 0);
            ~LibraryController();

        public slots:
            /*
             * functions from Core API
             */
            void find_exact(const QHash<QString, QString> &query, const QStringList &uris = QStringList());
            void lookup(const QString &uri);
            void refresh(const QString &uri = "");
            void search(const QHash<QString, QString> &query, const QStringList &uris = QStringList());


        signals:
            void onFindExact(const Mopidy::Models::SearchResult &);
            void onLookup(const Mopidy::Models::Tracks &);
            void onSearch(const Mopidy::Models::SearchResult &);

        protected:
            void processJsonResponse(const int &id, const QJsonValue &jv);

        private:
            enum LCEnum
            {
                LC_FINDEXACT,
                LC_LOOKUP,
                LC_SEARCH
            };
        };
    }
}

#endif //LIBRARYCONTROLLER_H
