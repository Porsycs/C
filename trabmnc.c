/*
 
Felipe Correa RA:
Lucca Bibar RA:
Lucas Bertoni RA:
Victor Bueno RA:

*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAXSIZE 100

float coeficiente[MAXSIZE][MAXSIZE];
float Dinv[MAXSIZE][MAXSIZE];
float approx[MAXSIZE][1];
float R[MAXSIZE][MAXSIZE];
float matrizRes[MAXSIZE][1];
float b[MAXSIZE][1];
float temp[MAXSIZE][1];
int linha,coluna,size,navigate;


// = funcoes de calculo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 

int checarFloatZero(float f)
{
    return (fabs(f) < 0.00001) ? 1 : 0;
}

void leMatriz(float mat[MAXSIZE][MAXSIZE], int size)
{
	int i, j;
	
    for(i = 0; i != size; i++){
        for(j = 0; j != size; j++){
            scanf("%f", &mat[i][j]);
        }   
    }
}

void leVetor(float vet[MAXSIZE], int size)
{
	int i;
	
    for(i = 0; i != size; i++){
        scanf("%f", &vet[i]);
    }
}

void imprimeMatriz(float mat[MAXSIZE][MAXSIZE], int size)
{
    int i, j;
	
    printf("s: %d\n", size);
    for(i = 0; i != size; i++){
        printf("[");
        for(j = 0; j != size; j++){
            printf(" %5.2f", mat[i][j]);
        }   
        printf(" ]\n");
    }
    printf("\n");
}

void imprimeVetor(float vet[MAXSIZE], int size)
{
    int i;
	
    printf("s: %d\n", size);
    printf("[");
    for(i = 0; i != size; i++){
        printf(" %5.2f", vet[i]);   
    }
    printf(" ]\n");
}

void imprimeVetorPrecisao(float vet[MAXSIZE], int size)
{
    int i;
	
    printf("s: %d\n", size);
    printf("[");
    for(i = 0; i != size; i++){
        printf(" %5.4f", vet[i]);   
    }
    printf(" ]\n");
}

int checkDiagNaoNula(float mat[MAXSIZE][MAXSIZE], int size)
{
    int i;

    // itera sobre a matriz
    for(i = 0; i != size; i++){
        if(checarFloatZero(mat[i][i]) == 1){
            return 0;
        }
    }

    return 1;
}

int checarTriangularInferior(float mat[MAXSIZE][MAXSIZE], int size)
{
    int i, j;

    // itera sobre a matriz
    for(i = 0; i != size; i++){
        for(j = 0; j != size; j++){
            // se algum elemento acima da diagonal for diferente de zero, retorna falso
            if(j > i && checarFloatZero(mat[i][j]) == 0){
                return 0;
            }
            // se algum elemento da diagoal eh zero
            else if(j == i && checarFloatZero(mat[i][j]) == 1){
                return 0;
            }
        }
    }
    
    return 1;
}

int checarTriangularSuperior(float mat[MAXSIZE][MAXSIZE], int size)
{
    int i, j;

    // itera sobre a matriz
    for(i = 0; i != size; i++){
        for(j = 0; j != size; j++){
            // se algum elemento acima da diagonal for diferente de zero, retorna falso
            if(j < i && checarFloatZero(mat[i][j]) == 0){
                return 0;
            }
            // se algum elemento da diagoal eh zero
            else if(j == i && checarFloatZero(mat[i][j]) == 1){
                return 0;
            }
        }
    }
    
    return 1;
}

float determinante(float mat[MAXSIZE][MAXSIZE], int size)
{   
    // condicao de saida
    if(size == 1){
        return mat[0][0];
    }

	int i, j, k;
    float det = 0;
    float matAux[MAXSIZE][MAXSIZE];
    int pulouCol = 0;

    // calcula o determinante, utlizando a linha 1 pra multiplicar seus elementos por seus cofatores e soma-los
    for(i = 0; i != size; i++){
        pulouCol = 0;
        //gera matriz auxiliar pra obter o determinante
        for(j = 0; j != size; j++){
            if(i == j){
                pulouCol = 1;
                continue;
            }

            for(k = 1; k != size; k++){
                matAux[k - 1][j - pulouCol] = mat[k][j];
            } 
        }

        det += mat[0][i] * determinante(matAux, size - 1) * ((1 + (i + 1)) % 2 == 0 ? 1 : -1);
    }

    return det;
}

void triangularInferior(float mat[MAXSIZE][MAXSIZE], int size, float termos[MAXSIZE], float s[MAXSIZE])
{
    int i, j;

    for(i = 0; i != size; i++){
        s[i] = termos[i];
        for(j = 0; j != i; j++){
            s[i] -= mat[i][j] * s[j];
        }
        s[i] /= mat[i][i];
    }    
}

void triangularSuperior(float mat[MAXSIZE][MAXSIZE], int size, float termos[MAXSIZE], float s[MAXSIZE])
{
    int i, j;

    for(i = (size - 1); i != -1; i--){
        s[i] = termos[i];
        for(j = (size - 1); j != i; j--){
            s[i] -= mat[i][j] * s[j];
        }
        s[i] /= mat[i][i];
    }    
}

void multiply(float matrizA[][MAXSIZE],float matrizB[][1]){
    int ctr,ictr;

    for(ctr=0;ctr<size;ctr++){
        matrizRes[ctr][0]=0;
            for(navigate=0;navigate<size;navigate++)
                matrizRes[ctr][0]=matrizRes[ctr][0]+matrizA[ctr][navigate]*matrizB[navigate][0];
    }

}

int checkPositivaDefinida(float mat[MAXSIZE][MAXSIZE], int size)
{
    int c;

    for(c = 1; c != (size + 1); c++){
        if(determinante(mat, c) == 0){
            return 0;
        }
    }

    return 1;
}

void decomporEmLU(float mat[MAXSIZE][MAXSIZE], int size, float l[MAXSIZE][MAXSIZE], float u[MAXSIZE][MAXSIZE])
{
    int i, j, k;

    // itera por COLUNAS, nao linhas
    for(j = 0; j != size; j++){
        for(i = 0; i != size; i++){
            // acima da diagonal
            if(i < j){
                l[i][j] = 0;

                // Uij = Aij - SUM(k=1, i-1, Lik * Ukj)
                u[i][j] = mat[i][j];
                for(k = 0; k <= (i - 1); k++){
                    u[i][j] -= (l[i][k] * u[k][j]);
                }
            }
            // diagonal
            else if(i == j){
                l[i][j] = 1;

                // Uij = Aij - SUM(k=1, i-1, Lik * Ukj)
                u[i][j] = mat[i][j];
                for(k = 0; k <= (i - 1); k++){
                    u[i][j] -= (l[i][k] * u[k][j]);
                }

            }
            // abaixo da diagonal
            else{
                u[i][j] = 0;

                // Lij = (Aij - SUM(k=1, j-1, Lik * Ukj))/ Ujj
                l[i][j] = mat[i][j];
                for(k = 0; k <= (j - 1); k++){
                    l[i][j] -= (l[i][k] * u[k][j]);
                }
                l[i][j] /= u[j][j];
            }
        }   
    }
}

void decomporEmLUCompacto(float mat[MAXSIZE][MAXSIZE], int size, float lu[MAXSIZE][MAXSIZE])
{
    int i, j, k;

    // itera por COLUNAS, nao linhas
    for(j = 0; j != (size + 1); j++){
        for(i = 0; i != size; i++){
            // acima da diagonal
            if(i < j){
                // Uij = Aij - SUM(k=1, i-1, Lik * Ukj)
                lu[i][j] = mat[i][j];
                for(k = 0; k <= (i - 1); k++){
                    lu[i][j] -= (lu[i][k] * lu[k][j]);
                }
            }
            // diagonal
            else if(i == j){
                // Uij = Aij - SUM(k=1, i-1, Lik * Ukj)
                lu[i][j] = mat[i][j];
                for(k = 0; k <= (i - 1); k++){
                    lu[i][j] -= (lu[i][k] * lu[k][j]);
                }

            }
            // abaixo da diagonal
            else{
                // Lij = (Aij - SUM(k=1, j-1, Lik * Ukj))/ Ujj
                lu[i][j] = mat[i][j];
                for(k = 0; k <= (j - 1); k++){
                    lu[i][j] -= (lu[i][k] * lu[k][j]);
                }
                lu[i][j] /= lu[j][j];
            }
        }   
    }
}

void decomposicaoLU(float mat[MAXSIZE][MAXSIZE], int size, float termos[MAXSIZE], float s[MAXSIZE])
{
    float y[MAXSIZE];
    float l[MAXSIZE][MAXSIZE], u[MAXSIZE][MAXSIZE];

    // define L e U
    decomporEmLU(mat, size, l, u);

    // resolve a equacao
    triangularInferior(l, size, termos, y);
    triangularSuperior(u, size, y, s);
}

void decomposicaoGaussCompacto(float mat[MAXSIZE][MAXSIZE], int size, float s[MAXSIZE])
{
	int i;
    float y[MAXSIZE];
    float lu[MAXSIZE][MAXSIZE];

    // define LU
    decomporEmLUCompacto(mat, size, lu);

    // extrai a ultima coluna pra nao reescrever uma funcao inteira de triangular superior
    for(i = 0; i < size; i++){
        y[i] = lu[i][size];
    }   

    // resolve a equacao
    triangularSuperior(lu, size, y, s);
}

int convergenciaCriterioLinhas(float mat[MAXSIZE][MAXSIZE], int size)
{
    int i, j;
    float lin, beta = -999999999;

    // max (0 -> size)
    for (i = 0; i < size; i++){
        lin = 0;
        // sum(j -> size)
        for (j = 0; j < size; j++){
            if(i == j){
                continue;
            }

            lin += fabs(mat[i][j] / mat[i][i]);
        }

        // se estourou 1, retorna falso
        beta = (beta > lin) ? beta : lin;
        if(beta >= 1){
            return 0;
        }
    }

    return 1;
}

int convergenciaCriterioSassenfeld(float mat[MAXSIZE][MAXSIZE], int size)
{
    int i, j;
    float lin, max = -999999999;
    float beta[MAXSIZE];

    // max (0 -> size)
    for (i = 0; i < size; i++){
        lin = 0;
        // sum(j -> i - 1)
        for(j = 0; j < i; j++){   
            lin += fabs(mat[i][j] / mat[i][i]) * beta[j];
        }
        
        // sum(i + i -> size)
        for(j = i + 1; j < size; j++){   
            lin += fabs(mat[i][j] / mat[i][i]);
        }

        // se estourou 1, retorna falso
        if(lin >= 1){
            return 0;
        }

        beta[i] = lin;
    }

    return 1;
}

void aproximacaoGaussSeidel(float mat[MAXSIZE][MAXSIZE], int size, float termos[MAXSIZE], float aprox[MAXSIZE], float aproxAnt[MAXSIZE])
{
	int i, j;
    for (i = 0; i < size; i++){
        aprox[i] = aproxAnt[i];
    }
	
    for(i = 0; i < size; i++){
        aprox[i] = termos[i];
        for(j = 0; j < size; j++){
            if(i == j){
                continue;
            }

            aprox[i] -=  (mat[i][j] * aprox[j]);
        }

        aprox[i] /= mat[i][i];
    }
}

int CPGaussSeidel(float aprox[MAXSIZE], int size, float aproxAnt[MAXSIZE], float epsilon)
{
    int i;
    float n, d, num = -1, den = -1;

    for(i = 0; i < size; i++){
        n = fabs(aprox[i] - aproxAnt[i]);
        num = (num > n) ? num : n;

        d = fabs(aprox[i]);
        den = (den > d) ? den : d;
    }

    printf("%f / %f = %f\n", num, den, num/den);
    return ((num / den) < epsilon) ? 1 : 0;
    
}

// = funcoes de rotinas = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 

void rotinaDeterminante() 
{
    system("cls");
    int size;
    float mat[MAXSIZE][MAXSIZE];

    printf("insira a ordem da matriz: ");
    scanf("%d", &size);
    
    printf("insira a matriz: \n");
    leMatriz(mat, size);
    printf("\n");

    printf("o determinante da matriz eh: %f\n", determinante(mat, size));
    printf("pressione qualquer tecla para continuar...\n");
    getch();
}

void rotinaSistemaTriangularInferior()
{
	system("cls");
    int size;
    float termos[MAXSIZE], s[MAXSIZE];
    float mat[MAXSIZE][MAXSIZE];

    printf("insira a ordem da matriz: ");
    scanf("%d", &size);
    
    printf("insira a matriz: \n");
    leMatriz(mat, size);
    printf("\n");

    if(checarTriangularInferior(mat, size) != 1){
        printf("esta matriz nao eh triangular inferior\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }

    printf("insira o vetor de termos independentes: \n");
    leVetor(termos, size);
    printf("\n");

    triangularInferior(mat, size, termos, s);
    printf("o vetor solucao da matriz eh: \n");
    imprimeVetor(s, size);

    printf("pressione qualquer tecla para continuar...\n");
    getch();
}

void rotinaSistemaTriangularSuperior() 
{
	system("cls");
    int size;
    float termos[MAXSIZE], s[MAXSIZE];
    float mat[MAXSIZE][MAXSIZE];

    printf("insira a ordem da matriz: ");
    scanf("%d", &size);
    
    printf("insira a matriz: \n");
    leMatriz(mat, size);
    printf("\n");

    if(checarTriangularSuperior(mat, size) != 1){
        printf("esta matriz nao eh triangular superior\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }

    printf("insira o vetor de termos independentes: \n");
    leVetor(termos, size);
    printf("\n");

    triangularSuperior(mat, size, termos, s);
    printf("o vetor solucao da matriz eh: \n");
    imprimeVetor(s, size);

    printf("pressione qualquer tecla para continuar...\n");
    getch();
}

void rotinaDecomposicaoLU() 
{
	system("cls");
    int size;
    float termos[MAXSIZE], s[MAXSIZE];
    float mat[MAXSIZE][MAXSIZE];

    printf("insira a ordem da matriz: ");
    scanf("%d", &size);

    printf("insira a matriz: \n");
    leMatriz(mat, size);
    printf("\n");

    if(checkPositivaDefinida(mat, size) != 1){
        printf("esta matriz nao eh positiva definida (para todo Ak, k = {1, 2, ..., n} | det(Ak) != 0)\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }

    printf("insira o vetor de termos independentes: \n");
    leVetor(termos, size);
    printf("\n");

    decomposicaoLU(mat, size, termos, s);
    printf("o vetor solucao da matriz eh: \n");
    imprimeVetor(s, size);

    printf("pressione qualquer tecla para continuar...\n");
    getch();
}

void rotinaCholesky()
{
	system("cls");
	int i, j, size, k = 0, sim = 1;    
	printf("\nDigite o tamanho da matriz: \n");     
	scanf("%d", &size);     
	float mat[MAXSIZE][MAXSIZE], A[MAXSIZE][MAXSIZE], vet[MAXSIZE] ;             
	printf("\nDigite os valores da matriz: ");
	 for (i = 0; i != size; i++){      
	 	for (j = 0; j != size; j++){                         
	  		scanf("%f", &mat[i][j]);        
	   	}   
	}
	for(sim = 1; sim != size; sim++) {
	if(mat[0][sim] != mat[sim][0]) {
		printf("Matriz nao simetrica!\n");
	}
	else {
		A[0][0] = sqrt(mat[0][0]);
		for(i = 1; i != size; i++) {
			A[i][0] = (mat[i][0])/(A[0][0]); 
			}
		for(i = 1, k =0; i != size; i++) {
			A[i][i] = sqrt(mat[i][i] - A[i][k] * A[i][k]);
		}
		for (j = 1; j != size; j++) {
			for(i = 0; i != size; i++) {
				A[i][j] = (mat[i][j] - A[i][k] * A[j][k])/(A[j][j]);
			}
		}
		for (i = 2; i != size; i++) {
			for(j = 1; j != size; j++) {
				A[i][j] = (mat[i][j] - A[i][k] * A[j][k])/(A[j][j]);
			}
		}
		printf("\nMatriz G: \n");    
			for(i = 0; i != size; i++){
				for (j = 0; j != size; j++){            
					printf ("%.2f", A[i][j]);
					if(j != size - 1) 
					printf("\t");      
					else 
					printf("\n");         
				}    
			}
		printf("\nMatriz G transposta: \n");
		for(i = 0; i != size; i++){
				for (j = 0; j != size; j++){            
					printf ("%.2f", A[j][i]);
					if(j != size - 1) 
					printf("\t");      
					else 
					printf("\n");         
					}    
				}
			} 
		}
	printf("pressione qualquer tecla para continuar...\n");
	getch();	
}

void rotinaGaussCompacto() 
{
	system("cls");
    int i, size;
    float termos[MAXSIZE], s[MAXSIZE];
    float mat[MAXSIZE][MAXSIZE];

    printf("insira a ordem da matriz: ");
    scanf("%d", &size);

    printf("insira a matriz: \n");
    leMatriz(mat, size);
    printf("\n");

    if(checkPositivaDefinida(mat, size) != 1){
        printf("esta matriz nao eh positiva definida (para todo Ak, k = {1, 2, ..., n} | det(Ak) != 0)\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }

    printf("insira o vetor de termos independentes: \n");
    leVetor(termos, size);
    printf("\n");

    for(i = 0; i < size; i++){
        mat[i][size] = termos[i];
    }

    decomposicaoGaussCompacto(mat, size, s);
    printf("o vetor solucao da matriz eh: \n");
    imprimeVetor(s, size);

    printf("pressione qualquer tecla para continuar...\n");
    getch();
}

void rotinaGaussJordan() 
{
	system("cls");
    int i, j, k, n, l;
    float A[MAXSIZE][MAXSIZE], c, x[MAXSIZE];

    printf("\nDigite o tamanho da matriz: ");
    scanf_s("%d", &n);

    printf("\nDigite os elementos da matriz:\n");
    for(i=1; i<=n; i++){
        for(j=1; j<=(n+1); j++){
            scanf_s("%f", &A[i][j]);
        }
    }

    printf("\nDigite o valor do vetor dos termos independentes: ");
    scanf_s("%d", &l);

    for(j=1; j<=n; j++){
        for(i=1; i<=n; i++){
            if(i!=j){
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++){
                    A[i][k] = A[i][k] - c * A[j][k];
                }
            }
        }
    }

    printf("\nA solucao eh:\n");
    for(i=1; i<=n; i++){
        x[i] = A[i][n+1]/A[i][i];
        printf("\n x%d=%f\n", i, x[i]);
    }
}

void rotinaJacobi()
{
	system("cls");
    printf("Digite o tamanho da matriz\n");
    scanf("%d",&size);

    printf("Digite os elementos da matriz\n");
    for(linha=0;linha<size;linha++)
        for(coluna=0;coluna<size;coluna++)
            scanf("%f",&coeficiente[linha][coluna]);

    printf("Digite a primeira aproximacao\n");
    for(linha=0;linha<size;linha++)
    scanf("%f",&approx[linha][0]);
    
    printf("Digite o coeficiente\n");
    for(linha=0;linha<size;linha++)
    scanf("%f",&b[linha][0]);

    for(linha=0;linha<size;linha++)
        for(coluna=0;coluna<size;coluna++){
            if(linha==coluna)
            Dinv[linha][coluna]=1/coeficiente[linha][coluna];
            else
            Dinv[linha][coluna]=0;
        }

    for(linha=0;linha<size;linha++)
        for(coluna=0;coluna<size;coluna++){
            if(linha==coluna)
            R[linha][coluna]=0;
            else
            if(linha!=coluna)
            R[linha][coluna]=coeficiente[linha][coluna];
        }

    int iter;
    printf("Digite o numero de iteracoes:\n");
    scanf("%d",&iter);

    int ctr=1;
    int octr;

    while(ctr<=iter){
        multiply(R,approx);
        for(linha=0;linha<size;linha++)
        temp[linha][0]=b[linha][0]-matrizRes[linha][0];
        multiply(Dinv,temp);
        for(octr=0;octr<size;octr++)
        approx[octr][0]=matrizRes[octr][0];
        printf("O valor apos a iteracao %d eh\n",ctr);
        for(linha=0;linha<size;linha++)
        printf("%.3f\n",approx[linha][0]);
        ctr++;
    }
    getch();

}

void rotinaGaussSeidel() 
{
	system("cls");
    int i, j, k, maxK, size, prec, cp;
    float epsilon;
    float termos[MAXSIZE], aproxAnt[MAXSIZE], aprox[MAXSIZE];
    float mat[MAXSIZE][MAXSIZE];

	printf("Digite o tamanho da matriz\n");
    scanf("%d", &size);

    printf("Digite os elementos da matriz\n");
    leMatriz(mat, size);
    printf("\n");

    // diag principal != 0
    if(checkDiagNaoNula(mat, size) != 1){
        printf("esta matriz tem a diagonal nula\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }

    // det != 0
    if(checarFloatZero(determinante(mat, size)) == 1){
        printf("esta matriz tem o determinante nulo\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }

    // verificar convergencia
    if(convergenciaCriterioLinhas(mat, size) == 0 && convergenciaCriterioSassenfeld(mat, size) == 0){
        printf("esta matriz nao tem covergencia garantida\n");
        printf("pressione qualquer tecla para continuar...\n");
        getch();

        return;
    }
    
    printf("insira o vetor de termos independentes: \n");
    leVetor(termos, size);
    printf("\n");

    printf("Digite a aproximacao inicial\n");
    leVetor(aproxAnt, size);
    printf("\n");

    printf("Digite a precisao (numero de casas decimais)\n");
    do{
        scanf("%d", &prec);
    }while(prec <= 0);
    printf("\n");

    epsilon = 1;
    for(i = 0; i < prec; i++){
        epsilon /= 10;
    }
    
    printf("Digite o maximo de iteracoes\n");
    do{
        scanf("%d", &maxK);
    }while(maxK <= 0);
    printf("\n");

    k = 0;
    do{
        aproximacaoGaussSeidel(mat, size, termos, aprox, aproxAnt);
        if(CPGaussSeidel(aprox, size, aproxAnt, epsilon) == 1){
            break;
        }
        for(i = 0; i < size; i++){
            aproxAnt[i] =  aprox[i];
        }

        k++;
    }while(k < maxK);
    
    printf("Apos %d iteracoes:\n", k);
    imprimeVetorPrecisao(aprox, size);
    printf("pressione qualquer tecla para continuar...\n");
    getch();        
}


void rotinaMatrizInversa() {
	system("cls");
	int i, j, size, k = 0;    
	printf("\nDigite o tamanho da matriz: \n");     
	scanf("%d",&size);     
	float mat[MAXSIZE][MAXSIZE], ident[MAXSIZE][MAXSIZE], pivo, p = 1, m = 0;   
    for(i = 0; i != size; i++)     
	{         
		for(j = 0; j != size; j++) {             
		    if(i == j){    
			    ident[i][j] = 1;            
				}
			else              
				ident[i][j] = 0;
		}   
	}             
	printf("\nDigite os valores da matriz: ");
	 for (i = 0; i != size; i++){      
	 	for (j = 0; j != size; j++){                         
	  		scanf("%f",&mat[i][j]);        
	   		}     
	   }
	   if(determinante(mat, size) == 0) {
			printf("\nDeterminante = 0, Inversa impossivel\n\n");
		}
		else {
		for(j = 0; j != size; j++){       
			pivo = mat[j][j];    
			for(k = j; k != size; k++) {      
				mat[j][k] = (mat[j][k])/(pivo);  
				ident[j][k] = (ident[j][k])/(pivo); 
			}                
			for(i = 0; i != size; i++){            
				if(i != j){           
					m = mat[i][j]/p;
					for(k = 0; k != size; k++){        
						mat[i][k] = (mat[i][k]) - (m * mat[j][k]);  
						ident[i][k] = (ident[i][k]) - (m * ident[j][k]);
				}        
			}    
		} 
	}
		printf("\nMatriz Inversa: \n");    
		for(i = 0; i != size; i++){
			for (j = 0; j != size; j++){            
				printf ("%.2f",ident[i][j]);
				if(j != size - 1) 
				printf("\t");      
				else 
				printf("\n");         
			}    
		}	
	}
	printf("pressione qualquer tecla para continuar...\n");
    getch();
}

// = main e funcoes gerais = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = 

int main()
{
    int op;
    do{
        system("cls");

        printf("selecione uma opcao:\n");
        printf("-------------------------\n");
        printf("\n");
        printf("01 - Calcular determinante\n");
        printf("02 - Calcular sistema triangular superior\n");
        printf("03 - Calcular sistema triangular inferior\n");
        printf("04 - Calcular decomposicao LU\n");
        printf("05 - Calcular rotina Cholesky\n");
        printf("06 - Calcular rotina Gauss Compacto\n");
        printf("07 - Calcular rotina Gauss Jordan\n");
        printf("08 - Calcular rotina Jacobi\n");
        printf("09 - Calcular rotina Gauss Seidel\n");
        printf("10 - Calcular matriz inversa\n");
        printf("11 - Sair\n");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op){
        case 1:
            rotinaDeterminante();
            break;
        
        case 2:
            rotinaSistemaTriangularInferior();
            break;

        case 3:
             rotinaSistemaTriangularSuperior();
            break;

        case 4:
            rotinaDecomposicaoLU();
            break;

        case 5:
            rotinaCholesky();
            break;

        case 6:
            rotinaGaussCompacto();
            break;

        case 7:
            rotinaGaussJordan();
            break;

        case 8:
            rotinaJacobi();
            break;

        case 9:
            rotinaGaussSeidel();
            break;

        case 10:
            rotinaMatrizInversa();
            break;
        }
    }while(op != 11);
	return 0;
}
