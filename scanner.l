%{
#include "variables.h"

char* yytext2;
%}

%%

\n return NEWLINE;
[^" \t\n\r\%\>\<]+  return WORD;
[%><]  return SPECIAL;
\"(.*)\"  { 
  yytext++; 
  int i=0;
  for(i=0; yytext[i] != '\0'; i++) {}
  yytext[i-1] = '\0';
  return STRING; 
}
[ \t] ;

%%

int yywrap(void)
{
  return 1;
}
