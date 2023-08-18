#ifndef FRACTION_GLOBAL_H
#define FRACTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FRACTION_LIBRARY)
#  define FRACTION_EXPORT Q_DECL_EXPORT
#else
#  define FRACTION_EXPORT Q_DECL_IMPORT
#endif

#endif // FRACTION_GLOBAL_H
