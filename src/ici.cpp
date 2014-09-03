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

static QVariantList nullVariantList;
static QVariantMap  nullVariantMap;
static QVariant  nullVariant;

static QVariantList & asList(QVariant & v) {
    if(v.type() != QVariant::List)
        return nullVariantList;
    return *const_cast<QVariantList*>(static_cast<const QVariantList*>(v.constData()));
}

static const QVariantList & asList(const QVariant & v) {
    if(v.type() != QVariant::List)
        return nullVariantList;
    return *static_cast<const QVariantList*>(v.constData());
}


static QVariantMap & asMap(QVariant & v) {
    if(v.type() != QVariant::Map)
        return nullVariantMap;
    return *const_cast<QVariantMap*>(static_cast<const QVariantMap*>(v.constData()));
}

static const QVariantMap & asMap(const QVariant & v) {
    if(v.type() != QVariant::Map)
        return nullVariantMap;
    return *static_cast<const QVariantMap*>(v.constData());
}

QVariant & value_unsafe(const QStringList & keys, QVariantMap & context){
    QVariantMap* map = &context;
    int i = 0;
    while(i < keys.size()) {
        const QString & key = keys.at(i++);
        QVariantMap::iterator it = map->find(key);
        if(it == map->constEnd())
            return nullVariant;
        QVariant & value = *it;
        if(i >= keys.size())
            return value;
        if(value.type() == QVariant::Map)
            map = &asMap(value);
        else if(i == keys.size() -1 && value.type() == QVariant::List) {
            const QString & idxStr = keys.at(i);
            bool ok;
            int idx = idxStr.toInt(&ok);
            if(ok) {
                QVariantList & lst = asList(value);
                if(idx < lst.size())
                    return lst[idx];
            }
        }
        else
            return nullVariant;
    }
    return nullVariant;
}

QVariant value(const QStringList & keys, const QVariantMap & context,
               const QVariant & defaultValue = QVariant()){
    const QVariantMap* map = &context;
    int i = 0;
    while(i < keys.size()) {
        const QString & key = keys.at(i++);
        QVariantMap::const_iterator it = map->find(key);
        if(it == map->constEnd())
            return defaultValue;
        const QVariant & value = *it;
        if(i >= keys.size())
            return value;
        if(value.type() == QVariant::Map)
            map = &asMap(value);
        else if(i == keys.size() -1 && value.type() == QVariant::List) {
            const QString & idxStr = keys.at(i);
            bool ok;
            int idx = idxStr.toInt(&ok);
            if(ok) {
                const QVariantList & lst = asList(value);
                if(idx < lst.size())
                    return lst[idx];
            }
        }
        else
            return defaultValue;
    }
    return defaultValue;
}

bool contains(const QStringList & keys, const QVariantMap & context){
    if(keys.size() == 1){
        return context.contains(keys.first());
    }
    int i = 0;
    QVariant variant = context;
    do{
        const QString & key = keys.at(i);
        if(variant.type() != QVariant::Map)
            return false;

        const QVariantMap & map = asMap(variant);
        QVariantMap::const_iterator it = map.find(key);
        if(it == map.constEnd())
             return false;
        variant = *it;
    }while(++i < keys.size());
    return true;
}

bool unset(const QStringList & keys, QVariantMap & context){
    if(keys.size() == 1){
        return context.remove(keys.first()) > 0;
    }
    QVariant v = value_unsafe(keys.mid(0, keys.size() - 1), context);
    if(v.isNull())
        return false;
    if(v.type() == QVariant::Map) {
        QVariantMap & map = asMap(v);
        return map.remove(keys.last()) != 0;
    }
    if(v.type() == QVariant::List) {
        QVariantList & lst = asList(v);
        bool ok;
        int idx = keys.last().toInt(&ok);
        if(!ok || idx >= lst.size())
            return false;
        lst.removeAt(idx);
        return true;

    }
    return false;
}

bool contains(const QString & key, const QVariantMap & context){
    return contains(key.split('.'), context);
}

