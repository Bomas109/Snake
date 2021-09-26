CC=gcc
CFLAGS=-Wall -pedantic

LIBS=-lncurses

NAME=snake

all: $(NAME)
	@echo !!!SUCCESS!!! $(NAME) has been compiled.

$(NAME): snake.c
	$(CC) $(CFLAGS) snake.c -o $@ $(LIBS)
