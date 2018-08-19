#include "game.h"
#include <string.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	initscr();             /* Initialize the gamewindow */
	noecho();              /* Don't echo any keypresses */
	curs_set(FALSE);       /* Don't display a cursor */
	keypad(stdscr,TRUE);   /* Use key code */
	nodelay(stdscr, TRUE); /* Cause getch() to be non-blocking */


	int max_x=0 , max_y=0; /* Window dimensions */

	getmaxyx(stdscr, max_y, max_x);              /* 'stdscr' is the screen created by initscr() */
	int ball_x=(max_x/2)+1 , ball_y=(max_y/2)+1; /* Ball's coordinates */
	int next_ball_x=0      , next_ball_y=0;      /* Ball's next coordinates */
	int x_ball_direction=1 , y_ball_direction=1; /* Ball's direction of travel */
	int ball_curr_delay=0;                       /* Ball's delay counter */

	int paddle_x=(max_x/2)-PADDLE_LEN, paddle_y=max_y-2;      /* Paddle's coordinates */
	int max_paddle_x=max_x-PADDLE_LEN, max_paddle_y=paddle_y; /* Paddle's boundaries */
	int paddle_key;                                           /* Paddle keyboard input */

	int* ball_brick_dir; /* xy direction for ball if brick collision */


	/* Initial welcome message */
	int start_key=0;
	mvprintw((max_y/2)-2,(max_x/2)-25/2, "Welcome to brick-breaker!");
	mvprintw((max_y/2)-1,(max_x/2)-16/2, "Move: Arrow keys");
	mvprintw(max_y/2,(max_x/2)-24/2,"Press spacebar to start.");
	while(start_key != ' ')
	{
		start_key = getch();
	}



	/* Create bricks */
	bricknode* bricklist_avail = NULL;
	bricknode* bricklist_gone  = NULL;
	generate_bricks( stdscr,&bricklist_avail );
	refresh();





	while(1)
	{
		/* * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *                    PRINT SPRITES                  *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */
		clear();                        /* Clear screen of all characters */
		getmaxyx(stdscr, max_y, max_x); /* 'stdscr' is the screen created by initscr() */
		paddle_y=max_paddle_y;          /* Put paddle at bottom */

		print_bricks(stdscr,bricklist_avail); /* Display available bricks */
		mvprintw( ball_y,ball_x,BALL );       /* Print ball at xy position */
		mvprintw( paddle_y,paddle_x,PADDLE ); /* Print paddle at xy position */

		usleep(DELAY); /* A short delay between ball prints */

		/* * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *                    SPRITE LOGIC                   *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */

		/* BALL */

		if( ball_curr_delay == BALL_DELAY )
		{
			/* Check if brick collision */
			ball_brick_dir = check_collision( ball_x,ball_y,x_ball_direction,y_ball_direction,&bricklist_avail,&bricklist_gone);
			/* If no brick collision, */
			if( ball_brick_dir[0]==0 && ball_brick_dir[1]==0 )
			{
				next_ball_x = ball_x + x_ball_direction;
				next_ball_y = ball_y + y_ball_direction;
				/* If ball at x boundary */
				if( next_ball_x >= max_x || next_ball_x < 0 )
				{
					x_ball_direction *= -1;
					ball_x += x_ball_direction;
				}
				/* If ball at paddle */
				else if( next_ball_y == paddle_y && (next_ball_x>=paddle_x && next_ball_x<=paddle_x+PADDLE_LEN) )
				{
					y_ball_direction *= -1;
				}
				else
				{
					ball_x += x_ball_direction;
				}
				/* If ball at y boundary */
				if( next_ball_y >= max_y || next_ball_y < 0 )
				{
					y_ball_direction *= -1;
					ball_y += y_ball_direction;
				}
				else
				{
					ball_y += y_ball_direction;
				}
			}
			/* If brick collision, */
			else
			{
				x_ball_direction = ball_brick_dir[0];
				y_ball_direction = ball_brick_dir[1];
				ball_x += x_ball_direction;
				ball_y += y_ball_direction;
			}
		}

		
		

		/* PADDLE */

		paddle_key = getch();
		if( paddle_key == KEY_LEFT && paddle_x-PADDLE_INTERVAL>=0 )
		{
			paddle_x-=PADDLE_INTERVAL;
		}
		else if( paddle_key == KEY_RIGHT && paddle_x+PADDLE_INTERVAL<=max_paddle_x )
		{
			paddle_x+=PADDLE_INTERVAL;
		}
		/* Exit if 'q' is pressed */
		else if( paddle_key == 'q' )
		{
			endwin();
			return 0;
		}
		else if( paddle_key == 'p' )
		{
			int unpause = getch();
			mvprintw((max_y/2)-2,(max_x/2)-28/2, "+-------------------------+");
			mvprintw((max_y/2)-1,(max_x/2)-28/2, "| Press space to unpause. |");
			mvprintw(max_y/2,(max_x/2)-28/2,     "+-------------------------+");
			refresh();
			while( unpause != ' ' && unpause != 'q' )
			{
				unpause = getch();
			}
			if( unpause == 'q' )
			{
				endwin();
				return 0;
			}
			clear();
		}
		
		
		/* Update ball delay counter */
		//ball_curr_delay = (ball_curr_delay+1) % BALL_DELAY;
		if( ball_curr_delay+1 > BALL_DELAY )
			ball_curr_delay = 0;
		else
			ball_curr_delay++;
		
		/* * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *                   REFRESH WINDOW                  *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */
		refresh();

	}

	endwin(); /* restore normal terminal behavior */
	
	return 0;
}
