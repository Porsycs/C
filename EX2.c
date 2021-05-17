#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
  FILE *arq;
  int cont = 0;
  char caracter, texto[50],palavra[50];
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
printf("Digite a palavra que procura no texto: ");
gets(palavra);
if(palavra == caracter) {
    cont++;
    }
printf("O numero de vezes que a palavra '%s' se repete eh: %d",palavra, cont);
fclose(arq);
return 0;
}
