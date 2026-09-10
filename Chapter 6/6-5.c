#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

typedef struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
} nlist;

static nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++ ) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE; 
}

nlist *lookup(char *s) {
    nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np -> next) {
        if (strcmp(s, np -> name) == 0) {
            return np;
        }
    }
    return NULL;
}

nlist *install(char *name, char *defn) {
    nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(nlist));
        if (np == NULL || (np -> name = strdup(name)) == NULL) {
            return NULL;
        } 
        hashval = hash(name);
        np -> next = hashtab[hashval];
        hashtab[hashval] = np;
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
    *head = NULL;
}

void undef (char *s) {
    nlist *np = lookup(s);
    if (strcmp(s, np -> name) == 0) {
        free(np -> name);
        free(np -> defn);
        free_list(&np -> next);
        free(np);
        np = NULL;
        return;
    }
    return;
}


int main () {
    nlist *tab;
    tab = NULL;
    char hola[7] = "define";
    char defn[5] = "hola";

    tab = install(hola, defn); 
    printf("%s\n%s\n", tab -> name, tab -> defn);
    undef(hola);
    tab = NULL;
    printf("Se libero la tabla correctamente\n");
    return 0;
}


























































































































































































































































































































































































































































































































































