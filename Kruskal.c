#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int origem;
    int valor;
    int Destino;
}Aresta;

Aresta* Criar(int Total_arestas);
void PreencheStruct(Aresta* Grafo);
void Ordernar(Aresta* Grafo, int Total_Arestas);
void Kruskal(Aresta* Grafo, Aresta* MST, int *Conjunto, int Total_Arestas, int Total_Vertices);
void PreencheConjunto(int *Conjunto, int Total_Vertices);
int Verifica_Conjunto(int origem, int destino, int *Conjunto, int Total_Vertices);
void printar_resultado(Aresta *MST, int Total_Vertices);

int main (){
    Aresta *Grafo, *MST;
    int *Conjunto, Total_Arestas, Total_Vertices;

    // valores de arestas e vertices já pre-determinados no programa para facilitar a desenvolver o código
    Total_Arestas = 14;
    Total_Vertices = 9;

    // cria as arestas e preenche os valores
    Grafo = Criar(Total_Arestas);
    PreencheStruct(Grafo);
    // aplica o algoritmo bubbleshort para fazer a ordenação das arestas pelo seu valor/peso
    Ordernar(Grafo, Total_Arestas);

    /*
        printf("\n-----Apos ordernar:\n");
        for(int i=0 ; i<Total_Arestas; i++){
            printf("\nOrigem:%d ", (Grafo+i)->origem);
            printf("Destino:%d ", (Grafo+i)->Destino);
            printf("Valor:%d ", (Grafo+i)->valor);
        }
    */

    // cria um auxiliar para receber as arestas válidas
    MST = Criar( (Total_Vertices - 1) );

    Conjunto = (int*) malloc( (Total_Vertices) * sizeof(int) );

    // preenche o conjunto com o seu próprio indice, para fazer a agrupação dos conjuntos depois
    PreencheConjunto(Conjunto, (Total_Vertices) );

    // usa o algoritmo de Kruskal
    Kruskal(Grafo, MST, Conjunto, Total_Arestas, Total_Vertices);

    /*
        printf("\n No fim:\n");
        for(int i=0 ; i<Total_Vertices; i++){
            printf("%d ", Conjunto[i]);
        }
    */

    printar_resultado(MST, Total_Vertices);

    free(Grafo);
    free(MST);

    return 0;
}

void printar_resultado(Aresta *MST, int Total_Vertices){
    int i;

    printf("Professor, coloquei para o programa iniciar com mesmo grafo do ultimo video, para facilitar a desenvolver o algoritmo e nao precisar colocar sempre uma entrada\n");
    printf("\na = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7, i = 8");
    printf("\n-----As arestas resultantes sao:\n");
    for(i=0; i< Total_Vertices - 1; i++){
        printf("\nOrigem:%d ", (MST+i)->origem);
        printf("Destino:%d ", (MST+i)->Destino);
        printf("Valor:%d ", (MST+i)->valor);        
    }
    printf("\n");
}

void PreencheConjunto(int *Conjunto, int Total_Vertices){
    int i;
    for(i=0 ; i<Total_Vertices; i++){
        // preenche o conjunto com o seu próprio indice, para fazer a agrupação dos conjuntos depois
        Conjunto[i] = i;
    }
}

int Verifica_Conjunto(int origem, int destino, int *Conjunto, int Total_Vertices){
    if(Conjunto[origem] != Conjunto[destino]){
        return 1;
    }else{
        return 10;
    }
}

void Kruskal(Aresta* Grafo, Aresta* MST, int *Conjunto, int Total_Arestas, int Total_Vertices){
    int i, Arestas_Colocadas = 0, aux;

    for(i=0; i< Total_Arestas; i++){
        if( Verifica_Conjunto( (Grafo + i)->origem, (Grafo + i)->Destino, Conjunto, Total_Vertices) != 10 ){
            // só vai cair aqui caso o valor do retorno for 1, significando que estão em diferentes conjuntos

            // aux vai receber o valor do conjunto do destino para juntar todos depois
            aux = Conjunto[(Grafo + i)->Destino];

            for(int j=0; j< Total_Arestas; j++){
                // percorre o vetor de conjunto para ver quais valores estão no conjunto do destino, assim ele converte todos
                // os que pertencem ao da origem e destino em 1 só conjunto
                if(Conjunto[j] == aux){
                    Conjunto[j] = Conjunto[(Grafo + i)->origem]; 
                }
            }

            /* usei para printar o vetor dos conjuntos, para verificar se estavam se juntando
                printf("\n No meio:\n");
                for(int i=0 ; i<Total_Vertices; i++){
                    printf("%d ", Conjunto[i]);
                }
            */

            // atribui a aresta atual para uma var auxiliar que vai receber os que pertencem ao MST 
            (MST + Arestas_Colocadas)->origem = (Grafo + i)->origem;
            (MST + Arestas_Colocadas)->valor = (Grafo + i)->valor;
            (MST + Arestas_Colocadas)->Destino = (Grafo + i)->Destino;

            // incrementa para não substituir o valor no próximo laço
            Arestas_Colocadas++;
        }
    }
}

