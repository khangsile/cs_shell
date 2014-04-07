#include <stdio.h>
#include "parser.h"
#include "variables.h"

void printCommand(struct command* cmd) {
  printf("cmd: %s, args: ", cmd->cmd);
  int i;
  for(i=0; i<cmd->arg_count; i++)
    printf("%s ", cmd->args[i]);  
}

void freeCommand(struct command* cmd) {
  free(cmd->args);
  free(cmd);
}

struct command* parse(struct token** tokenList) {
  struct token* t = *tokenList;
  struct command* cmd = malloc(sizeof(struct command));
  // get command from first token
  if(t != NULL) {
    if(t->type == WORD) {
      cmd->cmd = t->text;
      t = t->next;
    } else {
      // error
    }
  }
  // get args
  struct token* curr = t;
  cmd->arg_count = 0;
  // count args
  while(curr != NULL && curr->type != NEWLINE && strcmp(curr->text,"<")) {
    curr = curr->next;    
    cmd->arg_count++;
  }
  printf("%d\n",cmd->arg_count);
  cmd->args = malloc(cmd->arg_count * sizeof(char*));
  int i;
  for(i=0; i<cmd->arg_count; i++) {
    cmd->args[i] = t->text;
    t = t->next;
  }
  // check for redirect in
  if(t != NULL && t->type != NEWLINE && strcmp(curr->text,"<")) {
    // next token must be file
    if(t->next != NULL && t->next->type == WORD) {
      t = t->next;      
      cmd->input = t->text; 
    } else {
      // syntax error
    }      
  }
  // check for redirect out
  if(t != NULL && t->type != NEWLINE && !strcmp(curr->text,">")) {
    // next token must be file
    if(t->next != NULL && t->next->type == WORD) {
      t = t->next;      
      cmd->input = t->text; 
    } else {
      // syntax error
    }      
  } 
  return cmd;
}
