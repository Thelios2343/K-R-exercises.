#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

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

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (month < 1 || month > 12) return -1;
    if (day < 1 || day > daytab[leap][month]) return -1;

    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }

    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (year < 1) return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (yearday < 1 || yearday > (leap ? 366 : 365)) {
        return -1;
    }

    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }

    *pmonth = i;
    *pday = yearday;
    return 0;
} 
