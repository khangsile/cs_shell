# The compiler
CC = gcc

# Target
TARGET = main

all: $(TARGET)

$(TARGET): scanner.c
	$(CC) -o $(TARGET) scanner.c lex.yy.c token.c

clean: 
	$(RM) $(TARGET)