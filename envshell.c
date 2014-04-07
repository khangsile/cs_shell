#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "variables.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"


int builtinCommand(struct command* cmd);
void executeBuiltin(int cmd, char** args, int argc);

int main() {
  char* environ[100];
  //environ[0] = NULL:

  while(1) {
    struct token** tokenList = getTokens();
    struct command* cmd = parse(tokenList);
    
    int builtin;
    // if built in command
    if(builtin = builtinCommand(cmd)) {
      printf("Executing builtin... ");
      executeBuiltin(builtin, cmd->args, cmd->arg_count);
    } else { 
      printf("Executing non-builtin... ");
      int child_status,pid;
      pid = fork();
      if(pid>0) {
	// parent process
	printf("Parent");
	waitpid(pid,&child_status,0);
      } else {
	// child process
	printf("Child");
	execve(cmd->cmd,cmd->args,environ);
	exit(0);
      }
    }
    freeTokenList(tokenList);
    freeCommand(cmd);
  }
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

void executeBuiltin(int cmd, char** args, int argc) {
  if(cmd == SETDIR)
    setdir(args,argc);
}
