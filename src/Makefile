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
OBJDIR=../obj
LIBS=-lncurses
EXEC=brickbreaker


brick-breaker : $(OBJDIR)/brick-breaker.o $(OBJDIR)/brick.o
	$(CC) $(CFLAGS) -o $(ODIR)/$(EXEC) $(OBJDIR)/brick-breaker.o $(OBJDIR)/brick.o $(LIBS)

$(OBJDIR)/brick-breaker.o : game.h brick.h
	$(CC) $(CFLAGS) -c brick-breaker.c -o $(OBJDIR)/brick-breaker.o

$(OBJDIR)/brick.o : brick.c brick.h
	$(CC) $(CFLAGS) -c brick.c -o $(OBJDIR)/brick.o

.PHONY: clean

clean:
	rm -f *.o $(OBJDIR)/*.o $(ODIR)/$(EXEC)
