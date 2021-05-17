#include <stdio.h>
#include <string.h>

int main() {
    int IniPalavra = 0, numPalavras = 0, numLinhas = 0, numLetras = 0;
    FILE *texto;
    char arquivo[50];
    char *letra;    
    printf("Digite o arquivo que deseja abrir: ");
    gets(arquivo);
    texto = fopen(arquivo, "r");
    while (!feof(texto)) {
          fread(letra, 1, 1, texto);
          numLetras++;
          if  ((*letra!=' ') && (*letra!='\n') && (!IniPalavra)) {
             IniPalavra = 1;
          }
          if  (((*letra==' ') || (*letra == '\n')) && (IniPalavra)) {
             IniPalavra = 0;
             numPalavras++;
          }
          if (*letra=='\n') {
             numLinhas++;
             }
   
   }           
   printf("\n Quantidade de palavras do arquivo eh: %d", numPalavras);
   printf("\n Quantidade de linhas do arquivo eh: %d", numLinhas);
   printf("\n Quantidade de letras do arquivo eh: %d", numLetras);
   getchar();
}