bool set_value(QStringList & keys, const QVariant & value, QVariantMap & context){
    if(keys.isEmpty())
        return true;
    QString key = keys.takeFirst();
    if(keys.isEmpty()){
        context.insert(key, value);
    }
    else if(!context.contains(key) || context.value(key).type() != QVariant::Map){
        QVariantMap subcontext;
        set_value(keys, value, subcontext);
        context.insert(key, subcontext);
    }
    else {
        QVariant & subcontextV = context[key];
        if(!(subcontextV.type() == QVariant::Map)) return false;
        QVariantMap & subcontext = asMap(subcontextV);
        if(!set_value(keys, value,  subcontext))
            return false;
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


QString ICISettingsPrivate::replace_in_string(QString string, const QVariantMap & context){
    bool escaped = false;
    int in = 0;
    int begin = 0;
    for(int i = 0; i < string.size() && i>=0; i++) {
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
            QString substring = replace_in_string(string.mid(begin+2, (i-begin)-2), context);
            QStringList keys = substring.split('.');
            if(this->hasKey(keys)) {
                QVariant value = this->value(keys, QVariant());
                if(value.canConvert<QString>()){
                    QString replacement = value.toString();
                    string.replace(begin, (i - begin)+1, replacement);
                    i = (begin + replacement.size()) -2;
                }
            }
            in = false;
        }
        else {
            escaped = false;
        }
    }
    return string;
}

QStringList ICISettingsPrivate::identifier_keys(ICI::IdentifierNode* node, const QVariantMap & context) {
    QStringList keys;
    ICI::IdentifierNode* n = node;
    while(n) {
        if(n->type == ICI::Node::Type_Identifier)
            keys << n->name;
        else
            keys << replace_in_string(n->name, context);
        n = n->next;
    }
    return keys;
}


QString formatError(const QString & message, ICI::Node* node){
    return QString(QLatin1String("Error in %1 at line %2:%3 : %4"))
            .arg(node->file)
            .arg(node->line)
            .arg(node->pos)
            .arg(message);
}


ICISettings::ICISettings(const QByteArray &data, QObject* parent)
    :QObject(parent), d(new ICISettingsPrivate){

    d->parse(data);
}

ICISettings::ICISettings(const QString & file, QObject* parent)
    :QObject(parent), d(new ICISettingsPrivate){
    d->fileName = file;
    reload();
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
}

void ICISettings::setValue(const QString & key, const QVariant & value){
    d->setValue(key, value);
    set_value(key, value, d->userValues);
}

QVariant ICISettings::value(const QString & key, const QVariant & defaultValue) const{
    return d->value(key,defaultValue);
}

QMap<QString, QVariant> ICISettings::values() const{
    return d->context;
}

void expand_map(QStringList & keys, const QString & k, const QVariant & v){
    if(v.type() == QVariant::Map){
        const QVariantMap & map = asMap(v);
        for(QVariantMap::const_iterator it = map.begin(); it != map.end(); ++it){
            expand_map(keys, k.isEmpty() ? it.key() : k +"." + it.key(), it.value());
        }
    }
    else if(!k.isEmpty()){
        keys.append(k);
    }
}

QStringList ICISettings::keys() const {
    QStringList lst;
    expand_map(lst, QString(), values());
    return lst;
}

bool ICISettings::contains(const QString & key) const{
    return d->hasKey(key);
}

bool ICISettings::createFunction(const QString & name, IciFunction funct, void *data){
    if(d->functions.contains(name))
        return false;
    d->functions.insert(name, QPair<IciFunction, void*>(funct, data));
    return true;
}

bool ICISettings::evaluate(bool clear, bool ignore_errors) {
    if(d->parseError)
        return false;
    if(clear) {
        d->context = d->userValues;
    }
    d->evaluate(ignore_errors);
    return !d->error;
}

bool ICISettings::reload() {
    if(d->fileName.isEmpty())
        return true;
    QFile f(d->fileName);
    if(!f.exists())
        return true;
    d->parseError = d->error = !f.open(QIODevice::ReadOnly);
    if(d->error)
        d->errorString = f.errorString();
    QByteArray content = f.readAll();
    d->parse(content, f.fileName());
    return !d->error;
}

QStringList ICISettings::files() const {
    return QStringList() << d->fileName << d->includedFiles;
}


ICISettingsPrivate::ICISettingsPrivate():
    parseError(false), error(false), ast(0), currentNode(0){


    functions.insert("equals", QPair<ICISettings::IciFunction, void*>(ICI::equals, 0));
    functions.insert("equal",  QPair<ICISettings::IciFunction, void*>(ICI::equals, 0));
    functions.insert("eq",     QPair<ICISettings::IciFunction, void*>(ICI::equals, 0));
    functions.insert("lt",     QPair<ICISettings::IciFunction, void*>(ICI::lt, 0));
    functions.insert("lte",    QPair<ICISettings::IciFunction, void*>(ICI::lte, 0));
    functions.insert("gt",     QPair<ICISettings::IciFunction, void*>(ICI::gt, 0));
    functions.insert("gte",    QPair<ICISettings::IciFunction, void*>(ICI::gte, 0));

    functions.insert("min",    QPair<ICISettings::IciFunction, void*>(ICI::min, 0));
    functions.insert("max",    QPair<ICISettings::IciFunction, void*>(ICI::max, 0));

    functions.insert("sum",    QPair<ICISettings::IciFunction, void*>(ICI::sum, 0));
    functions.insert("mul",    QPair<ICISettings::IciFunction, void*>(ICI::mul, 0));
    functions.insert("div",    QPair<ICISettings::IciFunction, void*>(ICI::div, 0));

    functions.insert("is_list",   QPair<ICISettings::IciFunction, void*>(ICI::is_list, 0));
    functions.insert("is_map",    QPair<ICISettings::IciFunction, void*>(ICI::is_map, 0));
    functions.insert("is_string", QPair<ICISettings::IciFunction, void*>(ICI::is_string, 0));
    functions.insert("is_bool",   QPair<ICISettings::IciFunction, void*>(ICI::is_bool, 0));
    functions.insert("is_double", QPair<ICISettings::IciFunction, void*>(ICI::is_double, 0));


    functions.insert("to_int",  QPair<ICISettings::IciFunction, void*>(ICI::to_int, 0));
    functions.insert("contains",  QPair<ICISettings::IciFunction, void*>(ICI::contains, 0));
    functions.insert("extend",    QPair<ICISettings::IciFunction, void*>(ICI::extend, 0));
    functions.insert("has_function",  QPair<ICISettings::IciFunction, void*>(ICI::has_function, 0));
    functions.insert("join",   QPair<ICISettings::IciFunction, void*>(ICI::join, 0));
}

ICISettingsPrivate::~ICISettingsPrivate(){
    delete ast;
}

void ICISettingsPrivate::parse(const QByteArray & data, const QString & fileName){
    if(data.isEmpty()) {
        return;
    }

    ICIParser parser(data, fileName);

    parseError = error = false;
    if(!parser.parse()){
        parseError = error = true;
        errorString = parser.errorString();
    }
    else{
        ast = parser.ast();
    }
    includedFiles.clear();
}

void ICISettingsPrivate::evaluate(bool ignore_errors) {
    currentNode = ast;
    error = false;
    this->ignore_errors = ignore_errors;
    if(ast && !evaluate(ast->nodes)){
        error = true;
    }
}

bool ICISettingsPrivate::evaluate(ICI::StatementListNode* node){
    while(node){
        currentNode = node;
        if(!evaluate(node->node, node))
            return false;
        node = node->next;
    }
    return true;
}

bool ICISettingsPrivate::evaluate(ICI::StatementNode* node, ICI::StatementListNode* parent){
    if(!node)
        return true;
    currentNode = node;
    switch(node->type){
        case ICI::Node::Type_Assignement:{
           QVariant out;
           return evaluate(static_cast<ICI::AssignementStatementNode*>(node)->node, out);
        }
        case ICI::Node::Type_IfStatement:
           return evaluate(static_cast<ICI::IfStatementNode*>(node));
        case ICI::Node::Type_Include:
           return evaluate(static_cast<ICI::IncludeStatementNode*>(node), parent);
        case ICI::Node::Type_FunctionCall:{
           QVariant returnValue;
           bool success = evaluate(static_cast<ICI::FunctionCallStatementNode*>(node)->funct, returnValue);
           if(!returnValue.isNull()){
             qWarning() << QString("ignored return value of function %1 at line %2")
                       .arg(static_cast<ICI::FunctionCallStatementNode*>(node)->funct->name)
                       .arg(static_cast<ICI::FunctionCallStatementNode*>(node)->funct->line);
           }
           return success;
        }
        case ICI::Node::Type_Map:{
           QVariant value;
           bool success = evaluate(static_cast<ICI::MapStatementNode*>(node)->map, value);
           if(!success || value.type() != QVariant::Map){
               return false;
           }
           QVariantMap map = value.toMap();
           for(QVariantMap::const_iterator it = map.begin(); it != map.end(); ++it){
               setValue(it.key(), it.value());
           }
           return true;
        }

        case ICI::Node::Type_Unset:
            return evaluate(static_cast<ICI::UnsetStatementNode*>(node));
        default:return false;
    }
    return false;
}

bool ICISettingsPrivate::evaluate(ICI::IncludeStatementNode* node, ICI::StatementListNode* parent){
    currentNode = node;
    if(node->executed)
        return true;
    bool required = true;
    QString path = replace_in_string(node->path, context);
    if(path.at(0) == '?') {
       required = false;
       path = path.mid(1);
    }
    if(path.isEmpty()){
        errorString = formatError("include() requires a file", node);
        return false;
    }
    QDir dir(QFileInfo(node->file).absolutePath());
    path = dir.absoluteFilePath(path);
    QStringList paths;
    if(QFileInfo(path).isDir()){
        Q_FOREACH(const QFileInfo & file, QDir(path).entryInfoList(QDir::NoDotAndDotDot|QDir::Files)){
            qDebug() << file.absoluteFilePath();
            paths << file.absoluteFilePath();
        }
    }
    else if(!QFileInfo(path).isFile()) {
        errorString = formatError("include: File " + path + " does not exist", node);
        return required ? false : true;
    }
    else {
        paths << path;
    }

    ICI::StatementListNode* next_node = parent->next;
    Q_FOREACH(const QString & filepath, paths){

        QFile f(filepath);
        if(!f.open(QIODevice::ReadOnly)) {
            errorString = QString("Can not open file %1").arg(path);
            if (required) {
                error = true;
                return false;
            }
            continue;
        }
        QByteArray data = f.readAll();
        ICIParser parser(data, filepath);
        if(!parser.parse()) {
            errorString = QString("Can not parse file %1 : %2").arg(path, parser.errorString());
            if(required && !ignore_errors) {
                error = true;
                return false;
            }
            continue;
        }

        includedFiles.append(filepath);
        ICI::StatementListNode* firstIncludedNode = parser.ast()->nodes;
        ICI::StatementListNode* currentIncludedNode = firstIncludedNode;
        while(currentIncludedNode && currentIncludedNode->next)
            currentIncludedNode = currentIncludedNode->next;
        currentIncludedNode->next = next_node;
        next_node = firstIncludedNode;
        node->executed = true;
    }
    parent->next = next_node;
    return true;
}

bool ICISettingsPrivate::evaluate(ICI::AssignementNode* node, QVariant & out){
    if(!node)
        return true;
    currentNode = node;
    QVariant value;
    if(!evaluate(node->value, value))
        return false;
    QStringList keys = identifier_keys(node->id, this->context);
    switch(node->op->op){
        case ICI::Node::AssignementOperator:
            set_value(keys, value, context);
            out = value;
            break;
        case ICI::Node::AssignementAdditionOperator:{
            QVariant & v = ::value_unsafe(keys, context);
            if(v.type() == QVariant::List){
                QVariantList &lst = asList(v);
                lst.append(value);
                out = lst;
            }
            else {
                errorString = formatError(keys.join(".") +" is not a list", node);
                return false;
            }
            break;
        }
        case ICI::Node::AssignementSubstractionOperator:{
             QVariant & v = ::value_unsafe(keys, context);
            if(v.type() == QVariant::List) {
                QVariantList &lst = asList(v);
                asList(v).removeAll(value);
                out = lst;
            }
            else {
                errorString = formatError(keys.join(".") +" is not a list", node);
                return false;
            }
            break;
        }
        case ICI::Node::AssignementUniqueAdditionOperator:{
            QVariant & v = ::value_unsafe(keys, context);
            if(v.isNull()) {
                QVariantList lst;
                lst << value;
                set_value(keys, lst , context);
                out = lst;
            }
            else if(v.type() == QVariant::List){
                QVariantList & lst = asList(v);
                if(!lst.contains(value)) {
                    lst.append(value);
                }
                out = lst;
            }
            break;
        }
        default:
            qDebug() << "not implemented";
            return false;
    }
    return true;
}

bool ICISettingsPrivate::evaluate(ICI::UnsetStatementNode* node){
    currentNode = node;
    unset(identifier_keys(node->identifier, context), context);
    return true;
}

bool ICISettingsPrivate::evaluate(ICI::ExpressionNode* node, QVariant & value){
    currentNode = node;
    switch(node->type){
       case ICI::Node::Type_NumericLiteral:
           value = static_cast<ICI::NumericLiteralNode*>(node)->value;
           return true;
    case ICI::Node::Type_BooleanLiteral:
           value = static_cast<ICI::BooleanLiteralNode*>(node)->value;
           return true;
        case ICI::Node::Type_Null:
           value = QVariant();
           return true;
       case ICI::Node::Type_StringLiteral:
           value = replace_in_string(static_cast<ICI::StringLiteralNode*>(node)->value, context);
           return true;
       case ICI::Node::Type_Identifier:
       case ICI::Node::Type_IdentifierString:
           value = this->value(identifier_keys(static_cast<ICI::IdentifierNode*>(node), context), QVariant());
           return true;
       case ICI::Node::Type_LogicalExpression: {
            bool istrue = false;
            if(!evaluate(static_cast<ICI::LogicalExpressionNode*>(node), istrue))
                return false;
            value = istrue;
            return true;
       }
       case ICI::Node::Type_FunctionCall:
           return evaluate(static_cast<ICI::FunctionCallNode*>(node), value);
       case ICI::Node::Type_Assignement:
            return evaluate(static_cast<ICI::AssignementNode*>(node), value);
       case ICI::Node::Type_List:{
           QVariantList lst;
           ICI::ListElementNode* elem =  static_cast<ICI::ListNode*>(node)->nodes;
           if(!evaluate(elem, lst))
               return false;
           value = lst;
           return true;
       }
       case ICI::Node::Type_Map:{
            QVariantMap map;
            ICI::MapElementNode* elem =  static_cast<ICI::MapNode*>(node)->nodes;
            if(!evaluate(elem, map))
                return false;
            value = map;
            return true;
        }
       default:
        qDebug() << "Not a valid Expression ?";
        return false;
    }
    return false;
}

bool ICISettingsPrivate::evaluate(ICI::ListElementNode* elem, QVariantList &values){
    currentNode = elem;
    while(elem){
       QVariant value;
       if(!evaluate(elem->value, value))
           return false;
       values.append(value);
       elem = elem->next;
   }
   return true;
}

bool ICISettingsPrivate::evaluate(ICI::MapElementNode* elem, QVariantMap &values) {
    currentNode = elem;
    while(elem){
       QVariant value;
       if(!evaluate(elem->value, value))
           return false;
       QString key;
       if(elem->type == ICI::Node::Type_IdentifierString)
           replace_in_string(elem->key->name, this->context);
       else key = elem->key->name;
       set_value(key, value, values);
       elem = elem->next;
   }
   return true;
}

bool ICISettingsPrivate::evaluate(ICI::FunctionCallNode * node, QVariant & result){
    currentNode = node;
    if(!node)
        return false;
    QHash<QString, QPair<ICISettings::IciFunction, void* > >::const_iterator it = functions.find(node->name);
    if(it == functions.end()){
        errorString = formatError(QString("function %1 undefined").arg(node->name), node);
        if(ignore_errors)
            return true;
        return false;
    }
    QVariantList parameters;
    if(!evaluate(node->parameters, parameters))
        return false;
    ICISettingsContext ctx;
    ctx.d->ctx = this;
    ctx.d->args = parameters;
    ICI::ListElementNode* elem = node->parameters;
    while(elem){
        if(elem->value->type == ICI::Node::Type_Identifier )
            ctx.d->keys.append(identifier_keys(static_cast<ICI::IdentifierNode*>(elem->value), context).join("."));
        else
            ctx.d->keys.append(QString());
        elem = elem->next;
    }
    ctx.d->fdata = it.value().second;
    result = it.value().first(&ctx);
    return !error;
}

bool ICISettingsPrivate::evaluate(ICI::IfStatementNode* node){
    currentNode = node;
    QVariant value;
    if(!evaluate(node->condition, value))
        return false;
    bool istrue = !value.isNull();
    if(istrue && value.canConvert<bool>()){
        istrue = value.toBool();
    }
    return evaluate(istrue ? node->block : node->alternative_block);
}

bool ICISettingsPrivate::evaluate(ICI::LogicalExpressionNode* node, bool & istrue) {
    currentNode = node;
    QVariant value;
    if(!evaluate(node->condition, value)){
        return false;
    }
    istrue = !value.isNull();
    if(istrue && value.canConvert<bool>()){
        istrue = value.toBool();
    }
    if(node->op == ICI::Node::NotOperator){
        istrue = !istrue;
        return true;
    }
    if(node->next){
        if(node->op == ICI::Node::OrOperator && istrue)
            return true;
        bool nextistrue = false;
        QVariant nextvalue;
        if(!evaluate(node->next, nextvalue)) {
            return false;
        }
        nextistrue = !nextvalue.isNull();
        if(nextistrue && nextvalue.canConvert<bool>()){
            nextistrue = nextvalue.toBool();
        }
        if(node->op == ICI::Node::AndOperator)
            istrue = istrue && nextistrue;
        if(node->op == ICI::Node::OrOperator)
            istrue = istrue || nextistrue;
    }
    return true;
}


bool ICISettingsPrivate::hasKey(const QString & key) const{
    return hasKey(key.split('.'));
}

bool ICISettingsPrivate::hasKey(const QStringList & key) const {
    if (contains(key, context))
        return true;
    if(key.size() == 1) {
        if(key.at(0) == "PWD")
            return true;
    }
    return false;
}

QVariant ICISettingsPrivate::value(const QStringList & keys, const QVariant & defaultValue) const {
    //magic constant - evaluate first to make sure they are never overwritten
    if(keys.size() == 1) {
        if(keys.at(0) == "PWD")
            if(currentNode) return QFileInfo(currentNode->file).absolutePath();

        //When adding feature, create a flag there to maintain backward compatibility
        if(keys.at(0) == "__HAS_FUNCTION")
            return true;
        if(keys.at(0) == "__HAS_STRING_IDENTIFIER")
            return true;
    }
    QVariant value = ::value(keys, context, defaultValue);
    return value;
}

QVariant ICISettingsPrivate::value(const QString & key, const QVariant & defaultValue) const{
    return value(key.split('.'), defaultValue);
}

void ICISettingsPrivate::setValue(const QString & key, const QVariant & value) {
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

bool ICISettingsContext::hasFunction(const QString & name) const {
    return d->ctx->functions.contains(name);
}

QString ICISettingsContext::file() const {
    if(d->ctx->currentNode)
        return d->ctx->currentNode->file;
    return QString::null;
}

int ICISettingsContext::line() const {
    if(d->ctx->currentNode)
        return d->ctx->currentNode->line;
    return 0;
}

const QVariantList & ICISettingsContext::args() const{
    return d->args;
}

const QStringList & ICISettingsContext::keys() const {
    return d->keys;
}

void* ICISettingsContext::fdata() const {
    return d->fdata;
}
