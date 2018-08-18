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
	struct bricknode* prev;
} bricknode;

#define MAX_SIZE 4
#define HORIZ_SPACE 5
#define VERT_SPACE 3

int generate_bricks( WINDOW*, bricknode** );
int print_bricks( WINDOW*, bricknode* );
int* check_collision( int, int, int, int, bricknode**, bricknode** );

#endif
