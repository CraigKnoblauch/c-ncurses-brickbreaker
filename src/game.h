#ifndef _GAME_
#define _GAME_

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "brick.h"

#define DELAY 30000
#define BALL "o"
#define DEFAULT_BALL_DELAY 2 /* Default delay of ball, multiples of 'DELAY' */
#define PADDLE "/^^^^^^^^\\" /* Paddle sprite */
#define PADDLE_LEN 10        /* Length of paddle sprite */
#define PADDLE_INTERVAL 4    /* Unit step a paddle can travel */
#define LIVES 4              /* Player's starting number of lives */

int BALL_DELAY; /* Delay of ball, multiples of 'DELAY' */
int lives;      /* Placeholder for player's lives */


char start_game(WINDOW* window);

#endif
