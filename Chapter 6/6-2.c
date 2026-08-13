#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXARRAY 100
#define BUFSIZE 100000000
#define MAXWORD 1000

char buf[BUFSIZE];
int bufp = 0;

/* Node de linked list */
typedef struct node {
    char *word;
    struct node *next;
} node;

/* Node de arbol binario */

typedef struct tnode {
    char *base_word;
    node *nword;
    size_t count;
    struct tnode *left;
    struct tnode *right;
} tnode;


/* Funciones referentes al arbol binario */

tnode *addtree (tnode *p, char *w);
tnode *talloc (void);
void find (tnode *p, const char *w, size_t n);

/* Funciones para el manejo de nodos de la lista enlazada */
node *new_node(void);
void browse (node **p, const char *w );

/* Funciones referentes al lexer y clasificacion de palabras */
int getch(void);
void ungetch(int c);
int getword(char *word, int lim);
int getvar(char *s);

/* Funciones para el algoritmo merge sort */
node *merge(struct node *a, struct node *b);
void split(struct node *source, struct node **front, struct node **back);
node *mergesort(struct node *head);

/*funciones generales de impresion y liberacion de memoria*/
void print(tnode *p);
void print_words(node *l);
void free_all(tnode *p);
void free_list(node *l);

/* Array de strings para los tipos de variable.*/
const char* TIPOS_C[] = {
    "int", "char", "float", "double", 
    "void", "short", "long"
}; 



int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
} 

void ungetch(int c) {
    if (bufp >= BUFSIZE) 
        printf("Error: too many chars");

    else 
        buf[bufp++] = c;
}

/* Funcion para detectar alguna variable */
int getvar(char *s) {
    int n;
    int i;
    n = sizeof(TIPOS_C)/sizeof(TIPOS_C[0]);

    for (i=0; i < n; i++) {
        if(!strcmp(s, TIPOS_C[i])) {
            return 1;
        }
    }

    return 0;
}

int getword(char *s, int lim)
{
    int c, d;
    char *w;

    for (;;) {
        w = s;

        while (isspace((unsigned char)(c = getch())))
            ;

        if (c == EOF) {
            *s = '\0';
            return EOF;
        }

        if (c == '/') {
            if ((d = getch()) == '*') {
                while ((c = getch()) != EOF) {
                    if (c == '*' && (d = getch()) == '/')
                        break;
                    else if (d != EOF)
                        ungetch(d);
                }
                continue;  
            } else if (d == '/') {
                while ((c = getch()) != EOF && c != '\n')
                    ;
                continue;   
            } else {
                if (d != EOF)
                    ungetch(d);
            }
        }

        break;  
    }

    *w++ = c;
    /* Reservamos un char para el '\0' final desde ya */
    lim--;

    if (c == '"') {
        while ((c = getch()) != EOF && c != '"') {
            if (c == '\\') {
                getch();
            } else if (lim > 1) {
                *w++ = c;
                lim--;
            }
        }
    } else if (c == '\'') {
        while ((c = getch()) != EOF && c != '\'') {
            if (c == '\\') {
                getch();
            } else if (lim > 1) {
                *w++ = c;
                lim--;
            }
        }
    } else if (isalpha((unsigned char)c) || c == '_') {
        for ( ; --lim > 0; w++) {
            c = getch();
            if (!isalnum((unsigned char)c) && c != '_') {
                ungetch(c);
                break;
            }
            *w = c;
        }
    }

    *w = '\0';
    return s[0];
}


tnode *addtree(tnode *p, char *word) {
    int cond;

    if (p == NULL) {
        p = talloc();

        if (p == NULL) {
            /* Fallo de malloc: no seguimos construyendo el nodo */
            return NULL;
        }

        p -> base_word = strdup(word);
        if (p -> base_word == NULL) {
            free(p);
            return NULL;
        }
        p -> count = 1;
        p -> nword = NULL;
        p -> left = p -> right = NULL;
    } else if ((cond = strcmp(word, p -> base_word)) == 0) {
        p -> count++;
    } else if (cond < 0){
        p -> left = addtree(p -> left, word);
    } else {
        p -> right = addtree(p -> right, word);
    }
    return p;
}

