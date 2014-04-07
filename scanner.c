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
struct token** getTokens();

struct token** getTokens() {
  int ntoken, vtoken;

  struct token **head = NULL;
  // Get head first.                                                                                       
  ntoken = yylex();
  struct token *hd = (struct token*) malloc(sizeof(struct token));
  hd->type = ntoken;
  hd->text = cpystr(yytext);
  printToken(hd);

  // Set the head ptr                                                                             
  head = &hd;

  while(ntoken = yylex()) {
    struct token *tk = (struct token*) malloc(sizeof(struct token));
    tk->type = ntoken;
    tk->text = cpystr(yytext);

    addToken(head, tk);

    printToken(tk);
    if (ntoken == NEWLINE) break;
    ntoken = yylex();
  }

  return head;
}

char* cpystr(char* str) {
  int size = strlen(str);
  char *cpy = (char*) malloc(size);
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
