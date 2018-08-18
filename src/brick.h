#ifndef _BRICK_
#define _BRICK_

#include "game.h"

typedef struct Bricks
{
	int x1, x2;
	int y;
	int visible;
} brick;


typedef struct bricknode
{
	brick* br;
	struct bricknode* next;
} bricknode;

#define MAX_SIZE 4

int generate_bricks( WINDOW*, bricknode** );
int print_bricks( WINDOW*, bricknode* );

#endif
