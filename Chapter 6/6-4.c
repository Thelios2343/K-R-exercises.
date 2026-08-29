#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100

static char buf[BUFSIZE];
static int bufp = 0;

typedef struct Tnode {
    char *word;
    int cont;
    struct Tnode *left;
    struct Tnode *right;
} Tnode;

/* Funciones de analisis lexico */
int getch(void);
void ungetch(int c);
int getword(char *word, int lim);

/* Funciones del arbol binario */

Tnode *addtree(Tnode *ptt, char *word);
/* Funcion para imprimir de forma inversa al inorder para imprimir todo de forma descendente*/
void prinorder(Tnode *root);
void free_tree(Tnode *root);

int getch (void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch (int c) {
    if (bufp >= BUFSIZE) {
        printf("Error: Too Many Chars");
    } else {
        buf[bufp++] = c;
    }
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
        if (!isalnum(c)) {
            ungetch(c);
            break;
        }
        *w = c;
    }
    *w = '\0';
    return word[0];
}

Tnode *addtree(Tnode *ptt, char *word) {
    int cond;

    if (ptt == NULL) {
        ptt = malloc(sizeof(Tnode));
        if (ptt == NULL) {
            printf("Error: Memoria insuficiente\n");
            exit(1);
        }

        ptt -> word = strdup(word);
        if (ptt -> word == NULL) {
            printf("Error: Memoria insuficiente\n");
            exit(1);
        }
        ptt -> cont = 1;
        ptt -> left = ptt -> right = NULL;
    } else if ((cond = strcmp(ptt -> word, word)) == 0) {
        ptt -> cont++;
    } else if (cond > 0) {
        ptt -> left = addtree(ptt -> left, word);
    } else {
        ptt -> right = addtree(ptt -> right, word);
    }
    return ptt;
}

void prinorder(Tnode *root) {
    if (!root) {
        return;
    }
    prinorder(root -> right);
    printf("El Numero De Ocurrencias de la palabra: %s es de: %d veces\n", root -> word, root -> cont);
    prinorder(root -> left);
}

void free_tree(Tnode *root) {
    
    if (root == NULL) {
        return;
    }
    free_tree(root -> left);
    free_tree(root -> right);

    free(root -> word);
    free(root);
}

int main () {
    char word[MAXWORD];
    Tnode *root;
    int c;
    root = NULL;
    
     while ((c = getword(word, MAXWORD)) != EOF) {
        if (isalpha((unsigned char)word[0])) {
            root = addtree(root, word);
        }
    }

    prinorder(root);
    free_tree(root);
    return 0;
}




