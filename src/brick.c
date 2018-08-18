#include "brick.h"


int generate_bricks(WINDOW* window, bricknode** head)
{

	/* Get window dimensions */
	int win_height=0, win_width=0;
	getmaxyx( window,win_height,win_width );
	/* Get brick area dimensions */
	int brick_startx = 1;
	int brick_starty = 1;
	int brick_endx   = win_width-1;
	int brick_endy   = win_height/2;

	int curr_x, curr_size;

	/* Generate bricks */
	for( int row=brick_starty ; row<=brick_endy ; row+=(1+VERT_SPACE) )
	{
		curr_x = brick_startx;
		curr_size = (rand() % MAX_SIZE) + 1;
		while( curr_x<=brick_endx && curr_x+curr_size<=brick_endx )
		{
			/* Add brick to list */
			brick* newbrick = (brick*)malloc(sizeof(brick));
			newbrick->x1 = curr_x;
			newbrick->x2 = curr_x + curr_size;
			newbrick->y = row;
			bricknode* newbricknode = (bricknode *)malloc(sizeof(bricknode));
			newbricknode->br = newbrick;
			newbricknode->next = NULL;
			newbricknode->prev = NULL;

			/* If not first node, */
			if( *(head)!=NULL )
			{
				/* Set new node's next as head */
				newbricknode->next = *(head);
				/* Set old head's previous as new node */
				(*head)->prev = newbricknode;
				/* Set head to this new node */
				*(head) = newbricknode;
				newbricknode->prev = NULL;

			}
			/* If first node, */
			else
			{
				/* Set head to new node */
				*(head) = newbricknode;
				newbricknode->next = NULL;
				newbricknode->prev = NULL;
			}

			/* Draw brick */
			for( int i=0 ; i<curr_size ; i++ )
			{
				mvwprintw( window,row,curr_x+i, "%c",'+' );
			}
			curr_x += (curr_size+HORIZ_SPACE);
			curr_size = (rand() % MAX_SIZE) + 1;
		}
			
	}
	return 0;
}



int print_bricks(WINDOW* window, bricknode* head)
{
	bricknode* iter = head;
	if( iter )
	{
		while( iter->next != NULL )
		{
			for( int i=iter->br->x1 ; i<iter->br->x2 ; i++ )
			{
				mvwprintw( window,iter->br->y, i, "%c", '+' );
			}
			iter = iter->next;
		}
		
	}
	return 0;
}



int* check_collision(int ball_x, int ball_y, int ball_x_direction, int ball_y_direction, bricknode** bricklist_avail, bricknode** bricklist_gone)
{
	/* Integer list to return:
	 * 1. x: new ball x direction
	 * 2. y: new ball y direction
	 */
	int* ball_newxydir = (int*)malloc(2*sizeof(int));
	ball_newxydir[0] = 0;
	ball_newxydir[1] = 0;
	/* Brick iterator */
	bricknode* iter = *(bricklist_avail);

	/* For each available brick, */
	while( iter->next != NULL )
	{
		/* * * * * * * * * * * * * *
		 *     COLLISION LOGIC     *
		 * * * * * * * * * * * * * */

		/*  \
		 *  _\|
		 *    +--+
		 *    |  |
		 *    +--+
		 */
		if( ball_x_direction==1 && ball_y_direction==1 && ball_x==(iter->br->x1-1) && ball_y==(iter->br->y-1) )
		{
			ball_newxydir[0] = -1;
			ball_newxydir[1] = -1;
		}
		/*   __ | __
		 *     \|/
		 *      |
		 *     \|/
		 *    +--+
		 *    |  |
		 *    +--+
		 */
		else if( ball_y_direction==1 && (ball_x>=iter->br->x1 && ball_x<=iter->br->x2) && ball_y==(iter->br->y-1) )
		{
			ball_newxydir[0] = ball_x_direction;
			ball_newxydir[1] = -1;
		}
		/*          /
		 *        |/_
		 *    +--+
		 *    |  |
		 *    +--+
		 */
		else if( ball_x_direction==-1 && ball_y_direction==1 && ball_x==(iter->br->x2+1) && ball_y==(iter->br->y-1) )
		{
			ball_newxydir[0] = 1;
			ball_newxydir[1] = -1;
		}
		/*
		 *    +--+    /
		 *    |  | <-|----
		 *    +--+    \
		 */
		else if( ball_x_direction==-1 && ball_x==(iter->br->x2+1) && ball_y==(iter->br->y) )
		{
			ball_newxydir[0] = 1;
			ball_newxydir[1] = ball_y_direction;
		}
		/*
		 *    +--+
		 *    |  |
		 *    +--+ __
		 *        |\
		 *          \
		 */
		else if( ball_x_direction==-1 && ball_y_direction==-1 && ball_x==(iter->br->x2+1) && ball_y==(iter->br->y+1) )
		{
			ball_newxydir[0] = 1;
			ball_newxydir[1] = 1;
		}
		/*
		 *    +--+
		 *    |  |
		 *    +--+
		 *     /|\
		 *      |
		 *   __/|\__
		 *      |
		 */
		else if( ball_y_direction==-1 && (ball_x>=iter->br->x1 && ball_x<=iter->br->x2) && ball_y==(iter->br->y+1) )
		{
			ball_newxydir[0] = ball_x_direction;
			ball_newxydir[1] = 1;
		}
		/*
		 *    +--+
		 *    |  |
		 *  __+--+
		 *   /|
		 *  /
		 */
		else if( ball_x_direction==1 && ball_y_direction==-1 && ball_x==(iter->br->x1-1) && ball_y==(iter->br->y+1) )
		{
			ball_newxydir[0] = -1;
			ball_newxydir[1] = 1;
		}
		/*
		 *    \    +--+
		 * ----|-> |  |
		 *    /    +--+
		 */
		else if( ball_x_direction==1 && ball_x==(iter->br->x1-1) && ball_y==(iter->br->y) )
		{
			ball_newxydir[0] = -1;
			ball_newxydir[1] = ball_y_direction;
		}
		else
		{
			iter = iter->next;
		}

		/* If collision, reorganize brick lists */
		if( ball_newxydir[0]!=0 && ball_newxydir[1]!=0 )
		{
			/* If first node, */
			if( iter == *(bricklist_avail) )
			{
				*(bricklist_avail) = (*bricklist_avail)->next;
			}
			/* If end node, */
			else if( iter->next == NULL )
			{
				iter->prev->next = NULL;
			}
			/* If middle node, */
			else
			{
				iter->next->prev = iter->prev;
				iter->prev->next = iter->next;
			}

			/* Put orphaned node in list of hit bricks */
			/* If not first node, */
			if( *(bricklist_gone)!=NULL )
			{
				/* Set new node's next as head */
				iter->next = *(bricklist_gone);
				/* Set head to this new node */
				*(bricklist_gone) = iter;
				iter->prev = NULL;

			}
			/* If first node, */
			else
			{
				/* Set head to new node */
				*(bricklist_gone) = iter;
				iter->next = NULL;
				iter->prev = NULL;
			}
			break;
		}
	}
	return ball_newxydir;
}
