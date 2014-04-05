#include <stdlib.h>

struct token {

  int type;
  int usage;
  char* text;
  struct token* next;

};

void addToken(struct token** head, struct token* t);

void freeToken(struct token* t);

void freeTokenList(struct token** head);

