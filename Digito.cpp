#include <stdio.h>

int digitos(int n) {
	if (n <= 9) return 1;
	return digitos(n /10);
}

int main () {
	int n,digito;
	printf("De um digito:");
	scanf("%d",&n);
	digito = digitos(n);
	printf("\nA contagem eh: %d",digito);
}
