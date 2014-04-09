#include "builtin.h"
#include <stdlib.h>

void setdir(char** args, int argc) {
  if(argc >= 2) {
    int ret = chdir(args[1]);
    if(ret == 0) {
      // success
      printf("Success");
    } else {
      printf("Error in changing directory.");
    }
  } else {
    printf("setdir requires a target directory");
  }
}

void bye() {
  exit(0);
}
