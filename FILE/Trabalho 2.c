#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char haha[15]; 
}identi;

typedef struct{
	int dia, mes, ano; 
} Aniversario;

typedef struct{
	char nome[35];
	char telefone[25];
	char CPF[15];
	Aniversario data; 
	int f; 
} cadastro;

cadastro coleta_dados(){
	
	cadastro n; 
	int i, nada, validade;
	char e[4];
	 
	printf("\nTela de Cadastro: "); 
	printf("\n\nNome: "); 
	printf("\nTelefone: "); 
	printf("\nCPF: "); 
	printf("\nData de aniversario: ");
	n.f = 1;
	fflush(stdin);
	do{	
		gets(n.nome);
		for(i=0; i<strlen(n.nome);i++)
			if((n.nome[i] >= 'A' && n.nome[i] <= 'Z') || (n.nome[i] >= 'a' && n.nome[i] <= 'z') || n.nome[i] == ' '){
				validade = 0; 
			}
			else {
			printf("Nome invalido");					
			validade = 1; 
			break;
			}		
	} while (validade == 1);
	
	do{
		gets(n.telefone);
		for(i=0; i<strlen(n.telefone);i++)
			if(n.telefone[i] >= '0' && n.telefone[i] <= '9' || n.telefone[i] == ' '){
				validade = 0; 
			}else {
				printf("Numero de telefone invalido"); 
				validade = 1; 
				break; 
			}
	}while(validade == 1);
	
	do{								
		gets(n.CPF);
		for(i=0; i<strlen(n.CPF);i++)
			if(n.CPF[i] >= '0' && n.CPF[i] <= '9'){
				validade = 0; 
			}else {
				printf("CPF invalido"); 
				validade = 1; 
				break; 
			}
	}while(validade == 1);
	
	printf("                                                               ");
	
	do{
	
		printf("   /    /      "); 
		scanf("%d",&n.data.dia);  
		scanf("%d",&n.data.mes);  
		scanf("%d",&n.data.ano);
		
		switch(n.data.mes)
		{
			case 1: 
			case 3: 
			case 5: 
			case 7:
			case 8: 
			case 10: 
			case 12: 	if((n.data.dia >= 1) && n.data.dia <= 31)
							validade = 0; 
						else validade = 1; 
						break;
			case 2: 	if((n.data.ano%4) == 0)
							if(n.data.dia >= 1 && n.data.dia <= 29)
								validade = 0; 
							else validade = 1; 
						else if(n.data.dia >= 1 && n.data.dia <= 28)
								validade = 0; 
							 else validade = 1; 
						break; 
			case 4:
			case 6: 
			case 9:
			case 11: 	if(n.data.dia >= 1 && n.data.dia <= 30)
							validade = 0; 
						else validade = 1; 
						break;
			default: 	validade = 1; 
		}
		
		if(validade == 1) {
		printf("Data digitada invalida");		
		}
	}while(validade == 1);
	 
	printf("                                                               ");
	
	printf("\nCadastro concluido");
	return n;	
}

void cad(char name[]){
	
	cadastro n;
	FILE *arq; 
	char e; 
	
	if((arq = fopen(name,"r+b")) == NULL){
		printf("Erro de abertura");
		exit(1);
	}
	fflush(stdin); 
	fseek(arq,0,SEEK_END);
	
	do{
		n = coleta_dados(); 
		
		fwrite(&n,sizeof(n),1,arq); 
		
		printf("\nRealizar outro cadastro?(s/n)");
		do{
			scanf("%c",&e); 
			e = toupper(e); 
		}while(e != 'S' && e != 'N'); 
	}while(e == 'S');
	
	fclose(arq); 
	printf("\nCadastros realizados com sucesso"); 
}

void printa(cadastro n, int k){
	
	printf("\nNome: %s",n.nome); 
	printf("\nTelefone: %s",n.telefone); 
	printf("\nCPF: %s",n.CPF); 
	printf("\nData de aniversario: %d / %d / %d\n",n.data.dia,n.data.mes,n.data.ano); 
}

