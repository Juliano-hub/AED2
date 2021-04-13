#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int** criaMatriz(int vertices);
int* criarVetor(int vertices);
int* criarVetorInfinito(int vertices);

void preencheMatriz(int**matriz, int vertices);

void percorrer(int**matriz, int*distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int inicio, int valor_aresta);
void printar_resultado(int **matriz, int *distancia_atual, int *predecessor, int vertices, int destino, int inicio);

void Liberar(int**mat, int*distancia_atual, int*vertices_fechado, int*predecessor, int vertices);

int main (){
    // matriz
    int **matriz;
    // vetores de controle
    int *vertices_fechado, *predecessor, *distancia_atual;
    // variaveis de controle
    int vertices, inicio, destino;

    vertices = 6;
    //quantidade de vertices já predeterminados 

    matriz = criaMatriz(vertices);

    preencheMatriz(matriz, vertices);
    //chama essa função que já tem os valores e atribuições que devem ser feitas

    distancia_atual = criarVetorInfinito(vertices); 
    vertices_fechado = criarVetor(vertices);
    predecessor = criarVetor(vertices);

    do{
        printf("Digite o vertice de origem, vertices(0 ate %d): ", vertices-1);
        scanf("%d", &inicio);
    }while(inicio < 0 || inicio > vertices);

    do{
        printf("Digite o vertice de destino, vertices(0 ate %d): ", vertices-1);
        scanf("%d", &destino);
    }while(inicio == destino || destino > vertices || destino < 0);

    //como já vou estar no vértice inicial, sua estimativa é 0
    percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, inicio, 0);

    printf("\nCaminho: (origem)");

    printar_resultado(matriz, distancia_atual, predecessor, vertices, destino, inicio);
    printf("(destino)V%d", destino);

    Liberar(matriz, distancia_atual, vertices_fechado, predecessor, vertices);
    
    getchar();
    return 0;
}

void percorrer(int**matriz, int*distancia_atual, int*vertices_fechado, int*predecessor, int vertices, int inicio, int valor_aresta){
    int resultado=0, menor_estimativa=0, menor_valor=0, i;

    //verifica se o vertice atual já foi verificado/codificado/atualizado
    if( vertices_fechado[inicio] == 0 ){

        // como eu já sei o valor para o vertice atual, já coloco esse valor na sua posição
        distancia_atual[inicio] = valor_aresta; 

        for(i=0; i<vertices ;i++){
            //agora ele vai percorer as colunas da linha atual para ver se acha algum valor(aresta)

            if( matriz[inicio][i] != 0){
                //se ele encontrou uma aresta

                if( ( (matriz[inicio][i]) + valor_aresta) < distancia_atual[i] ){
                    //se essa aresta for o menor valor para essa posição, ele vai atualizar o valor
                    distancia_atual[i] = ( (matriz[inicio][i]) + valor_aresta);
                    //também atualiza o predecessor desse valor
                    predecessor[i] = inicio;
                }
            }
        }

        // fecha a posição que foi verificada nessa iteração
        vertices_fechado[inicio] = 1;

        // calcula para ver se ainda tem vertices abertos
        for(i=0; i < vertices; i++){
            if(vertices_fechado[i] == 1){
                resultado= resultado + 1;
            }
        }

        // se tiver vertices abertos
        if(resultado != vertices){

            //uso isso só porque o primeiro valor é 0, assim eu posso procurar pela matriz para ver qual é a menor aresta
            menor_estimativa = INT_MAX;

            for(i=0; i<vertices; i++){
                if(distancia_atual[i] < menor_estimativa && (distancia_atual[i] != 0) && (vertices_fechado[i] == 0) ){
                    //se for uma posição onde não está fechada(não passei), for um dado diferente de 0(que significa não ter arresta)
                    //e esse dado for o menor de todas as arestas do atual vertice

                    //então pego o valor
                    menor_estimativa = distancia_atual[i];
                    //e a posição
                    menor_valor = i;
                }

            }
            //já que eu sei qual é o valor do próximo vértice(que é o menor de todos), atribuo já para a variável (relaxo a aresta)
            valor_aresta = distancia_atual[menor_valor];

            //chamo a função dnv para o próximo vertice
            percorrer(matriz, distancia_atual, vertices_fechado, predecessor, vertices, menor_valor, valor_aresta);           
        }

    }//fim do if 

}//fim da função

void printar_resultado(int **matriz, int *distancia_atual, int *predecessor, int vertices, int destino, int inicio){
    int aux;

    aux = destino;

    destino =  predecessor[destino];

    if(destino != inicio){
                                                                          //chama a função para o predecessor do vertice destino
        printar_resultado(matriz, distancia_atual, predecessor, vertices, destino, inicio);    
    }

    if(aux != inicio){
        printf("V%d -> (valor: %d) ", destino, distancia_atual[aux]);
    }

}

int** criaMatriz(int vertices){
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
        //cria com as estimativas +infinito
        vetor[i] = INT_MAX;
    }

    return (int*) vetor;
}

void preencheMatriz(int**matriz, int vertices){
    matriz[0][0] = 0;
    matriz[0][1] = 10;
    matriz[0][2] = 0;
    matriz[0][3] = 5;
    matriz[0][4] = 0;
    matriz[0][5] = 0;

    matriz[1][0] = 0;
    matriz[1][1] = 0;
    matriz[1][2] = 1;
    matriz[1][3] = 0;
    matriz[1][4] = 0;
    matriz[1][5] = 0;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 0;
    matriz[2][3] = 0;
    matriz[2][4] = 4;
    matriz[2][5] = 4;

    matriz[3][0] = 0;
    matriz[3][1] = 3;
    matriz[3][2] = 8;
    matriz[3][3] = 0;
    matriz[3][4] = 2;
    matriz[3][5] = 0;

    matriz[4][0] = 0;
    matriz[4][1] = 0;
    matriz[4][2] = 0;
    matriz[4][3] = 0;
    matriz[4][4] = 0;
    matriz[4][5] = 6;

    matriz[5][0] = 0;
    matriz[5][1] = 0;
    matriz[5][2] = 0;
    matriz[5][3] = 0;
    matriz[5][4] = 0;
    matriz[5][5] = 0;
}

void Liberar(int**mat, int*distancia_atual, int*vertices_fechado, int*predecessor, int vertices){
    int i;

    for(i=0;i < (vertices);i++){
        free(mat[i]);
    }

    free(mat);
    
    for(i=vertices; i> 0;i--){
        free(distancia_atual[i]);
        free(vertices_fechado[i]);
        free(predecessor[i]);
    }

    free(distancia_atual);
    free(vertices_fechado);
    free(predecessor);

}