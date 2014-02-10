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
#include <functional>

namespace ICI{

QVariant has_function(ICISettingsContext* ctx){
    if(ctx->args().size() == 0){
        ctx->setErrorMessage(QString("has_function expect at least 1 argument"));
        return false;
    }
    for(int i = 0; i < ctx->args().size(); ++i){
        if(!ctx->hasFunction(ctx->args().at(i).toString()))
            return false;
    }
    return true;
}

QVariant contains(ICISettingsContext* ctx){
    if(ctx->args().size() != 2){
        ctx->setErrorMessage(QString("contains expect exactly 2 arguments"));
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

QVariant extend(ICISettingsContext* ctx){
    if(ctx->args().size() < 2){
        ctx->setErrorMessage(QString("extend expects at least 2 arguments"));
        return false;
    }
    if(ctx->keys().at(0).isEmpty()){
        ctx->setErrorMessage(QString("extend expects an identifier as first parameter"));
        return false;
    }
    if(!ctx->args().at(0).canConvert(QVariant::List)){
        ctx->setErrorMessage(QString("extend expects a list as first parameter"));
        return false;
    }
    QVariantList lst = ctx->args().at(0).toList();
    for(int i = 1; i < ctx->args().size(); ++i){
        QVariant other = ctx->args().at(i);
        if(other.canConvert(QVariant::List)){
            QVariantList other_list = other.toList();
            Q_FOREACH(const QVariant & item, other_list){
                lst.append(item);
            }
        }
        else {
            lst.append(other);
        }
        ctx->setValue(ctx->keys().at(0), lst);
    }
    return QVariant();
}

QVariant join(ICISettingsContext* ctx) {
    if(ctx->args().size() < 2){
        ctx->setErrorMessage(QString("join expects exactly 2 arguments"));
        return QString();
    }
    QStringList list = ctx->args().at(0).toStringList();
    QString sep = ctx->args().at(1).toString();
    return list.join(sep);
}


#define SWITCH_ITEM_COMPARE(typeName, type, op) \
case QMetaType::typeName: {return (a).value<type>() op (b).value<type>(); break;}



#define __variant_comp(NAME, op)                     \
bool NAME(const QVariant & a, const QVariant & b)    \
{                                                    \
    switch (b.type()) {                       \
        SWITCH_ITEM_COMPARE(UInt, quint32, op) \
        SWITCH_ITEM_COMPARE(Int,  qint32, op) \
        SWITCH_ITEM_COMPARE(ULongLong,  quint64, op) \
        SWITCH_ITEM_COMPARE(Long,  long, op)  \
        SWITCH_ITEM_COMPARE(ULong,  unsigned long, op) \
        SWITCH_ITEM_COMPARE(LongLong,  qint64, op)\
        SWITCH_ITEM_COMPARE(QString,  QString, op)\
        SWITCH_ITEM_COMPARE(QChar,  QChar, op)\
        SWITCH_ITEM_COMPARE(Bool,  bool, op) \
        SWITCH_ITEM_COMPARE(Char,  qint16, op) \
        SWITCH_ITEM_COMPARE(UChar, quint8, op) \
        SWITCH_ITEM_COMPARE(Double, double, op) \
        SWITCH_ITEM_COMPARE(Float,  float, op) \
        SWITCH_ITEM_COMPARE(Short,  qint16, op) \
        SWITCH_ITEM_COMPARE(UShort,  quint16, op)  \
        default: {return false; break;} \
    } \
    return false;\
}

#if (__GNUC__ == 4)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#endif

__variant_comp(_variant_equals, ==)
__variant_comp(_variant_lt, <)
__variant_comp(_variant_gt, >)
__variant_comp(_variant_gte, >=)
__variant_comp(_variant_lte, <=)

#if (__GNUC__ == 4)
#pragma GCC diagnostic pop
#endif

QVariant _compare_variants(ICISettingsContext* ctx, bool(*comp)(const QVariant & a, const QVariant & b)){
    if(ctx->args().size() < 2){
        ctx->setErrorMessage("Comparaison function takes at least 2 arguments");
        return false;
    }
    QVariant arg = ctx->args().at(0);
    for(int i = 1; i < ctx->args().size(); ++i){
        if(!comp(arg,ctx->args().at(i))){
            return false;
        }
        arg = ctx->args().at(i);
    }
    return true;
}

QVariant equals(ICISettingsContext* ctx) {
    if(ctx->args().size() >= 2 && ctx->args().at(0).isNull()) {
        for(int i = 1; i < ctx->args().size(); ++i){
            if(!ctx->args().at(1).isNull())
                return false;
        }
        return true;
    }
    return _compare_variants(ctx, _variant_equals);
}

QVariant lt(ICISettingsContext* ctx) {
    return _compare_variants(ctx, _variant_lt);
}

QVariant lte(ICISettingsContext* ctx) {
    return _compare_variants(ctx, _variant_lte);
}

QVariant gt(ICISettingsContext* ctx) {
    return _compare_variants(ctx, _variant_gt);
}

QVariant gte(ICISettingsContext* ctx) {
    return _compare_variants(ctx, _variant_gte);
}

QVariant max(ICISettingsContext* ctx) {
    if(ctx->args().size() < 2){
        ctx->setErrorMessage("Comparaison function takes at least 2 arguments");
        return false;
    }
    QVariant arg = ctx->args().at(0);
    for(int i = 1; i < ctx->args().size(); ++i){
        if(_variant_gt(ctx->args().at(i), arg)){
            arg = ctx->args().at(i);
        }
    }
    return arg;
}

QVariant min(ICISettingsContext* ctx) {
    if(ctx->args().size() < 2){
        ctx->setErrorMessage("Comparaison function takes at least 2 arguments");
        return false;
    }
    QVariant arg = ctx->args().at(0);
    for(int i = 1; i < ctx->args().size(); ++i){
        if(_variant_lt(ctx->args().at(i), arg)){
            arg = ctx->args().at(i);
        }
    }
    return arg;
}

QVariant sum(ICISettingsContext* ctx) {
    if(ctx->args().size() < 2){
        ctx->setErrorMessage("sum takes at least 2 arguments");
        return QVariant();
    }
    double result = 0;
    for(int i = 0; i < ctx->args().size(); ++i) {
        if(ctx->args().at(i).canConvert(QVariant::Double))
            result += ctx->args().at(i).toDouble();
    }
    return result;
}

QVariant mul(ICISettingsContext* ctx) {
    if(ctx->args().size() < 2){
        ctx->setErrorMessage("mul takes at least 2 arguments");
        return false;
    }
    if(!ctx->args().at(0).canConvert(QVariant::Double)) {
        ctx->setErrorMessage("NaN");
        return QVariant();
    }

    double result = ctx->args().at(0).toDouble();
    for(int i = 1; i < ctx->args().size(); ++i) {
        if(ctx->args().at(i).canConvert(QVariant::Double))
            result *= ctx->args().at(i).toDouble();
    }
    return result;
}

QVariant div(ICISettingsContext* ctx) {
    if(ctx->args().size() !=2){
        ctx->setErrorMessage("div takes 2 arguments");
        return false;
    }

    if(!ctx->args().at(0).canConvert(QVariant::Double) || !ctx->args().at(1).canConvert(QVariant::Double)) {
        ctx->setErrorMessage("NaN");
        return QVariant();
    }

    return ctx->args().at(0).toDouble() / ctx->args().at(1).toDouble();
}



}
