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
void ZeraAux(Aresta* MST, int Total_Vertices);
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

    for(int i=0 ; i<Total_Arestas; i++){
        printf("\nOrigem:%d ", (Grafo+i)->origem);
        printf("Destino:%d ", (Grafo+i)->Destino);
        printf("Valor:%d ", (Grafo+i)->valor);
    }

    // aplica o algoritmo bubbleshort para fazer a ordenação das arestas pelo seu valor/peso
    Ordernar(Grafo, Total_Arestas);

    printf("\n-----Apos ordernar:\n");
    for(int i=0 ; i<Total_Arestas; i++){
        printf("\nOrigem:%d ", (Grafo+i)->origem);
        printf("Destino:%d ", (Grafo+i)->Destino);
        printf("Valor:%d ", (Grafo+i)->valor);
    }

    // cria um auxiliar para receber as arestas válidas
    MST = Criar( (Total_Vertices - 1) );
    // zera todos os valores dela para usar na comparação depois dentro do algoritmo em si
    ZeraAux(MST, (Total_Vertices - 1) );

    // uso o 1 para separar os valores, assim eles estão em "conjuntos" diferentes, ex: 131141, o valor 3 e 4 estão em conj diferentes
    Conjunto = (int*) malloc( (Total_Vertices * 3) * sizeof(int) );
    PreencheConjunto(Conjunto, (Total_Vertices * 3) );

    // usa o algoritmo de Kruskal
    Kruskal(Grafo, MST, Conjunto, Total_Arestas, Total_Vertices);


    printf("\n No fim:\n");
    for(int i=0 ; i<Total_Vertices*3; i = i + 3){
        printf("%d%d%d ", Conjunto[i], Conjunto[i+1], Conjunto[i+2]);
    }

    printar_resultado(MST, Total_Vertices);

    return 0;
}

void printar_resultado(Aresta *MST, int Total_Vertices){
    int i;
    printf("\na = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7, i = 8");
    printf("\n-----As arestas resultantes sao:\n");
    for(i=0; i< Total_Vertices - 1; i++){
        printf("\nOrigem:%d ", (MST+i)->origem);
        printf("Destino:%d ", (MST+i)->Destino);
        printf("Valor:%d ", (MST+i)->valor);        
    }

}

void PreencheConjunto(int *Conjunto, int Total_Vertices){
    int i, j=0;
    for(i=0 ; i<Total_Vertices; i = i + 3, j++){
        Conjunto[i] = -1;
        Conjunto[i + 1] = j;
        Conjunto[i + 2] = -1;
    }

        printf("\n");
    for(i=0 ; i<Total_Vertices; i = i + 3){
        printf("%d%d%d ", Conjunto[i], Conjunto[i+1], Conjunto[i+2]);
    }
}

int Verifica_Conjunto(int origem, int destino, int *Conjunto, int Total_Vertices){
    int i=0, j;

    while(Conjunto[i] != origem){
        i++;
    }
    // cheguei no valor da origem da aresta

    j = i;

    if(Conjunto[i - 1] != -1){
    //se estiver em uma posição que não é a primeira do conjunto

        while(Conjunto[i] != -1){
            //----------eu vou voltar até achar o inicio desse conjunto
            if(Conjunto[i] == destino){
                // se o valor do destino estiver em uma posição atrás do inicio nesse 
                //conjunto, eu posso sair dessa função, já q eles estão juntos
                return 10;
            }
        i = i - 1;    
        }
    }

    while(Conjunto[j] != -1){
    //----------se eu procurei pelas posições atrás e não encontrei o destino, vou procurar até eu achar o outro 1,
    //significando que o destino pode estar a uma posição a frente do inicio

        if(Conjunto[j] == destino){
            // se o valor do destino estiver em uma posição na frente do inicio nesse 
            //conjunto, eu posso sair dessa função, já q eles estão juntos
            return 10;
        }
        j++;       
    }

    //----------só vai cair aqui caso eles não estiverem no mesmo conjunto
    i=0;
    while(Conjunto[i] != destino){
        // procuro pela posição do destino
        i++;
    }

    // como antes eu já salvei em j a posição do extremo 1, já recupero ele para fazer a junção dos conjuntos
    while(Conjunto[i] != -1){
            Conjunto[j] = Conjunto[i];
            Conjunto[i] = -1;
        i++;
        j++;
    }

    printf("\n No meio:\n");
    for(int i=0 ; i<Total_Vertices*3; i = i + 3){
        printf("%d%d%d ", Conjunto[i], Conjunto[i+1], Conjunto[i+2]);
    }

    return 1;
}


void Kruskal(Aresta* Grafo, Aresta* MST, int *Conjunto, int Total_Arestas, int Total_Vertices){
    int i, Arestas_Colocadas = 0;

    for(i=0; i< Total_Arestas; i++){
        if( Verifica_Conjunto( (Grafo + i)->origem, (Grafo + i)->Destino, Conjunto, Total_Vertices) != 10 ){

            // só vai cair aqui caso o valor do retorno for 1, significando que estão em diferentes conjuntos

            (MST + Arestas_Colocadas)->origem = (Grafo + i)->origem;
            (MST + Arestas_Colocadas)->valor = (Grafo + i)->valor;
            (MST + Arestas_Colocadas)->Destino = (Grafo + i)->Destino;

            Arestas_Colocadas++;
        }
    }
}

void ZeraAux(Aresta* MST, int Total_Vertices){
    int i;
    for(i=0; i<Total_Vertices; i++){
        (MST + i)->origem = 0;
        (MST + i)->Destino = 0;
        (MST + i)->valor = 0;       
    }
}

void Ordernar(Aresta* Grafo, int Total_Arestas){
    int i, j;
    Aresta *aux;

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