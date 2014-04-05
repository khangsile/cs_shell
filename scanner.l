%{
#include "variables.h"
%}

%%
[A-Za-z0-9^\%\>\<]+  return WORD;
[\%|\>|\<]  return SPECIAL;

\n  NEWLINE;

.  printf("unexpected character\n");

%%

int yywrap(void)
{
  return 1;
}