#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "variables.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"
#include "environ.h"

#define MAX 100

extern char** env;

int builtinCommand(command* cmd);
void executeBuiltin(int cmd, char** args, int argc);

char* myprompt = "envsh";

int main() {

  char* args[MAX];

  while(1) {
    struct token** tokenList = (struct token**) malloc(sizeof(struct token*)); 
    *tokenList = NULL;
    getTokens(myprompt, tokenList);
    
    if ((*tokenList)->type == NEWLINE) continue;
    
    command cmd;
    cmd.args = args;
    parse(tokenList, &cmd);

    // if num of args does not exceed capacity
    if(cmd.arg_count < MAX) {
      cmd.args[cmd.arg_count] = NULL;
    } else {
      printf("Max arguments exceeded.");
    }

    int builtin;
    // if built in command
    if(builtin = builtinCommand(&cmd)) {
      //      printf("Executing builtin... \n");
      executeBuiltin(builtin, cmd.args, cmd.arg_count);
    } else { 
      //      printf("Executing non-builtin... \n");
      int child_status,pid;
      pid = fork();
      if(pid>0) {
	// parent process
	waitpid(pid,&child_status,0);
      } else {
	// child process
	int ret = execve(cmd.cmd,cmd.args,env);
	if(ret < 0)
	  perror("Error");
	exit(0);
      }
    }

    freeTokenList(tokenList);
  }
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

void executeBuiltin(int cmd, char** args, int argc) {
  if(cmd == SETDIR)
    setdir(args,argc);
  if(cmd == LISTENV)
    list_env();
  if(cmd == SETENV)
    set_env(args, argc);
  if(cmd == UNSETENV)
    unset_env(args, argc);
  else if(cmd == BYE)
    bye();
  else if(cmd == PROMPT) {
    char* prompt1 = prompt(args,argc);
    if (prompt1 != NULL) {
      myprompt = malloc(strlen(prompt1)+1);
      strcpy(myprompt, prompt1);
    }
  }

}
