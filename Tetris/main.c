#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20

typedef enum {
	RED	= 41,
	YELLOW ,
	GREEN ,
	BLUE ,
	PURPLE ,
	CYAN ,
	WHITE ,
	BLACK = 0 
}Color;

typedef enum {
	EMPTY = -1,
	I,J,L,O,S,T,Z
}Shapeid;

typedef struct {
	Color color;
	Shapeid shape;
	bool current;
}Block;

typedef struct {
	Shapeid shape;
	Color color;
	int size;
	char rotate[4][4][4];
}Shape;

Shape shape[7] = {
	{
		.shape = I,
		.color = CYAN,
		.size = 4,
		.rotate = {
			{
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,0},
			},
			{
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
				{0,0,0,0},
			},
			{
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,0},
				{0,0,1,0},
			},
			{
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
				{0,0,0,0},
			},
		}
	},
	{
		.shape = J,
		.color = RED,
		.size = 3,
		.rotate = {
			{
				{0,0,1},
				{0,0,1},
				{0,1,1},
				
			},
			{
				{0,0,0},
				{1,0,0},
				{1,1,1},
			},
			{
				{1,1,0},
				{1,0,0},
				{1,0,0},
			},
			{
				{1,1,1},
				{0,0,1},
				{0,0,0},
			},
		}
	},
	{
		.shape = J,
		.color = YELLOW,
		.size = 3,
		.rotate = {
			{
				{1,1,1},
				{1,0,0},
				{0,0,0},

			},
			{
				{1,0,0},
				{1,0,0},
				{1,1,0},
			},
			{
				{0,0,0},
				{0,0,1},
				{1,1,1},
			},
			{
				{0,1,1},
				{0,0,1},
				{0,0,1},
			},
		}
	},
	{
		.shape = O,
		.color = GREEN,
		.size = 2,
		.rotate = {
			{
				{1,1},
				{1,1},
			},
			{
				{1,1},
				{1,1},
			},
			{
				{1,1},
				{1,1},
			},
			{
				{1,1},
				{1,1},
			},
		}
	},
	{
		.shape = S,
		.color = BLUE,
		.size = 3,
		.rotate = {
			{
				{0,1,1},
				{1,1,0},
				{0,0,0},

			},
			{
				{0,1,0},
				{0,1,1},
				{0,0,1},
			},
			{
				{0,1,1},
				{1,1,0},
				{0,0,0},
			},
			{
				{0,1,0},
				{0,1,1},
				{0,0,1},
			},
		}
	},
	{
		.shape = T,
		.color = PURPLE,
		.size = 3,
		.rotate = {
			{
				{1,1,1},
				{0,1,0},
				{0,0,0},

			},
			{
				{0,0,1},
				{0,1,1},
				{0,0,1},
			},
			{
				{0,0,0},
				{0,1,0},
				{1,1,1},
			},
			{
				{1,0,0},
				{1,1,0},
				{1,0,0},
			},
		}
	},
	{
		.shape = Z,
		.color = WHITE,
		.size = 3,
		.rotate = {
			{
				{1,1,0},
				{0,1,1},
				{0,0,0},

			},
			{
				{0,0,1},
				{0,1,1},
				{0,1,1},
			},
			{
				{1,1,0},
				{0,1,1},
				{0,0,0},
			},
			{
				{0,0,1},
				{0,1,1},
				{0,1,0},
			},
		}
},

};

typedef struct {
	int x;
	int y;
	int score;
	int rotate;
	int fallTime;
	Shapeid queue[4];
}State;

void resetBlock(Block* block) {
	block->color = BLACK;
	block->shape = EMPTY;
	block->current = false;
}

int main() {
	srand(time(NULL));
	State state = {
		.x = CANVAS_WIDTH / 2,
		.y = 0,
		.score = 0,
		.rotate = 0,
		.fallTime = 0
	};

	int i, j, r, s, t;

	for (i = 0; i < 4; i++) {
		state.queue[i] = rand() % 7;
	}

	Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH];

	for (i = 0; i < CANVAS_HEIGHT; i++) {
		for (j = 0; j < CANVAS_WIDTH; j++) {
			resetBlock(&canvas[i][j]);
		}
	}

	/*Color cur;
	for (i = 0; i < 7; i++) {
		for (r = 0; r < 4; r++) {
			for (s = 0; s < shape[i].size; s++) {
				for(t = 0; t < shape[i].size; t++) {
					if (shape[i].rotate[r][s][t]) {
						cur = shape[i].color;
					}
					else {
						cur = WHITE;
					}
				//	printf("\033[%d")
				}
			}
		}
	}*/

	system("cls");
	printf("\e[?25l"); // hide cursor
}