#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int** criaMatriz(int vertices);
int** criaMatrizNula(int vertices);
int* criarVetor(int vertices);
int* criarVetorInfinito(int vertices);
void leiaMatriz(int**matriz, int vertices);
void percorrer(int**matriz, int**distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int destino, int inicio, int valor_aresta);
int verificar_vertices_abertos( int*vertices_fechado, int vertices);

void imprimeMatriz(int**mat, int m, int n);

int main (){
    // matrizes 
    int **matriz,**distancia_atual;
    // vetores de controle
    int *vertices_fechado, *predecessor;
    // variaveis de controle
    int vertices, inicio, destino , maior_valor=0;


    do{
        printf("Digite a quantidade de vertices: ");
        scanf("%d", &vertices);
    }while(vertices < 0 && vertices > 20);

    matriz = criaMatriz(vertices);
    distancia_atual = criaMatrizNula(vertices); 
    vertices_fechado = criarVetor(vertices);
    predecessor = criarVetorInfinito(vertices);


    leiaMatriz(matriz, vertices);

    printf("Digite o vertice de origem, vertices(0 ate %d): ", vertices-1);
    scanf("%d", &inicio);
    printf("Digite o vertice de destino, vertices(0 ate %d): ", vertices-1);
    scanf("%d", &destino);

    percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, destino, inicio, 0);

    printf("\n-----saiu aq:\n");

    imprimeMatriz(distancia_atual, vertices, vertices);
    printf("\n");
    for(int i=0;i<vertices;i++){
        printf("%d", predecessor[i]);
    }

    printf("\n-----fechou aq:\n");
    getchar();
    return 0;

}

void percorrer(int**matriz, int**distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int destino, int inicio, int valor_aresta){
    int resultado=0, menor_estimativa=0, menor_valor=0, i;

    i = 0;
        //verifica se o vertice atual já foi verificado/codificado/atualizado
    if( vertices_fechado[inicio] == 0 ){

            // como eu já sei o valor para o vertice atual, já coloco esse valor na sua posição
                distancia_atual[inicio][inicio] = valor_aresta; 

            for(i; i<vertices ;i++){
                //agora ele vai percorer as colunas da linha atual para ver se acha algum valor(aresta)

                if( inicio == 0){
                    //caso seja a primeira passada, ele cai nesse if para não ficar -1
                    if(matriz[inicio][i] != 0){
                        distancia_atual[inicio][i] = matriz[inicio][i];
                        predecessor[i] = inicio;
                    }else if(inicio != i){
                        distancia_atual[inicio][i] = INT_MAX/2;
                        predecessor[i] = inicio;
                    }else{
                        distancia_atual[inicio][i] = 0;
                        predecessor[i] = inicio;
                    }


                    //-----------------------------se eu consigo chegar a esse determinado vertice
                }else if( matriz[inicio][i] != 0){
                        //se ele encontrou uma aresta

                    if( ( (matriz[inicio][i]) + valor_aresta) == distancia_atual[inicio-1][i] ){

                        distancia_atual[inicio][i] = ( (matriz[inicio][i]) + valor_aresta);

                    }else if( ( (matriz[inicio][i]) + valor_aresta) < distancia_atual[inicio-1][i] ){

                        distancia_atual[inicio][i] = ( (matriz[inicio][i]) + valor_aresta);

                        predecessor[i] = inicio;
                    // senão eu copio o último valor

                    }else if( (matriz[inicio][i] + valor_aresta) > distancia_atual[inicio-1][i] ){              
                            distancia_atual[inicio][i] =  distancia_atual[inicio-1][i];
                    }

                //-----------------------------se não consigo chegar a esse determinado vertice, eu copio seu valor anterior
                }else{
                    distancia_atual[inicio][i] =  distancia_atual[inicio-1][i]; 
                }

            }

            // fecha a posição que foi verificada nessa iteração
            vertices_fechado[inicio] = 1;
            
            imprimeMatriz(distancia_atual, vertices, vertices);

            for(i=0; i < vertices; i++){
                // calcula para ver se ainda tem vertices abertos
                if(vertices_fechado[i] == 1){
                    resultado= resultado + 1;
                }
            }

            // se tiver vertices abertos
            if(resultado != vertices){

                    //uso isso só porque o primeiro valor é 0, assim eu posso procurar pela matriz para ver qual é a menor aresta
                    menor_estimativa = INT_MAX/2;

                for(i=0; i<vertices; i++){
                    if(distancia_atual[inicio][i] < menor_estimativa && (distancia_atual[inicio][i] != 0) && (vertices_fechado[i] != 1) ){
                        menor_estimativa = distancia_atual[inicio] [ predecessor[i] ];
                        menor_valor = i;
                    }

                    }

                valor_aresta = distancia_atual[inicio][menor_valor];
                percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, destino, menor_valor, valor_aresta);        
            
            }
    }

}

int verificar_vertices_abertos( int*vertices_fechado, int vertices){
    int i=0, resultado = 0;

    for(i=0; i < vertices; i++){
        if(vertices_fechado[i] == 1){
            printf("%d", vertices_fechado[i]);
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

            matriz[i][j] = INT_MAX/2;

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

int*  criarVetorInfinito(int vertices){
    int *vetor, i;

    vetor = (int*) malloc( (vertices)*sizeof(int) );

    if(vetor == NULL){
        printf("\nNao foi possivel fazer o malloc\n");
        exit(0);
    }

    for(i=0;i < vertices;i++){
        vetor[i] = INT_MAX/2;
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

void imprimeMatriz(int**mat, int m, int n){
    int linha=0,coluna=0;

    printf("-----Matriz:\n");

    for(linha=0;linha < m;linha++){
        for(coluna=0;coluna < n;coluna++){
         printf("%d ", mat[linha][coluna]);
        }
    printf("\n");
    }
    printf("\n");
}