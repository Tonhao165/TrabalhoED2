
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
#define ENTER 13

typedef struct no *vertice;
struct no { 
	char nome;
	int visitado;
	int peso[MAX];
	vertice saindo[MAX]; // Vetor de ponteiros que apontam para as saidas desse vertice
};	

typedef vertice grafo[MAX]; //Vetor de Ponteiros que apontam para os vertices do grafo

// Grafo[i]  aponta para um vertice que aponta para varias saidas (resumindo)

void zera_visitados(grafo G){
	int j;
	for (j=0;j<MAX;j++){
		if (G[j] != NULL){
			G[j]->visitado = 0;
		}
	}
}

int adiciona_vertice(grafo G,char n){ // Aloca memoria para um vertice e coloca no grafo 
	vertice p;
	int i;
	
	for (i=0;i<MAX;i++){  //Verifica se ja existe o vertice com esse nome
		if(G[i] != NULL){
			if (G[i]->nome == n){
				printf("\nJa existe um Vertice com o nome %c !!\n",n);
				return 1;
			}
		}
	}
	
	p = (vertice) malloc(sizeof(struct no));
	
	p->nome = n;
	p->visitado = 0;
	
	for (i=0; i<MAX; i++) //Anula todas as saidas desse vertice
		p->saindo[i] = NULL;	
	
	for(i=0;i<MAX;i++) //Percorre o vetor grafo ate achar um espaco nulo para inserir
		if(G[i] == NULL){
			G[i] = p;
			return 0;
		}
	//Se chegou ate esse ponto, é porque nao achou um espaco vazio no vetor grafo
	printf("\nGrafo cheio! nao foi possivel adicionar um vertice!\n");
	return 1;
}

void Add_Vertice(grafo G){ // Adiciona um vertice no vetor grafo
	char nome;
	int i,errou=0;
	
	system("cls");
	printf("Insira o nome do vertice:\n");
	
	do{
		fflush(stdin);
		nome = toupper(getch());
	}while(nome == ENTER);
	
	if (nome == ESC)
		return;

	if (adiciona_vertice(G,nome) == 0){
		return;
	}
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
					printf("--> | %c-%d | ",G[i]->saindo[k]->nome,G[i]->peso[k]);
			}
			printf("\n");
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

int adiciona_aresta(grafo G,char v1, char v2,int peso){ //Adiciona uma aresta entre os dois vertices
	vertice origem,destino;
	int j;
	
	origem = busca_vertice(G,v1); //Recebe o ponteiro que aponta para o vertice origem
	
	if (origem != NULL){ //Se a busca pelo primeiro vertice foi um sucesso,
		destino = busca_vertice(G,v2);
		if (destino != NULL){ //Se a busca pelo segundo vertice foi um sucesso,
			for (j=0;j<MAX;j++){
				if (origem->saindo[j] != NULL){
					if (origem->saindo[j]->nome == destino->nome){ //Caca se ja existe essa aresta se sim, saia
						printf("\nA aresta %c -> %c ja existe!!\n",v1,v2);
						return 1;
					}
				}
			}
			for (j = 0;j<MAX;j++){ // 2 fors, meio porco mas o primeiro e para verificar se ja existe essa ligacao
				if (origem->saindo[j] == NULL){ //Caça um indice vazio do vetor de ligacoes do vertice
					origem->saindo[j] = destino;
					origem->peso[j] = peso;
					return 0;
				}
			}
		}
		else {
			printf("\n Nao foi possivel encontar o vertice %c!\n",v2);
			return 1;
		}
	}
	else {
		printf("\n Nao foi possivel encontar o vertice %c!\n",v1);
		return 1;
	}
	
	printf("\nO vertice %c ja tem o numero maximo de conexoes!!",v1);
	return 1;
}

