%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assem.tab.h"
void showError();
%}

%option outfile="lex.c"
%option noyywrap

OP		[A-Za-z]*
WS		[ \t\r\n]*
COM		"#"[^\r\n]*
HEX		0[Xx][0-9A-Fa-f]+
REG		[Rr][0-9]+
IMM		[0-9]*
 
%%

{OP}		{yylval.op = copy_str(yytext); return OPCODE;}
{HEX}		{sscanf(yytext, "%x", &yylval.hex; return HEXVAL;}
{REG}		{yylval.reg = atoi((yytext+1)); return REGISTER;}
{IMM}		{sscanf(yytext, "%d", &yylval.imm; return IMMEDIATE;}
"("		{return OPPER;}
")"		{return CLPER;}
";"		{return SEMI;}
","		{return COMMA;}
"$"		{return DOL;}
{WS}		{}
{COM}		{}

%%

void showError(){
  prinf("Error/n");
}
