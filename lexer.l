%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void showError();
%}

%option outfile="lex.c"
%option noyywrap

OP		[A-Za-z]*
WS		[ \t\r\n]*
COM		"#"[^\r\n]*
HEX		0[Xx][0-9A-Fa-f]+
REG		[Rr][0-9]+
IMM		[-]?[0-9]*
END  [\n\r]
LAB  [A-Za-z][0-9A-Za-z]*":"
 
%%

{OP}		{yylval.op = copy_str(yytext); return OPCODE;}
{HEX}		{sscanf(yytext, "%x", &yylval.num; return HEXVAL;}
{REG}		{yylval.num = atoi((yytext+1)); return REGISTER;}
{IMM}		{sscanf(yytext, "%d", &yylval.num; return IMMEDIATE;}
{LAB}  {
"("		{return OPPER;}
")"		{return CLPER;}
";"		{return SEMI;}
","		{return COMMA;}
"$"		{return DOL;}
{END}		{return EOL;}
{WS}		{}
{COM}		{}

%%

void showError(){
  prinf("Error/n");
}
