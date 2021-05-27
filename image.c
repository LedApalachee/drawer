#include "image.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void init_image(Image *img, int sx, int sy)
{
	img->sizeX = sx;
	img->sizeY = sy;
	img->content = (Pixel*) malloc(sizeof(Pixel) * sx * sy);

	for (int x = 0; x < sx; ++x)
		for (int y = 0; y < sy; ++y)
		{
			img->content[x * sy + y].ch = '\0';
			img->content[x * sy + y].color = NOCOLOR;
		}
}


void display(Image *img, Color origin_console)
{
	system("cls");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO origin;
	GetConsoleScreenBufferInfo(console, &origin);

	for (int x = 0; x < img->sizeX; ++x)
		for (int y = 0; y < img->sizeY; ++y)
		{
			SetConsoleCursorPosition(console, (COORD){x,y});
			SetConsoleTextAttribute(console, (int)img->content[x * img->sizeY + y].color);
			putchar(img->content[x * img->sizeY + y].ch);
		}

	// making image borders (only at bottom and the left side)
	SetConsoleTextAttribute(console, origin_console);
	for (int x = 0; x < img->sizeX; ++x)
	{
		SetConsoleCursorPosition(console, (COORD){x, img->sizeY});
		putchar('_');
	}
	for (int y = 0; y <= img->sizeY; ++y)
	{
		SetConsoleCursorPosition(console, (COORD){img->sizeX, y});
		putchar('|');
	}

	SetConsoleTextAttribute(console, origin.wAttributes);
}


void del_image(Image *img)
{
	free(img->content);
}