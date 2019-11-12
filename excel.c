#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t;

struct Grafo{
	int eh_ponderado;
	int nro_vertices;
	int grau_max; //numero maximo de ligações
	int** aresta; //as conexões 
	int** pesos;
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
			gr->pesos = (int**) malloc(nro_vertices * sizeof(int*));
			for (int j = 0; j < nro_vertices; j++){
				gr->pesos[j] = (int*) malloc(grau_max  *sizeof(int)); //fazendo a mesma coisa com os pesos
			}
		}
	}
	return gr; 
}

int insereAresta(grafo* gr, int orig, int dest, int eh_digrafo, int peso){
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

	if(eh_digrafo == 0){
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
//
	printf("%d", peso);
	gr->pesos[orig - 1][dest-1] = peso;
	// printf("%d %d \n", gr->grau[dest - 1], gr->grau[orig - 1]);
	gr->pesos[dest-1][orig - 1] = peso;


	return 1;
}

int pegarPeso(grafo *g, int coluna, int linha){
	return g->pesos[coluna - 1][linha-1];
}

void imprimirPlanilha(grafo *gr){
    printf("      ________________________________\n");
    printf("_____| A | B | C | D | E | F | G | H |\n");
	for( int i=8; i< 28; i++){
        printf("|%2dº ", i-7);
        for( int x=0; x<8; x++){
            printf("| %d ", gr->pesos[i][x]);
		}

        printf("|\n");
    }
}

void imprimirGrafo(grafo *gr){
	for( int x=0; x<gr->nro_vertices; x++){
		for( int i=0; i< gr->grau[x]; i++)
			printf("%d tem ligacao com %d e peso %d\n", x + 1, gr->aresta[x][i] + 1, gr->pesos[x][i]);
	}
}


void inserirTodasArestas(grafo *g){
    for(int i=0; i<8;i++){
        for (int x = 8; x < 28; x++){
            insereAresta(g,i+1,x+1,0,0);
        }
    }

}

void adicionarPeso(grafo *g){
    inserePeso(g,1,9,0);
}

int valorNoGrafo(char col){
	int c;
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
	return c;
}

void gravar(grafo *g, char lin, char col, char valor[]){
	int l, c;
	l = lin - '0' + 8;
	c = valorNoGrafo(col);

	if(valor[0] != '=' && valor[0] != '@'){
		int v = atoi(valor);
		inserePeso(g,c,l,v);
	}else if(valor[0] == '='){
		char col_aux = valorNoGrafo(valor[1]);
		char lin_aux = valor[2];
		// pega valor de (lin_aux, col_aux);
		int v = pegarPeso(g, col_aux, lin_aux - '0' + 8);
		inserePeso(g, c, l, v);
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
		char col1_aux = valorNoGrafo(valor[x]);
		x++;
		char lin1_aux = valor[x];
		x += 3;
		char col2_aux = valorNoGrafo(valor[x]);
		x++;
		char lin2_aux = valor[x];

		if(strcmp(palavra, "soma")  == 0){
<<<<<<< HEAD
			printf("%d %d\n", valorNoGrafo(col1_aux), lin1_aux - '0');

			int v1 = pegarPeso(g, valorNoGrafo(col1_aux), lin1_aux -'0');
			int v2 = pegarPeso(g, col2_aux, lin2_aux);
=======
			int v1 = pegarPeso(g, col1_aux, lin1_aux - '0' + 8);
			int v2 = pegarPeso(g, col2_aux, lin2_aux - '0' + 8);
>>>>>>> b60aa159d995a9e1dafd13ef7683bf3758b19e1f
			inserePeso(g, c, l, v1+v2);
		}else if(strcmp(palavra, "max")  == 0){
			int v1 = pegarPeso(g, col1_aux, lin1_aux - '0' + 8);
			int v2 = pegarPeso(g, col2_aux, lin2_aux - '0' + 8);
			int max = v1 > v2 ? v1 : v2;
			inserePeso(g, c, l, max);
		}else if(strcmp(palavra, "min")  == 0){
			int v1 = pegarPeso(g, col1_aux, lin1_aux - '0' + 8);
			int v2 = pegarPeso(g, col2_aux, lin2_aux - '0' + 8);
			int min = v1 < v2 ? v1 : v2;
			inserePeso(g, c, l, min);
		}else{
			int v1 = pegarPeso(g, col1_aux, lin1_aux - '0' + 8);
			int v2 = pegarPeso(g, col2_aux, lin2_aux - '0' + 8);
			int media = (v1 + v2) / 2;
			inserePeso(g, c, l, media);
		}

	}
}

int main(){
    grafo *g = NULL;
    g = cria_grafo(28,28,1);
    inserirTodasArestas(g);
    // insereAresta(g,1,1,0,2);
    // imprimirGrafo(g);


	printf("Exemplo de inserção A1 3\n");
	printf("Para parar o programa digite 00 0 sair\n");
	char col = 'a', lin = 'a', valor[50];
	while(col != '0' && lin != '0'){
		printf("Digite o valor\n");
		scanf(" %c%c %s", &col, &lin, valor);
		if(lin != '0' && col != '0'){
			gravar(g, lin, col, valor);
		}
	};
		
	imprimirPlanilha(g); 
	// inserePeso(g, 1, 9, 1);
	// inserePeso(g, 1, 13, 0);
	// inserePeso(g, 2, 12, 0);
	// imprimirGrafo(g);
	// printf("%f",pegarPeso(g,1,1));
	// imprimirGrafo(g); 
    return 0;
}