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

#include "icifunctions.h"

namespace ICI{

QVariant contains(ICISettingsContext* ctx){
    if(ctx->args().size() != 2){
        ctx->setErrorMessage(QString("contains expect exactly 2 argument"));
        return false;
    }
    QVariant a = ctx->args().at(0);
    QVariant b = ctx->args().at(1);
    if(a.canConvert<QVariantList>()){
        if(a.toList().contains(b))
            return true;
    }
    if(a.canConvert<QVariantMap>() && b.canConvert<QString>()){
        if(a.toMap().contains(b.toString()))
            return true;
    }
    if(a.canConvert<QString>() && b.canConvert<QString>()){
        if(a.toString().contains(b.toString()))
            return true;
    }
    return false;
}

QVariant equals(ICISettingsContext* ctx){
    if(ctx->args().size() < 2){
        ctx->setErrorMessage(QString("equals expects at least 2 arguments"));
        return false;
    }
    QVariant arg = ctx->args().at(0);
    for(int i = 1; i < ctx->args().size(); ++i){
        if(arg != ctx->args().at(i)){
            return false;
        }
        arg = ctx->args().at(i);
    }
    return true;
}

}
