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
%type <num> arg;
%type <num> instr;

%%

line: 
  | line instr EOL { toLE($1);}
;

instr: OPCODE SEMI {$$ = toHex($1, NULL, NULL);}
  | OPCODE arg SEMI {$$ = toHex($1, NULL, $2);}
  | OPCODE arg COMA arg SEMI {$$ = toHex($1, $2, $4);}
;

arg: HEXVAL
  | REGISTER
  | DOL IMMEDIATE {$$ = $2}
;

int toHex(char *op, int src, int dest){
  int opcode;
  int rDest;
  int immHi;
  int immLo;
  
  if(strcmp(op, "ADDI") == 0) {
  
  }
  else if(strcmp(op, "ADD") == 0) {
  
  }
  else if(strcmp(op, "SUBI") == 0) {
  
  }
  else if(strcmp(op, "SUB") == 0) {
  
  }
  else if(strcmp(op, "CMPI") == 0) {
  
  }
  else if(strcmp(op, "CMP") == 0) {
  
  }
  else if(strcmp(op, "ANDI") == 0) {
  
  }
  else if(strcmp(op, "AND") == 0) {
  
  }
  else if(strcmp(op, "ORI") == 0) {
  
  }
  else if(strcmp(op, "OR") == 0) {
  
  }
  else if(strcmp(op, "XORI") == 0) {
  
  }
  else if(strcmp(op, "XOR") == 0) {
  
  }
  else if(strcmp(op, "MOVI") == 0) {
  
  }
  else if(strcmp(op, "MOV") == 0) {
  
  }
  else if(strcmp(op, "LSHI") == 0) {
  
  }
  else if(strcmp(op, "LSH") == 0) {
  
  }
  else if(strcmp(op, "LUI") == 0) {
  
  }
  else if(strcmp(op, "LOAD") == 0) {
  
  }
  else if(strcmp(op, "STOR") == 0) {
  
  }
  else if(strcmp(op, "Bcond") == 0) {
  
  }
  else if(strcmp(op, "Jcond") == 0) {
  
  }
  else if(strcmp(op, "JAL") == 0) {
  
  }
}
