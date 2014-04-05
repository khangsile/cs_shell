#include <stdio.h>
#include "variables.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void) {

  int ntoken, vtoken;

  ntoken = yylex();
  while(ntoken) {
    if (ntoken != NEWLINE)
      printf("%d: %s\n", ntoken, yytext);
    ntoken = yylex();
  }

  return 0;
}
