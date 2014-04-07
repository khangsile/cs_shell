#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include <string.h>

int main() {

  struct token** tokenList = getTokens();
  struct command* cmd = parse(tokenList);
  printCommand(cmd);
  freeTokenList(tokenList);
  freeCommand(cmd);
}
