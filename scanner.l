%{
#include "variables.h"

char* yytext2;
%}

%%

[^ %><\n\"\t]+  return WORD;
[%><]  return SPECIAL;
\"(.*)\"  { 
  yytext++; 
  int i=0;
  for(i=0; yytext[i] != '\0'; i++) {}
  yytext[i-1] = '\0';
  return STRING; 
}
\n return NEWLINE;
[ \t]+  ;

%%

int yywrap(void)
{
  return 1;
}