void printa_nome(cadastro n){
	
	printf("\nNome: %s\n",n.nome); 
}

void consulta(char name[]){
	int num = 0, aux2; 
	cadastro n; 
	char aux[35]; 
	FILE *arq; 
	if((arq = fopen(name,"r+b")) == NULL){
		printf("\nErro na abertura do arquivo"); 
		exit(1);
	}
	
	printf("\nTela de consulta: "); 
	printf("\n\n1 - Consultar por nome "); 
	printf("\n2 - Consultar por telefone "); 
	printf("\n\nEscolha: ");
	
	do{
		scanf("%d",&num); 
	}while(num < 1 || num > 2); 
	
	fflush(stdin); 
	
	switch(num){
		case 1:		printf("\nDigite o nome: "); 
					gets(aux); 
					while(fread(&n,sizeof(n),1,arq) == 1){
						if(strcmp(aux,n.nome) == 0){
							printa(n,1);			
							aux2 = 1; 
							break; 
						}else aux2 = 0; 
					}
					
					if(!aux2) printf("\nNao encontrado"); 
					printf("\n"); 
					break; 
		case 2: 	printf("\nDigite o telefone: "); 
					gets(aux); 
					while(fread(&n,sizeof(n),1,arq) == 1){
						if(strcmp(aux,n.telefone) == 0){
							printa(n,1); 
							aux2 = 1; 
							break; 
						}else aux2 = 0; 
					}
					
					if(!aux2) printf("\nNao encontrado"); 
					printf("\n"); 					
					break; 	} 
					
	}

void listar(char name[]){
	
	FILE *arq; 
	cadastro n; 
	int cont = 0, op; 
	
	if((arq = fopen(name,"r+b")) == NULL){
		printf("Erro na abertura do arquivo!"); 
		exit(1);
	}	
	
	do{
		printf("\nLista cliente"); 
		printf("\n\n1 - Listar todos os clientes"); 
		printf("\n2 - Voltar");
		printf("\n\nEsclha: "); 
		do{
			scanf("%d",&op); 
		}while(op < 1 || op > 2);
		
		rewind(arq); 
		cont = 0; 
		
		switch(op){
			case 1:
						while(fread(&n,sizeof(n),1,arq) == 1)
							if(n.f == 1) 
								printa(n,0);
							
						printf("\nTodos os clientes: ");
						break; 
			case 2:		break;	
				}
	}while(op != 2);
	
}

void ajuda(){
	
	int i; 
	char texto[200], chave[] = "entei", aux, aux2; 
	FILE *ajuda; 
	
	if((ajuda = fopen("help.txt","rt")) == NULL){
		printf("Erro na abertura do arquivo"); 
		exit(1); 
	}
	
	do{
		aux = getc(ajuda);
		aux2 = aux - chave[i];
		printf("%c",aux2);
		i++;
		if(i == strlen(chave)) i = 0; 
	}while(aux != EOF);
	
	fclose(ajuda);
	printf("\n\n"); 
}

int menu(char name[]){
	
	int n, aux = 0;
	
	do{
	printf("\nArquivo padrao: %s\n\n",name);
	printf("\n1 - Consulta de cliente"); 
	printf("\n2 - Listar os clientes"); 
	printf("\n3 - Cadastrar novo cliente"); 
	printf("\n4 - Alterar cadastro");
	printf("\n5 - Excluir Cadastro");
	printf("\n6 - Modificar arquivos");
	printf("\n7 - Sair");
	printf("\n\nEscolha: "); 
	printf("\n\n\n\nF1 - (Pressione para ajuda)");
	
	do{
		  
		n = getch(); 
			if(n == 0){
				n = getch(); 
					if(n == 59){
						printf("\nBotao ajuda"); 
						ajuda();
						break; 
					}else	n = n; 
			}else n = n - 48;
		
		if(n < 1 || n > 7) {
			
			printf("Opcao invalida");
		}
	}while(n < 1 || n > 7);
	}while((n < 1 || n > 7));
	
	return n; 	
}

