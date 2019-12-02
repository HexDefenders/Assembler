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
  outFile = fopen("test.dat" , "a");
  
  //yydebug = 1;
  dup2(fileno(outFile),1);
  yyparse();
   
  int i = pc;
  const int MEMSIZE = 256;
  char *zeros = "0000";
  //printf("%d\n", i);

  for(i; i <= MEMSIZE; i++)
    printf("%s\n", zeros);
  
  fclose(yyin);
  fclose(outFile);
  return 0;

}
