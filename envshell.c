#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "variables.h"
#include <string.h>
#include <unistd.h>


int builtinCommand(struct command* cmd);

int main() {
  //  char* environ[100];
  //  environ[0] = NULL:
  struct token** tokenList = getTokens();
  struct command* cmd = parse(tokenList);
  printCommand(cmd);
    /*
  while(1) {
    struct token** tokenList = getTokens();
    struct command* cmd = parse(tokenList);
    printCommand(cmd);
    
    int builtin;
    // if built in command
    if(builtin = builtinCommand(cmd)) {
      
    } else { 
      int pid = fork();
      // child process
      if(pid) {
	execve(
      } else {
	// parent process
	wait();
      }
    }


    freeTokenList(tokenList);
    freeCommand(cmd);
    } */
}

int builtinCommand(struct command* cmd) {
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
