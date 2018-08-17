#include "game.h"
#include <string.h>
#include <stdio.h>

#define DELAY 30000
#define BALL "o"
#define PADDLE "/^^^^^^^^\\"
#define PADDLE_LEN 10
#define PADDLE_INTERVAL 4


int main(int argc, char* argv[])
{
	initscr();             /* Initialize the window */
	noecho();              /* Don't echo any keypresses */
	curs_set(FALSE);       /* Don't display a cursor */
	keypad(stdscr,TRUE);   /* Use key code */
	nodelay(stdscr, TRUE); /* Cause getch() to be non-blocking */


	int max_x=0 , max_y=0; /* Window dimensions */

	int ball_x=0          , ball_y=0;           /* Ball's coordinates */
	int next_ball_x=0     , next_ball_y=0;      /* Ball's next coordinates */
	int x_ball_direction=1, y_ball_direction=1; /* Ball's direction of travel */
	getmaxyx(stdscr, max_y, max_x);             /* 'stdscr' is the screen created by initscr() */

	int paddle_x=0                   , paddle_y=max_y-2;      /* Paddle's coordinates */
	int max_paddle_x=max_x-PADDLE_LEN, max_paddle_y=paddle_y; /* Paddle's boundaries */
	int paddle_key;                                           /* Paddle keyboard input */


	int start_key=0;
	mvprintw((max_y/2)-2,(max_x/2)-25/2, "Welcome to brick-breaker!");
	mvprintw((max_y/2)-1,(max_x/2)-16/2, "Move: Arrow keys");
	mvprintw(max_y/2,(max_x/2)-24/2,"Press spacebar to start.");
	while(start_key != ' ')
	{
		start_key = getch();
	}



	/* Create bricks */






	while(1)
	{
		/* * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *                    PRINT SPRITES                  *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */
		clear(); /* Clear screen of all characters */
		getmaxyx(stdscr, max_y, max_x); /* 'stdscr' is the screen created by initscr() */
		paddle_y=max_paddle_y;

		mvprintw( ball_y,ball_x,BALL );       /* Print ball at xy position */
		mvprintw( paddle_y,paddle_x,PADDLE ); /* Print paddle at xy position */

		usleep(DELAY); /* A short delay between ball prints */

		/* * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *                    SPRITE LOGIC                   *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */

		/* BALL */
		
		next_ball_x = ball_x + x_ball_direction;
		next_ball_y = ball_y + y_ball_direction;

		/* If ball at x boundary */
		if( next_ball_x >= max_x || next_ball_x < 0 )
		{
			x_ball_direction *= -1;
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

		if( next_ball_y >= max_y || next_ball_y < 0 )
		{
			y_ball_direction *= -1;
		}
		else
		{
			ball_y += y_ball_direction;
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

		
		
		/* * * * * * * * * * * * * * * * * * * * * * * * * * *
		 *                   REFRESH WINDOW                  *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * */
		refresh();
	}

	endwin(); /* restore normal terminal behavior */

	return 0;
}