void Ordernar(Aresta* Grafo, int Total_Arestas){
    int i, j;
    Aresta *aux;

    aux =  (Aresta*) malloc( (Total_Arestas)*sizeof(Aresta) );

    // implementado um bubblesort
    for(i=1; i < Total_Arestas; i++){
        for(j=0; j < Total_Arestas - 1; j++){
            if( (Grafo + j)->valor > (Grafo + (j + 1) )->valor ){

                aux->Destino = (Grafo + j)->Destino;
                aux->origem = (Grafo + j)->origem;
                aux->valor = (Grafo + j)->valor;

                (Grafo + j)->Destino = (Grafo + (j + 1) )->Destino;
                (Grafo + j)->origem = (Grafo + (j + 1) )->origem;
                (Grafo + j)->valor = (Grafo + (j + 1) )->valor;

                (Grafo + (j + 1) )->Destino = aux->Destino;
                (Grafo + (j + 1) )->origem = aux->origem;
                (Grafo + (j + 1) )->valor = aux->valor;
            }
        }
    }
    free(aux);
}

Aresta* Criar(int Total_arestas){
    Aresta *vetor;

    vetor = (Aresta*) malloc( (Total_arestas)*sizeof(Aresta) );

    if(vetor == NULL){
        printf("\nNao foi possivel fazer o malloc\n");
        exit(0);
    }

    return (Aresta*) vetor;
}

void PreencheStruct(Aresta* Grafo){
    //   a 0 / b 1 / c 2 / d 3 / e 4 / f 5 / g 6 / h 7 / i 8
    Grafo->origem = 0;
    Grafo->Destino = 1;
    Grafo->valor = 4;

    (Grafo + 1)->origem = 0;
    (Grafo + 1)->Destino = 7;
    (Grafo + 1)->valor = 8;

    (Grafo + 2)->origem = 1;
    (Grafo + 2)->Destino = 7;
    (Grafo + 2)->valor = 11; 

    (Grafo + 3)->origem = 1;
    (Grafo + 3)->Destino = 2;
    (Grafo + 3)->valor = 8; 

    (Grafo + 4)->origem = 2;
    (Grafo + 4)->Destino = 8;
    (Grafo + 4)->valor = 2; 

    (Grafo + 5)->origem = 2;
    (Grafo + 5)->Destino = 5;
    (Grafo + 5)->valor = 4;

    (Grafo + 6)->origem = 2;
    (Grafo + 6)->Destino = 3;
    (Grafo + 6)->valor = 7;

    (Grafo + 7)->origem = 8;
    (Grafo + 7)->Destino = 7;
    (Grafo + 7)->valor = 7; 

    (Grafo + 8)->origem = 8;
    (Grafo + 8)->Destino = 6;
    (Grafo + 8)->valor = 6; 

    (Grafo + 9)->origem = 6;
    (Grafo + 9)->Destino = 7;
    (Grafo + 9)->valor = 1;   

    (Grafo + 10)->origem = 6;
    (Grafo + 10)->Destino = 5;
    (Grafo + 10)->valor = 2; 

    (Grafo + 11)->origem = 3;
    (Grafo + 11)->Destino = 5;
    (Grafo + 11)->valor = 14; 

    (Grafo + 12)->origem = 3;
    (Grafo + 12)->Destino = 4;
    (Grafo + 12)->valor = 9;

    (Grafo + 13)->origem = 4;
    (Grafo + 13)->Destino = 5;
    (Grafo + 13)->valor = 10;    
}