#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define LEFT_KEY 0x25
#define RIGHT_KEY 0x27
#define ROTATE_KEY 0x26
#define DOWN_KEY 0x28
#define FALL_KEY 0x20

#define FALL_DELAY 500
#define RENDER_DELAY 100

#define LEFT_FUNC() GetAsyncKeyState(LEFT_KEY) & 0x8000
#define RIGHT_FUNC() GetAsyncKeyState(RIGHT_KEY) & 0x8000
#define ROTATE_FUNC() GetAsyncKeyState(ROTATE_KEY) & 0x8000
#define DOWN_FUNC() GetAsyncKeyState(DOWN_KEY) & 0x8000
#define FALL_FUNC() GetAsyncKeyState(FALL_KEY) & 0x8000

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
		.rotate =
		{
			{
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			},
			{
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 1, 0},
				{0, 0, 1, 0}
			},
			{
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{1, 1, 1, 1},
				{0, 0, 0, 0}
			},
			{
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0},
				{0, 1, 0, 0}
			}
		}
	},
	{
		.shape = J,
		.color = BLUE,
		.size = 3,
		.rotate =
		{
			{
				{1, 0, 0},
				{1, 1, 1},
				{0, 0, 0}
			},
			{
				{0, 1, 1},
				{0, 1, 0},
				{0, 1, 0}
			},
			{
				{0, 0, 0},
				{1, 1, 1},
				{0, 0, 1}
			},
			{
				{0, 1, 0},
				{0, 1, 0},
				{1, 1, 0}
			}
		}
	},
	{
		.shape = L,
		.color = YELLOW,
		.size = 3,
		.rotate =
		{
			{
				{0, 0, 1},
				{1, 1, 1},
				{0, 0, 0}
			},
			{
				{0, 1, 0},
				{0, 1, 0},
				{0, 1, 1}
			},
			{
				{0, 0, 0},
				{1, 1, 1},
				{1, 0, 0}
			},
			{
				{1, 1, 0},
				{0, 1, 0},
				{0, 1, 0}
			}
		}
	},
	{
		.shape = O,
		.color = WHITE,
		.size = 2,
		.rotate =
		{
			{
				{1, 1},
				{1, 1}
			},
			{
				{1, 1},
				{1, 1}
			},
			{
				{1, 1},
				{1, 1}
			},
			{
				{1, 1},
				{1, 1}
			}
		}
	},
	{
		.shape = S,
		.color = GREEN,
		.size = 3,
		.rotate =
		{
			{
				{0, 1, 1},
				{1, 1, 0},
				{0, 0, 0}
			},
			{
				{0, 1, 0},
				{0, 1, 1},
				{0, 0, 1}
			},
			{
				{0, 0, 0},
				{0, 1, 1},
				{1, 1, 0}
			},
			{
				{1, 0, 0},
				{1, 1, 0},
				{0, 1, 0}
			}
		}
	},
	{
		.shape = T,
		.color = PURPLE,
		.size = 3,
		.rotate =
		{
			{
				{0, 1, 0},
				{1, 1, 1},
				{0, 0, 0}
			},

				{{0, 1, 0},
				{0, 1, 1},
				{0, 1, 0}
			},
			{
				{0, 0, 0},
				{1, 1, 1},
				{0, 1, 0}
			},
			{
				{0, 1, 0},
				{1, 1, 0},
				{0, 1, 0}
			}
		}
	},
	{
		.shape = Z,
		.color = RED,
		.size = 3,
		.rotate =
		{
			{
				{1, 1, 0},
				{0, 1, 1},
				{0, 0, 0}
			},
			{
				{0, 0, 1},
				{0, 1, 1},
				{0, 1, 0}
			},
			{
				{0, 0, 0},
				{1, 1, 0},
				{0, 1, 1}
			},
			{
				{0, 1, 0},
				{1, 1, 0},
				{1, 0, 0}
			}
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
	int i, j, k;
	for (i = 0; i < CANVAS_HEIGHT; i++) {
		printf("|");
		for (j = 0; j < CANVAS_WIDTH; j++) {
			printf("\033[%dm\u3000", canvas[i][j].color);
		}
		printf("\033[0m|\n");
	}

	Shape shapeData = shapes[state->queue[1]];
	for (i = 1; i <= 3; i++)
	{
		shapeData = shapes[state->queue[i]];
		for (j = 0; j < 4; j++) {
			printf("\033[%d;%dH", i * 4 + j, CANVAS_WIDTH * 2 + 15);
			for (k = 0; k < 4; k++) {
				if (j < shapeData.size && k < shapeData.size && shapeData.rotate[0][j][k]) {
					printf("\x1b[%dm  ", shapeData.color);
				}
				else {
					printf("\x1b[0m  ");
				}
			}
		}
	}
	return;
}

int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH]) {
	int i, j, k;
	for (i = 0; i < CANVAS_HEIGHT; i++) {
		for (j = 0; j < CANVAS_WIDTH; j++) {
			if (canvas[i][j].current) {
				canvas[i][j].current = false;
			}
		}
	}

	int linesCleared = 0;

	for (i = CANVAS_HEIGHT - 1; i >= 0; i--)
	{
		bool isFull = true;
		for (j = 0; j < CANVAS_WIDTH; j++)
		{
			if (canvas[i][j].shape == EMPTY) {
				isFull = false;
				break;
			}
		}

		if (isFull) {
			linesCleared += 1;

			for (j = i; j > 0; j--)
			{
				for (k = 0; k < CANVAS_WIDTH; k++)
				{
					setBlock(&canvas[j][k], canvas[j - 1][k].color, canvas[j - 1][k].shape, false);
					resetBlock(&canvas[j - 1][k]);
				}
			}
			i++;
		}
	}


	return linesCleared;
}

