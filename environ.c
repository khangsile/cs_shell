#include "environ.h"

char* env[MAX_VARS];
int size;

void swapVars(int i, int j) {
  char* temp = env[i];
  env[i] = env[j];
  env[j] = temp;
}

void deleteVar(int i) {
  if(i<MAX_VARS) {
    size--;
    free(env[i]);
    for(; i<size; i++) {
      swapVars(i, i+1);
    }
    env[size] = NULL;
  }
}

void addVar(char* var, char* value) {
  int i = searchEnviron(var);
  // if variable exists
  if(i >= 0) {
    deleteVar(i);    
  }

  if(size+1<MAX_VARS) {
    char* entry = malloc(strlen(var)+strlen(value)+2*sizeof(char));
    strcpy(entry,var);
    env[size++] = strcat(strcat(entry,"="),value);
    env[size] = NULL;
    printf("%s\n", env[size-1]);
  }

}

int searchEnviron(char* var) {
  int i;
  for(i=0; i<size; i++) {
    char curr[strlen(env[i])+1];
    char* temp = strcpy(curr,env[i]);
    char* target = strtok(temp,"=");
    if(target == NULL)
      break;
    if(strcmp(target,var)==0)
      return i;
  }
  return -1;
}

void displayEnv() {
  int i=0;
  for(; i<size; i++) {
    printf("%s\n",env[i]);
  }
}
