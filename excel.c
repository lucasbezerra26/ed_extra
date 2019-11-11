#include <stdio.h>
#include <stdlib.h>
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
		printf("Entrando: %d\n", orig);
		insereAresta(gr,dest,orig,1,peso); //se não for digrafo ele vai ligando o dest a orig, o 1 indicando que é digrafo é para ele repetir somente uma vez
	}
	return 1;
}

int inserePeso(grafo* gr, int orig, int dest, int eh_digrafo, float peso){
	
	if (gr == NULL)
		return 0;
	if(orig-1 < 0 || orig-1 >= gr->nro_vertices)
		return 0;
	if(dest-1 < 0 || dest-1 >= gr->nro_vertices)
		return 0;

	gr->pesos[orig-1][gr->grau[orig-1]-1] = peso; //se for ponderado faz a mesma coisa ao peso

	if(eh_digrafo == 0){
		inserePeso(gr,dest,orig,1,peso); //se não for digrafo ele vai ligando o dest a orig, o 1 indicando que é digrafo é para ele repetir somente uma vez
	}
	return 1;
}

void imprimirPlanilha(grafo *gr){
    printf("|      A | B | C | D | E | F | G | H |\n");
	for( int i=8; i< 28; i++){
        printf("|%dº ", i-7);
        for( int x=0; x<8; x++){
            printf("| %.2f ", gr->pesos[i][x]);
		}

        printf("|\n");
    }
}

void imprimirGrafo(grafo *gr){
	for( int x=0; x<gr->nro_vertices; x++){
		for( int i=0; i< gr->grau[x]; i++)
			printf("%d tem ligacao com %d e peso %f\n", x + 1, gr->aresta[x][i] + 1, gr->pesos[x][i]);
	}
}


void inserirTodasArestas(grafo *g){
    for(int i=0; i<8;i++){
        for (int x = 8; x < 28; x++){
            insereAresta(g,i+1,x+1,0,-1);
        }
    }

}

void adcionarPeso(grafo *g){
    inserePeso(g,1,2,0,2);
}

int main(){
    grafo *g = NULL;
    g = cria_grafo(28,28,1);
    inserirTodasArestas(g);
    // insereAresta(g,1,1,0,2);
    // imprimirGrafo(g); 
    imprimirPlanilha(g); 
    return 0;
}