SRC = $(wildcard *.c)
OBJ = $(src:.c=.o)
CC = gcc
LDFLAGS = -Wall -Werror

clox: $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS)

.phony: clean
clean: 
	rm -f $(OBJ) clox
