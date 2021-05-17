#include <stdio.h>

int i;

void CountSort(int vetor[], int n) {
  	int vetor1[10];

  	int aux = vetor[0];
  	for (i = 1; i < n; i++) {
    	if (vetor[i] > aux)
      		aux = vetor[i];
  }

  
  	int contavet[10];

  	for (i = 0; i <= aux; ++i) {
    	contavet[i] = 0;
  }

  	for (i = 0; i < n; i++) {
    	contavet[vetor[i]]++;
  }

  	for (i = 1; i <= aux; i++) {
    	contavet[i] += contavet[i - 1];
  }

 
  	for (i = n - 1; i >= 0; i--) {
    	vetor1[contavet[vetor[i]] - 1] = vetor[i];
    	contavet[vetor[i]]--;
  }

  	for (i = 0; i < n; i++) {
    	vetor[i] = vetor1[i];
  }
}

void printar(int vetor[], int n) {
  	for (i = 0; i < n; ++i) {
    	printf("%d  ", vetor[i]);
  }
  
}

int main() {
	int x;
	int vetor[x], tam;
	for (x = 1; x <= tam; x++) {
		scanf("%d",&vetor[x]);
		printf("Vetor original: ",vetor[x]);
	}
  	int n = sizeof(vetor) / sizeof(vetor[0]);
  	CountSort(vetor, n);
  	printar(vetor, n);
}
