#include<stdio.h>
#include<stdlib.h>
#include"staren.h"
// pra mudar pro grafo exemplar eh mudar esse define pra 4, descomentar os grafo_insere_duplo la embaixo e comentar os grafo_insere_duplo embaixo do grafo do computerphile,
// fazer o contrario pra fazer o contrario


int main(){
    
    plan ** grafo = malloc(sizeof**grafo * QPLANETAS); // Inicia o vetor da lista de adjacência
    int i,j; // Auxiliares pro for
    for (i = 0; i < QPLANETAS; i += 1){ // Inicia cada um dos planetas
        grafo[i] = grafo_inicia(i);
    } 
    // Criação de grafo arbitrário nao direcionado ( Grafo exemplar)
    // ------------------------------------------------------ //
    //grafo_insere_duplo(grafo, 0, 1, 2, 0);
    //grafo_insere_duplo(grafo, 0, 2, 5, 0);
    //grafo_insere_duplo(grafo, 1, 2, 2, 0);
    //grafo_insere_duplo(grafo, 2, 3, 5, 0);
    //grafo_insere_duplo(grafo, 3, 0, 1, 0);

    // Grafo do computerphile 
    grafo_insere_duplo(grafo, 0, 1, 3, 0);
    grafo_insere_duplo(grafo, 0, 3, 2, 0);
    grafo_insere_duplo(grafo, 0, 2, 7, 0);
    grafo_insere_duplo(grafo, 1, 4, 2, 0);
    grafo_insere_duplo(grafo, 2, 3, 3, 0);
    grafo_insere_duplo(grafo, 2, 7, 4, 0);
    grafo_insere_duplo(grafo, 3, 7, 4, 0);
    grafo_insere_duplo(grafo, 3, 9, 1, 0);
    grafo_insere_duplo(grafo, 4, 5, 4, 0);
    grafo_insere_duplo(grafo, 4, 6, 4, 0);
    grafo_insere_duplo(grafo, 5, 6, 6, 0);
    grafo_insere_duplo(grafo, 5, 10, 4, 0);
    grafo_insere_duplo(grafo, 6, 10, 4, 0);
    grafo_insere_duplo(grafo, 7, 8, 5, 0);
    grafo_insere_duplo(grafo, 8, 9, 3, 0);
    grafo_insere_duplo(grafo, 9, 11, 2, 0);
    grafo_insere_duplo(grafo, 10, 12, 5, 0);
    grafo_insere_duplo(grafo, 11, 12, 2, 0);

    // ------------------------------------------------------ //

    // --------------- Printa o grafo -------------------- //
    for (i = 0; i < QPLANETAS; i += 1){
        plan * aux = grafo[i];
        printf("\n %d: ",i+1);
        while (aux->prox != NULL){
            printf("%d (%d)  ",aux->prox->gfIndice+1,aux->prox->iTempo);
            aux = aux->prox;
        }
    }
    // ---------------------------------------------------- //

    // ------------ CALCULA e printa O DIJKSTRA -------------------------// 
    int * iCusto = malloc(sizeof*iCusto * QPLANETAS);
    int * gfAnterior = malloc(sizeof*gfAnterior * QPLANETAS);

    grafo_dijkstra(grafo, 0, iCusto, gfAnterior);
    printf("\n Sendo o vertice inicial o de indice 0");
    printf("\n Custo: ");
    for (i = 0; i < QPLANETAS; i += 1){
        printf("%d ",iCusto[i]);
    }
    printf("\n gfAnterior: ");
    for (i = 0; i < QPLANETAS; i += 1){
        printf("%d ",gfAnterior[i]);
    }
    printf("\n");
    printf("\n Dijkstra menor distancia entre pos 0 e 2: %d",dijkstra_pesototal(grafo,0,2));
    printf("\n Dijkstra proximo vertice do menor caminho origem 0 e destino 2: %d",dijkstra_proximo(grafo,0,2));
    printf("\n");

    // --------------------------------------------------- //

    // ------------ Libera o grafo e as listas ----------------------------- //
    for (i = 0; i < QPLANETAS; i += 1){
        grafo_libera(grafo[i]);
    }
    free(grafo);
    free(iCusto);
    free(gfAnterior);
    // ---------------------------------------------------------- //
}

plan * grafo_inicia(int gfIndice){
    plan * aIniciar = malloc(sizeof*aIniciar);
    aIniciar->gfIndice = gfIndice;
    aIniciar->iTempo = 1; // Ir de um planeta para o mesmo significa esperar uma hora nele
    aIniciar->bEmGuerra = 0; // Deixar em zero por enquanto pra depois implementar isso
    aIniciar->prox = NULL;
    return aIniciar;
}


