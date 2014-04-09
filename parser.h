#include <stdlib.h>
#include "token.h"
#include <stdio.h>
#include "variables.h"
#include <string.h>

typedef struct {
  char* cmd;
  char** args; 
  char* input;
  char* output;
  int arg_count;
  int builtin;
}command;

void parse(struct token** t, command* cmd);
void printCommand(command* cmd);
