CC=gcc
CFLAGS=-I.
ODIR=..
LIBS=-lncurses
EXEC=brickbreaker

brick-breaker : brick-breaker.o brick.o
	$(CC) $(CFLAGS) -o $(ODIR)/$(EXEC) brick-breaker.o brick.o -lncurses

brick-breaker.o : game.h brick.h
	$(CC) $(CFLAGS) -c brick-breaker.c

brick.o : brick.h

.PHONY: clean

clean:
	rm -f *.o $(ODIR)/$(EXEC)
