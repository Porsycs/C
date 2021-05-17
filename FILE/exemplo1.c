#include <stdio.h>
#include <stdlib.h>
int main () {
  FILE *arq;
  char caracter, nomearq[15];
  printf ("Digite o nome do arquivo: ");
  gets (nomearq);
  if ((arq = fopen (nomearq, "r"))==NULL)
  	printf ("Problemas para abertura do arquivo.");
  else
    while (!feof(arq)) {
      caracter = getc(arq);
      printf ("%c",caracter);
    } 
  return 0;
}
