%{
   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   #include "parser.h"
   #include "helpers.h"
%}

%x FIRST_PASS
%option noyywrap
%option outfile="lexer.c" header-file="lexer.h"

%%

%{
if(first_enter)
   BEGIN(FIRST_PASS);
%}

<FIRST_PASS>{
[A-Za-z][0-9A-Za-z]*":"    {yylval.op = strdup(yytext); return LABEL;}
[\r\n]+                    {return EOL;}
";"                        {return SEMI;}
<<EOF>>                    {first_enter = 0; pc = 1; rewind(yyin); BEGIN(0); return EOP;}
.                          {}
}
[A-Za-z]*               {yylval.op = strdup(yytext); return OPCODE;}
0[Xx][0-9A-Fa-f]+       {sscanf(yytext, "%x", &yylval.num); return HEXVAL;}
[Rr][0-9]+              {yylval.num = atoi((yytext+1)); return REGISTER;}
[-]?[0-9]*              {sscanf(yytext, "%d", &yylval.num); return IMMEDIATE;}
"("                     {return OPPER;}
")"                     {return CLPER;}
";"                     {return SEMI;}
","                     {return COMMA;}
"$"                     {return DOL;}
[\r\n]                  {return EOL;}
[ \t]*                  {}
"#".*             {}
[A-Za-z][0-9A-Za-z]*    {yylval.op = strdup(yytext); return GLAB;}
[A-Za-z][0-9A-Za-z]*":" {}
.                       {}
<<EOF>>                 {yyterminate();}

%%

void yyerror(const char* msg) {
    fprintf(stderr, "lexer error: %s\n", msg);
}
