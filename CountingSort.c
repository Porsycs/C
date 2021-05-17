//Counting Sort funciona apenas para numeros inteiros e positivos, pouco eficiente para numeros muito grandes por causa do espaçamento entre eles e o acrescimo de 0s
#include <stdio.h>

//Escopo Global
int i;

void CountSort(int vet[], int tam) {
  int output[100]; //Tamanho limite
  int max = vet[0];
  for (i = 1; i <= tam; i++) {
    if (vet[i] > max)
      max = vet[i];
  }

  int Count[100]; //Contagem limite
  
  //A contagem começando do 0
  for (i = 0; i <= max; ++i) {
    Count[i] = 0;
  }

  //A partir do 0, ir adicionando ++ para cada elemento do vetor caso numero repitido vai 2, 3, 4 e assim por diante
  for (i = 0; i < tam; i++) {
    Count[vet[i]]++;
  }

  //Somar a posição 1 do vetor com a 2, depois a soma da 2 com a 3...
  for (i = 1; i <= max; i++) {
    Count[i] += Count[i - 1];
  }

  //Arruma a posição antiga do vetor na nova arrumada
  for (i = tam - 1; i >= 0; i--) {
    output[Count[vet[i]] - 1] = vet[i];
    Count[vet[i]]--;
  }

  //Coloca os elementos arrumados no vetor
  for (i = 0; i < tam; i++) {
    vet[i] = output[i];
  }
  
}

void MostraVet(int vet[], int tam) {
  printf("Vetor Arrumado: ");
  for (i = 0; i < tam; ++i) {
    printf("%d  ", vet[i]);
  }
  
}

int main() {
  int vet[] = {6, 9, 9, 10, 2, 2, 2, 1, 4}; //Vetor genérico para teste
  int n = sizeof(vet) / sizeof(vet[0]);
  CountSort(vet, n);
  MostraVet(vet, n);
}
