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

#include "ici.h"
#include "ici_p.h"
#include "iciast.h"
#include "iciparser.h"
#include "icifunctions.h"
#include <QFile>
#include <QHash>

QVariant value(QStringList keys, const QVariantMap & context, const QVariant & defaultValue = QVariant()){
    if(keys.size() == 1){
        return context.value(keys.first(), defaultValue);
    }
    QVariant variant = context;
    do{
        QString key = keys.takeFirst();
        if(variant.canConvert<QVariantMap>()){
            QVariantMap map = variant.toMap();
            if(map.contains(key))
                variant = map.value(key);
            else
                return defaultValue;
        }
        else
            return defaultValue;
    }while(!keys.isEmpty());
    return variant;
}

bool contains(QStringList keys, const QVariantMap & context){
    if(keys.size() == 1){
        return context.contains(keys.first());
    }
    QVariant variant = context;
    do{
        QString key = keys.takeFirst();
        if(variant.canConvert<QVariantMap>()){
            QVariantMap map = variant.toMap();
            if(map.contains(key))
                variant = map.value(key);
            else
                return false;
        }
        else
            return false;
    }while(!keys.isEmpty());
    return true;
}
bool contains(QString key, const QVariantMap & context){
    return contains(key.split('.'), context);
}

bool set_value(QStringList & keys, const QVariant & value, QVariantMap & context){
    if(keys.isEmpty())
        return true;
    QString key = keys.takeFirst();
    if(keys.isEmpty()){
        context.insert(key, value);
    }
    else if(!context.contains(key) || !context.value(key).canConvert<QVariantMap>()){
        QVariantMap subcontext;
        set_value(keys, value, subcontext);
        context.insert(key, subcontext);
    }
    else {
        QVariantMap subcontext = context.value(key).toMap();
        if(!set_value(keys, value,subcontext))
            return false;
        context.insert(key, subcontext);
    }
    return true;
}

bool set_value(const QString & key, const QVariant & value, QVariantMap & context){
    QStringList keys = key.split('.');
    if(keys.size() == 1){
        context.insert(key, value);
        return true;
    }
    return set_value(keys, value, context);
}


QString replace_in_string(QString string, const QVariantMap & context){
    bool escaped = false;
    int in = 0;
    int begin = 0;
    int end = 0;
    for(int i = 0; i < string.size(); i++){
        QChar c = string.at(i);
        if (c == '\\') {
            escaped = !escaped ;
        }
        else if (c == '$' && !escaped &&  i+1 < string.size() && string.at(i+1) == '{'){
            if(in == 0)
                begin = i;
            in++;
        }
        else if( c == '}' && !escaped && --in == 0){
            end = i;
            QString substring = replace_in_string(string.mid(begin+2, (i-begin)-2), context);
            qDebug() << string.mid(begin+2, (i-begin)-2);
            QStringList keys = substring.split('.');
            bool replaced = false;
            if(contains(keys, context)){
                QVariant value = ::value(keys, context);
                if(value.canConvert<QString>()){
                    QString replacement = value.toString();
                    string.replace(begin, (i - begin)+1, replacement);
                    replaced = true;
                    i = (begin + replacement.size()) -2;
                }
            }
            if(!replaced){
                string.replace(begin, end-begin, substring);
                i = begin + substring.size() -1;
            }
            in = false;
        }
        else {
            escaped = false;
        }
    }
    return string;
}


ICISettings::ICISettings(const QString & file, QObject* parent)
    :QObject(parent), d(new ICISettingsPrivate){

    QFile f(file);
    f.open(QIODevice::ReadOnly);
    if(f.error()!=QFile::NoError){
        d->error = true;
        d->errorString = f.errorString();
    }
    else {
        QByteArray data = f.readAll();
        d->parse(data);
    }
}

ICISettings::~ICISettings(){
    delete d;
}

bool ICISettings::hasError() const{
    return d->error;
}
QString ICISettings::errorString() const{
    return d->errorString;
}

void ICISettings::setContext(const QVariantMap & context){
    d->context = context;
    d->evaluate();
}

void ICISettings::setValue(const QString & key, const QVariant & value){
    d->setValue(key, value);
}

QVariant ICISettings::value(const QString & key, const QVariant & defaultValue) const{
    return d->value(key,defaultValue);
}

QVariantMap ICISettings::values() const{
    return d->context;
}

bool ICISettings::contains(const QString & key) const{
    return d->hasKey(key);
}

bool ICISettings::createFunction(const QString & name, IciFunction funct){
    if(d->functions.contains(name))
        return false;
    d->functions.insert(name, funct);
    return true;
}





ICISettingsPrivate::ICISettingsPrivate():
    error(false), ast(0){

    functions.insert("contains", ICI::contains);
    functions.insert("equals", ICI::equals);
}

void ICISettingsPrivate::parse(const  QByteArray & data){
    ICIParser parser(data);
    if(!parser.parse()){
        error = true;
        errorString = parser.errorString();
    }
    else{
        ast = parser.ast();
        evaluate();
    }
}

