%option noyywrap
%option nounput
%option nounistd
%option never-interactive
%option reentrant


%{
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
#include <cstdlib>

#define YY_DECL int ICIParser::nextToken(void* yyscanner)
#define YY_USER_ACTION m_pos += yyleng;


static QByteArray stringbuffer;
%}
%x simple_string
%x double_string
%x raw_string
%%

"\n" { ++m_line; m_pos = 0; }

"="	{ return TOKEN_EQUAL; }
"+=" { return TOKEN_PLUS_EQUAL; }
"-=" { return TOKEN_MINUS_EQUAL; }
"*=" { return TOKEN_STAR_EQUAL; }
"("	{ return TOKEN_LPAREN; }
")"	{ return TOKEN_RPAREN; }
"{" { return TOKEN_LBRACKET; }
"}" { return TOKEN_RBRACKET; }
"[" { return TOKEN_LSQUARE_BRACKET; }
"]" { return TOKEN_RSQUARE_BRACKET; }
"." { return TOKEN_DOT; }
"," { return TOKEN_COMMA; }
":" { return TOKEN_COLON; }
"and" { return TOKEN_AND; }
"or" { return TOKEN_OR; }
"!" { return TOKEN_NOT; }
"if" { return TOKEN_IF; }
"else" { return TOKEN_ELSE; }
"true" { return TOKEN_TRUE; }
"false" { return TOKEN_FALSE; }
"null" { return TOKEN_NULL; }
"include" { return TOKEN_INCLUDE; }
"unset" { return TOKEN_UNSET; }

\"  { BEGIN double_string; stringbuffer.clear(); }
<double_string>[^\\"]*   { stringbuffer.append(yytext); }
<double_string>\\[\\"]   { stringbuffer.append(yytext[1]); }
<double_string>\"         { yylval.str = storeString(stringbuffer); BEGIN 0; return TOKEN_STRING; }

\'  { BEGIN simple_string; stringbuffer.clear(); }
<simple_string>[^\\']*   { stringbuffer.append(yytext); }
<simple_string>\\[\\']   { stringbuffer.append(yytext[1]); }
<simple_string>\'         { yylval.str = storeString(stringbuffer); BEGIN 0; return TOKEN_STRING; }

\"\"\"  { BEGIN raw_string; stringbuffer.clear(); }
<raw_string>[\n]*     { if(!stringbuffer.isEmpty()) {stringbuffer.append(yytext);}}
<raw_string>\n\"\"\"  { yylval.str = storeString(stringbuffer); BEGIN 0; return TOKEN_STRING; }
<raw_string>.*   { stringbuffer.append(yytext); }

[0-9]+ { yylval.dval = QByteArray(yytext).toDouble(); return TOKEN_DIGIT; }
[0-9]+\.[0-9]+ { yylval.dval = QByteArray(yytext).toDouble(); return TOKEN_DIGIT; }
[a-zA-Z_][a-zA-Z_0-9]*    { yylval.str = storeString(yytext) ; return TOKEN_IDENT; }

#.* {/* skip */}
[\t ] {/* skip */}

%%
