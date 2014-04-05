#include <stdlib.h>

struct token {

  int type;
  int usage;
  char* text;
  struct token* next;

}

