#include "choice_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

HANDLE console;


char char_choice_interface(int imgsizeY, Color origin)
{
	char ch;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console, (COORD){0, imgsizeY+3});
	SetConsoleTextAttribute(console, 15);
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


Color color_choice_interface(int imgsizeY)
{
	int choice;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console, (COORD){0, imgsizeY+3});
	/*
	SetConsoleTextAttribute(console, 15);
	printf("1) blue              ");
	printf("2) green\n");
	printf("3) cyan              ");
	printf("4) red\n");
	printf("5) purple            ");
	printf("6) yellow\n");
	printf("7) white             ");
	printf("8) grey\n");
	printf("9) bright blue       ");
	printf("10) bright green\n");
	printf("11) bright cyan      ");
	printf("12) bright red\n");
	printf("13) bright purple    ");
	printf("14) bright yellow\n");
	printf("15) bright white\n");
	printf("\nenter a number of color: ");
	scanf("%d", &choice);
	if (choice <= 0 || choice > 15) return BRIGHT_WHITE;
	SetConsoleTextAttribute(console, choice);

	// cleaning
	for (int x = 0; x < 38; ++x)
		for (int y = 0; y < 16; ++y)
		{
			SetConsoleCursorPosition(console, (COORD){x, imgsizeY+3+y});
			putchar(' ');
		}
	*/

	for (int i = 1; i <= 15; ++i)
	{
		SetConsoleTextAttribute(console, i);
		if ((i-1) % 3 == 0) printf("\n");
		printf("%d", i);
		if (i < 10) printf("    ");
		else printf("   ");
	}

	SetConsoleTextAttribute(console, 15);
	printf("\n\nenter a number of color: ");
	scanf("%d", &choice);

	// cleaning
	for (int x = 0; x < 27; ++x)
		for (int y = 0; y < 8; ++y)
		{
			SetConsoleCursorPosition(console, (COORD){x, imgsizeY+3+y});
			putchar(' ');
		}

	if (choice <= 0 || choice > 15) return BRIGHT_WHITE;
	SetConsoleTextAttribute(console, choice);

	return (Color)choice;
}