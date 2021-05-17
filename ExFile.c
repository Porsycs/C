#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

int x;
char aux[50];

 struct cliente {
    int nconta;
    char nome[30];
    float saldo;
    char data[30];
    };
int main() {
    struct cliente Cliente;
    FILE *ficha;
    if((ficha = fopen("ficha.dat","r+b")) == NULL) {
    if((ficha = fopen("ficha.dat","wb")) == NULL) {
    printf("Erro!");
    exit(1);
        }
    }
    fseek(ficha,0,SEEK_END);
    printf("\t\t\tCadastramento de cliente:\n\n");
    do {
    printf("Numero da conta: ");
    gets(aux);
    Cliente.nconta  = atoi(aux);
    printf("\nNome do cliente: ");
    gets(Cliente.nome);
    printf("\nSaldo: ");
    gets(aux);
    Cliente.saldo = atof(aux);
    printf("\nData de operacao(Ex 19/10/2020): ");
    gets(Cliente.data);
    fwrite(&Cliente, sizeof(Cliente), 1, ficha);
    printf("\nDeseja adicionar mais contas?\n1-Sim\n2-Nao\n\n");
    printf("Resposta: ");
    scanf("%d",&x);
    printf("\n");
    } while(x == 1);
     fclose(ficha);
     ficha = fopen("ficha.dat","rb");
    while (fread(&Cliente, sizeof(Cliente), 1, ficha) == 1) {
        rewind(ficha);
        printf ("\n Numero da conta: %d ", Cliente.nconta);
        printf ("\n Nome do cliente: %s", Cliente.nome);
        printf ("\n Saldo: %.2f",Cliente.saldo);
        printf("\n Data: %s",Cliente.data);
    }
    fclose(ficha);
    ficha = fopen("ficha.dat","rb");
    while(fread(&Cliente, sizeof(Cliente),1, ficha) == 1) {
        if(Cliente.saldo < 0) {
            printf("\t\t\tPessoas com saldo negativo:\n\n ");
            printf("Nome: %s",Cliente.nome);
        }
    }
    fclose(ficha);
    return 0;
}