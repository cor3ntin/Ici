%option noyywrap

%{

#include "iciparser.h"
#include <cstdlib>

#define YY_DECL int ICIParser::nextToken()

static QByteArray stringbuffer;
%}
%x simple_string
%x double_string
%x raw_string
%%


"="	{ return TOKEN_EQUAL; }
"+=" { return TOKEN_PLUS_EQUAL; }
"-=" { return TOKEN_MINUS_EQUAL; }
"("	{ return TOKEN_LPAREN; }
")"	{ return TOKEN_RPAREN; }
"{" { return TOKEN_LBRACKET; }
"}" { return TOKEN_RBRACKET; }
"[" { return TOKEN_LSQUARE_BRACKET; }
"]" { return TOKEN_RSQUARE_BRACKET; }
"." { return TOKEN_DOT; }
"," { return TOKEN_COMMA; }
"&&" { return TOKEN_AND; }
"||" { return TOKEN_OR; }
"!" { return TOKEN_NOT; }


[0-9]+ { return TOKEN_DIGIT; }
[a-zA-Z\-_][a-zA-Z\-_0-9]*    { yylval = QByteArray(yytext) ; return TOKEN_IDENT; }

\"  { BEGIN double_string; stringbuffer.clear(); }
<double_string>[^\\"]*   { stringbuffer.append(yytext); }
<double_string>\\[\\"]   { stringbuffer.append(yytext[1]); }
<double_string>\"         { yylval = stringbuffer; BEGIN 0; return TOKEN_STRING; }

\'  { BEGIN simple_string; stringbuffer.clear(); }
<simple_string>[^\\']*   { stringbuffer.append(yytext); }
<simple_string>\\[\\']   { stringbuffer.append(yytext[1]); }
<simple_string>\'         { yylval = stringbuffer; BEGIN 0; return TOKEN_STRING; }

\{\{\{  { BEGIN raw_string; stringbuffer.clear(); }
<raw_string>[\n]*     { if(!stringbuffer.isEmpty()) {stringbuffer.append(yytext);}}
<raw_string>\n\}\}\}  { yylval = stringbuffer; BEGIN 0; return TOKEN_STRING; }
<raw_string>.*   { stringbuffer.append(yytext); }


#.* {
  /* skip */
}

%%
