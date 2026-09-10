#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 100
#define TABSIZE 100
#define HASHSIZE 101

static char buf[BUFSIZE];
int bufp = 0;

/* Struct para guardar las macros del preprocesador */
typedef struct nlist {
    char *name;
    char *defn;
    struct nlist *next;
} nlist;

/* Arreglo de apuntadores a structs */
static struct nlist *hashtab[TABSIZE]; 

/* Funciones de manejo lexico */
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
int isdefine(char *s);

/* Funciones de la busqueda e instalacion por tablas */
unsigned hash(const char *s);
nlist *install(const char *name, const char *defn);
nlist *lookup(const char *s);
void undef(const char *s);
void free_list(nlist **head);

unsigned hash(const char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}


int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Error: too many chars\n");
        return;
    } else {
        buf[bufp++] = c;
    }
}
 
int isdefine(char *s) {
    if (strcmp(s, "define") == 0) {
        return 1;
    }
    return 0;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c == EOF) {
        word[0] = '\0';
        return EOF;
    }

    if (!isalpha(c)) {
        word[0] = c;
        word[1] = '\0';
        return c;
    }
    *w++ = c;

    for (; --lim > 0; w++) {
        c = getch();
        if (!isalpha(c)) {
            ungetch(c);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}

nlist *lookup(const char *s) {
    nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np -> next) {
        if (strcmp(s, np -> name) == 0) {
            return np;
        };
    } 
    return NULL;
}

nlist *install(const char *name, const char *defn) {
    nlist *np;

    if((np = lookup(name)) == NULL) {
        np = malloc(sizeof(nlist));
        if (np == NULL) {
            return NULL;
        } else if ((np -> name = strdup(name)) == NULL) {
            return NULL;
        }
        np -> next = hashtab[hash(name)];
        hashtab[hash(name)] = np;
    } else {
        free(np -> defn);
    } if ((np -> defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
} 

void free_list(nlist **head) {
    nlist *current = *head;
    while (current != NULL) {
        nlist *next = current -> next;
        free(current);
        current = next;
    } 
} 

void undef(const char *s) {
    nlist *p;
    p = lookup(s);
    if (p != NULL) {
        free(p -> name);
        free(p -> defn);
        free_list(&p -> next);
        free(p);
    } 
    return;
} 

int main() {
    nlist *p;
    char word[MAXWORD];
    char *tmp;
    while(getword(word, MAXWORD) != EOF)  {
        if (isalpha((unsigned char)word[0]) && isdefine(word)) {
            getword(word, MAXWORD);
            tmp = strdup(word);
            getword(word, MAXWORD);
            install(tmp, word);
            free(tmp);
            tmp = NULL;
        } 
    }
    p = lookup("hola");
    printf("Se ha encontrado tu macro de nombre: %s con la definicion: %s ", p -> name, p -> defn); 
    undef("hola");
    return 0;
}
