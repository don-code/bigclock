#include <stdlib.h>
#include <stdio.h> 
#include <time.h>
#include <string.h>

#include "display.h"
#include "charset.h"

#define DATE_LENGTH 6
#define TIME_LENGTH 9

void drawStr(char* buf, char strlen, char x, char y) {
	char i;

	for(i=0; i<strlen - 1; i++) {
		drawChar(i*(CHAR_WIDTH + 2) + x, y, buf[i]);
	}
}

/* Draws the hours, minutes, and seconds in block letters. */
void drawTime(struct tm * timeinfo) {
	char buf[TIME_LENGTH];

	gotoxy(2,15);
	printf("Local Time");
	strftime(buf, TIME_LENGTH, "%H:%M:%S", timeinfo);
	drawStr(buf, TIME_LENGTH, 9, 18);
}

/* Draws a calendar. */
void drawCalendar(struct tm * timeinfo) {
	char i;
	char wk1;
	char wk_offset;
	char day_offset;
	char today;
	char month;
	char buf[15]; /* 15 = max number of characters in a month/year combo */

	today = timeinfo->tm_mday;
	month = timeinfo->tm_mon;
	wk1 = 0;
	wk_offset = 0;
	day_offset = 0;
	
	/* Print a calendar header. */
	gotoxy(3,2);
	strftime(buf, 15, "%B %Y",timeinfo);
	printf("%s Calendar", buf);
	gotoxy(3,4);
	printf("Su Mo Tu We Th Fr Sa  Wk");
	
	/* Blank out the calendar area. */
	for(i=0; i < 8; i++) {
		gotoxy(3, 5+i);
		printf("                        ");
	}
	
	for(i=1; i < 32; i++) { /* Iterate over all possible days in the month. */
		timeinfo->tm_mday = i;
		mktime(timeinfo);
		
		/* If it's the first day of the month, calculate the start position. */
		if(i==1) {
			day_offset = timeinfo->tm_wday;
			strftime(buf, 3, "%U", timeinfo);
			wk1 = atoi(buf);
			gotoxy(25, 5);
			printf("%d",wk1);
			
		/* If it's any other Sunday, with iteration still in the same month. */
		} else if(timeinfo->tm_wday == 0 && month == timeinfo->tm_mon) {
			/* Calculate what week it is. */
			wk_offset++;
			day_offset = 0;
			gotoxy(25, 5 + wk_offset);
			printf("%d",wk1+wk_offset);
		}
		
		/* Print out a single day in the correct position, provided that day
           exists in the month (prevents Feb. 30, etc.) */
		if(month == timeinfo->tm_mon) {
			/* Invert console colors to mark the current day. */
			if(i==today) {
				invertColors();
			}
			
			gotoxy((day_offset * 3)+3,wk_offset + 5);
			printf("%d",timeinfo->tm_mday);
			day_offset++;
			
			/* Un-invert colors of the current day. */
			if(i==today) {
				restoreColors();
			}
		}
	}
}

/* Draws the three-letter month and two-digit day in block letters. */
void drawDate(struct tm * timeinfo) {
	char buf[DATE_LENGTH];

	gotoxy(36,2);
	printf("Today's date");
	gotoxy(36,5);
	strftime(buf, DATE_LENGTH, "%a%d", timeinfo);
	drawStr(buf, DATE_LENGTH, 36, 5);
}

/* Entry point. */
int main() {
	char day;
	time_t rawtime;
	struct tm * timeinfo;

	day = 0;
	clrscr();

	while(1) { /* Run until interrupted. */
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		/* Draw the time on every update. */
		drawTime(timeinfo);
		
		/* If the date has changed, draw the date and year. This avoids console
		   shearing on older hardware. */
		if(day != timeinfo->tm_mday) {
			/* Update the day. */
			day = timeinfo->tm_mday;
			drawDate(timeinfo);
			
			/* Update the calendar. */
			drawCalendar(timeinfo);
		}
		
		fflush(stdout);
		sleep(1);
	}
}