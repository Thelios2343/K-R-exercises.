#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 100


/* node del arbol binario */
typedef struct Tnode {
    char *word;
    struct Lnode *nlines;
    struct Tnode *left;
    struct Tnode *right;
} Tnode;

/* node de la linked list */
typedef struct Lnode {
    int nline;
    struct Lnode *next;
} Lnode;

/* Variables globales compartidas para el buffer de getch y ungetch */
static int buf[BUFSIZE];
static int bufp = 0;

/* Variable global para obtener el numero de linea */
static int nol = 0;

/* Variable con todas las "stop words" en idioma spanish */
const char *stop_words[] = {
    "a", "acá", "ahí", "al", "algo", "alguien", "algún", "alguna", "algunas",
    "alguno", "algunos", "allá", "allí", "ambos", "ante", "antes", "aquel",
    "aquella", "aquellas", "aquello", "aquellos", "aquí", "arriba", "así",
    "atrás", "aun", "aunque", "bien", "cabe", "cada", "casi", "cierto",
    "cierta", "ciertos", "ciertas", "como", "con", "conmigo", "conseguimos",
    "conseguir", "consigo", "consigue", "consiguen", "consigues", "contigo",
    "contra", "cual", "cuales", "cualquier", "cualquiera", "cualquieras",
    "cuán", "cuando", "cuanta", "cuánta", "cuantas", "cuántas", "cuanto",
    "cuánto", "cuantos", "cuántos", "de", "dejar", "del", "demás", "demasiada",
    "demasiadas", "demasiado", "demasiados", "dentro", "desde", "donde", "dos",
    "el", "él", "ella", "ellas", "ello", "ellos", "en", "encima", "entonces",
    "entre", "era", "eras", "eramos", "eran", "eres", "es", "esa", "esas",
    "ese", "eso", "esos", "esta", "está", "estaba", "estaban", "estado",
    "estamos", "están", "estar", "estas", "éstas", "este", "éste", "esto",
    "estos", "éstos", "estoy", "ex", "fue", "fueron", "fui", "fuimos", "ha",
    "hace", "hacen", "hacer", "hacia", "hago", "hasta", "hay", "incluso",
    "intenta", "intentas", "intento", "ir", "la", "las", "le", "les", "lo",
    "los", "luego", "me", "menos", "mi", "mía", "mías", "mientras", "mío",
    "míos", "mis", "misma", "mismas", "mismo", "mismos", "modo", "mucho",
    "muchos", "muy", "nada", "ni", "ningún", "ninguna", "ningunas", "ninguno",
    "ningunos", "no", "nos", "nosotras", "nosotros", "nuestra", "nuestras",
    "nuestro", "nuestros", "nunca", "o", "os", "otra", "otras", "otro",
    "otros", "para", "parecer", "pero", "poca", "pocas", "poco", "pocos",
    "podéis", "podemos", "poder", "podría", "podrías", "podríais",
    "podríamos", "podrían", "por", "por qué", "porque", "primero", "puede",
    "pueden", "puedo", "pues", "que", "qué", "querer", "quién", "quienes",
    "quienesquiera", "quienquiera", "quizá", "quizás", "sabe", "sabes",
    "saben", "sabemos", "saber", "se", "según", "ser", "si", "sí", "siempre",
    "siendo", "sin", "sino", "so", "sobre", "sois", "solamente", "solo",
    "sólo", "somos", "soy", "su", "sus", "suya", "suyas", "suyo", "suyos",
    "tal", "tales", "también", "tampoco", "tan", "tanta", "tantas", "tanto",
    "tantos", "te", "tener", "tiempo", "tiene", "tienen", "toda", "todas",
    "todo", "todos", "tomar", "trabaja", "trabajo", "tras", "tú", "tu", "tus",
    "tuya", "tuyas", "tuyo", "tuyos", "último", "un", "una", "unas", "uno",
    "unos", "usa", "usas", "uso", "usted", "ustedes", "va", "van", "vais",
    "valor", "vamos", "varias", "varios", "vaya", "verdad", "verdadera",
    "verdadero", "vez", "vosotras", "vosotros", "voy", "vuestra", "vuestras",
    "vuestro", "vuestros", "y", "ya", "yo"
};

/* Variable con el numero de elementos del arreglo de strings */
const int num_stop_words = sizeof(stop_words)/sizeof(stop_words[0]);


/* Funciones del analisis lexico */
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
int getstop(char *s);

/* Funciones del arbol binario (addtree ahora inserta y busca. se elimino walk_tree*/
Tnode *addtree(Tnode *node, char *word, int line);
void print_tree(Tnode *root);

/* Funciones de la linked list */
void add_line(Lnode *head, int line);
void print_list(Lnode *head);

/* Funciones para liberar memoria */
void free_tree(Tnode *root);
void free_list(Lnode **head);

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Error: Too Many Chars\n");
    } else {
        buf[bufp++] = c;
    }
}

/* Funcion para obtener la palabra */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    /* Saltar espacios/saltos de linea, contando cada '\n' */
    while (isspace(c = getch())) {
        if (c == '\n') {
            ++nol;
        }
    }

    if (c != EOF) {
        *w++ = c;
    }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

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

/* Funcion para evaluar si una palabra es alguna stop word */
int getstop(char *word) {
    int i;
    for (i = 0; i < num_stop_words; i++) {
        if (strcmp(word, stop_words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/* Inserta o busca 'word' en el arbol y registra la linea 'line' donde aparece.
   Devuelve la raiz (posiblemente nueva) del (sub)arbol -> el llamador SIEMPRE
   debe reasignar: root = addtree(root, word, nol); */
Tnode *addtree(Tnode *node, char *word, int line) {
    int cond;

    if (node == NULL) {
        node = malloc(sizeof(Tnode));
        node->word = strdup(word);
        node->nlines = malloc(sizeof(Lnode));
        node->nlines->nline = line;
        node->nlines->next = NULL;
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) == 0) {
        add_line(node->nlines, line);   /* palabra ya existe: solo agregar linea */
    } else if (cond < 0) {
        node->left = addtree(node->left, word, line);
    } else {
        node->right = addtree(node->right, word, line);
    }
    return node;
}

/* Agrega 'line' al final de la lista si no es igual a la ultima registrada
   (evita duplicar la misma linea cuando la palabra aparece varias veces
   seguidas en la misma linea) */
void add_line(Lnode *head, int line) {
    Lnode *new = malloc(sizeof(Lnode));
    if (new == NULL) {
        return;
    }
    new->nline = line;
    new->next = NULL;

    while (head->next != NULL) {
        head = head->next;
    }
    if (head->nline == new->nline) {
        free(new);
        return;
    }
    head->next = new;
}

void free_tree(Tnode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);

    free(root->word);
    free_list(&root->nlines);
    free(root);
}

void free_list(Lnode **head) {
    Lnode *current = *head;
    while (current != NULL) {
        Lnode *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void print_tree(Tnode *root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("%s:", root->word);
        print_list(root->nlines);
        print_tree(root->right);
    }
}

void print_list(Lnode *head) {
    while (head != NULL) {
        printf("%4d", head->nline);
        head = head->next;
    }
    printf("\n");
}


int main(void) {
    char word[MAXWORD];
    Tnode *root = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha((unsigned char)word[0]) && !getstop(word)) {
            root = addtree(root, word, nol);
        }
    }

    print_tree(root);
    free_tree(root);

    return 0;
}
