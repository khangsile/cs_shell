#include <stdio.h>
#include <string.h>
#include "variables.h"
#include "token.h"

extern int yylex();
extern int yylineno;
extern int yyleng;
extern char* yytext;

char* cpystr(char*);

struct token **head = NULL;

int main(void) {

  int ntoken, vtoken;

  // Get head first.
  ntoken = yylex();
  struct token *hd = (struct token*) malloc(sizeof(struct token));
  hd->type = ntoken;
  hd->text = cpystr(yytext);
  printf("%d: %s\n", hd->type, hd->text);

  // Set the head ptr
  head = &hd;

  ntoken = yylex();
  while(ntoken) {
    struct token *tk = (struct token*) malloc(sizeof(struct token));
    tk->type = ntoken;
    tk->text = cpystr(yytext);
    if (tk->type != 4)
      printf("%d: %s\n", tk->type, tk->text);
    ntoken = yylex();
  }

  freeTokenList(head);

  return 0;
}

char* cpystr(char* str) {
  int size = strlen(str);
  char *cpy = (char*) malloc(size);
  strcpy(cpy, str);
  return cpy;
}
