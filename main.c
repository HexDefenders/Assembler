#include "helpers.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

extern int yydebug;
int first_enter = 1;

int main(int argc, char* argv[])
{
  FILE *outFile;
  yyin = fopen("input.txt", "r");
  outFile = fopen("output.txt" , "a");
  
  //yydebug = 1;
  dup2(fileno(outFile),1);
  yyparse();

  fclose(yyin);
  fclose(outFile);
  return 0;

}
