#include <stdio.h>

void reverse_rec(char *inicio, char *final);
void reverse(char *s);

int main() {
   char s[100];
   printf("\nIntroduzca la cadena a invertir: ");
   fgets(s, sizeof(s), stdin);
   reverse(s);
   printf("\nTu cadena invertida es: %s", s);

} 

void reverse_rec(char *inicio, char *final) {
    
    char temp;

    if (inicio >= final) {
        return;
    }

    temp = *inicio;
    *inicio = *final;
    *final = temp;

    reverse_rec(inicio + 1, final - 1);
}

void reverse(char *s) {
   
    char *fin = s;

    while (*fin != '\0') {
        fin ++;
    }
    fin --;

    reverse_rec(s, fin);

}
