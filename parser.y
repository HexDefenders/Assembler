%{
  #include <stdio.h>
  void showError();
%}

%output "parser.c"

%union {
  char *op;
  int num;
}

%token <op> OPCODE
%token HEXVAL
%token REGISTER
%token IMMEDIATE
%token OPPER CLPER SEMI COMA DOL
%token EOL
%token <op> LABEL
%type <num> arg;
%type <op> instr;

%%

line: 
  | line instr EOL {toLE($1);}
  | line LABEL EOL
  | line LABEL instr EOL
;

instr: OPCODE SEMI {$$ = toHex($1, NULL, NULL);}
  | OPCODE OPCODE SEMI
  | OPCODE arg SEMI {$$ = toHex($1, NULL, $2);}
  | OPCODE arg COMA arg SEMI {$$ = toHex($1, $2, $4);}
;

arg: HEXVAL
  | REGISTER
  | DOL IMMEDIATE {$$ = $2}
;
