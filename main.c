#include "helpers.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char* argv[])
{

  yyparse();

  return 0;

}
