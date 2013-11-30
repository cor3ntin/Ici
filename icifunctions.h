/****************************************************************************
**
** Copyright (C) 2012 Corentin Jabot
** Contact: https://github.com/cor3ntin/Ici
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/

#ifndef _ICIFUNCTIONS_H
#define _ICIFUNCTIONS_H

#include <QObject>
#include <QVariantMap>
#include "ici.h"

namespace ICI{

QVariant contains(ICISettingsContext* ctx);
QVariant equals(ICISettingsContext* ctx);
QVariant extend(ICISettingsContext* ctx);
QVariant has_function(ICISettingsContext* ctx);
QVariant join(ICISettingsContext* ctx);

}

#endif // _ICIFUNCTIONS_H
