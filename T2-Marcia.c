
// 	Trabalho ED II - BCC 2017 4º Semestre
// 	Antonio Eugenio Domingues Silva
// 	Denis Akira Ise Washio


// Liberar memoria vertice excluido




#include <ctype.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MAX 15
#define ESC 27

typedef struct no *vertice;
struct no { 
	char nome;
	vertice saindo[MAX]; // Vetor de ponteiros que apontam para as saidas desse vertice
};	

typedef vertice grafo[MAX]; //Vetor de Ponteiros que apontam para os vertices do grafo

// Grafo[i]  aponta para um vertice que aponta para varias saidas (resumindo)

vertice criar_vertice(char n){ // Aloca memoria para um vertice e retorna este
	vertice p;
	int i;
	
	p = (vertice) malloc(sizeof(struct no));
	
	p->nome = n;
	
	for (i=0; i<MAX; i++){ //Anula todas as saidas desse vertice
		p->saindo[i] = NULL;	
	}
	return p;
}

void Add_Vertice(grafo G){ // Adiciona um vertice no vetor grafo
	char nome;
	int i,errou=0;
	
	system("cls");
	printf("Insira o nome do vertice:\n");
	do{
		fflush(stdin);
		nome = toupper(getch());
		if (nome == ESC)
			return;
		
		for (i=0;i<MAX;i++){  //Verifica se ja existe o vertice com esse nome
			if(G[i] != NULL){
				if (G[i]->nome == nome){
					printf("\nJa existe um Vertice com esse nome, insere outro!\n");
					errou = 1;
					break;
				}
			}
			errou = 0;
		}
	}while (errou == 1);
	
	
	for(i=0;i<MAX;i++) //Percorre o vetor grafo ate achar um espaco nulo para inserir
		if(G[i] == NULL){
			G[i] = criar_vertice(nome);
			return;
		}
	//Se chegou ate esse ponto, é porque nao achou um espaco vazio no vetor grafo
	printf("\nGrafo cheio! nao foi possivel adicionar um vertice!");
	system("pause");
	
}

void inicia_grafo(grafo G){ //Inicia todos os ponteiros do grafo como nullo
	int i,j;
	for (i=0;i<MAX;i++){
		G[i] = NULL;
	}
}

void mostrar(grafo G){ //Printa todos os vertices em ordem de inserçao com todas as suas saidas
	int i,k;
	
	system("cls");
	for (i=0;i<MAX;i++){
		if (G[i] != NULL){
			printf("| %c | ",G[i]->nome);
			for (k=0;k<MAX;k++){
				if(G[i]->saindo[k] != NULL )
					printf("--> | %c | ",G[i]->saindo[k]->nome);
			}
			printf("\n");
		}
		else {
			printf("| - |\n");
		}
	}
	printf("\n\n");
}

vertice busca_vertice(grafo G, char v){ //Busca no grafo o vertice cujo nome é v, e retorna este ponteiro
	int i;
	for (i=0;i<MAX;i++){
		if (G[i] != NULL)
			if (G[i]->nome == v)
				return G[i];
	}
	return NULL;
}

void Add_Aresta(grafo G){ //Adiciona uma aresta entre os dois vertices, pode ser bi-direcional ou nao
	char v1, v2,op;
	vertice origem,destino;
	int j;
	
	system("cls");
	mostrar(G);
	printf("Qual o vertice que deseja adicionar aresta?\n");
	
	fflush(stdin);
	v1 = toupper(getch());
	if (v1 == ESC)
		return;
	
	origem = busca_vertice(G,v1); //Recebe o ponteiro que aponta para o vertice origem
	
	if (origem != NULL){ //Se a busca pelo primeiro vertice foi um sucesso,
		printf("Qual o vertice destino de %c?\n",origem->nome);
		
		fflush(stdin);
		v2 = toupper(getch());
		if (v2 == ESC)
			return;
		
		destino = busca_vertice(G,v2);
		if (destino != NULL){ //Se a busca pelo segundo vertice foi um sucesso,
			do{
				printf("\nEssa ligacao e bi-direcional? (s/n)\n"); 
				fflush(stdin);
				op = getch();
				fflush(stdin);
			}while(op != 's' && op != 'S' && op != 'n' && op != 'N');
			
			if (op == 's' || op == 'S'){ //Se for bi-direcional, liga tambem o destino a origem
				for (j=0;j<MAX;j++){ 
					if (destino->saindo[j] == NULL){ //Percorre o vetor de saidas ate encontrar um nulo e insere a aresta
						destino->saindo[j] = origem;
						break;
					}
				}
			}
			
			for (j=0;j<MAX;j++){
				if (origem->saindo[j] == NULL){ //Caça um indice vazio do vetor de ligacoes do vertice
					origem->saindo[j] = destino;
					break;
				}
			}
		}
		else {
			printf("\n Nao foi possivel encontar o segundo vertice!\n");
			system("pause");
			return;
		}
	}
	else {
		printf("\n Nao foi possivel encontar o primeiro vertice!\n");
		system("pause");
		return;
	}
}

void Remove_Aresta(grafo G){
	
}

void Remove_Vertice(grafo G){
	char removido;
	vertice r;
	int i,k;
	
	system("cls");
	mostrar(G);
	printf("Qual o vertice que deseja remover?\n OBS: Todas as conexoes ATE ele e SAINDO dele serao apagadas!\n");
	fflush(stdin);
	removido = toupper(getch());
	r = busca_vertice(G,removido);
	if (r != NULL){
		for (i=0;i<MAX;i++){
			if (G[i] != NULL){
				if (G[i]->nome == removido)
					G[i] = NULL;
				else {
					for (k=0;k<MAX;k++){
						if (G[i]->saindo[k] == r)
							G[i]->saindo[k] = NULL;	
					}
				}
			}			
		}
		system("cls");
		printf("Vertice removido com sucesso!\n\n");
		free(r);
	}
	else{
		system("cls");
		printf("Nao foi possivel localizar esse vertice!\n\n");
	}
}

void introducao_do_trabalho(){
	printf("Trabalho EDII - Marcia\n"
			"Quarto Termo - BCC 2017\n\n"
			"Antonio Eugenio Domingues Silva \t 161021336\n"
			"Allison Francisco \t 0000000\n"
			"Denis Akira Ise Washio \t 0000000\n\n\n");
	system("pause");
}

int main (){
	introducao_do_trabalho();
	
	int op;
	grafo G;
	
	inicia_grafo(G);
	
	do{
		system("cls");
		mostrar(G);
		printf("1-Adicionar Vertice\n"
				"2-Remover Vertice\n"
				"3-Adicionar Aresta\n"
				"4-Remover Aresta\n"
				"6-Sair\n"
				"7-Mostrar\n");
	
		do {
			scanf("%d",&op);
		}while(op < 0 || op > 7);
		
		switch(op){
			case 1:
				Add_Vertice(G);
				break;
			case 2:
				Remove_Vertice(G);
				system("pause");
				break;
			case 3:
				Add_Aresta(G);
				break;
			case 4:
				Remove_Aresta(G);
				break;
			case 7:
				mostrar(G);
				system("pause");
				break;
			default:
				break;
		}
		
	}while(op != 6);
}
