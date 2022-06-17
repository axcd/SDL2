#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int year = 2022;
int month = 6;

//存放每个月月份天数的数组，这是全局变量
int monthDays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};


char *week[7] = {"日", "一", "二", "三", "四", "五", "六"};
//月天数
char *day[32] = {"0","01","02","03","04","05","06","07","08","09",
				"10","11","12","13","14","15","16","17","18","19",
				"20","21","22","23","24","25","26","27","28","29",
				"30","31"
				};

//当前年月
void date()
{
	time_t now;
	struct tm *p;
	time (&now);
	p=localtime(&now);
	year = p->tm_year+1900;
	month = p->tm_mon+1;
}

//判断是否润年
int isLeapYear(int year)
{
    return((year%4==0&&year%100!=0)||year%400==0); 
}

int dayOftheWeekThisYear(int year)
{
    //蔡勒公式，此处是计算这一年的第一天是星期几
    int i=((5*(year-1)/4-(year-1)/100+(year-1)/400)%7)+1;
    return i;
}

//把这个天数和加上之前计算的查询年的第一天的星期几在进行计算，即可求出查询月的第一天是星期几
int dayOftheWeekThisYearQueryMonth(int year,int month)
{
    int totalDays=0;
	
	//同样的修正数组，修正二月的天数
    if(isLeapYear(year)==1)
		monthDays[2]=29;
    else 
		monthDays[2]=28;
		
	//计算这一年从一月到查询月之前的所有月份的天数和
    for(int i=1;i<month;i++)
    {
        totalDays+=monthDays[i];
    }
    totalDays=totalDays+dayOftheWeekThisYear(year);
	
    return (totalDays%7);
}

//上月
void lastmonth(int *year, int *month)
{
        (*month)--;
        if(*month==0)
        {
                *month = 12;
                (*year)--;
        }
}

//下月
void nextmonth(int *year, int *month)
{
        (*month)++;
        if(*month==13)
        {
             *month = 1;
              (*year)++;
        }
}

//int转char*
void itoa(int a, char *s)
{
	char *p = s;
    int b = a;
    while((b = b/10)>0) p++;

    do{
         char c = a%10 +48;
         *p-- = c;
     }while((a=a/10)>0);
}

//日期str
char *datestr(char *dstr, char * spit)
{
	itoa(year, dstr);
	char tmp[11]={'0'};
	itoa(month, tmp);
	strcat(dstr, spit);
	strcat(dstr, tmp);
	return dstr;
}
