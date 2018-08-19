#ifndef _GAME_
#define _GAME_

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "brick.h"

#define DELAY 30000
#define BALL "o"
#define DEFAULT_BALL_DELAY 2; /* Default delay of ball, multiples of 'DELAY' */
#define PADDLE "/^^^^^^^^\\"
#define PADDLE_LEN 10
#define PADDLE_INTERVAL 1    /* Unit step a paddle can travel */

int BALL_DELAY; /* Delay of ball, multiples of 'DELAY' */


/*char* choices[] = {
			"Play",
			"Settings",
			"Exit"
		};
int n_choices = sizeof(choices) / sizeof(char*);
*/
void print_menu(WINDOW *menu_win, int highlight);

#endif
