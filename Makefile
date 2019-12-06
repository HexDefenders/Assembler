SRCS = main.c helpers.c parser.c lexer.c
CC = gcc

all: $(SRCS) helpers.h
	$(CC) $(SRCS) -o parser

lexer.c: lexer.l helpers.h
	flex lexer.l

parser.c: parser.y lexer.l helpers.h
	bison parser.y
