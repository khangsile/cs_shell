#include <stdio.h>
#include <string.h>
#include "variables.h"
#include "token.h"
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern int yyleng;
extern char* yytext;

char* cpystr(char*);

struct token** getTokens(struct token** head) {
  int ntoken, vtoken;

  // Get head first. 
  ntoken = yylex();
  struct token* hd = (struct token*) malloc(sizeof(struct token));
  hd->type = ntoken;
  hd->text = cpystr(yytext);
  hd->next = NULL;

  // Set the head
  *head = hd;

  if (hd->type == NEWLINE)
    return head;

  while(ntoken = yylex()) {
    struct token* tk = (struct token*) malloc(sizeof(struct token));
    tk->type = ntoken;
    tk->text = cpystr(yytext);
    tk->next = NULL;
    addToken(head, tk);

    if (ntoken == NEWLINE) break;
  }

  return head;
}

char* cpystr(char* str) {
  int size = strlen(str);
  char *cpy = (char*) malloc((size+1)*sizeof(char));
  strcpy(cpy, str);
  return cpy;
}
