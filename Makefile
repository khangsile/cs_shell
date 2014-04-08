# The compiler
CC = gcc

# Target
TARGET = main

all: $(TARGET)

$(TARGET): envshell.c
	$(CC) -g -o $(TARGET) scanner.c lex.yy.c token.c parser.c builtin.c envshell.c

clean: 
	$(RM) $(TARGET)