#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    int i, j, cont = 0, diamante;
    char n[1000];

    scanf("%d", &cont);

    while (cont--){
        scanf("%s", n);
        diamante = 0;
        for (i = 0; i < strlen(n); i++){
            if (n[i] == '\0')
                break;
            if (n[i] == '<'){
                for (j = i; j< strlen(n); j++){
                    if (n[j] == '>'){
                        diamante++;
                        n[j] = '0';
                        break;
                    }
                }
            }
        }
        printf("%d\n", diamante);
    }
}