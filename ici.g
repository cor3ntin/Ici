%parser ICIGrammar
%decl iciparser.h
%impl iciparser.cpp


%token_prefix TOKEN_
%token STRING
%token DIGIT
%token IDENT
%token VARIABLE
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

%start Input

/:
#ifndef _ICIPARSER_H_
#define _ICIPARSER_H_

#include <QtCore>
#include "icigrammar_p.h"

class ICIParser: protected $table
{
public:
    ICIParser(const QByteArray & data);

    bool parse();
    int nextToken();
    QVariantMap values() const;

protected:
    union Value {
       const QString  *k;
       const QVariant *v;
    };
    struct StackItem {
        int state;
        QByteArray value;
    };

    void reallocateStack();

    inline QByteArray &sym(int index)
    { return m_stack [m_tos + index - 1].value; }

    int m_tos;
    int m_stack_size;

    QByteArray yylval;

    QVarLengthArray<StackItem> m_stack;
    QByteArray m_data;
    void* m_lexdata;

    QVariantMap m_values;
};


#endif // _ICIPARSER_H_
:/




/.
#include "iciparser.h"
#include "ici-lex.inc"

#include <QtDebug>

ICIParser::ICIParser(const QByteArray & data)
:m_tos(0), m_stack_size(0), m_data(data){
}

QVariantMap ICIParser::values() const{
    return m_values;
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
          qDebug() << "token" << yytoken;
      }

      int act = t_action (state, yytoken);

      if (act == ACCEPT_STATE)
        return true;

      else if (act > 0)
        {
          if (++m_tos == m_stack_size)
            reallocateStack();

          m_stack [m_tos].value = yylval; // ### save the token value here
          m_stack [m_tos].state = act;
          yytoken = -1;
        }

      else if (act < 0)
        {
          int r = - act - 1;

          m_tos -= rhs [r];
          act = m_stack [m_tos++].state;

          qDebug() << r << sym(1);
          switch (r) {
./

Input: Expression ;
Input: Input Expression ;


Expression: Assignement ;
Expression: Condition LBRACKET Expression RBRACKET ;

Condition: Condition AND Condition ;
Condition: Condition OR Condition ;
Condition: NOT Condition;
Condition: Function ;


Function: IDENT LPAREN FunctionsParametersOpt RPAREN ;

FunctionsParameters: Value ;
FunctionsParameters: FunctionsParameters COMMA Value ;
FunctionsParametersOpt: ;
FunctionsParametersOpt: FunctionsParameters ;

AssignementOperator: EQUAL ;
AssignementOperator: PLUS_EQUAL ;
AssignementOperator: MINUS_EQUAL ;

Assignement: Key AssignementOperator Value ;

Value: DIGIT ;
Value: STRING;
Value: Key ;
Value: List ;

List : LSQUARE_BRACKET ListParametersOpt RSQUARE_BRACKET;
ListParameters: Value ;
ListParameters: ListParameters COMMA Value ;
ListParametersOpt: ;
ListParametersOpt: ListParameters ;

Key: Key DOT IDENT;
Key: IDENT ;


/.
        } // switch
        m_stack [m_tos].state = nt_action (act, lhs [r] - TERMINAL_COUNT);
        }
        else {
            qDebug() << "Error";
            break;
        }
    }
   return false;
}

./
