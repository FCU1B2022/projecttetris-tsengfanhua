#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20

typedef enum {
	RED = 41,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
	CYAN,
	WHITE,
	BLACK = 0
}Color;

typedef enum {
	EMPTY = -1,
	I, J, L, O, S, T, Z
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

Shape shapes[7] = {
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

void setBlock(Block* block, Color color, Shapeid shape, bool current)
{
	block->color = color;
	block->shape = shape;
	block->current = current;
}

void resetBlock(Block* block) {
	block->color = BLACK;
	block->shape = EMPTY;
	block->current = false;
}

bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int originalX, int originalY, int originalRotate, int newX, int newY, int newRotate, Shapeid shapeid) {
	Shape shapeData = shapes[shapeid];
	int size = shapeData.size;
	int i, j;

	// check if the new position is valid to place the block
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (shapeData.rotate[newRotate][i][j]) {
				if (newX + j < 0 || newX + j >= CANVAS_WIDTH || newY + i < 0 || newY + i >= CANVAS_HEIGHT) {
					return false;
				}
				if (!canvas[newY + i][newX + j].current && canvas[newY + i][newX + j].shape != EMPTY) {
					return false;
				}
			}
		}
	}

	// remove the old position
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (shapeData.rotate[originalRotate][i][j]) {
				resetBlock(&canvas[originalY + i][originalX + j]);
			}
		}
	}

	// move the block
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (shapeData.rotate[newRotate][i][j]) {
				setBlock(&canvas[newY + i][newX + j], shapeData.color, shapeid, true);
			}
		}
	}

	return true;
}

void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state) {
	printf("\033[0;0H\n");
	int i, j;
	for (i = 0; i < CANVAS_HEIGHT; i++) {
		printf("|");
		for (j = 0; j < CANVAS_WIDTH; j++) {
			printf("\033[%dm\u3000", canvas[i][j].color);
		}
		printf("\033[0m|\n");
	}
	return;
}

void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state) {
	if (move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0])) {
		state->y++;
	}
	return;
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
	//	printf("\e[?25l"); // hide cursor

	while (1) {
		logic(canvas, &state);
		printCanvas(canvas, &state);
		Sleep(100);
	}
	//
}