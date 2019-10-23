SRCS = main.c helpers.c parser.c lexer.c
CC = gcc

lexer.c: lexer.l helpers.h
	flex lexer.l

parser.c: parser.y lexer.l helpers.h
	bison parser.y

all: $(SRCS) helpers.h
	$(CC) $(SRCS) -o parser

clean:
	rm -f *.o
