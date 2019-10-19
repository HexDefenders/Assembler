%{
  #include <stdio.h>
  void showError();
%}

%output "parser.c"

%union {
  
}

%token OPCODE
%token HEXVAL
%token REGISTER
%token IMMEDIATE
%token OPPER CLPER SEMI COMA DOL
%token EOL

%%

line: 
  | line instr EOL { toLE($1);}
;

instr: OPCODE SEMI {$$ = toHex($1, NULL, NULL);}
  | OPCODE arg SEMI {$$ = toHex($1, $2, NULL);}
  | OPCODE arg COMA arg SEMI {$$ = toHex($1, $2, $4);}
;

arg: HEXVAL
  | REGISTER
  | DOL IMMEDIATE {$$ = $2}
;
