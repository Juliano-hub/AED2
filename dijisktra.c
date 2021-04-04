#include <stdio.h>
#include <stdlib.h>

int** criaMatriz(int vertices);
int** criaMatrizNula(int vertices);
int* criarVetor(int vertices);
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
    distancia_atual = criaMatrizNula(vertices); 
    vertices_fechado = criarVetor(vertices);
    predecessor = criarVetor(vertices);


    leiaMatriz(matriz, vertices);

    printf("Digite os dois vertices para calcular, vertices(0 ate %d): ", vertices);
    getchar();
    scanf("%d %d", &inicio, &destino);

    percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, destino, inicio, 0);

    return 0;
}

void percorrer(int**matriz, int**distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int destino, int inicio, int valor_aresta){
    int resultado, menor_estimativa=0, menor_valor=0, i=0;

    //faz o algoritmo enquanto tiver vertices abertos
    while( (resultado = verificar_vertices_abertos(vertices_fechado, vertices)) != 1 ){
        //verifica se o vertice atual já foi verificado/codificado/atualizado
        if( vertices_fechado[inicio] == 0 ){
            // como eu já sei o valor para o vertice atual, já coloco esse valor na sua posição
            distancia_atual[inicio][inicio] = valor_aresta; 

            for(i=0; i<vertices ;i++){
                //agora ele vai percorer as colunas da linha atual para ver se acha algum valor(aresta)
                if(matriz[inicio][i] != 0){
                    //se ele encontrou
                
                    //agora vai anotar os valores na matriz auxiliar

                    //se o valor da matriz dessa posição for vazia
                    if(distancia_atual[inicio][i] == 0){

                        distancia_atual[inicio][i] = matriz[inicio][i];

                        predecessor[i] = inicio;

                     //se já tiver algo lá, ele verifica se o valor da posição atual é menor do que a que já está lá   
                    }else if(matriz[inicio][i] < distancia_atual[inicio][i]){

                        distancia_atual[inicio][i] = matriz[inicio][i];

                        predecessor[i] = inicio;
                    }
                }
            }
        }
    }
    // fecha a posição que foi verificada nessa iteração
    vertices_fechado[inicio] = 1;
        
    menor_valor = matriz[inicio][0];     
    for (i = 0; i < vertices; i++){
        if (matriz[inicio][i] < menor_valor){
            menor_valor = matriz[inicio][i];
            menor_estimativa = i;
        }
    }

    valor_aresta = valor_aresta + matriz[inicio][menor_estimativa];

    percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, destino, menor_estimativa, valor_aresta);
}

int verificar_vertices_abertos( int*vertices_fechado, int vertices){
    int i=0, resultado = 0;

    for(i=0; i < vertices; i++){
        if(vertices_fechado[i] == 1){
            resultado+= 1;
        }
    }

    if(resultado != vertices){
        return 0;
    }else{
        return 1;
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

int** criaMatrizNula(int vertices){
    int **matriz,i=0, j=0;

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

    for(i=0;i < vertices; i++){
        for(j=0;j < vertices; j++){

            matriz[i][j] = 0;

        }
    }

    return (int**) matriz;
}

int* criarVetor(int vertices){
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

