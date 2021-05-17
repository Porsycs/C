#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int c;

struct Estoque {
    int codigo;
    char nome[50];
    char data[10];
    int quantAtual;
    struct Estoque *prox;
}; typedef struct Estoque estoque;

int vazia(estoque *le) {
    if(le->prox == NULL){
        return 1;
    }
    else {
        return 0;
    }
}
void lerArq(estoque *le) {
    FILE *arq;
    arq = fopen("arquivo.txt","rb"); // Apenas para leitura e se o arquivo existir
    if(arq == NULL) {
        printf("O arquivo nao existe!");
    }
    else {
    char ch;
    estoque *tmp;
    tmp = le->prox;
    while((ch=fgetc(arq))!= EOF) {
        putchar(ch);
        tmp = tmp->prox;
        fclose(arq);
        }
    }
    printf("\n\n");
}

void insereInicio(estoque *le) {
    int n;
    printf("Quantos produtos deseja cadastrar? ");
    scanf("%d",&n);
    struct Estoque estq[n];
    FILE *arq;
    arq = fopen("arquivo.txt","a+b");
        if(arq == NULL) {
            printf("Nao foi possivel criar o arquivo!");
        }
        estoque *novo = (estoque*)malloc(sizeof(estoque));
       // struct Estoque input = {101010, "BATATA", "29/01/1998", 10};
       // fwrite(&input, sizeof(struct Estoque), 1, arq);
        /*printf("Informe o codigo: ");
        fwrite(&novo->codigo,sizeof(int), 10, arq);
        printf("Informe o nome: ");
        fwrite(&novo->nome, sizeof(char), 50, arq);                 //Input pulando (?)
        fprintf(arq,"%s",&novo->nome);
        printf("Informe a data: ");
        scanf("%s", &novo->data);
        fwrite(&novo->data, sizeof(char), 10, arq);
        printf("Informe a quantidade: ");
        fwrite(&novo->quantAtual, sizeof(int), 100, arq);*/
        for (int i = 0; i < n; i++) {
            printf("Digite o codigo do produto: ");
            fflush(stdin);
            scanf("%d",&estq[i].codigo);
            printf("Digite o nome do produto: ");
            fflush(stdin);
            gets(estq[i].nome);
            printf("Digite a data atual: ");
            fflush(stdin);
            gets(estq[i].data);
            printf("Digite a quantidade atual do produto: ");
            fflush(stdin);
            scanf("%d",&estq[i].quantAtual);

        }
        fwrite(estq,sizeof(struct Estoque),3,arq);
        printf("Dados salvos");
        estoque *oldHead = le->prox;
        le->prox = novo;
        novo->prox = oldHead;
        fclose(arq);
    }

/*void removeFim(estoque *le) {
    aux = estoque;
    if (aux == NULL) {
        printf("A lista esta vazia");
    }
    else {
        if (estoque->prox == NULL) {
    free(estoque);
    return NULL;
   }
   else {
    while (aux->prox->prox != NULL) {
        aux = aux->prox;
     }
     free(aux->prox);
     aux->prox = NULL;
        }
    }
}*/
void dispestq(estoque *le) {
    FILE *arq;
    arq = fopen("arquivo.txt","rb");
    estoque *p;
    if(arq == NULL) {
        printf("Nao foi possivel abrir o arquivo");
    }

    }
void opcao(estoque *le, int op) {
    switch(op) {
        case 0:
            return 0;
            break;
        case 1:
            lerArq(le);
            break;
        case 2:
            insereInicio(le);
            break;
        case 3:
           // removeFim(le);
            break;
        case 4:
            dispestq(le);
            break;
        case 5:
            break;
        default:
            printf("\nOpcao invalida");

    }
}

int main() {
    estoque *le = (estoque*)malloc(sizeof(estoque));
    int op;
    do {
        printf("\nDigite uma das opcoes: \n0-Sair\n1-Ler o arquivo\n2-Adicionar itens ao inicio do arquivo\n3-Remover o ultimo elemento do arquivo\n4-Produtos disponiveis em estoque\n5-Produtos iniciados em consoante");
        printf("\nOpcao: ");
        scanf("%d",&op);
        opcao(le, op);
    }while(op);
    free(le);
    return 0;
}
