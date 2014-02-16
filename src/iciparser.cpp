
#line 147 "ici.g"

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

#line 325 "ici.g"

case 0: {
  sym(1).Node = ICI::makeAstNode<ICI::RootNode> (ICI::finish(sym(1).StatementList));
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
  m_ast = static_cast<ICI::RootNode*>(sym(1).Node);
} break;

#line 334 "ici.g"

case 1: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).StatementList, sym(2).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
} break;

#line 341 "ici.g"

case 2: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
} break;

#line 349 "ici.g"

case 3: {
  sym(1).Node =  ICI::finish(sym(2).StatementList);
} break;

#line 355 "ici.g"

case 4: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> ());
} break;

#line 361 "ici.g"

case 5: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement));
} break;

#line 373 "ici.g"

case 10: {
sym(1).Node = ICI::makeAstNode<ICI::FunctionCallStatementNode>(sym(1).FunctionCall);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 381 "ici.g"

case 11: {
    sym(1).Node = ICI::makeAstNode<ICI::IncludeStatementNode>(*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 390 "ici.g"

case 12: {
    sym(1).Node = ICI::makeAstNode<ICI::UnsetStatementNode>(sym(2).Identifier);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 399 "ici.g"

case 13: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(2).LogicalExpression,
                  sym(3).StatementList, sym(5).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(5))
    break;
}

#line 408 "ici.g"

case 14: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(2).LogicalExpression, sym(3).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 418 "ici.g"

case 15: {
    sym(1).Node = sym(2).Node;
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 426 "ici.g"

case 16: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).LogicalExpression, ICI::Node::AndOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 434 "ici.g"

case 17: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).LogicalExpression, ICI::Node::OrOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 442 "ici.g"

case 18: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(2).Expression, (ICI::LogicalExpressionNode*)0, ICI::Node::NotOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 450 "ici.g"

case 19: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 461 "ici.g"

case 21: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 469 "ici.g"

case 22: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(sym(1).str), ICI::finish(sym(3).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 478 "ici.g"

case 23: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 486 "ici.g"

case 24: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 494 "ici.g"

case 25: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementSubstractionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 503 "ici.g"

case 26: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementUniqueAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 512 "ici.g"

case 27: {
    sym(1).Node = ICI::makeAstNode<ICI::AssignementNode> (sym(1).Identifier, sym(2).Operator, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 522 "ici.g"

case 29: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 530 "ici.g"

case 30: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 538 "ici.g"

case 31: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 546 "ici.g"

case 32: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 554 "ici.g"

case 33: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).ListElement, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 564 "ici.g"

case 35: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 572 "ici.g"

case 36: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> (ICI::finish(sym(2).MapElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 580 "ici.g"

case 37: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> (ICI::finish(sym(2).MapElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 589 "ici.g"

case 38: {
    sym(1).Node = ICI::makeAstNode<ICI::MapElementNode> (sym(1).Identifier, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 598 "ici.g"

case 39: {
    sym(1).Node = ICI::makeAstNode<ICI::MapElementNode> (sym(1).MapElement, sym(3).Identifier, sym(5).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 609 "ici.g"

case 41: {
    sym(1).Node = ICI::finish(sym(1).Identifier);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 618 "ici.g"

case 42: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (sym(1).Identifier, *(sym(3).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 627 "ici.g"

case 43: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierStringNode> (sym(1).Identifier, *(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 636 "ici.g"

case 44: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 645 "ici.g"

case 45: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierStringNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}


#line 654 "ici.g"

case 46: {
    sym(1).str = yylval.str;
    break;
}

#line 661 "ici.g"

case 47: {
    sym(1).Node = ICI::makeAstNode<ICI::NumericLiteralNode> (yylval.dval);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 670 "ici.g"

case 48: {
    sym(1).Node = ICI::makeAstNode<ICI::StringLiteralNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 679 "ici.g"

case 49: {
    sym(1).Node = ICI::makeAstNode<ICI::NullNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 687 "ici.g"

case 50: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (true);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 695 "ici.g"

case 51: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (false);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 703 "ici.g"

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