void Add_Aresta(grafo G){ // Obtem as input do usuario e adiciona as arestas desejadas
	char v1, v2,op;
	
	system("cls");
	mostrar(G);
	
	printf("Qual o vertice que deseja adicionar aresta?\n");
	do{
		fflush(stdin);
		v1 = toupper(getch());
	}while(v1 == ENTER);
	
	if (v1 == ESC)
		return;
		
	printf("Qual o vertice destino de %c?\n",v1);	
	
	do{
		fflush(stdin);
		v2 = toupper(getch());
	}while (v2 == ENTER);
	
	if (v2 == ESC)
		return;
		
	int peso;
	
	printf("\nQual o peso da aresta %c -> %c? ",v1,v2);
	fflush(stdin);
	scanf("%d",&peso);
		
	if (adiciona_aresta(G,v1,v2,peso) == 0)
		printf("\nAresta %c -> %c adicionada com sucesso!",v1,v2);
	else{
		system("pause");
		return;
	}
	
	do{
		printf("\nLigar tambem %c -> %c? (s/n)\n",v2,v1); 
		fflush(stdin);
		op = getch();
		fflush(stdin);
	}while(op != 's' && op != 'S' && op != 'n' && op != 'N' && op != ESC);
	
	if (toupper(op) != 'S')
		return;
	else {
		printf("\nQual o peso da aresta %c -> %c? ",v2,v1);
		fflush(stdin);
		scanf("%d",&peso);
		
		if (adiciona_aresta(G,v2,v1,peso) == 0){
			printf("\nAresta %c -> %c adicionada com sucesso!\n",v2,v1);
			system("pause");
		}
		else{
			system("pause");
			return;
		}
	}
	
}


int remove_aresta(grafo G,char v1, char v2){ //Remove a aresta v1 -> v2 se existir
	int i;
	
	vertice origem, destino;
	
	origem = busca_vertice(G,v1); // Caca se existe o vertice 1
	if (origem != NULL){
		destino = busca_vertice(G,v2); //Caca se existe o vertice 2
		if (destino != NULL){
			for (i=0;i<MAX;i++){
				if (origem->saindo[i] == destino){ //Localiza a ligacao e torna-a nula
					origem->saindo[i] = NULL;
					return 0;
				}
			}
		}
		else {
			printf("\nNao foi encontrado o vertice %c!\n\n",v2);
			return 1;
		}
	}
	else {
		printf("\nNao foi encontrado o vertice %c!\n\n",v1);
		return 1;
	}
	printf("\nNao existe a aresta %c -> %c !!\n",v1,v2);
	return 1;
	
}

void Retirar_Aresta(grafo G){ //Obtem as input do usuario e executa a remocao da aresta
	char v1,v2,op;
	
	system("cls");
	mostrar(G);
	printf("Insira qual o primeiro vertice da aresta que deseja retirar:\n");
	
	do {
		fflush(stdin);
		v1 = toupper(getch());
	}while(v1 == ENTER);
	
	if (v1 == ESC)
		return;
	
	printf("Qual aresta de %c deseja retirar?\n",v1);
	
	do{
		fflush(stdin);
		v2 = toupper(getch());
	}while(v2 == ENTER);
	
	if (v2 == ESC)
		return;
		
	if (remove_aresta(G,v1,v2) == 0){
		printf("\nAresta %c -> %c removida com sucesso!\n\n",v1,v2);
	}
	else{
		system("pause");
		return;
	}
		
			
	printf("Remover %c -> %c tambem?(s/n) (se existe)\n", v2,v1);
	
	do{
		fflush(stdin);
		op = toupper(getch());	
	}while(op != 'S' && op != 'N');
	
	if (op == 'S'){
		if (remove_aresta(G,v2,v1) == 0){
			printf("\nAresta %c -> %c removida com sucesso!\n\n",v2,v1);
			system("pause");
		}
		else{
			system("pause");
			return;
		}
	}

	
}

int remove_vertice(grafo G,char removido){
	vertice r;
	int i,k;
	
	r = busca_vertice(G,removido);
	if (r != NULL){ //Se achou o vertice,
		for (i=0;i<MAX;i++)
			if (G[i] != NULL){
				if (G[i]->nome == removido) //Remove ele do Grafo
					G[i] = NULL;
				else 
					for (k=0;k<MAX;k++)
						if (G[i]->saindo[k] == r) //Retira todas as conexoes ate esse vertice de todos os vertices ainda existentes
							G[i]->saindo[k] = NULL;	
			}			
		free(r);
		return 0;
	}
	else{
		system("cls");
		printf("Nao foi possivel localizar o vertice %c!\n\n",removido);
		return 1;
	}
}

