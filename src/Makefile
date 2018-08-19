# Dependency tree:
#    /\                brickbreaker
#    ||               /           \
#   link           game.o       brick.o
#    ||               |            |
#  compile         game.c       brick.c
#    ||               \           /
#    ||                \         brick.h
#  include              \       /
#    ||                  game.h
#    ||


CC=gcc
CFLAGS=-I. --std=c99 -g
ODIR=..
OBJDIR=../obj
LIBS=-lncurses
EXEC=brickbreaker


brick-breaker : $(OBJDIR)/game.o $(OBJDIR)/brick.o
	$(CC) $(CFLAGS) -o $(ODIR)/$(EXEC) $(OBJDIR)/game.o $(OBJDIR)/brick.o $(LIBS)

$(OBJDIR)/game.o : game.c game.h
	$(CC) $(CFLAGS) -c game.c -o $(OBJDIR)/game.o

$(OBJDIR)/brick.o : brick.c brick.h game.h
	$(CC) $(CFLAGS) -c brick.c -o $(OBJDIR)/brick.o

.PHONY: clean

clean:
	rm -f *.o $(OBJDIR)/*.o $(ODIR)/$(EXEC)
