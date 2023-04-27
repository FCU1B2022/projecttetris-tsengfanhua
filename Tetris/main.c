#inclde<stdio.h>



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
}ShapeID;

typedef struct {
	Color color;
	ShapeID shape;
}Block;

int main() {

}