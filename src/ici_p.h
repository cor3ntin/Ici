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

#ifndef _ICIPRIVATE_H
#define _ICIPRIVATE_H

#include <QObject>
#include <QVariantMap>

#include "ici.h"
#include "iciast.h"
#include "iciparser.h"

class ICISettingsContextPrivate{
public:
    ICISettingsPrivate* ctx;
    QVariantList args;
    QStringList keys;
    void* fdata;
};

class ICISettingsPrivate{
public:
    ICISettingsPrivate();
    ~ICISettingsPrivate();
    void parse(const  QByteArray & data,const QString & fileName = QString());

    bool error;
    QString fileName;
    QStringList includedFiles;
    QString errorString;
    ICI::RootNode* ast;
    QVariantMap context;
    QHash<QString, QPair<ICISettings::IciFunction, void* > > functions;
    ICI::Node* currentNode;


    void evaluate();
    bool evaluate(ICI::StatementListNode*);
    bool evaluate(ICI::StatementNode*, ICI::StatementListNode*);
    bool evaluate(ICI::IncludeStatementNode*, ICI::StatementListNode*);
    bool evaluate(ICI::ExpressionNode*, QVariant &value);
    bool evaluate(ICI::ListElementNode*, QVariantList &value);
    bool evaluate(ICI::MapElementNode*, QVariantMap &values);
    bool evaluate(ICI::IdentifierNode*);
    bool evaluate(ICI::AssignementNode*);
    bool evaluate(ICI::UnsetStatementNode*);
    bool evaluate(ICI::FunctionCallNode*,QVariant &);
    bool evaluate(ICI::IfStatementNode*);
    bool evaluate(ICI::LogicalExpressionNode*,bool & istrue);

    QString replace_in_string(QString string, const QVariantMap & context);
    QStringList identifier_keys(ICI::IdentifierNode* node, const QVariantMap & context);
    bool hasKey(const QString & key) const;
    bool hasKey(const QStringList & key) const;
    QVariant value(const QString & key, const QVariant & defaultValue) const;
    QVariant value(const QStringList & keys, const QVariant & defaultValue) const;
    void setValue(const QString & key, const QVariant & value);
};

#endif // _ICIPRIVATE_H
