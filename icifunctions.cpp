#include "icifunctions.h"
#include <QDebug>

namespace ICI{

QVariant contains(ICISettingsContext* ctx){
    if(ctx->args().size() != 1){
        ctx->setErrorMessage(QString("contains expect exactly 1 argument"));
        return false;
    }
    return ctx->exists(ctx->args().at(0).toString());
}

QVariant equals(ICISettingsContext* ctx){
    if(ctx->args().size() < 2){
        ctx->setErrorMessage(QString("equals expect at least 2 arguments"));
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
