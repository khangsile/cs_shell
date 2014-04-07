#include <stdlib.h>

struct token {
  char* text;
  struct token* next;
  int type;
  int usage;
};

void addToken(struct token** head, struct token* t);

void freeToken(struct token* t);

void freeTokenList(struct token** head);

