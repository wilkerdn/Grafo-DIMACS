#include "dimacs.h"

int main(){
	FILE *arq1;
	int op1,op2,n_vert,n_ares,inserir=1,n,i,menu=1,menu2=1,num1=1,pesq;
	int n_vertm,n_aresm,j,vert_d,aresta_d;

	while(menu==1){
	printf("---MENU---\n");
	printf("[1]-Criar grafo\n");
	printf("[2]-Grafo DIMACS\n");
	printf("[0]-Encerrar programa\n");
	printf("Opcao = ");
	scanf("%d",&op1);
	
	if(op1==1){
		printf("\nDigite a quantidade de vertices: ");
		scanf("%d",&n_vert);
		int vertices[n_vert];
		printf("Digite a quantidade de arestas: ");
		scanf("%d",&n_ares);
		int arestas[n_ares];

		if(calculo_densidade(n_vert,n_ares)==0){
			printf("Digite os vertices do grafo:\n");
			for(i=0;i<n_vert;i++){
				scanf("%d",&vertices[i]);
			}
			Lista* vertices_l[n_vert];
			int posicao[n_vert];
			printf("\nVamos criar a lista de adjacencia\n");
			for(i=0;i<n_vert;i++){
				vertices_l[i] = criar_lista();
				posicao[i] = 0;
			}
			for(i=0;i<n_vert;i++){
				printf("Insira os vertices que tem relacao com %d\n",vertices[i]);
				printf("Para parar de inserir = -10\n");
				while(inserir==1){
					scanf("%d",&n);
					if(n==-10){
						break;
					}else{
						inserir_num(vertices_l[i],n,posicao[i]);
						posicao[i]++;
						inserir = 1;
					}
				}
			}
			printf("\nLISTA DE ADJACENCIA");
			for(i=0;i<n_vert;i++){
				printf("\n%d-> ",vertices[i]);
				exibir_l(vertices_l[i],posicao[i]);
			}
			printf("\nLista excluida\n\n");
			menu = 1;

		}else{
			printf("Digite os vertices do grafo:\n");
			for(i=0;i<n_vert;i++){
				scanf("%d",&vertices[i]);
			}
			printf("Digite as arestas do grafo:\n");
			for(i=0;i<n_ares;i++){
				scanf("%d",&arestas[i]);
			}
			printf("\nVamos criar a matriz de adjacencia");
			matriz_adjacente(vertices,n_vert);
			printf("\nVamos criar a matriz de incidencia");
			matriz_incidente(vertices,arestas,n_vert,n_ares);
			printf("\nMatrizes excluidas\n\n");
			menu = 1;
		}
	}else if(op1==2){
		printf("\nLendo arquivo do grafo DIMACS...\n\n");

		arq1 = fopen("grafo.txt", "rt");
		fscanf(arq1, "%d %d", &n_vertm, &n_aresm);
		leitura_grafo(&n_vertm, &n_aresm);

		int m_dimacs[n_vertm][n_vertm],origem,destino,peso,num=1;

		for(i=0;i<n_vertm;i++){
			for(j=0;j<n_vertm;j++){
				m_dimacs[i][j] = 0;
			}
		}
		
		for(i=0;i<n_aresm;i++){
			fscanf(arq1, "%d %d %d", &origem, &destino, &peso);
			m_dimacs[origem-1][destino-1] = peso;
		}
	
		printf("\nMATRIZ ADJACENCIA - GRAFO DIMACS\n");
		printf("  ");
		for(i=0;i<n_vertm;i++){
			printf("%d ",num);
			num++;
		}
		num=1;
		printf("\n");

		for(i=0;i<n_vertm;i++){
			printf("%d ",num);
				for(j=0;j<n_vertm;j++){
					printf("%d ",m_dimacs[i][j]);
				}
				num++;
				printf("\n");
		}
		

		while(menu2==1){
			printf("\n---MENU GRAFO DIMACS---\n");
			printf("[1]-Arestas adjacentes a uma aresta\n");
			printf("[2]-Vertices adjacentes a um vertice\n");
			printf("[3]-Arestas incidentes a um vertice\n");
			printf("[4]-Vertices incidentes a uma aresta\n");
			printf("[5]-Imprimir o grau de um vertice\n");
			printf("[6]-Verificar 2 vertices adjacentes\n");
			printf("[7]-Trocar dois vertices\n");
			/*printf("[8]-Algoritmo de Dijktra\n");
			printf("[9]-Busca em largura\n");
			printf("[10]-Busca em profundidade\n");*/
			printf("[0]-Sair do menu\n");
			printf("Opcao = ");
			scanf("%d",&op2);

			if(op2==1){
				int aresta[n_aresm],vertice1[n_aresm],vertice2[n_aresm],x,y;
				printf("\nARESTAS\n");
				for(i=0;i<n_vertm;i++){
					for(j=0;j<n_vertm;j++){
						if(m_dimacs[i][j]!=0){
							aresta[num1]=num1;
							vertice1[num1]=i+1;
							vertice2[num1]=j+1;
							printf("Aresta [%d] = %d---%d\n",num1,i+1,j+1);
							num1++;
						}
					}
				}
				num1=0;
				printf("Digite o numero da aresta: ");
				scanf("%d",&pesq);
				x = vertice1[pesq];
				y = vertice2[pesq];
				printf("Arestas adjacentes:\n");
				for(i=1;i<=n_aresm;i++){
					if(((vertice1[i]==x||vertice1[i]==y)||(vertice2[i]==x||vertice2[i]==y))&&i!=pesq){
					printf("Aresta[%d]\n",i);
					}
				}
				menu2 = 1;
			}else if(op2==2){
				int controle=0;
				printf("\nDigite o vertice: ");
				scanf("%d",&vert_d);
				printf("Vertices adjacentes:\n");
				for(i=0;i<n_vertm;i++){
					if(m_dimacs[vert_d-1][i]!=0){
					printf("%d\n",i+1);
					controle = 1;
					}
				}
				if(controle==0){
				printf("O vertice nao possui adjacencia.\n");
				}
				menu2 = 1;
			}else if(op2==3){
				printf("\nDigite o vertice: ");
				scanf("%d",&vert_d);
				printf("\nAs arestas incidentes ao vertice %d sao:\n",vert_d);
				for(i=0;i<n_vertm;i++){
					for(j=0;j<n_vertm;j++){
					if((m_dimacs[i][j]!=0)&&(j==vert_d-1||i==vert_d-1)){
					printf("%d---%d\n",i+1,j+1);
					}
					}
				}
				menu2 = 1;
			}else if(op2==4){
				num1=1;
				printf("\nARESTAS\n");
				for(i=0;i<n_vertm;i++){
					for(j=0;j<n_vertm;j++){
						if(m_dimacs[i][j]!=0){
							printf("Aresta [%d] = %d---%d\n",num1,i+1,j+1);
							num1++;
						}
					}
				}
				num1=1;
				printf("\nDigite o numero da aresta: ");
				scanf("%d",&vert_d);
				num=0;
				for(i=0;i<n_vertm;i++){
					for(j=0;j<n_vertm;j++){
						if(m_dimacs[i][j]!=0){
						num++;
						}
						if(num==vert_d){
						printf("\nOs vertices incidentes a aresta %d sao: %d e %d\n",vert_d,i+1,j+1);
						num++;
						}
					}
				}
				menu2 = 1;
			}else if(op2==5){
				int grau=0;
				printf("\nDigite o vertice: ");
				scanf("%d",&vert_d);
				for(i=0;i<n_vertm;i++){
					if(m_dimacs[vert_d-1][i]!=0){
					grau++;
					}
				}
				for(i=0;i<n_vertm;i++){
					if(m_dimacs[i][vert_d-1]!=0){
					grau++;
					}
				}
				printf("O numero de grau do vertice %d e igual a %d\n",vert_d,grau);
				menu2 = 1;
			}else if(op2==6){
				int x1,x2;
				printf("\nDigite o vertice: ");
				scanf("%d",&x1);
				printf("Digite o vertice para verificar adjacencia: ");
				scanf("%d",&x2);

				if(m_dimacs[x1-1][x2-1]!=0){
					printf("O vertice %d possui adjacencia com o vertice %d\n",x1,x2);
				}else{
					printf("O vertice %d nao possui adjacencia com o vertice %d\n",x1,x2);
				}
				menu2 = 1;
			}else if(op2==7){
				int aux,v1,v2,m_aux[n_vertm][n_vertm];
				for(i=0;i<n_vertm;i++){
					for(j=0;j<n_vertm;j++){
						m_aux[i][j] = m_dimacs[i][j];
					}
				}
				printf("\nDigite os vertices para trocar\n");
				printf("Vertice 1 = ");
				scanf("%d",&v1);
				printf("Vertice 2 = ");
				scanf("%d",&v2);
				printf("\n");
				num=1;
				for(i=0;i<n_vertm;i++){
					aux = m_aux[v1-1][i];
					m_aux[v1-1][i] = m_aux[v2-1][i];
					m_aux[v2-1][i] = aux;
				}

				printf("\nMATRIZ ADJACENCIA - GRAFO DIMACS\n");
				printf("  ");
				for(i=0;i<n_vertm;i++){
					printf("%d ",num);
					num++;
				}
				num=1;
				printf("\n");

				for(i=0;i<n_vertm;i++){
				printf("%d ",num);
					for(j=0;j<n_vertm;j++){
						printf("%d ",m_dimacs[i][j]);
					}
					num++;
					printf("\n");
				}
				menu2 = 1;
			}else if(op2==0){
				printf("\n");
				menu2 = 0;
			}else{
				printf("\nOpcao invalida, digite novamente\n");
				menu2 = 1;
			}
		}
		menu = 1;	
	}else if(op1==0){
		menu = 0;
	}else{
		printf("\nOpcao invalida, digite novamente\n\n");
		menu = 1;
	}
	}
	printf("\nPrograma finalizado\n");
	return 0;
}
