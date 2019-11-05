%{
  #include <stdio.h>
  #include "helpers.h"
  #define YYDEBUG 1
  int yylex(void);
  void yyerror(const char *s);
  int pc = 1;
  int trigger = 0;
  %}

%error-verbose
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
%token EOP
%token <op> GLAB
%token <op> LABEL
%type <num> arg;
%type <op> instr;
%type <num> lab;
%start first

%%
first: search EOP line
;
line: {pc = 1;}
| line EOL {}
| line instr EOL {toLE($2); pc++;}
;
search: {pc = 1;}
| search LABEL EOL {holdLabel($2, pc);}
| search SEMI EOL {pc++;}
| search EOL
| search LABEL SEMI EOL {pc++;}
;
instr: OPCODE SEMI {$$ = toHex($1, 0, 0);}
| OPCODE arg SEMI {$$ = toHex($1, 0, $2);}
| OPCODE arg COMMA arg SEMI {$$ = toHex($1, $2, $4);}
| OPCODE lab SEMI {$$ = toHex($1, $2, 0);}
| OPCODE lab COMMA arg SEMI {$$ = toHex($1, $2, $4);}
| OPCODE arg COMMA lab SEMI {trigger = 1; $$ = toHex($1, $2, $4);}
| OPCODE lab COMMA lab SEMI {$$ = toHex($1, $2, $4);}
;
lab: GLAB {$$ = needLabel($1);}
| OPCODE {$$ = needLabel($1);}
;
arg: HEXVAL {$$ = $1;}
| REGISTER {$$ = $1;}
| DOL IMMEDIATE {$$ = $2;}
;
