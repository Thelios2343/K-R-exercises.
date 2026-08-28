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

/* Variable global para obtener el numero de line */
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

/* Funciones del arbol binario */
Tnode *addtree(Tnode *node, char *word);
void walk_tree(Tnode *root, char *word);
void print_tree(Tnode *root);

/* Funciones de la linked list */
void brws_list(Lnode *node, int nl);
void print_list(Lnode *head);

/* Funciones Para liberar memoria */
void free_tree(Tnode *root);
void free_list(Lnode **head);

int getch(void) { 
    /* En caso de que la condicion de que el puntero del buffer sea mayot a 0 se retorna un caracter del buffer en caso de que no se toma el caracter de stdin mediante la funcion getchar*/
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Funcion para "desleer" caracteres. guardandolos en un buffer en caso de que se cumplan ciertas condiciones puestas por las funciones que llamen a esta funcion */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Error: Too Many Chars\n");
    } else {
        buf[bufp++] = c;
    }
}

/* Funcion para obtener la palabra*/
int getword(char *word, int lim) {
    int c;
    char *w = word;
    
    /* Esto es para saltar espacions */
    while (isspace(c = getch()))
        ;

    if (c != EOF) {
        *w++ = c;
    }

    if (!isalpha(c)) {
       *w = '\0';
       return c;
    }

    /* Este bloque hace varias cosas. primero evita desbordamientos leyendo solo el limite y restandolo en uno en cada iteracion deteniendose en el momento que lo supera, segundo si lo que hay en getch sea el caracter del buffer o stdin no es alfanumerico se guarda el caracter en el buffer y se detiene el condicional y se vuelve a repetir el bucle*/
    for (; --lim > 0; w++) {
        if(!isalnum(*w = getch())) {
            if (*w == '\n') {
                ++nol;
            }
            ungetch(*w);
            break;
        } 
    } 
    /* Se pone el \0 al finall y se retorna la palabra.*/
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

/* Funcion para agregar nodo al arbol binario (es una funcion sencilla. no trata con cosas como autobalanceo aun) en base a la condicion si son mayores o menores en la busqueda al arbol binario */
Tnode *addtree(Tnode *node, char *word) {
    int cond;
    
    if (node == NULL) {
        node = malloc(sizeof(Tnode));
        node -> word = strdup(word);
        node -> left = node -> right = NULL;
    } else if ((cond = strcmp(word, node -> word)) == 0) {
        return 0;
    } else if (cond < 0) {
        node -> left = addtree(node -> left, word);
    } else {
        node -> right = addtree(node -> right, word);
    }
    return node;
}

/* Funcion para recorrer el arbol buscando coincidencias de palabras. en caso de que el nodo se encuentre NULL se llama ra a la funcion addtree para agragar un nuevo nodo al arbol. en caso de que si se encuentre se llamara a la funcion brows_list para que inserte un nuevo nodo a la lista enlazada */
void walk_tree(Tnode *root, char *word) {
    int cond;
    if (root == NULL) {
        addtree(root, word);
        walk_tree(root, word);
    } else {
    if ((cond = strcmp(word, root -> word)) == 0) {
        brws_list(root -> nlines, nol);
    } else if (cond < 0) {
        walk_tree(root -> left, word);
    } else {
        walk_tree(root -> right, word);
    }
    }
} 

/* en esta funcion recorremos toda la lista enlazada e insertamos el numero de linea al final */
void brws_list(Lnode *node, int nl) {
    Lnode *new = malloc(sizeof(Lnode));
    if (new == NULL) {
        return;
    }
    new -> nline = nl;
    new -> next = NULL;
    while (node -> next != NULL) {
        node = node -> next;
    } 
    if (node -> nline == new -> nline) {
        free(new);
        return;
    }
    node -> next = new;
}

void free_tree(Tnode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root -> left);
    free_tree(root -> right);

    free(root -> word);
    free_list(&root -> nlines);    
    free(root);
}

void free_list(Lnode **head) {
    Lnode *current = *head;
    while (current != NULL) {
        Lnode *next = current -> next;
        free (current);
        current = next;
    }
    *head = NULL;
}

void print_tree(Tnode *root) {
    if (root != NULL) {
        print_tree(root -> left);
        printf("%s\n", root -> word);
        print_list(root -> nlines);
        print_tree(root -> right);
    }
}

void print_list(Lnode *head) {
    while (head -> next != NULL) {
        printf ("%4d", head -> nline);
        head = head -> next;
    }
}


int main (){ 
    char word[MAXWORD];
    Tnode *root;
    root = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (!getstop(word)) {
            walk_tree(root, word);
        } else {
            break;
        }
    }
    print_tree(root);
    free_tree(root);

    return 0;
}
