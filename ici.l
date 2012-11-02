%option noyywrap
%option nounput

%{

#include "iciparser.h"
#include <cstdlib>

#define YY_DECL int ICIParser::nextToken()
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
"("	{ return TOKEN_LPAREN; }
")"	{ return TOKEN_RPAREN; }
"{" { return TOKEN_LBRACKET; }
"}" { return TOKEN_RBRACKET; }
"[" { return TOKEN_LSQUARE_BRACKET; }
"]" { return TOKEN_RSQUARE_BRACKET; }
"." { return TOKEN_DOT; }
"," { return TOKEN_COMMA; }
"and" { return TOKEN_AND; }
"or" { return TOKEN_OR; }
"!" { return TOKEN_NOT; }
"else" { return TOKEN_ELSE; }

\"  { BEGIN double_string; stringbuffer.clear(); }
<double_string>[^\\"]*   { stringbuffer.append(yytext); }
<double_string>\\[\\"]   { stringbuffer.append(yytext[1]); }
<double_string>\"         { yylval.str = storeString(stringbuffer); BEGIN 0; return TOKEN_STRING; }

\'  { BEGIN simple_string; stringbuffer.clear(); }
<simple_string>[^\\']*   { stringbuffer.append(yytext); }
<simple_string>\\[\\']   { stringbuffer.append(yytext[1]); }
<simple_string>\'         { yylval.str = storeString(stringbuffer); BEGIN 0; return TOKEN_STRING; }

\{\{\{  { BEGIN raw_string; stringbuffer.clear(); }
<raw_string>[\n]*     { if(!stringbuffer.isEmpty()) {stringbuffer.append(yytext);}}
<raw_string>\n\}\}\}  { yylval.str = storeString(stringbuffer); BEGIN 0; return TOKEN_STRING; }
<raw_string>.*   { stringbuffer.append(yytext); }

[0-9]+ { yylval.dval = strtold(yytext, 0); return TOKEN_DIGIT; }
[a-zA-Z_]+    { yylval.str = storeString(yytext) ; return TOKEN_IDENT; }

#.* {/* skip */}
[\t ] {/* skip */}

%%
