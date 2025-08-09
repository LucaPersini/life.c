//A really basic game of life implementation in C
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define GRID_ROWS 20
#define GRID_COLS 40
#define N_CELLS GRID_ROWS*GRID_COLS
#define ALIVE 'O'
#define DEAD '+'

//The function set all the cell of a grid to dead
void set_grid(char *grid) {
	for(int i = 0; i < N_CELLS; i++) {
		grid[i] = DEAD;
	}
}

//The function set the cell on the x,y coordinates with the given state
//Out of bounds coordinate are handled with a wrap around
void set_state(int x, int y, char *grid, char state) {
	if(x<0) {
		x = GRID_COLS - abs(x);
	}	

	if(y<0) {
		y = GRID_ROWS - abs(y);
	}

	x = x%GRID_COLS;
	y = y%GRID_ROWS;

	grid[GRID_COLS*y + x] = state;
}

//The function return the state of a cell on the x,y coordinates
//Out of bounds coordinate are handled with a wrap around
char get_state(int x, int y, char *grid) {
 if(x<0) {
 	x = GRID_COLS - abs(x);
 }

 if(y<0) {
 	y = GRID_ROWS - abs(y);
 }

 x = x%GRID_COLS;
 y = y%GRID_ROWS;

 return grid[GRID_COLS*y + x];
}

//The function print the given grid to the screen
void print_grid(char *grid) {
	printf("\x1B[2J"); //use ANSI escape sequences to clear the screen
	printf("\x1B[H"); //moves cursor to home position (0,0)
	for(int i = 0; i < GRID_ROWS; i++) {
		for(int j = 0; j < GRID_COLS; j++) {
			printf("%c", get_state(j, i, grid));
		}
		printf("\n");
	}
}

//The function return the number of alive neighbours of a cell
int count_alive_neighbours(int x, int y, char *grid) {
	int counter = 0;
	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			int n_x = x+j;
			int n_y = y+i;

			if(n_x == x && n_y == y) {
				continue;
			}

			if(get_state(n_x, n_y, grid) == ALIVE) {
				counter++;
			}
		}
	}

	return counter;
}

//The function compute the new state of a grid
void compute_new_state(char *old_grid, char *new_grid) {
	for(int i = 0; i < GRID_ROWS; i++) {
		for(int j = 0; j < GRID_COLS; j++) {
			int new_state = DEAD;
			int n_alive = count_alive_neighbours(j, i, old_grid);
			
			if(get_state(j, i, old_grid) == ALIVE) {
				if(n_alive == 2 || n_alive == 3) {
					new_state = ALIVE;
				}
			} else {
				if(n_alive == 3) {
					new_state = ALIVE;
				}
			}

			set_state(j, i, new_grid, new_state);
		}
	}
}

//Set the glider pattern
void glider(char *grid) {
	set_state(5, 5, grid, ALIVE);
	set_state(5, 6, grid, ALIVE);
	set_state(5, 7, grid, ALIVE);
	set_state(4, 7, grid, ALIVE);
	set_state(3, 6, grid, ALIVE);
}

//Set the blinker pattern
void blinker(char *grid) {
	set_state(10, 10, grid, ALIVE);
	set_state(10, 11, grid, ALIVE);
	set_state(10, 12, grid, ALIVE);
}

void toad(char *grid) {
	set_state(8, 8, grid, ALIVE);
	set_state(9, 8, grid, ALIVE);
	set_state(10, 8, grid, ALIVE);
	set_state(7, 7, grid, ALIVE);
	set_state(8, 7, grid, ALIVE);
	set_state(9, 7, grid, ALIVE);
	
}

int main() {
	//Set the initial state of the game
	char old_grid[N_CELLS];
	char new_grid[N_CELLS];
	set_grid(old_grid);
	set_grid(new_grid);
	// glider(old_grid);
	// blinker(old_grid);
	toad(old_grid);
	print_grid(old_grid);

	//Game loop
	while(1) {
		compute_new_state(old_grid, new_grid);
		print_grid(new_grid);
		usleep(300000);
		compute_new_state(new_grid, old_grid);
		print_grid(old_grid);
		usleep(300000);
	}

	return 0;
}
