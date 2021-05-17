#include <stdio.h>

int fibo(int n) {
 if (n == 0) return 0;
 if (n == 1) return 1;
 return fibo(n - 1) + fibo(n - 2);
}


int main() {
	int n,f;
	printf("Digite o numero para calcular em Fibonacci: ");
	scanf("%d",&n);
	f = fibo(n);
	printf("\nNumero %d em Fibonacci: %d",n,f);
}
