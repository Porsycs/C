#include <stdio.h>

struct produto {
    int codigo;
    char descricao[20];
    float preco;
};

int main () {
    struct produto Produto;
    FILE *arq;
    int ch,loop;
    do {
        printf("\n1- Caso deseje criar um novo arquivo de produtos\n2- Caso deseje alterar ou pesquisar em um arquivo ja existente\nResposta: ");
        scanf("%d",&ch);
        switch(ch) {
            case 1: // Criação de um novo produto.dat
                arq = fopen("produtos.dat","wb");
                fseek(arq,0,SEEK_END);
                do {
                    printf("\nCodigo do produto:");
                    scanf("%d",&Produto.codigo);
                    printf("Descricao do produto:");
                    scanf("%s",&Produto.descricao);
                    printf("Preco do produto:");
                    scanf("%f",&Produto.preco);
                    printf("\nCadastrar mais produtos? 1- Sim 2- Nao\nResposta:");
                    scanf("%d",&loop);
                }while(loop==1);
                fclose(arq);
                break;

            case 2:
                printf("\n1- Caso deseje alterar o arquivo\n2- Caso queira pesquisar produtos\nResposta: ");
                scanf("%d",&ch);
                switch(ch) {
                    case 1: //Alterar preço de arquivo ja existente
                        arq = fopen("produtos.dat","a+b");
                        do {
                            printf("\nDigite o codigo do produto para alterar: ");
                            scanf("%d",&Produto.codigo);
                            if(Produto.codigo != NULL) {
                                printf("De o novo valor do produto: ");
                                scanf("%f",&Produto.preco);
                                printf("\n\nDeseja alterar mais algum valor? 1- Sim 2- Nao\nResposta: ");
                                scanf("%d",&loop);
                                }
                            }while(loop == 1);
                        printf("\n\nCodigo: %d Novo Valor: %.2f",Produto.codigo,Produto.preco);
                        break;
                    case 2: //Apenas analize do arquivo já existente
                        arq = fopen("produtos.dat","rb");
                        printf("\nCodigo: %d Preco: %.2f",Produto.codigo,Produto.preco);
                        printf("\n\n\t\t\tProdutos com valor superior a R$500:\n\n");
                        if(Produto.preco > 500) {
                            printf("Codigo: %d Preco: %.2f",Produto.codigo,Produto.preco);
                        }
                        break;
                }
                fclose(arq);
                break;
            default: //Caso nao seja 1 ou 2
                printf("Opcao invalida tente novamente\n");
                fclose(arq);
                }

    printf("\nDeseja refazer alguma operacao? 1- Sim 2- Nao\nResposta: ");
    scanf("%d",&ch);
    } while(ch == 1);
    fclose(arq); //Fechamento do arquivo
    getch();
    return 0;
}