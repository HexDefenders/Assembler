%{
  #include <stdio.h>
  int yylex(void);
  #include "helpers.h"
  void yyerror(const char *s);
  int pc = 1;
  %}

%output "parser.c"
%defines "parser.h"

%union {
  char *op;
  int num;
}

%token <op> OPCODE
%token <num> HEXVAL
%token <num> REGISTER
%token <num> IMMEDIATE
%token OPPER CLPER SEMI COMMA DOL
%token EOL
%token <op> LABEL
%type <num> arg;
%type <op> instr;

%%

line:
| line instr EOL {toLE($2); pc++;}
;

instr: OPCODE SEMI {$$ = toHex($1, 0, 0);}
| OPCODE arg SEMI {$$ = toHex($1, 0, $2);}
| OPCODE arg COMMA arg SEMI {$$ = toHex($1, $2, $4);}
;

arg: HEXVAL {$$ = $1;}
| REGISTER {$$ = $1;}
| DOL IMMEDIATE {$$ = $2;}
;
