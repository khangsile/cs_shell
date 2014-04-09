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
void printToken(struct token*);

struct token** getTokens(char* prompt, struct token** head) {
  int ntoken, vtoken;

  printf("%s > ", prompt);

  // Get head first. 

  ntoken = yylex();
  struct token* hd = (struct token*) malloc(sizeof(struct token));
  hd->type = ntoken;
  hd->text = cpystr(yytext);
  hd->next = NULL;

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

    printToken(tk);
    //    ntoken = yylex();
  }

  return head;
}

char* cpystr(char* str) {
  int size = strlen(str);
  char *cpy = (char*) malloc((size+1)*sizeof(char));
  strcpy(cpy, str);
  return cpy;
}

void printToken(struct token *tk) {
  char* type;
  char* text = tk->text;
  switch(tk->type) {
  case 1:
    type = "word";
    break;
  case 2:
    type = "metachar";
    break;
  case 3:
    type = "string";
    break;
  case 4:
    type = "end-of-line";
    text = "EOL";
  }
  printf("Token Type = %s Token = %s\n", type, text);
}
