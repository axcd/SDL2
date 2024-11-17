#ifndef CALENDAR_h_
#define CALENDAR_h_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void date(int *year, int *month, int *day);

int isLeapYear(int year);

int dayOftheWeekThisYear(int year);

int dayOftheWeekThisYearQueryMonth(int year,int month);

void lastmonth(int *year, int *month);

void nextmonth(int *year, int *month);

void itoa(int a, char *s);

char *datestr(int year, int month, char *dstr, char * spit);

#endif   /* CALENDAR_h_ */
