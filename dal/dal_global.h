#ifndef DAL_GLOBAL_H
#define DAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DAL_LIBRARY)
#  define DAL_EXPORT Q_DECL_EXPORT
#else
#  define DAL_EXPORT Q_DECL_IMPORT
#endif

#endif // DAL_GLOBAL_H
