#include <stdio.h>
#include <string.h>
#include "variables.h"
#include "token.h"

extern int yylex();
extern int yylineno;
extern int yyleng;
extern char* yytext;

char* cpystr(char*);

struct token *head = NULL;

int main(void) {

  int ntoken, vtoken;

  // Get head first.
  ntoken = yylex();
  while(ntoken) {
    struct token *tk = (struct token*) malloc(sizeof(struct token));
    tk->type = ntoken;
    tk->text = cpystr(yytext);
    if (tk->type != 4)
      printf("%s\n", tk->text);
    ntoken = yylex();
  }

  return 0;
}

char* cpystr(char* str) {
  int size = strlen(str);
  char *cpy = (char*) malloc(size);
  strcpy(cpy, str);
  return cpy;
}
