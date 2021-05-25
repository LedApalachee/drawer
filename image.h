#ifndef IMAGE_H
#define IMAGE_H

typedef enum
{
	NOCOLOR,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_PURPLE,
	BRIGHT_YELLOW,
	BRIGHT_WHITE,
	MAX_ELEMENTS
} Color;


typedef struct
{
	char ch;
	Color color;
} Pixel;


typedef struct
{
	int sizeX, sizeY;
	Pixel *content;
} Image;


void init_image(Image *img, int sx, int sy);
void display(Image *img);

#endif