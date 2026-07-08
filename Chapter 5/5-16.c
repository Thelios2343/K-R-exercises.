#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORAGE (MAXLINES * MAXLEN)


int readlines(char *lineptr[], int nlines, char *storage);
void writelines(char *lineptr[], int nlines);
int get_line(char s[], int lim);
/*Funciones de escritura y lectura*/

void my_qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *));
void swap(char *v[], int i, int j);
/*Algoritmo de ordenamiento (Quicksort)*/

int strcmp_fold(const char *s1, const char *s2);
int strcmp_d(const char *s1, const char *s2);
int strcmp_fold_d(const char *s1, const char *s2);
int numcmp(const char *s1, const char *s2);
int comp(const char *s1, const char *s2);
/*Funciones de comparaciones en base a flags*/

int is_valid_for_d(int c);

/*Protitpos de funciones*/


char *lineptr[MAXLINES];
int numeric = 0;
int reverse = 0;
int directory = 0;
int fold = 0;

int is_valid_for_d(int c) {
    return isalnum(c) || isspace(c);
}

int strcmp_d(const char *s1, const char *s2) {
    while (*s1 || *s2) {
        while (*s1 && !is_valid_for_d(*s1)) s1++;
        while (*s2 && !is_valid_for_d(*s2)) s2++;
        
        if (!*s1 && !*s2) return 0;
        if (!*s1) return -1;
        if (!*s2) return 1;
        
        if (*s1 != *s2) return *s1 - *s2;
        
        s1++;
        s2++;
    }

    return 0;
}


int strcmp_fold(const char *s1, const char *s2) {
    while (*s1 || *s2) {
        char c1 = tolower((unsigned char)*s1);
        char c2 = tolower((unsigned char)*s2);
        if (c1 != c2)
            return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

int strcmp_fold_d(const char *s1, const char *s2) {
    while (*s1 || *s2) {
        while (*s1 && !is_valid_for_d(*s1)) s1++;
        while (*s2 && !is_valid_for_d(*s2)) s2++;
        
        if (!*s1 && !*s2) return 0;
        if (!*s1) return -1;
        if (!*s2) return 1;
        
        char c1 = tolower(*s1);
        char c2 = tolower(*s2);
        
        if (c1 != c2) return c1 - c2;
        
        s1++;
        s2++;
    }
    return 0;
}

int numcmp(const char *s1, const char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

int comp(const char *s1, const char *s2) {
    int cmp;

    if (numeric)
        cmp = numcmp(s1, s2);
    else if (directory && fold)
        cmp = strcmp_fold_d(s1, s2);
    else if (directory)
        cmp = strcmp_d(s1, s2);
    else if (fold)
        cmp = strcmp_fold(s1, s2);
    else
        cmp = strcmp(s1, s2);

    return reverse ? -cmp : cmp;
}

int main(int argc, char *argv[]) {
    static char storage[MAXSTORAGE]; /* static: 5MB no cabe en el stack */
    int nlines;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            numeric = 1;
        else if (strcmp(argv[i], "-r") == 0)
            reverse = 1;
        else if (strcmp(argv[i], "-d") == 0)
            directory = 1;
        else if (strcmp(argv[i], "-f") == 0)
            fold = 1;
        else {
            fprintf(stderr, "Uso: %s [-n] [-r] [-d] [-f]\n", argv[0]);
            exit(1);
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
        my_qsort(lineptr, 0, nlines - 1, comp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: demasiada entrada para ordenar\n");
        return 1;
    }
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void my_qsort(char *v[], int left, int right, int (*comp)(const char *, const char *)) {
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (comp(v[i], v[left]) < 0)  
            swap(v, ++last, i);
    }
    swap(v, left, last);
    my_qsort(v, left, last - 1, comp);
    my_qsort(v, last + 1, right, comp);
}

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int readlines(char *lineptr[], int maxlines, char *storage) {
    int len, nlines = 0;
    char line[MAXLINES];
    char *p = storage;
    char *end = (storage + MAXSTORAGE) - 1;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > end) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}

int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c |= 0x20;
    }

    return c;
}