void alterar(char name[]){	
	; 
	FILE *arq; 
	cadastro n; 
	char no[35], e; 
	int op, day, month, year, aux = 0;
	float sal; 
	
	if((arq = fopen(name,"r+b")) == NULL){
		printf("Erro na abertura do arquivo"); 
		exit(1);
		}
	
	do{
	printf("\nTela para alterar o cadastro\n");
	printf("\nDigite o nome ou celular do cliente: "); 
	fflush(stdin);
	gets(no); 
	aux = 0; 
	
	rewind(arq);
	
	while(fread(&n,sizeof(n),1,arq) == 1)
		if(n.f == 1 && (strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
			
			aux = 1; 
			printf("\nSelecione o campo para modificar: %s",n.nome); 
			printf("\n1 - Nome"); 
			printf("\n2 - Telefone"); 
			printf("\n3 - CPF"); 
			printf("\n4 - Data de aniversario"); 
			printf("\n\nEscolha: "); 
			do{
				scanf("%d",&op); 				
			}while(op < 1 || op > 5); 
			
			switch(op){
				
				case 1: 	printf("\nDigite o novo nome: "); 
							fflush(stdin);
							gets(no); 
							break;
				case 2: 	printf("\nDigite o novo numero: "); 
							fflush(stdin);
							gets(no); 
							break;
				case 3: 	printf("\nDigite o novo CPF: "); 
							fflush(stdin);
							gets(no); 
							break;
				case 4: 	printf("\nDigite a nova data: "); 
							scanf("%d %d %d",&day,&month,&year);
							break;
				case 5: 
							break;				
			}			
			break; 
		}
		
		if(!aux) {
			printf("\nCadastro não encontrado\n\n");
			}
			
		if(aux) {
			fseek(arq,-sizeof(n),SEEK_CUR);
			fwrite(&n,sizeof(n),1,arq);}		
		
		printf("\nDeseja modificar outro cliente?");		
		do{
			scanf("%c",&e); 
			e = toupper(e); 
		}while(e != 'S' && e != 'N'); 		
		}while(e == 'S');			
			
		fclose(arq);	
}

void excluir(char name []){
	
	FILE *arq, *copia; 
	cadastro n;  
	int op, op2, aux = 0; 
	char no[35], e;	
		
	do{ 	
	
	printf("\nExcluir cadastro"); 
	printf("\n\n1 - Tela de exclusao logica");
	printf("\n2 - Tela de exclusao fisica"); 
	printf("\n3 - Voltar");
	printf("\n\n Escolha: ");
	
	do{
		scanf("%d",&op); 
	}while(op < 1 || op > 3); 
	
	switch(op){
		
		case 1: 		do{
						aux = 0;  
						printf("\nExclusao Logica"); 
						printf("\n\n1 - Listar cadastros excluidos logicamente"); 
						printf("\n2 - Excluir um cadastro logicamente"); 
						printf("\n3 - Restaurar um cadastro"); 
						printf("\n4 - Voltar ");
						printf("\n\nEscolha: "); 
						
						rewind(arq);
						
						do{
							scanf("%d",&op2); 
						}while(op2 < 1 || op2 > 4); 
						
						switch(op2){
							case 1: 	if((arq = fopen(name,"r+b")) == NULL){
											printf("\nErro na abertura do arquivo");
											exit(1);
										}
							
										while(fread(&n,sizeof(n),1,arq) == 1){
											if(n.f == 0){
												printa_nome(n); 
												printf("\n");
											}																				
										}
										
										fclose(arq);
										break; 
							case 2: 	printf("\nDigite o nome ou numero do cliente: "); 
										fflush(stdin);
										gets(no); 
										
										if((arq = fopen(name,"r+b")) == NULL){
											printf("\n\tErro na abertura do arquivo");
											exit(1);
										}
										
										while(fread(&n,sizeof(n),1,arq) == 1)
											if(n.f == 1 && (strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
												aux = 1; 				
										}
										fseek(arq,-sizeof(n),SEEK_CUR); 
										fwrite(&n,sizeof(n),1,arq); 
										
										if(!aux) printf("\nCadastro nao encontrado\n\n");
										fclose(arq);
										break; 
										
							case 3:  	printf("\nRecuperacao de cadastro"); 
										printf("\nDigite o nome ou numero do cliente, para recuperar: "); 
										fflush(stdin);
										gets(no); 
										
										if((arq = fopen(name,"r+b")) == NULL){
											printf("\nErro na abertura do arquivo");
											exit(1);
										}
										
										while(fread(&n,sizeof(n),1,arq) == 1)
											if(n.f == 0 && (strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
												
												printf("\nCadastro encontrado!"); 
												aux = 1; 
												printf("\nDeseja mesmo restaurar?"); 
												do{
													scanf("%c",&e); 
													e = toupper(e); 
												}while(e != 'S' && e != 'N'); 
												
												if(e == 'S'){
													n.f = 1; 
													 
													printf("\nCadastro restaurado com sucesso\n\n"); 
													break; 
												}
												
											}
											
											fseek(arq,-sizeof(n),SEEK_CUR); 
											fwrite(&n,sizeof(n),1,arq);
											
											if(!aux) printf("\nCadastro nao encontrado\n\n");
											fclose(arq);
											break; 
										
							case 4: 
										break; 
									}
									
								}while(op2 != 4);
								break; 
			case 2: 		printf("\nTela de exclusao fisica"); 
							printf("\nDigite o nome do cliente para exclusao: "); 
							fflush(stdin);
							gets(no); 
							
							if((arq = fopen(name,"r+b")) == NULL){
								printf("\nErro na abertura do arquivo");
								exit(1);
							}
										
							while(fread(&n,sizeof(n),1,arq) == 1)
								if((strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
									 
									aux = 1; 											
											if((copia = fopen("copia.dat","w+b")) == NULL){
												printf("\nErro na abertura do arquivo"); 
												exit(1);
											} 
											
											rewind(arq);
											
											while(fread(&n,sizeof(n),1,arq) == 1)
												if(strcmp(no,n.nome) != 0)
													fwrite(&n,sizeof(n),1,copia); 
													
											fclose(arq); 
											
											arq = fopen(name,"w+b"); 
											
											rewind(copia); 
											
											while(fread(&n,sizeof(n),1,copia) == 1)
												fwrite(&n,sizeof(n),1,arq); 
												
											fclose(arq); 
											fclose(copia); 
											
											remove("copia.dat"); 
											
											printf("\nCadastro excluido com sucesso\n\n"); 
											break; 									
								}
								
								if(!aux) printf("\nCadastro nao encontrado\n\n");								
							break;
			case 3:
							break;						
						}
					}while(op != 3);
				
				}

void nome_arq(char n[]){
	
	int i, j;  
	char dat[] = ".dat";
	printf("\nNao existe arquivo inicial"); 
	printf("\nDigite um novo para o arquivo para armazenamento:");
	gets(n);
	
	strcat(n,".dat");
}

void funcoes_sistema(char name[]){
	
	int op, ret; 
	char horario[100];
	char data[100];
	int hora,minuto,segundo,dia,mes,ano;
	char e; 
	char path[20]; 
	char aux[20]; 
	char caminho1[130], caminho2[130];
	FILE *arq1, *arq2; 
	identi m; 
	
	do{ 
		printf("\nFuncoes do sistema: ");
		printf("\n1 - Criar uma pasta"); 
		printf("\n2 - Renomear uma pasta");
		printf("\n3 - Acessar uma pasta");
		printf("\n4 - Excluir um arquivo");
		printf("\n5 - Mostrar conteudo do diretorio atual");
		printf("\n6 - Criar um arquivo"); 
		printf("\n7 - Renomear um arquivo");
		printf("\n0 - Voltar");
		printf("\n\nEscolha: ");
		
		do{
			scanf("%d",&op);
		}while(op < 0 || op > 8);
		
		switch(op){
			case 1: 
							printf("\nDigite o nome da pasta a ser criada:  "); 
							fflush(stdin); 
							gets(path);  
							
							printf("\n");  
							break; 
							
			case 2: 		printf("\nDigite o nome da pasta para modificar: ");
							fflush(stdin);
							gets(path); 
							
								printf("\nDigite o novo nome: "); 
								fflush(stdin);
								gets(aux);
												
							rename(path,aux);
							
							printf("\nRenomeado com sucesso\n"); 
							
							break;
							
			case 3: 
							printf("\nDigite o nome da pasta:  "); 
							fflush(stdin); 
							gets(path);
							
							 
							break; 
							 
			case 4:			printf("\n\tDigite o nome do arquivo a ser excluido: "); 
							fflush(stdin); 
							gets(path); 
							
							if((arq1 = fopen(path,"r")) == NULL)
								printf("Arquivo nao encontrado"); 
							else{							
								fclose(arq1); 
									if(remove(path) == 0){
									printf("\nArquivo removido com sucesso"); 
									}else printf("\nErro na remoção do arquivo"); 
							}
							break; 
			case 5:
							break; 		
			case 6:  
							printf("\nDeseja continuar?"); 
							do{
								scanf("%c",&e); 
								e = toupper(e); 
							}while(e != 'S' && e != 'N'); 
							
							if(e == 'S'){								
								printf("\nDigite o nome do arquivo a ser criado: "); 
								fflush(stdin); 
								gets(path); 
								
								arq2 = fopen(path,"w");
								if(!arq2) printf("\nErro na abertura do arquivo"); 
								else printf("\nArquivo criado com sucesso"); 							
							}else printf("\nCriacao cancelada");
							fclose(arq2);							
							break; 
							
			case 7:		printf("\nDigite o nome do arquivo para renomear:");
							fflush(stdin); 
							gets(path); 
							
							if((arq1 = fopen(path,"r")) == NULL){
								printf("\nArquivo não encontrado\n");
							}else{
								printf("\nDigite o novo nome: "); 
								gets(aux); 
								fclose(arq1);
								rename(path,aux); 								
								printf("\nArquivo renomeado com sucesso!\n");															
							}
							break; 		 					
		}
							
		
	}while (op != 0);
}

int main(){
	cadastro n; 
	identi names; 
	FILE *arq, *nomes; 
	int tecla, op; 
	char aux; 
	char name[15];
	
	if((nomes = fopen("nomes.dat","r+b")) != NULL)
		while(fread(&names,sizeof(names),1,nomes) == 1)
			strcpy(name,names.haha); 
	else if((nomes = fopen("nomes.dat","w+b")) != NULL){
			nome_arq(name);
			
			strcpy(names.haha,name);
			fwrite(&names,sizeof(names),1,nomes); 
			fclose(nomes);
		}
	
	
	if((arq = fopen(name,"r+b")) == NULL){
		if((arq = fopen(name,"w+b")) == NULL){
			printf("\n\tErro na abertura do arquivo"); 
			exit(1);
		}
	}
	
	fclose(arq);
	
	do{
			op = menu(name); 
			switch (op){
				case 1: 	consulta(name);
							break; 
				case 2: 	listar(name);
							break; 
				case 3: 	cad(name);
							break; 
				case 4: 	alterar(name);
							break; 
				case 5: 	excluir(name);					
							break; 
				case 6: 	funcoes_sistema(name);			
							break; 
				case 7:
							break; 
			}
			
	}while(op != 7);	
}
