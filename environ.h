#include <stdlib.h>
#include <string.h>
#define MAX_VARS 100

void swapVars(int i, int j);

void deleteVar(int i);

void addVar(char* var, char* value);

int searchEnviron(char* var);

void displayEnv();
