#include "helpers.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
  FILE *outFile;
  yyin = fopen("input.txt", "r");
  outFile = fopen("output.txt" , "a");
  dup2(fileno(outFile),1);
  yyparse();
  
  fclose(yyin);
  fclose(outFile);
  return 0;

}
