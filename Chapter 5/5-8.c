#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);
int is_leap(int year);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char (*dayptr)[13] = daytab;

int main () {

    int a = day_of_year(1988, 3, 29); 
    int mes = 0;
    int dia = 0;
    int yearday = 124;
    int year = 1998;

    month_day(year, yearday, &mes, &dia);
    printf("Ese dia es el numero: %d del año\n", a);
    printf("El mes: %d dia: %d del dia numero: %d del año: %d\n", mes, dia, yearday, year);
}

int day_of_year(int year, int month, int day) {
    int i, leap;

    if (year < 1) return -1;

    leap = is_leap(year);

    if (month < 1 || month > 12) return -1;
    if (day < 1 || day > dayptr[leap][month]) return -1;

    for (i = 1; i < month; i++) {
        day += dayptr[leap][i];
    }

    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (year < 1) return -1;

    leap = is_leap(year); 

    if (yearday < 1 || yearday > (leap ? 366 : 365)) {
        return -1;
    }

    for (i = 1; yearday > dayptr[leap][i]; i++) {
        yearday -= dayptr[leap][i];
    }

    *pmonth = i;
    *pday = yearday;
    return 0;
}

int is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) ||
           (year % 400 == 0);    
}
