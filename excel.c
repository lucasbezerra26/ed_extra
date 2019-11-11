#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t;

struct Grafo{
	int eh_ponderado;
	int nro_vertices;
	int grau_max; //numero maximo de ligações
	int** aresta; //as conexões 
	float** pesos;
	int* grau; //quantas aresta o vertice ja possue
    char *operacao;
};
typedef struct Grafo grafo;

grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado){
	grafo *gr = (grafo*) malloc(sizeof(grafo));
	int i;
	gr->nro_vertices = nro_vertices;
	gr->grau_max = grau_max;
	gr->eh_ponderado = eh_ponderado;//só para garanatir que vai ser 0 ou 1
	gr->grau = (int*) calloc(nro_vertices,sizeof(int)); //criando a lista
	gr->aresta = (int**) malloc(sizeof(int*)*nro_vertices);
	for (int i = 0; i < nro_vertices; i++){
		gr->aresta[i] = (int*) malloc(grau_max * sizeof(int)); //colocando para apontar cada posição da lista para outra lista  
		
		if (gr->eh_ponderado){
			gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
			for (int j = 0; j < nro_vertices; j++){
				// printf("peso\n");
				gr->pesos[j] = (float*) malloc(grau_max  *sizeof(float)); //fazendo a mesma coisa com os pesos
			}
		}
	}
	// printf("terminei\n");
	return gr; 
}

int insereAresta(grafo* gr, int orig, int dest, int eh_digrafo, float peso){
	//inicio (verificando se tudo existe)
	
	if (gr == NULL)
		return 0;
	if(orig-1 < 0 || orig-1 >= gr->nro_vertices)
		return 0;
	if(dest-1 < 0 || dest-1 >= gr->nro_vertices)
		return 0;
	//fim;
	gr->aresta[orig-1][gr->grau[orig-1]] = dest-1; //adicionando o destino a ultima posicao da lista
	if(gr->eh_ponderado)
		gr->pesos[orig-1][gr->grau[orig-1]] = peso; //se for ponderado faz a mesma coisa ao peso
	gr->grau[orig-1]++; // e incrementa o numero de ligações para aquele vertice 	

	// printf("Entrando antes do print: %d\n", orig);
	if(eh_digrafo == 0){
		// printf("Entrando: %d\n", orig);
		insereAresta(gr,dest,orig,1,peso); //se não for digrafo ele vai ligando o dest a orig, o 1 indicando que é digrafo é para ele repetir somente uma vez
	}
	return 1;
}

int inserePeso(grafo* gr, int orig, int dest, int peso){
	
	if (gr == NULL)
		return 0;
	if(orig-1 < 0 || orig-1 >= gr->nro_vertices)
		return 0;
	if(dest-1 < 0 || dest-1 >= gr->nro_vertices)
		return 0;

	gr->pesos[orig-1][gr->grau[orig-1]-1] = peso; //se for ponderado faz a mesma coisa ao peso

	return 1;
}

void imprimirGrafo(grafo *gr){
    printf("|      A | B | C | D | E | F | G | H |\n");
	for( int i=8; i< 28; i++){
        printf("|%dº ", i - 7);
        for( int x=0; x<8; x++)
            printf("| %.2f ", gr->pesos[x][i]);
        printf("|\n");
    }
}


void inserirTodasArestas(grafo *g){
    for(int i=0; i<8;i++){
        for (int x = 8; x < 28; x++){
            insereAresta(g,i+1,x+1,0,-1);
        }
    }

}

void gravar(grafo *g, char lin, char col, char valor[]){
	int l, c;
	int l = atoi(lin) + 8;
	switch (col){
	case 'A':
		c = 1;
		break;
	case 'B':
		c = 2;
		break;
	case 'C':
		c = 3;
		break;
	case 'D':
		c = 4;
		break;
	case 'E':
		c = 5;
		break;
	case 'F':
		c = 6;
		break;
	case 'G':
		c = 7;
		break;
	case 'H':
		c = 8;
		break;
	}


	if(valor[0] != '=' && valor[0] != '@'){
		valor++;
		int v = atoi(valor);
		inserePeso(g,c,l,v);
	}else if(valor[0] == '='){
		char lin_aux = valor[1];
		char col_aux = valor[2];
		// pega valor de (lin_aux, col_aux);
		// insere aresta (lin, col, valor_aux);
	}else{
		int x = 1, j = 0;
		char palavra[50];
		while(valor[x] != '('){
			palavra[j] = valor[x];
			x++;
			j++;
		}
		palavra[j] = '\0';
		x++;
		char lin1_aux = valor[x];
		x++;
		char col1_aux = valor[x];
		x += 3;
		char lin2_aux = valor[x];
		x++;
		char col2_aux = valor[x];

		if(strcmp(palavra, "soma")  == 0){
			// soma valor(lin1_aux, col1_aux) + valor(lin2_aux, col2_aux);
		}else if(strcmp(palavra, "max")  == 0){
			// max valor(lin1_aux, col1_aux) && valor(lin2_aux, col2_aux);
		}else if(strcmp(palavra, "min")  == 0){
			// min valor(lin1_aux, col1_aux) && valor(lin2_aux, col2_aux);
		}else{
			// media valor(lin1_aux, col1_aux) && valor(lin2_aux, col2_aux);
		}

	}
}


int main(){
    grafo *g = NULL;
    g = cria_grafo(28,28,1);
    inserirTodasArestas(g);
    // inserePeso(g,1,2,0,2);
    // insereAresta(g,1,1,0,2);

		printf("Para parar o programa digite 00\n");
		char col = 'a', lin = 'a', valor[50];
		while(col != '0' && lin != '0'){
			printf("Digite o valor\n");
			scanf(" %c%c %s", &col, &lin, valor);
			if(lin != '0' && col != '0'){
				gravar(g, lin, col, valor);
			}
		};

    imprimirGrafo(g); 
    return 0;
}