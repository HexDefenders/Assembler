%{
   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   #include "parser.h"
   #include "helpers.h"
%}

%option noyywrap
%option outfile="lexer.c" header-file="lexer.h"

OP         [A-Za-z]*
WS         [ \t\r\n]*
COM        "#"[^\r\n]*
HEX        0[Xx][0-9A-Fa-f]+
REG        [Rr][0-9]+
IMM        [0-9]*
EOL        [\r\n]

%%

{OP}        {yylval.op = strdup(yytext); return OPCODE;}
{HEX}       {sscanf(yytext, "%x", &yylval.num); return HEXVAL;}
{REG}       {yylval.num = atoi((yytext+1)); return REGISTER;}
{IMM}       {sscanf(yytext, "%d", &yylval.num); return IMMEDIATE;}
"("         {return OPPER;}
")"         {return CLPER;}
";"         {return SEMI;}
","         {return COMMA;}
"$"         {return DOL;}
{EOL}       {return EOL;}
{WS}        {}
{COM}       {}

%%

void yyerror(const char* msg) {
    fprintf(stderr, "lexer error: %s\n", msg);
}
