#include <stdlib.h>
#include "token.h"

typedef struct {
  char* cmd;
  char** args; 
  char* input;
  char* output;
  int arg_count;
}command;

void parse(struct token** t, command* cmd);
void printCommand(command* cmd);
