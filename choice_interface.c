#include "choice_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

HANDLE console;


char char_choice_interface(int imgsizeY, Color origin, Color console_origin)
{
	char ch;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console, (COORD){0, imgsizeY+3});
	SetConsoleTextAttribute(console, console_origin);
	printf("enter a character: "); // string length = 19 + entered char
	ch = getch();
	for (int i = 0; i < 20; ++i)
	{
		SetConsoleCursorPosition(console, (COORD){i, imgsizeY+3});
		putchar('\0');
	}
	SetConsoleTextAttribute(console, origin);
	return ch;
}


Color color_choice_interface(int imgsizeY, Color origin, Color console_origin)
{
	int choice;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console, (COORD){0, imgsizeY+3});

	for (int i = 1; i <= 15; ++i)
	{
		SetConsoleTextAttribute(console, ((int)(console_origin/16) * 16 + i));
		if ((i-1) % 3 == 0) printf("\n");
		printf("%d", i);
		if (i < 10) printf("    ");
		else printf("   ");
	}

	SetConsoleTextAttribute(console, console_origin);
	printf("\n\nenter a number of color: ");
	scanf("%d", &choice);

	// cleaning
	for (int x = 0; x < 27; ++x)
		for (int y = 0; y < 8; ++y)
		{
			SetConsoleCursorPosition(console, (COORD){x, imgsizeY+3+y});
			putchar(' ');
		}

	if (choice <= 0 || choice > 15) return origin;
	SetConsoleTextAttribute(console, ((int)(console_origin/16) * 16 + choice));

	return ((int)(console_origin/16) * 16 + choice);
}


char* file_choice_interface(int imgsizeY, Color origin, Color console_origin)
{
	char *file_path;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console, (COORD){0, imgsizeY+3});
	SetConsoleTextAttribute(console, console_origin);
	printf("enter the file path: ");
	gets(file_path);
	for (int i = 0; i < strlen(file_path) + 21; ++i)
	{
		SetConsoleCursorPosition(console, (COORD){i, imgsizeY+3});
		putchar('\0');
	}
	SetConsoleTextAttribute(console, origin);
	return file_path;
}