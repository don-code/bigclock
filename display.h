/* Compatibility for DOS. Note that the DOS API forms the basis for some of
   these calls, and thus this compatibility section does not define them. */
   
#ifndef _CLOCK_DISPLAY
#define _CLOCK_DISPLAY
   
#ifdef _WIN32
#include <windows.h>

void clrscr() {
    HANDLE screen;
    COORD pos;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO screen_attr;
    unsigned size;
	
	screen = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = 0;
	pos.Y = 0;

    GetConsoleScreenBufferInfo(screen, &screen_attr);

    size = screen_attr.dwSize.X * screen_attr.dwSize.Y;

    FillConsoleOutputCharacter(screen, ' ', size, pos, &written);
    SetConsoleCursorPosition(screen, pos);
}

void gotoxy(short x, short y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void sleep(int seconds) {
	Sleep(seconds * 1000);
}

void invertColors() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void restoreColors() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

/* Else, assume an ANSI-capable terminal. */
#else

/* UNIX and DOS put their API routines in different headers. */
#ifdef unix
#include <unistd.h>
#else
#include <conio.h>
#endif

void clrscr() {
	printf("\033[2J");
}

void gotoxy(char x, char y) {
	printf("\033[%d;%dH", y, x);
}

void invertColors() {
	printf("\033[7m");
}

void restoreColors() {
	printf("\033[0m");
}
#endif

#endif