#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "variables.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"
#include "environ.h"
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX 100

extern char** env;

int builtinCommand(command* cmd);
void executeBuiltin(int cmd, char** args, int argc);

bool validateBuiltin(int cmd, struct token** tokenList);
bool validateSetenv(struct token** tokenList);
bool validateUnsetenv(struct token** tokenList);
bool validateListenv(struct token** tokenList);

char* myprompt = "envsh";

int main() {

  char* args[MAX];

  myprompt = malloc(sizeof(char) * strlen(myprompt));
  strcpy(myprompt, "envsh");
  printf("%s > ", myprompt);

  while(1) {
    struct token** tokenList = (struct token**) malloc(sizeof(struct token*)); 
    *tokenList = NULL;

    getTokens(tokenList);
    printTokens(tokenList);
    if ((*tokenList)->type == NEWLINE) {
      printf("%s > ", myprompt);
      continue;
    }
    if ((*tokenList)->type == SPECIAL && !strcmp((*tokenList)->text,"%")) continue;
    
    command cmd;
    cmd.args = args;
    parse(tokenList, &cmd);

    // if num of args does not exceed capacity
    if(cmd.arg_count < MAX) {
      cmd.args[cmd.arg_count] = NULL;
    } else {
      printf("Max arguments exceeded.");
    }

    int in = 0, saved_stdin;
    if(cmd.input != NULL) {
      in = open(cmd.input, O_RDONLY);
      saved_stdin = dup(0);
      dup2(in, 0);
    }

    int out = 0, saved_stdout;
    if(cmd.output != NULL) {
      out = open(cmd.output, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IRGRP|S_IWGRP|S_IWUSR);
      saved_stdout = dup(1);
      dup2(out, 1);
    }

    int builtin;
    // if built in command
    if(cmd.builtin) {
      if(validateBuiltin(cmd.builtin,tokenList))
	executeBuiltin(cmd.builtin, cmd.args, cmd.arg_count);      
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

    if(cmd.input != NULL) {
      close(in);
      dup2(saved_stdin, 0);
    }
    if(cmd.output != NULL) {
      close(out);
      dup2(saved_stdout, 1);
    }

    printf("%s > ", myprompt);

    freeTokenList(tokenList);
  }
  free(myprompt);
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
      free(myprompt);
      myprompt = malloc(sizeof(char)*(strlen(prompt1)+1));
      strcpy(myprompt, prompt1);
    }
  }

}

bool validateBuiltin(int cmd, struct token** tokenList) {
  if(cmd == SETENV)
    return validateSetenv(tokenList);
  if(cmd == UNSETENV)
    return validateUnsetenv(tokenList);
  if(cmd == LISTENV)
    return validateListenv(tokenList);
  return true;
}

bool validateListenv(struct token** tokenList) {
  struct token* curr = *tokenList;
  curr = curr->next;
  if(curr != NULL && curr->type != NEWLINE) {
    printf("Too many arguments.\n");
    return false;
  }
}

bool validateUnsetenv(struct token** tokenList) {
  struct token* curr = *tokenList;
  curr = curr->next;
  if(curr != NULL && curr->type != WORD) {
    printf("First argument must be a word.\n");
    return false;
  }
  curr = curr->next;
  if(curr != NULL && curr->type != NEWLINE) {
    printf("Too many arguments.\n");
    return false;
  }
  return true;
}

bool validateSetenv(struct token** tokenList) {
  struct token* curr = *tokenList;
  curr = curr->next;
  if(curr != NULL && curr->type != WORD) {
    printf("First argument must be a word.\n");
    return false;
  }
  curr = curr->next;
  if(curr != NULL && curr->type != STRING) {
    printf("Second argument must be a string.\n");
    return false;
  }
  curr = curr->next;
  if(curr != NULL && curr->type != NEWLINE) {
    printf("Too many arguments.\n");
    return false;
  }
  return true;
}
