CC = gcc
CFLAGS = -g -Wall -Werror -std=c99 -m64
PROG = encoder

all: csim $(PROG) handin

csim: csim.c cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o csim csim.c cachelab.c -lm

$(PROG): data.h $(PROG).c data.o
	$(CC) $(CFLAGS) $(PROG).c data.o -o $(PROG)

handin:
	tar -cvf $(shell whoami)-handin.tar encoder.c csim.c
