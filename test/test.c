#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

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

int generate_bricks(bricknode** );
int print_bricks(bricknode* );



int generate_bricks(bricknode** head)
{
	/* Generate bricks */
	for( int i=0 ; i<=10 ; i++ )
	{
		/* Add brick to list */
		brick* newbrick = (brick*)malloc(sizeof(brick));
		newbrick->x1 = i;
		newbrick->x2 = i + i;
		newbrick->y = i+1;
		bricknode* newbricknode = (bricknode *)malloc(sizeof(bricknode));
		newbricknode->br = newbrick;
		newbricknode->next = NULL;

		/* If not first node, */
		if( *(head)!=NULL )
		{
			/* Set new node's next as head */
			newbricknode->next = *(head);
			/* Set head to this new node */
			*(head) = newbricknode;

		}
		/* If first node, */
		else
		{
			/* Set head to new node */
			*(head) = newbricknode;
			newbricknode->next = NULL;
		}
			
	}
	return 0;
}



int print_bricks(bricknode* head)
{
	bricknode* iter = head;

	if( iter )
	{
		while( iter->next != NULL )
		{
			/*for( int i=iter->br->x1 ; i<iter->br->x2 ; i++ )
			{
				mvwprintw( window,iter->br->y, i, "%c", '+' );
			}*/
			/*if( iter->next == NULL )
				mvwprintw(window, 8, 8, "NULL" );
			else
			*/
			printf("%d\n",iter->br->x1);
			iter = iter->next;
		}
		
	}
	return 0;
}




int main(int argc, char* argv[])
{
	/* Create bricks */
	struct bricknode* bricklist = NULL;
	generate_bricks( &bricklist );
	print_bricks(bricklist);
	return 0;
}