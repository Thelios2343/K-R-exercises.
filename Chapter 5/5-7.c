#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORAGE (MAXLINES * MAXLEN)

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *storage);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int get_line(char s[], int lim);

int main() {
    char storage[MAXSTORAGE];
    char *lineptr[MAXLINES];
    char *pruebas[] = {
        "Alo",
        "Bao",
        "Cap",
        "lucho",
        "kerry",
        "nice",
        "i hate Cpp"
    };

    int nlines = sizeof(pruebas) / sizeof(pruebas[0]);
    char *p = storage;

    for (int i = 0; i < nlines; i++) {
        strcpy(p, pruebas[i]);
        lineptr[i] = p;
        p += strlen(pruebas[i]) + 1;  
    }

    printf("Antes de ordenar:\n");
    writelines(lineptr, nlines);

    qsort(lineptr, 0, nlines - 1);

    printf("\nDespues de ordenar:\n");
    writelines(lineptr, nlines);

    return 0;
}

int readlines(char *lineptr[], int maxlines, char *storage) {
    int len, nlines = 0;
    char line[MAXLINES];
    char *p = storage;
    char *end = (storage + MAXSTORAGE) - 1;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > end) {
            return -1;
        }
        else {
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

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++){
        s[i] = c;
    }
     
    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
} 

void writelines(char *lineptr[], int nlines) {
    while (nlines -- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++){
        if (strcmp(v[i], v[left]) < 0){
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