tnode *talloc(void) {
    return malloc(sizeof(tnode));
}



/* funcion para buscar los grupos del arbol*/
void find (tnode *p, const char *w, size_t n) {
    if (p == NULL) {
        return;
    }

    if (strcmp(p -> base_word, w) != 0 && strncmp(p -> base_word, w, n) == 0) {
        browse(&(p -> nword), w);
        
        p -> nword = mergesort(p -> nword);
    }
    find (p -> left, w, n);
    find (p -> right, w, n);
}

node *new_node(void) {
    node *node = malloc(sizeof *node);
    return node;
}

/* funcion para buscar el final de los elementos de la linked list */

void browse (node **p, const char *w ) {
    node *q = *p;

    if (q == NULL) {
        *p = new_node();
        (*p) -> word = strdup(w);
        (*p) -> next = NULL;
        return;
    }

    while (q -> next != NULL) {
        q = q -> next;
    }

    q -> next = new_node();
    q -> next -> word = strdup(w);
    q -> next -> next = NULL;
}

struct node *merge(struct node *a, struct node *b)
{
    if (a == NULL)
        return b;

    if (b == NULL)
        return a;

    if (strcmp(a -> word, b -> word) <= 0) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

void split(struct node *source, struct node **front, struct node **back) {
    struct node *slow;
    struct node *fast;

    if (source == NULL || source->next == NULL) {
        *front = source;
        *back = NULL;
        return;
    }

    slow = source;
    fast = source -> next;

    while (fast != NULL) {
        fast = fast -> next;

        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;

    slow -> next = NULL;
}

struct node *mergesort(struct node *head) {
    struct node *a;
    struct node *b;

    if (head == NULL || head->next == NULL)
        return head;

    split(head, &a, &b);

    a = mergesort(a);
    b = mergesort(b);

    return merge(a, b);
}

void print_words(node *l) {
    while (l != NULL) {
        printf("%s\n", l -> word);
        l = l -> next;
    }
}

void print (tnode *p) {
    if (p == NULL) {
        return;
    }
    print(p -> left);

    printf("\nBase word of the group %s: ", p -> base_word);
    print_words(p -> nword);
    printf("\n");
    
    print(p -> right);

}

void free_list(node *p) {

    node *next;

    while (p != NULL) {
        next = p -> next;

        free (p -> word); 
        free (p);

        p = next;
    }
}

void free_all(tnode *p) {
    if (p == NULL) {
        return;
    }

    free_all(p -> left);
    free_all(p -> right);

    free_list(p -> nword);

    free(p -> base_word);
    free(p);
}

int main (int argc, char *argv[]) {
    
    int condition;
    int cond_input;
    tnode *root;
    char word[MAXWORD];
    int start_char;
    root = NULL;

     if (argc == 1) {
         cond_input = 6;
     }    

     else {
         cond_input = atoi(argv[1]);
         if (argc > 2) {
             printf("Use Of The Program %s: %s Number.", argv[0], argv[0]);
         }
     }

    if (cond_input < 0) {
        printf("Error: el numero debe ser >= 0\n");
        return 1;
    }
    condition = cond_input;

    while ((start_char = getword(word, MAXWORD)) != EOF) {        
        if (isalpha(start_char) || start_char == '_') {
            if (getvar(word) == 1) {
                int c;
                while ((c = getword(word, MAXWORD)) != EOF) {
                    if (isalpha(c) || c == '_') {
                        root = addtree(root, word);

                        
                        if (root == NULL) {
                            fprintf(stderr, "Error: memoria insuficiente\n");
                            return 1;
                        }

                        find(root, word, condition);
                    } else if (c == ',') {
                        continue;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    print(root);
    free_all(root);

    printf("\nAnalisis finalizado.\n");
    return 0;
}
