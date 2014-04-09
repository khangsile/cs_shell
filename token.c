#include "token.h";
#include <stdio.h>;

void addToken(struct token** head, struct token* t) {
  struct token* curr = *head;
  t->next = NULL;
  if(head == NULL) {
    head = &t;
  } else {
    while(curr->next != NULL)
      curr = curr->next;
    curr->next = t;
  }
}

void freeTokenList(struct token** head) {
  struct token* curr = *head;
  freeTokens(curr);
  free(head);
}

void freeTokens(struct token* t) {
  if(t == NULL)
    return;
  freeTokens(t->next);
  freeToken(t);
}

void freeToken(struct token* t) {
  if (t == NULL) return;
  if (t->text != NULL)
    free(t->text);
  free(t);
}

void printTokens(struct token** head) {
  struct token* curr = *head;
  if (curr != NULL)
    printtk(curr);
}

void printtk(struct token* tk) {
  if (tk == NULL) return;
  printf("%d: %s\n", tk->type, tk->text);
  printtk(tk->next);
}
