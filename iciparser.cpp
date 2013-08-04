
#line 145 "ici.g"

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

      if (act == ACCEPT_STATE) {
        yy_delete_buffer(reinterpret_cast<YY_BUFFER_STATE>(m_lexdata));
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

#line 234 "ici.g"

case 0: {
  sym(1).Node = ICI::makeAstNode<ICI::RootNode> (ICI::finish(sym(1).StatementList));
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
  m_ast = static_cast<ICI::RootNode*>(sym(1).Node);
} break;

#line 243 "ici.g"

case 1: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).StatementList, sym(2).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
} break;

#line 250 "ici.g"

case 2: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
} break;

#line 258 "ici.g"

case 3: {
  sym(1).Node =  ICI::finish(sym(2).StatementList);
} break;

#line 264 "ici.g"

case 4: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> ());
} break;

#line 270 "ici.g"

case 5: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement));
} break;

#line 282 "ici.g"

case 10: {
sym(1).Node = ICI::makeAstNode<ICI::FunctionCallStatementNode>(sym(1).FunctionCall);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 290 "ici.g"

case 11: {
    sym(1).Node = ICI::makeAstNode<ICI::IncludeStatementNode>(*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 299 "ici.g"

case 12: {
    sym(1).Node = ICI::makeAstNode<ICI::UnsetStatementNode>(sym(2).Identifier);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 308 "ici.g"

case 13: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(2).LogicalExpression,
                  sym(3).StatementList, sym(5).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(5))
    break;
}

#line 317 "ici.g"

case 14: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(2).LogicalExpression, sym(3).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 327 "ici.g"

case 15: {
    sym(1).Node = sym(2).Node;
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 335 "ici.g"

case 16: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).LogicalExpression, ICI::Node::AndOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 343 "ici.g"

case 17: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).LogicalExpression, ICI::Node::OrOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 351 "ici.g"

case 18: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(2).Expression, (ICI::LogicalExpressionNode*)0, ICI::Node::NotOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 359 "ici.g"

case 19: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 370 "ici.g"

case 21: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 378 "ici.g"

case 22: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(sym(1).str), ICI::finish(sym(3).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 387 "ici.g"

case 23: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 395 "ici.g"

case 24: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 403 "ici.g"

case 25: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementSubstractionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 412 "ici.g"

case 26: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementUniqueAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 421 "ici.g"

case 27: {
    sym(1).Node = ICI::makeAstNode<ICI::AssignementNode> (sym(1).Identifier, sym(2).Operator, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 431 "ici.g"

case 29: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 439 "ici.g"

case 30: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 447 "ici.g"

case 31: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 455 "ici.g"

case 32: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 463 "ici.g"

case 33: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).ListElement, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 473 "ici.g"

case 35: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 481 "ici.g"

case 36: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> (ICI::finish(sym(2).MapElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 489 "ici.g"

case 37: {
    sym(1).Node = ICI::makeAstNode<ICI::MapNode> (ICI::finish(sym(2).MapElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 498 "ici.g"

case 38: {
    sym(1).Node = ICI::makeAstNode<ICI::MapElementNode> (sym(1).Identifier, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 507 "ici.g"

case 39: {
    sym(1).Node = ICI::makeAstNode<ICI::MapElementNode> (sym(1).MapElement, sym(3).Identifier, sym(5).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

#line 518 "ici.g"

case 41: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (ICI::finish(sym(1).Identifier));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 527 "ici.g"

case 42: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (sym(1).Identifier, *(sym(3).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

#line 536 "ici.g"

case 43: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 544 "ici.g"

case 44: {
    sym(1).str = yylval.str;
    break;
}

#line 551 "ici.g"

case 45: {
    sym(1).Node = ICI::makeAstNode<ICI::NumericLiteralNode> (yylval.dval);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 559 "ici.g"

case 46: {
    sym(1).Node = ICI::makeAstNode<ICI::StringLiteralNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 567 "ici.g"

case 47: {
    sym(1).Node = ICI::makeAstNode<ICI::NullNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 575 "ici.g"

case 48: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (true);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 583 "ici.g"

case 49: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (false);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

#line 591 "ici.g"

        } // switch
        m_stack [m_tos].state = nt_action (act, lhs [r] - TERMINAL_COUNT);
        }
        else {
            m_errorString = QString("Syntax error at Line %1:%2")
            .arg(m_line).arg(m_pos);
            break;
        }
    }
    yy_delete_buffer(reinterpret_cast<YY_BUFFER_STATE>(m_lexdata));
    return false;
}

QString ICIParser::errorString() const{
   return m_errorString;
}

