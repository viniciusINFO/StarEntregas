#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define QPLANETAS 4

typedef struct planeta{
    int iNdice;
    int iTempo;
    int bEmGuerra;
    struct planeta * prox;
}plan;

plan * grafo_inicia(int iNdice);
void grafo_insere(plan * aInserir, int iNdice, int iTempo, int bEmGuerra);
void grafo_libera(plan * grafo);
void grafo_insere_duplo(plan ** grafo, int prim, int sec, int iTempo, int bEmGuerra);

int main(){
    srand(time(NULL));
    plan ** grafo = malloc(sizeof**grafo * QPLANETAS); // Inicia o vetor da lista de adjacência
    int i,j; // Auxiliares pro for
    for (i = 0; i < QPLANETAS; i += 1){ // Inicia cada um dos planetas
        grafo[i] = grafo_inicia(i);
    } 
    // Criação de grafo arbitrário nao direcionado
    // ------------------------------------------------------ //
    //grafo_insere(grafo[0], 1, 2, 0);
    //grafo_insere(grafo[1], 0, 2, 0);
    grafo_insere_duplo(grafo, 0, 1, 2, 0);

    //grafo_insere(grafo[0], 2, 5, 0);
    //grafo_insere(grafo[2], 0, 5, 0);
    grafo_insere_duplo(grafo, 0, 2, 5, 0);

    //grafo_insere(grafo[1], 2, 2, 0);
    //grafo_insere(grafo[2], 1, 2, 0);
    grafo_insere_duplo(grafo, 1, 2, 2, 0);

    //grafo_insere(grafo[2], 3, 5, 0);
    //grafo_insere(grafo[3], 2, 5, 0);
    grafo_insere_duplo(grafo, 2, 3, 5, 0);

    grafo_insere_duplo(grafo, 3, 0, 1, 0);
    // ------------------------------------------------------ //
   
    
    // --------------- Printa o grafo -------------------- //
    for (i = 0; i < QPLANETAS; i += 1){
        plan * aux = grafo[i];
        printf("\n %d: ",i);
        while (aux->prox != NULL){
            printf("%d (%d)  ",aux->prox->iNdice,aux->prox->iTempo);
            aux = aux->prox;
        }
    }



    // ------------ Libera o grafo ----------------------------- //
    for (i = 0; i < QPLANETAS; i += 1){
        grafo_libera(grafo[i]);
    }
    free(grafo);
}

plan * grafo_inicia(int iNdice){
    plan * aIniciar = malloc(sizeof * aIniciar);
    aIniciar->iNdice = iNdice;
    aIniciar->iTempo = 1; // Ir de um planeta para o mesmo significa esperar uma hora nele
    aIniciar->bEmGuerra = 0; // Deixar em zero por enquanto pra depois implementar isso
    aIniciar->prox = NULL;
    return aIniciar;
}


void grafo_insere(plan * aInserir, int iNdice, int iTempo, int bEmGuerra){
    plan * aux = aInserir;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    plan * novo = malloc(sizeof * novo);
    aux->prox = novo;
    novo->iTempo = iTempo;
    novo->bEmGuerra = bEmGuerra;
    novo->iNdice = iNdice;
    novo->prox = NULL;

}

void grafo_insere_duplo(plan ** grafo, int prim, int sec, int iTempo, int bEmGuerra){
    plan * aInserir = grafo[prim];

    plan * aux = aInserir;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    plan * novo = malloc(sizeof * novo);
    aux->prox = novo; 
    novo->iTempo = iTempo;
    novo->bEmGuerra = grafo[sec]->bEmGuerra;
    novo->iNdice = sec; // Conexão do primário pro segundário
    novo->prox = NULL;


    plan * aInserirSec = grafo[sec];
    aux = aInserirSec;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    plan * novoSec = malloc(sizeof * novoSec);
    aux->prox = novoSec;
    novoSec->iTempo = iTempo;
    novoSec->bEmGuerra = grafo[prim]->bEmGuerra;
    novoSec->iNdice = prim; // Conexão do secundario pro primário
    novoSec->prox = NULL;
}

void grafo_libera(plan * grafo){
    if (grafo->prox == NULL){
        free(grafo);
        return;
    }
    grafo_libera(grafo->prox);
    free(grafo);
}







