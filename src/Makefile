# Dependency tree:
#    /\                brickbreaker
#    ||               /           \
#   link       brick-breaker.o     brick.o
#    ||               |              |
#  compile     brick-breaker.c     brick.c
#    ||               \           /
#    ||             game.h       /
#  include              \       /
#    ||                  brick.h
#    ||


CC=gcc
CFLAGS=-I.
ODIR=..
LIBS=-lncurses
EXEC=brickbreaker
OBJ=brick-breaker.o brick.o


brick-breaker : $(OBJ)
	$(CC) $(CFLAGS) -o $(ODIR)/$(EXEC) $(OBJ) $(LIBS)

brick-breaker.o : game.h brick.h
	$(CC) $(CFLAGS) -c brick-breaker.c

brick.o : brick.h

.PHONY: clean

clean:
	rm -f *.o $(ODIR)/$(EXEC)
