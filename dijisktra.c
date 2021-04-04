#include <stdio.h>
#include <stdlib.h>

int** criaMatriz(int vertices);
int* criarVetor(vertices);
void leiaMatriz(int**matriz, int vertices);
void percorrer(int**matriz, int**distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int destino, int inicio, int valor_aresta);
int verificar_vertices_abertos( int*vertices_fechado, int vertices);

int main (){
    // matrizes 
    int **matriz,**distancia_atual;
    // vetores de controle
    int *vertices_fechado, *predecessor;
    // variaveis de controle
    int vertices, inicio, destino;


    do{
        printf("Digite a quantidade de vertices: ");
        scanf("%d", &vertices);
    }while(vertices < 0 && vertices > 20);

    matriz = criaMatriz(vertices);
    distancia_atual = criaMatriz(vertices); 
    vertices_fechado = criarVetor(vertices);
    predecessor = criarVetor(vertices);


    leiaMatriz(matriz, vertices);

    printf("Digite os dois vertices para calcular, vertices(0 - %d): ", vertices);
    getchar();
    scanf("%d %d", &inicio, &destino);

    percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, destino, inicio, 0);

    return 0;
}

void percorrer(int**matriz, int**distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int destino, int inicio, int valor_aresta){
    int resultado;

    while( (resultado = verificar_vertices_abertos(vertices_fechado, vertices)) != 0 ){
        int menor_vertice, i=0;

        i = i + valor_aresta;
        
        distancia_atual[inicio][i] = valor_aresta; 

        for(i=0; i<vertices ;i++){
            if(matriz[inicio][i] != 0 && () ){
                distancia_atual = matriz[inicio][i];
            }

        }
    }

}

int verificar_vertices_abertos( int*vertices_fechado, int vertices){
    int i=0, resultado = 0;

    for(i=0; i < vertices; i++){
        if(vertices_fechado[i] == 1){
            resultado = 1;
        }
    }

    if(resultado = 1){
        return 1;
    }else{
        return 0;
    }

}


int** criaMatriz(int vertices){
    int **matriz,i=0;

    //aloca as linhas
    matriz = (int**) malloc( (vertices)*sizeof(int*) );

    if(matriz == NULL){
        printf("\nNao foi possivel fazer o malloc\n");
        exit(0);
    }

    //aloca as colunas
    for(i=0;i < vertices;i++){
        matriz[i] = (int *)malloc((vertices)*sizeof(int));
    }

    return (int**) matriz;
}

int* criaVetor(int vertices){
    int *vetor, i;

    vetor = (int*) malloc( (vertices)*sizeof(int) );

    if(vetor == NULL){
        printf("\nNao foi possivel fazer o malloc\n");
        exit(0);
    }

    for(i=0;i < vertices;i++){
        vetor[i] = 0;
    }

    return (int*) vetor;
}

void leiaMatriz(int**matriz, int vertices){
    int linha=0,coluna=0;
    printf("Digite zero para nao ter a aresta!\n");

    for(linha=0;linha < vertices; linha++){
    for(coluna=0;coluna < vertices; coluna++){

        do{
            printf("Digite um valor da aresta (%d ; %d): ", linha, coluna);
            scanf("%d",&matriz[linha][coluna]);
        }while( matriz[linha][coluna] < 0 );

    }
    }

}

