#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
  FILE *arq;
  int cont = 0;
  char caracter, texto[50],palavra[50],vogal[50];
  printf ("Digite o nome do arquivo: ");
  gets (texto);
  if ((arq = fopen (texto, "r"))==NULL) {
  	printf ("O arquivo nao foi encontrado.");
  }
  else {
   while ((caracter = getc(arq)) != EOF) {
     printf ("%c",caracter);
    }
}
printf("Digite o nome do arquivo para salvar as vogais: ");
gets(vogal);
if((arq = fopen(vogal, "r")) == NULL) {
    printf("O arquivo nao foi encontrado.");
}
else {
    printf("Passando as palavras com inicio vogal para o arquivo.");
    sleep(0.5);
    fprintf(vogal,"%c",caracter);
    }
}