#include <unistd.h>
#include <stdio.h>
#include "environ.h"

extern char** env;
extern int size;

void setdir(char** args, int argc);

void set_env(char** args, int argc);
void unset_env(char** args, int argc);
void list_env();

void bye();
char* prompt(char** ags, int argc);

