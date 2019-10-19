**Beginning pseudo-code, or bones of lexicon. Notes must be edited out of final version

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assem.tab.h"  *** THIS MAY BE CHANGED LATER
void showError();
}%

%option outfile="lex.c"
%option noyywrap

**** definitions ****
OP		[A-Za-z]*		**since OP codes don't have numbers
WS		[ \t\r\n]*		**Whitespace
COM		"#"[^\r\n]*		**anything except return or newline after a comment indicator
HEX		0[Xx][0-9]*		**address
REG		[Rr][0-9]+		**Register
IMM		[0-9]*			**Immediate value
 
%%

**** declarations ****
{OP}		{yylval.op = copy_str(yytext); return OPCODE;}
{HEX}		{sscanf(yytext, "%x", &yylval.hex; return HEXVAL;}
{REG}		{yylval.reg = atoi((yytext+1)); return REGISTER;}
{IMM}		{sscanf(yytext, "%d", &yylval.imm; return IMMEDIATE;}
"("		{return OPPER;}
")"		{return CLPER;}
";"		{return SEMI;}
","		{return COMMA;}
"$"		{return DOL;} 		**This is used for immediates of the form $12
{WS}		{}
{COM}		{}

%%

void showError(){
  prinf("Error/n");
}