void Retirar_Vertice(grafo G){ //Obtem o input do usuario e executa a remocao do vertice
	char removido;
	system("cls");
	mostrar(G);
	printf("Qual o vertice que deseja remover?\n OBS: Todas as conexoes ATE ele e SAINDO dele serao apagadas!\n");
	do{
		fflush(stdin);
		removido = toupper(getch());
	}while(removido == ENTER);
	
	if (removido == ESC)
		return;
	
	if (remove_vertice(G,removido) == 0){
		printf("\nVertice %c removido com sucesso!\n",removido);
	}
	system("pause");
}

void introducao_do_trabalho(){
	printf("Trabalho EDII - Marcia\n"
			"Quarto Termo - BCC 2017\n\n"
			"Antonio Eugenio Domingues Silva\n"
			"Allison Francisco\n"
			"Denis Akira Ise Washio\n\n\n");
	system("pause");
}



int busca_profundidade(vertice inicio){
	printf("%c",inicio->nome);
	inicio->visitado = 1;
	int i;
	for (i=0;i<MAX;i++){
		if (inicio->saindo[i] != NULL && inicio->saindo[i]->visitado == 0){
			printf(" -> ");
			busca_profundidade(inicio->saindo[i]);
		}
	}
}

void Controla_BP(grafo G){
	char v1;
	int i;
	
	system("cls");
	mostrar(G);
	printf("\nQual o vertice que voce deseja iniciar a Busca em Profundidade?: ");
	
	do{
		fflush(stdin);
		v1 = toupper(getch());
		if (busca_vertice(G,v1) == NULL)
			printf("\nErro na busca pelo vertice %c, insere outro...\n",v1);
	}while(v1 == ENTER || busca_vertice(G,v1) == NULL);
	
	if (v1 == ESC)
		return;
	
	printf("\nBusca em profundidade do vertice %c:\n",v1);
	busca_profundidade(busca_vertice(G,v1));
	printf("\n\n");
	system("pause");
		
}

int main (){
	introducao_do_trabalho();
	
	
	
	
	
	
	
	
	
	
	
	int op;
	grafo G;
	char visitados[MAX] = ""; //Vetor que armazena todos os nomes dos vertices ja visitados na busca de profundidade
	
	inicia_grafo(G);


	//TESTE
	adiciona_vertice(G,'A');
	adiciona_vertice(G,'B');
	adiciona_vertice(G,'C');
	adiciona_vertice(G,'D');
	adiciona_vertice(G,'E');
	
	adiciona_aresta(G,'A','E',1);
	adiciona_aresta(G,'A','D',3);
	adiciona_aresta(G,'A','C',4);
	adiciona_aresta(G,'A','B',5);
	
	adiciona_aresta(G,'B','C',2);
	adiciona_aresta(G,'B','A',3);
	//adiciona_aresta(G,'B','E',4);
	
	adiciona_aresta(G,'C','D',5);
	adiciona_aresta(G,'C','B',6);
	adiciona_aresta(G,'C','A',3);
	
	adiciona_aresta(G,'D','E',7);
	adiciona_aresta(G,'D','C',3);
	adiciona_aresta(G,'D','A',2);
	
	adiciona_aresta(G,'E','D',1);
	adiciona_aresta(G,'E','A',3);

	//
	
	int i;
	do{
		system("cls");
		mostrar(G);
		printf("1-Adicionar Vertice\n"
				"2-Remover Vertice\n"
				"3-Adicionar Aresta\n"
				"4-Remover Aresta\n"
				"6-Sair\n"
				"7-Busca em profundidade\n");
	
		do {
			scanf("%d",&op);
		}while(op < 0 || op > 8);
		
		switch(op){
			case 1:
				Add_Vertice(G);
				break;
			case 2:
				Retirar_Vertice(G);
				break;
			case 3:
				Add_Aresta(G);
				break;
			case 4:
				Retirar_Aresta(G);
				break;
			case 7:
				Controla_BP(G);
				break;
			/*case 8:
				mostrar(G);
				system("pause");
				break;*/
			default:
				break;
		}
		
	}while(op != 6);
}
