#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORAGE (MAXLINES * MAXLEN)

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *storage);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *));
int get_line(char s[], int lim);
void swap(char *v[], int i, int j);
int strcmp_fold(const char *s1, const char *s2);
int tolower(int c);


int strcmp_fold(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = tolower((unsigned char)*s1);
        char c2 = tolower((unsigned char)*s2);
        if (c1 != c2)
            return c1 - c2;
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

int main(int argc, char *argv[]) {
    char storage[MAXSTORAGE];
    char *lineptr[MAXLINES];
    char *pruebas[] = {
        "Alo",
        "cao",
        "baaosda",
        "hola",
        "Zor"
    };
    int nlines = sizeof(pruebas) / sizeof(pruebas[0]);
    char *p = storage;
    int reverse = 0;
    int fold = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        }
        if (strcmp(argv[i], "-f") == 0) {
            fold = 1;
        }
    }

    for (int i = 0; i < nlines; i++) {
        strcpy(p, pruebas[i]);
        lineptr[i] = p;
        p += strlen(pruebas[i]) + 1;
    }

    printf("Antes de ordenar:\n");
    writelines(lineptr, nlines);

    int (*comp)(const char *, const char *);
    if (fold) {
        comp = strcmp_fold;
        printf("\nOrdenando ignorando mayúsculas/minúsculas (-f)...\n");
    } else {
        comp = strcmp;
        printf("\nOrdenando normalmente...\n");
    }

    qsort(lineptr, 0, nlines - 1, comp);

    if (!reverse) {
        printf("\nDespues de ordenar:\n");
        writelines(lineptr, nlines);
    } else {
        printf("\nDespues de ordenar de forma descendente (-r):\n");
        for (int i = nlines - 1; i >= 0; i--) {
            printf("%s\n", lineptr[i]);
        }
    }

    return 0;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void qsort(char *v[], int left, int right, int (*comp)(const char *, const char *)) {
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
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
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
