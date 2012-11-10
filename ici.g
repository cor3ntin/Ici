----------------------------------------------------------------------------
--
-- Copyright (C) 2012 Corentin Jabot
-- Contact: https://github.com/cor3ntin/Ici
--
-- GNU Lesser General Public License Usage
-- This file may be used under the terms of the GNU Lesser
-- General Public License version 2.1 as published by the Free Software
-- Foundation and appearing in the file LICENSE.LGPL included in the
-- packaging of this file.  Please review the following information to
-- ensure the GNU Lesser General Public License version 2.1 requirements
-- will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
--
----------------------------------------------------------------------------

%parser ICIGrammar
%decl iciparser.h
%impl iciparser.cpp


%token_prefix TOKEN_
%token STRING
%token DIGIT
%token IDENT
%token NULL
%token TRUE
%token FALSE
%token DOT
%token EQUAL
%token PLUS_EQUAL
%token MINUS_EQUAL
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LSQUARE_BRACKET
%token RSQUARE_BRACKET
%token COMMA
%token AND
%token OR
%token NOT
%token ELSE
%token INCLUDE
%token UNSET

%start Source

/:
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

class ICIParser: protected $table
{
public:
    ICIParser(const QByteArray & data, const QString & fileName = QString());

    bool parse();
    QString errorString() const;
    ICI::RootNode* ast() const;

protected:
    int nextToken();
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


    inline const QString* storeString(const QString & string){
        return &*m_strings.insert(string);
    }

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
:/




/.
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

#include "iciparser.h"
#include "ici-lex.inc"
#include "iciast.h"

#define ICI_UP_LOC(node, start, end) node->file = m_fileName; node->line = start.line; node->pos = start.pos;

ICIParser::ICIParser(const QByteArray & data, const QString & fileName)
:m_ast(0), m_tos(0), m_stack_size(0), m_data(data),m_fileName(fileName), m_line(0), m_pos(0){
}

ICI::RootNode* ICIParser::ast() const{
   return m_ast;
}

void ICIParser::reallocateStack()
{
    if (! m_stack_size)
        m_stack_size = 128;
    else
        m_stack_size <<= 1;

    m_stack.resize (m_stack_size);
}

bool ICIParser::parse()
{
    const int INITIAL_STATE = 0;

    int yytoken = -1;
    reallocateStack();

    m_tos = 0;
    m_stack [++m_tos].state = INITIAL_STATE;
    m_lexdata = yy_scan_string(m_data.constData());

    while (true)
    {
      const int state = m_stack [m_tos].state;

      if (yytoken == -1 && - TERMINAL_COUNT != action_index [state]){
          yytoken = nextToken();
      }

      int act = t_action (state, yytoken);

      if (act == ACCEPT_STATE)
        return true;

      else if (act > 0)
        {
          if (++m_tos == m_stack_size)
            reallocateStack();

          m_stack [m_tos].value.dval = yytoken; // ### save the token value here
          m_stack [m_tos].state = act;
          m_stack [m_tos].loc.line = m_line;
          m_stack [m_tos].loc.pos = m_pos - yyleng;
          yytoken = -1;
        }

      else if (act < 0)
        {
          int r = - act - 1;

          m_tos -= rhs [r];
          act = m_stack [m_tos++].state;

          switch (r) {
./

Source: StatementList ;
/.
case $rule_number: {
  sym(1).Node = ICI::makeAstNode<ICI::RootNode> (ICI::finish(sym(1).StatementList));
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
  m_ast = static_cast<ICI::RootNode*>(sym(1).Node);
} break;
./

StatementList: StatementList Statement ;
/.
case $rule_number: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).StatementList, sym(2).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
} break;
./
StatementList: Statement ;
/.
case $rule_number: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
} break;
./

StatementBlock: LBRACKET StatementList RBRACKET ;
/.
case $rule_number: {
  sym(1).Node =  ICI::finish(sym(2).StatementList);
} break;
./
StatementBlock: LBRACKET RBRACKET ;
/.
case $rule_number: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> ());
} break;
./

Statement: Assignement ;
Statement: IfStatement ;
Statement: IncludeStatement;
Statement: UnsetStatement;

Statement: FunctionCall;
/.
case $rule_number: {
sym(1).Node = ICI::makeAstNode<ICI::FunctionCallStatementNode>(sym(1).FunctionCall);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
IncludeStatement: INCLUDE STRING;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IncludeStatementNode>(*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

UnsetStatement: UNSET Identifier;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::UnsetStatementNode>(sym(2).Identifier);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

IfStatement: LogicalExpression StatementBlock ELSE StatementBlock;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(1).LogicalExpression,
                  sym(2).StatementList, sym(4).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(4))
    break;
}
./
IfStatement: LogicalExpression StatementBlock ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(1).LogicalExpression, sym(2).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

LogicalExpression: LPAREN Expression RPAREN ;
/.
case $rule_number: {
    sym(1).Node = sym(2).Node;
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./
LogicalExpression: Expression AND LogicalExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(2).LogicalExpression, ICI::Node::AndOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
LogicalExpression: Expression OR LogicalExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).LogicalExpression, ICI::Node::OrOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
LogicalExpression: NOT Expression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(2).Expression, (ICI::LogicalExpressionNode*)0, ICI::Node::NotOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./
LogicalExpression: Expression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./


Expression: FunctionCall;
FunctionCall: StoredIdent LPAREN RPAREN ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
FunctionCall: StoredIdent LPAREN ListParameters RPAREN ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(sym(1).str), ICI::finish(sym(3).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

AssignementOperator: EQUAL ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
AssignementOperator: PLUS_EQUAL ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
AssignementOperator: MINUS_EQUAL ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementSubstractionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

Assignement: Identifier AssignementOperator Expression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::AssignementNode> (sym(1).Identifier, sym(2).Operator, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

Expression : List ;
List : LSQUARE_BRACKET RSQUARE_BRACKET ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
List : LSQUARE_BRACKET ListParameters RSQUARE_BRACKET ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./
ListParameters: Expression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
ListParameters: ListParameters COMMA Expression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).ListElement, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

Expression: Identifier;

Identifier: IdentifierPart ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (ICI::finish(sym(1).Identifier));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

IdentifierPart: IdentifierPart DOT StoredIdent ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (sym(1).Identifier, *(sym(3).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

IdentifierPart: StoredIdent ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
StoredIdent: IDENT ;
/.
case $rule_number: {
    sym(1).str = yylval.str;
    break;
}
./
Expression: DIGIT ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::NumericLiteralNode> (yylval.dval);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
Expression: STRING;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::StringLiteralNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
Expression: NULL;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::NullNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
Expression: TRUE;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (true);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
Expression: FALSE;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (false);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

/.
        } // switch
        m_stack [m_tos].state = nt_action (act, lhs [r] - TERMINAL_COUNT);
        }
        else {
            m_errorString = QString("Syntax error at Line %1:%2")
            .arg(m_line).arg(m_pos);
            break;
        }
    }
   return false;
}

QString ICIParser::errorString() const{
   return m_errorString;
}

./
