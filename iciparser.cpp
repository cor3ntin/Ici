
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

#define ICI_UP_LOC(node, start, end) node->line = start.line; node->pos = start.pos;

ICIParser::ICIParser(const QByteArray & data)
:m_ast(0), m_tos(0), m_stack_size(0), m_data(data),m_line(0), m_pos(0){
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

case 0: {
  sym(1).Node = ICI::makeAstNode<ICI::RootNode> (ICI::finish(sym(1).StatementList));
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
  m_ast = static_cast<ICI::RootNode*>(sym(1).Node);
} break;

case 1: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).StatementList, sym(2).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
} break;

case 2: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
} break;

case 3: {
  sym(1).Node = ICI::makeAstNode<ICI::StatementListNode> (sym(1).Statement);
  ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
} break;

case 4: {
  sym(1).Node =  ICI::finish(sym(2).StatementList);
} break;

case 5: {
  sym(1).Node = ICI::finish(ICI::makeAstNode<ICI::StatementListNode> ());
} break;

case 9: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(1).LogicalExpression,
                  sym(2).StatementList, sym(4).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(4))
    break;
}

case 10: {
    sym(1).Node = ICI::makeAstNode<ICI::IfStatementNode> (sym(1).LogicalExpression, sym(2).StatementList);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 11: {
    sym(1).Node = sym(2).Node;
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

case 12: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(2).LogicalExpression, ICI::Node::AndOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 13: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression, sym(3).LogicalExpression, ICI::Node::OrOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 14: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(2).Expression, (ICI::LogicalExpressionNode*)0, ICI::Node::NotOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

case 15: {
    sym(1).Node = ICI::makeAstNode<ICI::LogicalExpressionNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 17: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 18: {
    sym(1).Node = ICI::makeAstNode<ICI::FunctionCallNode> (*(sym(1).str), ICI::finish(sym(3).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

case 19: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 20: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementAdditionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 21: {
    sym(1).Node = ICI::makeAstNode<ICI::OperatorNode> (ICI::Node::AssignementSubstractionOperator);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 22: {
    sym(1).Node = ICI::makeAstNode<ICI::AssignementNode> (sym(1).Identifier, sym(2).Operator, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 24: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 25: {
    sym(1).Node = ICI::makeAstNode<ICI::ListNode> (ICI::finish(sym(2).ListElement));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

case 26: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 27: {
    sym(1).Node = ICI::makeAstNode<ICI::ListElementNode> (sym(1).ListElement, sym(3).Expression);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(3))
    break;
}

case 29: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (ICI::finish(sym(1).Identifier));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 30: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (sym(1).Identifier, *(sym(3).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(2))
    break;
}

case 31: {
    sym(1).Node = ICI::makeAstNode<ICI::IdentifierNode> (*(sym(1).str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 32: {
    sym(1).str = yylval.str;
    break;
}

case 33: {
    sym(1).Node = ICI::makeAstNode<ICI::NumericLiteralNode> (yylval.dval);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 34: {
    sym(1).Node = ICI::makeAstNode<ICI::StringLiteralNode> (*(yylval.str));
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 35: {
    sym(1).Node = ICI::makeAstNode<ICI::NullNode> ();
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 36: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (true);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

case 37: {
    sym(1).Node = ICI::makeAstNode<ICI::BooleanLiteralNode> (false);
    ICI_UP_LOC(sym(1).Node, loc(1), loc(1))
    break;
}

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

