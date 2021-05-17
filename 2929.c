#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct No {
	long numero;
	struct No *proximo;
} No;

typedef struct Pilha {

	No *topo;
} Pilha;


void pop(Pilha *pilha);
void criaPilha(Pilha *pilha);
long menorPilha(Pilha *pilha);
void push(Pilha *pilha, long numero);

void main () {
	Pilha pilha;
	char operacao[10];
	unsigned numOperacoes;
	long numero, tmp;

	scanf("%u", &numOperacoes);

	criaPilha(&pilha);

	while (numOperacoes--) {
		scanf("%s", operacao);

		if (strcmp(operacao, "PUSH") == 0) {
			scanf("%ld", &numero);
			push(&pilha, numero);
		}
		else if (strcmp(operacao, "POP") == 0) {
			pop(&pilha);
        }
		else {
			tmp = menorPilha(&pilha);
			if (tmp == -1)
				printf("EMPTY\n");
			else
				printf("%ld\n", tmp);
		}
	}
}
void criaPilha(Pilha *pilha) {
	pilha->topo = NULL;
}
void push(Pilha *pilha, long numero) {
	No *aux;

	aux = (No *) malloc(sizeof(No));

	if (!aux)
		exit(1);

	aux->proximo = pilha->topo;
	pilha->topo = aux;
	aux->numero = numero;
}

void pop(Pilha *pilha) {
	No *aux;
	aux = pilha->topo;

	if (aux) {
		pilha->topo = aux->proximo;
		free(aux);
	}
	else 
		printf("EMPTY\n");
}
long menorPilha(Pilha *pilha) {
	No *aux;
	aux = pilha->topo;

	if (!aux)
		return -1;

	long menor = aux->numero;

	while (aux) {
		if (aux->numero < menor)
			menor = aux->numero;

		aux = aux->proximo;
	}
	return menor;
}