#include<stdio.h>

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

int main() {
	int i, r, s, t;
	Color cur;
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
	}

}