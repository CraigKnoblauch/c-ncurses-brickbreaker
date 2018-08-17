#include "brick.h"

int generate_bricks(WINDOW* window, bricknode** head)
{
	/* List of bricks */
	*(head) = (bricknode*)malloc(sizeof(bricknode));
	bricknode* iter = *(head);

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
	for( int row=brick_starty ; row<=brick_endy ; row++ )
	{
		curr_x = brick_startx;
		curr_size = (rand() % MAX_SIZE) + 1;
		while( curr_x<=brick_endx && curr_x+curr_size<=brick_endx )
		{

			/* Add brick to list */
			if( iter == *(head) )
			{
				iter->br.y = row;
				iter->br.x1 = curr_x;
				iter->br.x2 = curr_x + curr_size;
				iter->next = NULL;
			}
			else
			{
				iter = iter->next;
				iter = (bricknode*)malloc(sizeof(bricknode));
				iter->br.y = row;
				iter->br.x1 = curr_x;
				iter->br.x2 = curr_x + curr_size;
				iter->next = NULL;
			}

			/* Draw brick */
			for( int i=0 ; i<curr_size ; i++ )
			{
				mvwprintw( window,row,curr_x+i, "%c",'+' );
			}
			curr_x += (curr_size+1);
			curr_size = (rand() % MAX_SIZE) + 1;
		}
			
	}
	return 0;
}



int print_bricks(WINDOW* window, bricknode* head)
{
	bricknode* iter = head;
	mvwprintw( window, 5, 4, "3");//"%d", head->br.x1 );
	mvwprintw( window, 5, 5, "4");//"%d", head->next->br.x1 );
	/*while( iter->next!=NULL )
	{
		for( int i=iter->br.x1 ; i<iter->br.x2 ; i++ )
		{
			mvwprintw( window,iter->br.y, i, "%c", '+' );
		}
		iter = iter->next;
	}*/
	return 0;
}
