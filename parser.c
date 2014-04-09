#include "parser.h"

void printCommand(command* cmd) {
  printf("cmd: %s, args: ", cmd->cmd);
  int i;
  for(i=0; i<cmd->arg_count; i++)
    printf("%s ", cmd->args[i]);  
  printf("\ninput: %s, ", cmd->input);
  printf("output: %s\n", cmd->output);
}

int builtinCommand(command* cmd) {
  if(!strcmp(cmd->cmd,"prompt"))
    return PROMPT;
  if(!strcmp(cmd->cmd,"setenv"))
    return SETENV;
  if(!strcmp(cmd->cmd,"unsetenv"))
    return UNSETENV;
  if(!strcmp(cmd->cmd,"listenv"))
    return LISTENV;
  if(!strcmp(cmd->cmd,"setdir"))
    return SETDIR;
  if(!strcmp(cmd->cmd,"bye"))
    return BYE;
  return 0;
}

void parse(struct token** tokenList, command* cmd) {
  struct token* t = *tokenList;

  cmd->cmd = NULL; cmd->output = NULL; cmd->input = NULL;

  // get command from first token
  if(t != NULL) {
    if(t->type == WORD) {
      cmd->cmd = t->text;
    } else {
      // error
    }
  }

  struct token* curr = t;
  cmd->arg_count = 0;
  // count args
  while(curr != NULL && curr->type != NEWLINE && curr->type != SPECIAL) {
    curr = curr->next;    
    cmd->arg_count++;
  }
  // get args  
  int i;
  for(i=0; i<cmd->arg_count; i++) {
    cmd->args[i] = t->text;
    t = t->next;
  }

  // check for redirect in
  if(t != NULL && t->type == SPECIAL && !strcmp(t->text,"<")) {
    t = t->next;
    // next token must be file
    if(t != NULL && t->type == WORD) {
      cmd->input = t->text;
      t = t->next;
    } else {
      // syntax error
    }      
  }
  // check for redirect out
  if(t != NULL && t->type == SPECIAL && !strcmp(t->text,">")) {
    t = t->next;      
    // next token must be file
    if(t != NULL && t->type == WORD) {
      cmd->output = t->text; 
      t = t->next;
    } else {
      // syntax error
    }      
  }

  cmd->builtin = builtinCommand(cmd);
}