void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state) {
	if (1) {//
		int newRotate = (state->rotate + 1) % 4;
		if (move(canvas, state->x, state->y, state->rotate, state->x, state->y, newRotate, state->queue[0])) {
			state->rotate = newRotate;
		}
		//增加讀取1234按鍵指定當下旋轉情況
		//瘋狂模式rotate不停
	}
	if (ROTATE_FUNC()) {//
		int newRotate = (state->rotate + 1) % 4;
		if (move(canvas, state->x, state->y, state->rotate, state->x, state->y, newRotate, state->queue[0])) {
			state->rotate = newRotate;
		}
//增加讀取1234按鍵指定當下旋轉情況
//瘋狂模式rotate不停
	}
	
	else if (LEFT_FUNC()) {
		if (move(canvas, state->x, state->y, state->rotate, state->x - 1, state->y, state->rotate, state->queue[0])) {
			state->x -= 1;
		}

	}
	else if (RIGHT_FUNC()) {
		if (move(canvas, state->x, state->y, state->rotate, state->x + 1, state->y, state->rotate, state->queue[0])) {
			state->x += 1;
		}

	}
	else if (DOWN_FUNC()) {
		state->fallTime = FALL_DELAY;
	}
	else if (FALL_FUNC()) {//falldelay可用作難度操作,越小越快
		state->fallTime += FALL_DELAY * CANVAS_HEIGHT;
	}

	state->fallTime += RENDER_DELAY;

	while (state->fallTime >= FALL_DELAY) {
		state->fallTime -= FALL_DELAY;

		if (move(canvas, state->x, state->y, state->rotate, state->x, state->y + 1, state->rotate, state->queue[0])) {
			state->y++;
		}
		else {
			state->score += clearLine(canvas);

			state->x = CANVAS_WIDTH / 2;
			state->y = 0;
			state->rotate = 0;
			state->fallTime = 0;
			state->queue[0] = state->queue[1];
			state->queue[1] = state->queue[2];
			state->queue[2] = state->queue[3];
			state->queue[3] = rand() % 7;

			if (!move(canvas, state->x, state->y, state->rotate, state->x, state->y, state->rotate, state->queue[0]))
			{
				printf("\033[%d;%dH\x1b[41m GAME OVER \x1b[0m\033[%d;%dH", CANVAS_HEIGHT - 3, CANVAS_WIDTH * 2 + 5, CANVAS_HEIGHT + 5, 0);
				exit(0);
			}
		}
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