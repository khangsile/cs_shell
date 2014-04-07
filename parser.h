#include <stdlib.h>
#include "token.h"

struct command {
  char* cmd;
  char** args; 
  char* input;
  char* output;
  int arg_count;
};

struct command* parse(struct token** t);
