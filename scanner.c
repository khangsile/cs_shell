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

  // If type isn't end of file use the actual text
  // else end of file is equivalent to bye token
  if (hd->type != 0)
    hd->text = cpystr(yytext);
  else {
    hd->type = WORD;
    hd->text = cpystr("bye");
  }

  hd->next = NULL;

  // Set the head
  *head = hd;

  // Newlines/end of file should represent the end of a command
  if (hd->type == NEWLINE || ntoken == 0) 
    return head;

  // add tokens until a newline or end of file
  while(ntoken = yylex()) {
    struct token* tk = (struct token*) malloc(sizeof(struct token));
    tk->type = ntoken;
    tk->text = cpystr(yytext);
    tk->next = NULL;
    addToken(head, tk);

    // newlines/end of file should represent the end of a command
    if (ntoken == NEWLINE || ntoken == 0) break;
  }

  return head;
}

char* cpystr(char* str) {
  int size = strlen(str);
  char *cpy = (char*) malloc((size+1)*sizeof(char));
  strcpy(cpy, str);
  return cpy;
}
