#include <stdio.h>
//Teste de FILE
int main() {
    FILE *arq;
        arq = fopen("exemplo.dat","wb"); 
        if(arq == NULL) {
            printf("Erro na abertura do arquivo!");
        }
        else
        {
            printf("Sucesso na abertura!");
        }
        
}