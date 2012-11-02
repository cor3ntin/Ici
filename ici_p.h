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
};

class ICISettingsPrivate{
public:
    ICISettingsPrivate();
    void parse(const  QByteArray & data);

    bool error;
    QString errorString;
    ICI::RootNode* ast;
    QVariantMap context;
    QHash<QString, ICISettings::IciFunction> functions;


    void evaluate();
    bool evaluate(ICI::StatementListNode*);
    bool evaluate(ICI::StatementNode*);
    bool evaluate(ICI::ExpressionNode*, QVariant &value);
    bool evaluate(ICI::ListElementNode*, QVariantList &value);
    bool evaluate(ICI::IdentifierNode*);
    bool evaluate(ICI::AssignementNode*);
    bool evaluate(ICI::FunctionCallNode*,QVariant &);
    bool evaluate(ICI::IfStatementNode*);
    bool evaluate(ICI::LogicalExpressionNode*,bool & istrue);

    bool hasKey(const QString & key) const;
    QVariant value(const QString & key, const QVariant & defaultValue) const;
    void setValue(const QString & key, const QVariant & value);
};

#endif // _ICIPRIVATE_H
