#include "builtin.h"

void set_env(char** args, int argc) {
  if(argc > 2) {
    addVar(args[1], args[2]);
  } else {
    printf("error: not enough arguments\n");
  }  
}

void unset_env(char** args, int argc) {
  if(argc > 1) {
    int i = searchEnviron(args[1]);
    if(i >= 0)
      deleteVar(i);
    else
      printf("error: environment variable does not exist\n");
  } else
    printf("error: not enough arguments\n");
}

void list_env() {
  displayEnv();
}

void setdir(char** args, int argc) {
  if(argc >= 2) {
    int ret = chdir(args[1]);
    if(ret == 0) {
      // success
    } else {
      printf("Error in changing directory.\n");
    }
  } else {
    printf("setdir requires a target directory\n");
  }
}
