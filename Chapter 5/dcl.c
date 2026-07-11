#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 1000

enum { NAME, PARENS, BRACKETS, CONST, VOLATILE };

void dcl(void);
void dirdcl(void);
int gettoken(void);

int tokentype;          
char token[MAXTOKEN];   
char name[MAXTOKEN];    
char datatype[MAXTOKEN]; 
char out[1000];         

int main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);  
        out[0] = '\0';
        
        dcl();
        
        if (tokentype != '\n')
            printf("error: se esperaba nueva línea\n");
        
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void) {
    int ns;
    
    for (ns = 0; gettoken() == '*'; ns++)
        ;
    
    dirdcl();
    
    while (ns-- > 0)
        strcat(out, " puntero a");
}

void dirdcl(void) {
    int type;
    
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: falta )\n");
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("error: se esperaba nombre o (dcl)\n");
    }
    
    while ((type = gettoken()) == PARENS || type == BRACKETS || 
           type == CONST || type == VOLATILE) {
        if (type == PARENS)
            strcat(out, " funcion que devuelve");
        else if (type == BRACKETS) {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " de");
        } else if (type == CONST) {
            strcat(out, " const");
        } else if (type == VOLATILE) {
            strcat(out, " volatile");
        }
    }
}

int gettoken(void) {
    int c;
    char *p = token;
    
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    
    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            strcpy(token, "(");
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (c == '*') {
        token[0] = c;
        token[1] = '\0';
        return tokentype = '*';
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        
        if (strcmp(token, "const") == 0)
            return tokentype = CONST;
        else if (strcmp(token, "volatile") == 0)
            return tokentype = VOLATILE;
        else
            return tokentype = NAME;
    } else {
        token[0] = c;
        token[1] = '\0';
        return tokentype = c;
    }
}
