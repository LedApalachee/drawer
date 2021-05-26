#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "image.h"
#include "choice_interface.h"

void input(Image *img);
void fill(Image *img);
void clear(Image *img);


// main info
CONSOLE_SCREEN_BUFFER_INFO origin;
HANDLE console;
char quit;


// image size and cursor's coordinates
int sizeX, sizeY;
int cursorposX, cursorposY;


// picked char and color
char picked_char;
Color picked_color;


// moves cursor in the console at his defined coordinates
void update_cursor(void)
{
	SetConsoleCursorPosition(console, (COORD){cursorposX, cursorposY});
}



int main(int argc, char **argv)
{
	// ending a program if there're not enough parameters
	if (argc < 3) return 0;

	// initial actions 
	system("cls");
	quit = 0;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &origin);
	picked_char = '?';
	picked_color = origin.wAttributes;


	// creating image
	Image image;
	sizeX = atoi(argv[1]);
	sizeY = atoi(argv[2]);
	init_image(&image, sizeX, sizeY);


	// locating the cursor at the centre of image
	cursorposX = sizeX/2;
	cursorposY = sizeY/2;


	// making image borders (only at bottom and the left side)
	for (int x = 0; x < sizeX; ++x)
	{
		SetConsoleCursorPosition(console, (COORD){x, sizeY});
		putchar('_');
	}
	for (int y = 0; y <= sizeY; ++y)
	{
		SetConsoleCursorPosition(console, (COORD){sizeX, y});
		putchar('|');
	}


	update_cursor();


	// main loop
	while (!quit)
	{
		input(&image);
		update_cursor();
	}


	// ending actions
	SetConsoleTextAttribute(console, origin.wAttributes);
	SetConsoleCursorPosition(console, (COORD){0, sizeY+1});
	return 0;
}


#include "keybindings.h"
void input(Image *img)
{
	switch (getch())
	{
		case MOVE_UP:
			if (cursorposY > 0) --cursorposY;
			break;
		
		case MOVE_DOWN:
			if (cursorposY < sizeY-1) ++cursorposY;
			break;
		
		case MOVE_LEFT:
			if (cursorposX > 0) --cursorposX;
			break;
		
		case MOVE_RIGHT:
			if (cursorposX < sizeX-1) ++cursorposX;
			break;
		
		case PICK_CHAR:
			picked_char = char_choice_interface(sizeY, picked_color, origin.wAttributes);
			break;
		
		case PICK_COLOR:
			picked_color = color_choice_interface(sizeY, picked_color, origin.wAttributes);
			break;
		
		case PUT:
			img->content[cursorposX * sizeY + cursorposY].ch = picked_char;
			img->content[cursorposX * sizeY + cursorposY].color = picked_color;
			putchar(picked_char);
			break;
		
		case ERASE:
			img->content[cursorposX * sizeY + cursorposY].ch = '\0';
			img->content[cursorposX * sizeY + cursorposY].color = NOCOLOR;
			putchar(' ');
			break;
		
		case FILL:
			fill(img);
			break;
		
		case DISPLAY:
			display(img);
			break;

		case CLEAR:
			clear(img);
			break;
		
		case QUIT:
			quit = 1;
			break;
	}
}


void fill(Image *img)
{
	for (int x = 0; x < sizeX; ++x)
		for (int y = 0; y < sizeY; ++y)
		{
			img->content[x * sizeY + y].ch = picked_char;
			img->content[x * sizeY + y].color = picked_color;
			SetConsoleCursorPosition(console, (COORD){x,y});
			putchar(picked_char);
		}
}


void clear(Image *img)
{
	for (int x = 0; x < sizeX; ++x)
		for (int y = 0; y < sizeY; ++y)
		{
			img->content[x * sizeY + y].ch = '\0';
			img->content[x * sizeY + y].color = NOCOLOR;
			SetConsoleCursorPosition(console, (COORD){x,y});
			putchar(' ');
		}
}