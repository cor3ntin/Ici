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
%token STAR_EQUAL
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LSQUARE_BRACKET
%token RSQUARE_BRACKET
%token COMMA
%token COLON
%token AND
%token OR
%token NOT
%token IF
%token ELSE
%token INCLUDE
%token UNSET
%token FOREACH

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

#include <ctype.h>
#include <QString>
#include <QByteArray>
#include <QVarLengthArray>
#include <QSet>
#include <QDebug>
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
    int nextToken(void* scanner);
    union Value {
          double dval;
          ICI::Node* Node;
          ICI::StatementNode* Statement;
          ICI::FunctionCallNode* FunctionCall;
          ICI::AssignementNode* Assignement;
          ICI::StatementListNode* StatementList;
          ICI::IdentifierNode* Identifier;
          ICI::ExpressionNode* Expression;
          ICI::LogicalExpressionNode* LogicalExpression;
          ICI::ListElementNode* ListElement;
          ICI::MapElementNode* MapElement;
          ICI::MapNode* Map;
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



namespace ICI {
template <typename NodeType, typename... Args>
NodeType* makeAstNode(Args&&...args){
    return new NodeType(std::forward<Args>(args)...);
}

template <typename NodeType> NodeType* finish(NodeType* node) {
    if(!node)
        return 0;
    NodeType* front = node->next;
    node->next = 0;
    return front;
}
}

bool ishexnstring(const QString & string) {
    for (int i = 0; i < string.length(); i++) {
        if (isxdigit(string[i] == 0))
            return false;
    }
    return true;
}

QString ICIParser::unescape( const QByteArray & ba) {
    QString res;
    QByteArray seg;
    bool bs = false;
    for (int i = 0, size = ba.size(); i < size; ++i) {
        const char ch = ba[i];
        if (!bs) {
            if (ch == '\\')
                bs = true;
            else
                seg += ch;
        }
        else {
            bs = false;
            switch (ch) {
            case 'b':
                seg += '\b';
                break;
            case 'f':
                seg += '\f';
                break;
            case 'n':
                seg += '\n';
                break;
            case 'r':
                seg += '\r';
                break;
            case 't':
                seg += '\t';
                break;
            case 'u':
            {
                res += QString::fromUtf8( seg );
                seg.clear();

                if (i > size - 5) {
                    //error
                    return QString();
                }

                const QString hex_digit1 = QString::fromUtf8( ba.mid( i + 1, 2 ));
                const QString hex_digit2 = QString::fromUtf8( ba.mid( i + 3, 2 ));
                i += 4;

                if (!ishexnstring( hex_digit1 ) || !ishexnstring( hex_digit2 )) {
                    qCritical() << "Not an hex string:" << hex_digit1 << hex_digit2;
                    return QString();
                }
                bool hexOk;
                const ushort hex_code1 = hex_digit1.toShort( &hexOk, 16 );
                if (!hexOk) {
                    qCritical() << "error converting hex value to short:" << hex_digit1;
                    return QString();
                }
                const ushort hex_code2 = hex_digit2.toShort( &hexOk, 16 );
                if (!hexOk) {
                    qCritical() << "error converting hex value to short:" << hex_digit2;
                    return QString();
                }

                res += QChar(hex_code2, hex_code1);
                break;
            }
            case '\\':
                seg  += '\\';
                break;
            default:
                seg += ch;
                break;
            }
        }
    }
    res += QString::fromUtf8( seg );
    return res;
}

ICIParser::ICIParser(const QByteArray & data, const QString & fileName)
:m_ast(0), m_tos(0), m_stack_size(0), m_data(data),m_fileName(fileName), m_line(1), m_pos(0){
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
    void* scanner;
    yylex_init(&scanner);
    struct yyguts_t * yyg = (struct yyguts_t*)scanner;

    const int INITIAL_STATE = 0;

    int yytoken = -1;
    reallocateStack();

    m_tos = 0;
    m_stack [++m_tos].state = INITIAL_STATE;
    m_lexdata = yy_scan_string(m_data.constData(), scanner);

    while (true)
    {
      const int state = m_stack [m_tos].state;

      if (yytoken == -1 && - TERMINAL_COUNT != action_index [state]){
          yytoken = nextToken(scanner);
      }

      int act = t_action (state, yytoken);

      if (act == ACCEPT_STATE) {
        yy_delete_buffer(reinterpret_cast<YY_BUFFER_STATE>(m_lexdata), scanner);
        yylex_destroy(scanner);
        return true;
    }

      else if (act > 0)
        {
          if (++m_tos == m_stack_size-1)
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
StatementBlock: Statement ;
/.
case $rule_number: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement));
} break;
./

Statement: Assignement ;
/.
case $rule_number: {
sym(1).Node = ICI::makeAstNode<ICI::AssignementStatementNode>(sym(1).Assignement);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

Statement: Map ;
/.
case $rule_number: {
sym(1).Node = ICI::makeAstNode<ICI::MapStatementNode>(sym(1).Map);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

Statement: IfStatement ;
Statement: ForeachStatement ;
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

IfStatement: IF RExpression StatementBlock ELSE StatementBlock;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(2).Expression,
                  sym(3).StatementList, sym(5).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(5))
    break;
}
./
IfStatement: IF RExpression StatementBlock ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(2).Expression, sym(3).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

ForeachStatement : FOREACH StoredIdentifier COLON RExpression StatementBlock ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ForeachStatementNode> (*(sym(2).str), sym(4).Expression, sym(5).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

RExpression: LPAREN RExpression RPAREN ;
/.
case $rule_number: {
    sym(1).Node = sym(2).Node;
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

LogicalExpression: RExpression AND RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).Expression, ICI::Node::AndOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
LogicalExpression: RExpression OR RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).Expression, ICI::Node::OrOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
LogicalExpression: NOT RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(2).Expression, (ICI::LogicalExpressionNode*)0, ICI::Node::NotOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

RExpression: LogicalExpression;



RExpression: FunctionCall;
FunctionCall: StoredIdentifier LPAREN RPAREN ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
FunctionCall: StoredIdentifier LPAREN ListParameters RPAREN ;
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

AssignementOperator: STAR_EQUAL ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementUniqueAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

RExpression: Assignement;

Assignement: LExpression AssignementOperator RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::AssignementNode> (sym(1).Identifier, sym(2).Operator, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

RExpression : List ;
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
List : LSQUARE_BRACKET ListParameters COMMA RSQUARE_BRACKET ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./
ListParameters: RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
ListParameters: ListParameters COMMA RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).ListElement, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

RExpression : Map ;
Map : LBRACKET RBRACKET ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./
Map : LBRACKET MapParameters RBRACKET ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> (ICI::finish(sym(2).MapElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./
Map : LBRACKET MapParameters COMMA RBRACKET ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> (ICI::finish(sym(2).MapElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

MapParameters: Identifier COLON RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::MapElementNode> (sym(1).Identifier, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

MapParameters: MapParameters COMMA Identifier COLON RExpression ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::MapElementNode> (sym(1).MapElement, sym(3).Identifier, sym(5).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

RExpression: String;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::StringLiteralNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

RExpression: Double;
/.
case $rule_number: {
sym(1).Node = ICI::makeAstNode<ICI::NumericLiteralNode> (sym(1).dval);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

RExpression: NULL;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::NullNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
RExpression: TRUE;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (true);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./
RExpression: FALSE;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (false);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

RExpression: LExpression;

LExpression: Identifier;


Identifier: IdentifierPart ;
/.
case $rule_number: {
    sym(1).Node = ICI::finish(sym(1).Identifier);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

Identifier: DOT IdentifierPart ;
/.
case $rule_number: {
    sym(1).Node = ICI::finish(sym(2).Identifier);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}
./

IdentifierPart: IdentifierPart DOT StoredIdentifier ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (sym(1).Identifier, *(sym(3).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

IdentifierPart: IdentifierPart DOT String;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierStringNode> (sym(1).Identifier, *(sym(3).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

IdentifierPart: IdentifierPart DOT Double;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (sym(1).Identifier, QString::number(sym(3).dval));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}
./

IdentifierPart: StoredIdentifier ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./

IdentifierPart: String ;
/.
case $rule_number: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierStringNode>(*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}
./


String: STRING;
/.
case $rule_number: {
    sym(1).str = yylval.str;
    break;
}
./

StoredIdentifier: IDENT;
/.
case $rule_number: {
    sym(1).str = yylval.str;
    break;
}
./

Double: DIGIT ;
/.
case $rule_number: {
    sym(1).dval = yylval.dval;
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
    yy_delete_buffer(reinterpret_cast<YY_BUFFER_STATE>(m_lexdata), scanner);
    yylex_destroy(scanner);
    return false;
}

QString ICIParser::errorString() const{
   return m_errorString;
}

./
