#include "token.h";
#include <stdio.h>;

void addToken(struct token** head, struct token* t) {
  struct token* curr = *head;
  if(curr == NULL) {
    curr = t;
  } else {
    while(curr->next != NULL)
      curr = curr->next;
    curr->next = t;
  }
}

void freeTokenList(struct token** head) {
  struct token *curr = *head, *next = *head;
  while(curr != NULL) {
    next = curr->next;
    freeToken(curr);
    curr = next;
  }
}

void freeToken(struct token* t) {
  free(t->text);
  free(t);
}
