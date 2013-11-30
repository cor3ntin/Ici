
#line 51 "ici.g"

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

#ifndef _ICIPARSER_H_
#define _ICIPARSER_H_

#include <QtCore>
#include "icigrammar_p.h"
#include "iciast_fwd.h"

class ICIParser: protected ICIGrammar
{
public:
    ICIParser(const QByteArray & data, const QString & fileName = QString());

    bool parse();
    QString errorString() const;
    ICI::RootNode* ast() const;

protected:
    int nextToken(void* scanner);
    union Value {
          double dval;
          ICI::Node* Node;
          ICI::StatementNode* Statement;
          ICI::FunctionCallNode* FunctionCall;
          ICI::StatementListNode* StatementList;
          ICI::IdentifierNode* Identifier;
          ICI::ExpressionNode* Expression;
          ICI::LogicalExpressionNode* LogicalExpression;
          ICI::ListElementNode* ListElement;
          ICI::MapElementNode* MapElement;
          ICI::OperatorNode*    Operator;
          const QString* str;
    };
    struct Loc {
        int line;
        int pos;
    };
    struct StackItem {
        int state;
        Value value;
        Loc loc;
    };

    void reallocateStack();

    inline Value &sym(int index)
    { return m_stack [m_tos + index - 1].value; }
    inline Loc &loc(int index)
    { return m_stack [m_tos + index - 1].loc; }


    inline const QString* storeString(const QByteArray & string){
        return &*m_strings.insert(unescape(string));
    }
    QString unescape( const QByteArray & ba);

    ICI::RootNode* m_ast;
    int m_tos;
    int m_stack_size;

    Value yylval;
    QVarLengthArray<StackItem> m_stack;
    QSet<QString> m_strings;


    QByteArray m_data;
    QString m_fileName;
    void* m_lexdata;

    int m_line, m_pos;
    QString m_errorString;

};


#endif // _ICIPARSER_H_
