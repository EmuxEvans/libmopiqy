#ifndef MOPIQY_EXPORT
#define MOPIQY_EXPORT

#include <QtGlobal>

#ifdef Q_OS_WIN
#   ifdef LIBMOPIQY_SHARED
#       define LIBMOPIQY_EXPORT Q_DECL_EXPORT
#   else
#       define LIBMOPIQY_EXPORT Q_DECL_IMPORT
#   endif //LIBMOPIQY_SHARED
#else
#define LIBMOPIQY_EXPORT
#endif // Q_OS_WIN

#endif //MOPIQY_EXPORT
