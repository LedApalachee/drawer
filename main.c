#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "image.h"
#include "choice_interface.h"

void input(Image *img);
void fill(Image *img);
void clear(Image *img);
void save(Image *img, char *path);
void load(Image *img, char *path);


// main info
CONSOLE_SCREEN_BUFFER_INFO origin;
HANDLE console;
char quit;


// cursor's coordinates
int cursorposX, cursorposY;


// picked char and color
char picked_char;
Color picked_color;


// moves cursor in the console at his actual coordinates
void update_cursor(void)
{
	SetConsoleCursorPosition(console, (COORD){cursorposX, cursorposY});
}



int main(int argc, char **argv)
{
	if (argc < 2) return 0;

	// initial actions
	SetConsoleTitle("Led's drawer");
	system("cls");
	quit = 0;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &origin);
	picked_char = '?';
	picked_color = origin.wAttributes;


	// creating image
	Image img;
	if (argc == 2) load(&img, argv[1]);
	else init_image(&img, atoi(argv[1]), atoi(argv[2]));


	// locating the cursor at the centre of image
	cursorposX = img.sizeX/2;
	cursorposY = img.sizeY/2;

	display(&img, origin.wAttributes);
	update_cursor();


	// main loop
	while (!quit)
	{
		input(&img);
		update_cursor();
	}


	// ending actions
	SetConsoleTextAttribute(console, origin.wAttributes);
	SetConsoleCursorPosition(console, (COORD){0, img.sizeY+1});
	del_image(&img);
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
			if (cursorposY < img->sizeY-1) ++cursorposY;
			break;
		
		case MOVE_LEFT:
			if (cursorposX > 0) --cursorposX;
			break;
		
		case MOVE_RIGHT:
			if (cursorposX < img->sizeX-1) ++cursorposX;
			break;
		
		case PICK_CHAR:
			picked_char = char_choice_interface(img->sizeY, picked_color, origin.wAttributes);
			break;
		
		case PICK_COLOR:
			picked_color = color_choice_interface(img->sizeY, picked_color, origin.wAttributes);
			break;
		
		case PUT:
			img->content[cursorposX * img->sizeY + cursorposY].ch = picked_char;
			img->content[cursorposX * img->sizeY + cursorposY].color = picked_color;
			putchar(picked_char);
			break;
		
		case ERASE:
			img->content[cursorposX * img->sizeY + cursorposY].ch = '\0';
			img->content[cursorposX * img->sizeY + cursorposY].color = NOCOLOR;
			putchar('\0');
			break;
		
		case FILL:
			fill(img);
			break;
		
		case DISPLAY:
			display(img, origin.wAttributes);
			break;

		case CLEAR:
			clear(img);
			break;

		case SAVE:
			save(img, file_choice_interface(img->sizeY, picked_color, origin.wAttributes));
			break;

		case LOAD:
			del_image(img);
			load(img, file_choice_interface(img->sizeY, picked_color, origin.wAttributes));
			cursorposX = img->sizeX/2;
			cursorposY = img->sizeY/2;
			display(img, origin.wAttributes);
			break;
		
		case QUIT:
			quit = 1;
			break;
	}
}


void fill(Image *img)
{
	for (int x = 0; x < img->sizeX; ++x)
		for (int y = 0; y < img->sizeY; ++y)
		{
			img->content[x * img->sizeY + y].ch = picked_char;
			img->content[x * img->sizeY + y].color = picked_color;
			SetConsoleCursorPosition(console, (COORD){x,y});
			putchar(picked_char);
		}
}


void clear(Image *img)
{
	for (int x = 0; x < img->sizeX; ++x)
		for (int y = 0; y < img->sizeY; ++y)
		{
			img->content[x * img->sizeY + y].ch = '\0';
			img->content[x * img->sizeY + y].color = NOCOLOR;
			SetConsoleCursorPosition(console, (COORD){x,y});
			putchar('\0');
		}
}


void save(Image *img, char *path)
{
	fflush(stdout);
	FILE *file = fopen(path, "wb");
	fwrite(&img->sizeX, sizeof(int), 1, file);
	fwrite(&img->sizeY, sizeof(int), 1, file);

	for (int x = 0; x < img->sizeX; ++x)
		for (int y = 0; y < img->sizeY; ++y)
		{
			fwrite(&img->content[x * img->sizeY + y].ch, sizeof(char), 1, file);
			fwrite(&img->content[x * img->sizeY + y].color, sizeof(char), 1, file);
		}

	fclose(file);
}


void load(Image *img, char *path)
{
	int sx, sy;
	fflush(stdin);
	FILE *load = fopen(path, "rb");
	fread(&sx, sizeof(int), 1, load);
	fread(&sy, sizeof(int), 1, load);
	init_image(img, sx, sy);

	for (int x = 0; x < img->sizeX; ++x)
		for (int y = 0; y < img->sizeY; ++y)
		{
			fread(&img->content[x * img->sizeY + y].ch, sizeof(char), 1, load);
			fread(&img->content[x * img->sizeY + y].color, sizeof(char), 1, load);
		}

	fclose(load);
}
