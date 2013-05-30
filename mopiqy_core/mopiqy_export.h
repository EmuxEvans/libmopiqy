#ifndef MOPIQY_EXPORT
#define MOPIQY_EXPORT

#include <QtGlobal>

#ifdef Q_OS_WIN
#   ifdef MOPIQY_CORE_SHARED
#       define MOPIQY_CORE_EXPORT Q_DECL_EXPORT
#   else
#       define MOPIQY_CORE_EXPORT Q_DECL_IMPORT
#   endif //MOPIQY_CORE_SHARED
#else
#define MOPIQY_CORE_EXPORT
#endif // Q_OS_WIN

#endif //MOPIQY_EXPORT
