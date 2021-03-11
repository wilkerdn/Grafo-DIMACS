#include "dimacs.h"

int calculo_densidade(int v,int a){
	float dens,part1,part2;
	part1 = 2*a;
	part2 = (v-1)*v;
	dens = part1/part2;
	if(dens>=0.5){
		printf("\nDensidade alta = %f,vamos utilizar matriz\n",dens);
		return 1;
	}else{
		printf("\nDensidade baixa = %f,vamos utilizar lista\n",dens);
		return 0;
	}
}

Lista *criar_lista(){
	Lista* l;
	l = malloc(sizeof(Lista));
	l->comeco = NULL;
	return l;
}

int Vazia(Lista* l){
	if(l->comeco==NULL){
		return 1;
	}else
		return 0;
}

int inserir_num(Lista* l,int y,int z){
	Vertice *novo = malloc(sizeof(Vertice));
	Vertice *temp;
	int i;
	novo->num = y;
	if(Vazia(l)==1){
		novo->proximo = l->comeco;
		l->comeco = novo;
	}else if(Vazia(l)!=1){
		temp = l->comeco;
		for(i=1;i<z;i++){
			if(temp->proximo==NULL){
				break;
			}else
				temp = temp->proximo;
		}
	}
	novo->proximo = temp->proximo;
	temp->proximo = novo;
	return 1;
}

void exibir_l(Lista *l,int z){
	int i=0;
	Vertice *temp;
	if(l->comeco!=NULL){
	temp=l->comeco;
	printf("%d ",temp->num);
		for(i=1;i<z;i++){
			if(temp->proximo==NULL){
			break;
			}
			temp=temp->proximo;
			printf("%d ",temp->num);
		}
	}
}

void matriz_adjacente(int aux[],int x){
	int m_adj[x][x],i=0,j=0,aux2;

	printf("\nSe o vertice tiver relacao de adjacencia com o vertice posterior = 1\n");
	printf("Se o vertice tiver relacao de incidencia com o vertice posterior = 2\n");
	printf("Se os vertices nao possuirem relacao = 0\n");

	for(i=0;i<x;i++){
		for(j=0;j<x;j++){
		printf("[%d][%d] = ",aux[i],aux[j]);
		scanf("%d",&aux2);
		m_adj[i][j] = aux2;
		}
	}

	printf("\nMATRIZ ADJACENTE\n");
	printf("  ");
	for(i=0;i<x;i++){
		printf("%d ",aux[i]);
	}
	printf("\n");

	for(i=0;i<x;i++){
		printf("%d ",aux[i]);
		for(j=0;j<x;j++){
		printf("%d ",m_adj[i][j]);
		}
		printf("\n");
	}
}

void matriz_incidente(int aux_v[],int aux_a[],int x,int y){
	int m_inc[x][y],i=0,j=0,aux2;

	printf("\nSe o vertice possuir relacao de saida com a aresta = 1\n");
	printf("Se o vertice possuir relacao de entrada com a aresta = 2\n");
	printf("Se o vertice nao possuir relacao com a aresta = 0\n");

	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
		printf("[%d][%d] = ",aux_v[i],aux_a[j]);
		scanf("%d",&aux2);
		m_inc[i][j] = aux2;
		}
	}

	printf("\nMATRIZ INCIDENTE\n");
	printf("  ");
	for(i=0;i<y;i++){
		printf("%d ",aux_a[i]);
	}
	printf("\n");

	for(i=0;i<x;i++){
		printf("%d ",aux_v[i]);
		for(j=0;j<y;j++){
		printf("%d ",m_inc[i][j]);
		}
		printf("\n");
	}
}

int leitura_grafo(int *n_vert, int *n_ares){
	char str[10];
	char *linha;
	FILE *arq;
	arq = fopen("grafo.txt", "r");
	int cont=0, origem=0, destino=0, peso=0;
	char delimitador[2] = {' '};

	if(arq == NULL){
		printf("Problema ao abrir o arquivo!\n");
		exit(1);
	}

	while((linha=fgets(str, 10, arq))!=NULL){
	cont++;
	if(cont==1){
		char *res = NULL;
		res = strtok( linha, delimitador );

            	for(int quant=1; quant<=2; quant++){
                	if(quant==1){
				*n_vert = atoi(res);
                     		printf("Numero de vertices: %d\n", *n_vert);
                	}else if(quant==2){
                     		*n_ares = atoi(res);
                     		printf("Numero de arestas: %d\n\n", *n_ares);
                	}
                	res = strtok( NULL, delimitador );
            	}
	}else{
            	char *res = NULL;
            	res = strtok( linha, delimitador );
            	int quant;
            	while( res != NULL ){
                	for(quant=1; quant<=3; quant++){
                   		if(quant==1){
                        		origem= atoi(res);
                        		printf("origem: %d\n", origem);
                   		}else if (quant==2){
                        		destino= atoi(res);
                        		printf("destino: %d\n", destino);
                   		}else if(quant==3){
                        		peso= atoi(res);
                        		printf("peso: %d\n\n", peso);
                   		}
                    	res = strtok( NULL, delimitador);
                	}
            	}
        }
    	}
	fclose(arq);
	return 0;
}
