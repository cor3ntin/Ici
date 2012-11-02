#ifndef _ICIFUNCTIONS_H
#define _ICIFUNCTIONS_H

#include <QObject>
#include <QVariantMap>
#include "ici.h"

namespace ICI{

QVariant contains(ICISettingsContext* ctx);
QVariant equals(ICISettingsContext* ctx);

}

#endif // _ICIFUNCTIONS_H
