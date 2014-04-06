#include "parser.h"

void printCommand(struct command* cmd) {
  printf("cmd: %s, args: ", cmd.cmd);
  for(int i=0; i<cmd.arg_count; i++)
    printf("%s ", cmd.args[i]);
  
}

struct command* parse(struct token* t) {
  struct command* cmd = malloc(struct command);
  // get command
  if(t != NULL) {
    if(t.type == WORD) {
      cmd.cmd = t.text;
    } else {
      // error
    }
  }
  // get args
  struct token* curr = t;
  cmd.arg_count = 0;
  // count args
  while(curr.type != EOF && curr.type != REDIRECT_IN) {
    curr = curr.next;
    cmd.arg_count++;
  }
  cmd.args = malloc(i * sizeof(char*));
  for(int i=0; i<cmd.arg_count; i++) {
    args[i] = t.text;
    t = t.next;
  }
  // check for redirect in
  if(t.type != EOF && t.type == REDIRECT_IN) {
    // next token must be file
    if(t.next != NULL && t.next.type == WORD) {
      t = t.next;      
      cmd.input = t.text; 
    } else {
      // syntax error
    }      
  }
  // check for redirect out
  if(t.type != EOF && t.type == REDIRECT_OUT) {
    // next token must be file
    if(t.next != NULL && t.next.type == WORD) {
      t = t.next;      
      cmd.input = t.text; 
    } else {
      // syntax error
    }      
  } 
}