void ICISettingsPrivate::evaluate(){
    if(!ast || !evaluate(ast->nodes)){
        error = true;
    }
}

bool ICISettingsPrivate::evaluate(ICI::StatementListNode* node){
    while(node){
        if(!evaluate(node->node))
            return false;
        node = node->next;
    }
    return true;
}

bool ICISettingsPrivate::evaluate(ICI::StatementNode* node){
    if(!node)
        return true;
    switch(node->type){
        case ICI::Node::Type_Assignement:
           return evaluate(static_cast<ICI::AssignementNode*>(node));
        case ICI::Node::Type_IfStatement:
           return evaluate(static_cast<ICI::IfStatementNode*>(node));
        default:return false;
    }
    return false;
}

bool ICISettingsPrivate::evaluate(ICI::AssignementNode* node){
    if(!node)
        return true;
    QVariant value;
    if(!evaluate(node->value, value))
        return false;
    QStringList keys = node->id->keys();
    switch(node->op->op){
        case ICI::Node::AssignementOperator:
            set_value(keys, value, context);
            break;
        default:
            qDebug() << "not implemented";
            break;
    }
    return true;
}

bool ICISettingsPrivate::evaluate(ICI::ExpressionNode* node, QVariant & value){
    switch(node->type){
       case ICI::Node::Type_NumericLiteral:
           value = static_cast<ICI::NumericLiteralNode*>(node)->value;
           return true;
       case ICI::Node::Type_StringLiteral:
           value = replace_in_string(static_cast<ICI::StringLiteralNode*>(node)->value, context);
           return true;
       case ICI::Node::Type_Identifier:
           value = ::value(static_cast<ICI::IdentifierNode*>(node)->keys(), context);
           return true;
       case ICI::Node::Type_FunctionCall:
           return evaluate(static_cast<ICI::FunctionCallNode*>(node), value);
       case ICI::Node::Type_List:{
           QVariantList lst;
           ICI::ListElementNode* elem =  static_cast<ICI::ListNode*>(node)->nodes;
           if(!evaluate(elem, lst))
               return false;
           value = lst;
           return true;
       }
       default: return false;
    }
    return false;
}

bool ICISettingsPrivate::evaluate(ICI::ListElementNode* elem, QVariantList &values){
    while(elem){
       QVariant value;
       if(!evaluate(elem->value, value))
           return false;
       values.append(value);
       elem = elem->next;
   }
   return true;
}

bool ICISettingsPrivate::evaluate(ICI::FunctionCallNode * node, QVariant & result){
    if(!node)
        return false;
    QHash<QString, ICISettings::IciFunction>::const_iterator it = functions.find(node->name);
    if(it == functions.end()){
        errorString = QString("Error at line %1:%2 : function %3 undefined")
                .arg(node->line).arg(node->pos).arg(node->name);
        return false;
    }
    QVariantList parameters;
    if(!evaluate(node->parameters, parameters))
        return false;
    ICISettingsContext ctx;
    ctx.d->ctx = this;
    ctx.d->args = parameters;
    result = it.value()(&ctx);
    qDebug() << result.toBool();
    return !error;
}

bool ICISettingsPrivate::evaluate(ICI::IfStatementNode* node){
    bool istrue = false;
    if(!evaluate(node->condition, istrue))
        return false;
    return evaluate(istrue ? node->block : node->alternative_block);
}

bool ICISettingsPrivate::evaluate(ICI::LogicalExpressionNode* node, bool & istrue){
    QVariant value;
    if(!evaluate(node->condition, value)){
        return false;
    }
    if(!value.canConvert<bool>()){
        errorString = QString("Error at line %1:%2 : boolean expression expected")
                .arg(node->line).arg(node->pos);
        return false;
    }
    istrue = value.toBool();
    return true;
}


bool ICISettingsPrivate::hasKey(const QString & key) const{
    return contains(key.split('.'), context);
}

QVariant ICISettingsPrivate::value(const QString & key, const QVariant & defaultValue) const{
    return ::value(key.split('.'), context, defaultValue);
}

void ICISettingsPrivate::setValue(const QString & key, const QVariant & value){
    set_value(key, value, context);
}


ICISettingsContext::ICISettingsContext()
:d(new ICISettingsContextPrivate){
}

ICISettingsContext::~ICISettingsContext(){
    delete d;
}

void ICISettingsContext::setErrorMessage(const QString & message){
    d->ctx->errorString = message;
    d->ctx->error = true;
}

QVariant ICISettingsContext::value(const QString & key, const QVariant & defaultValue) const{
    return d->ctx->value(key, defaultValue);
}

bool ICISettingsContext::exists(const QString & key) const{
    return d->ctx->hasKey(key);
}

void ICISettingsContext::setValue(const QString & key, const QVariant & defaultValue){
    set_value(key, defaultValue, d->ctx->context);
}

const QVariantList & ICISettingsContext::args() const{
    return d->args;
}
