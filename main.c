#include<stdio.h>
#include<stdlib.h>
#include<time.h>
// pra mudar pro grafo exemplar eh mudar esse define pra 4, descomentar os grafo_insere_duplo la embaixo e comentar os grafo_insere_duplo embaixo do grafo do computerphile,
// fazer o contrario pra fazer o contrario

#define QPLANETAS 13

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
void grafo_dijkstra(plan ** grafo, int gfInicio, int * iCusto, int * gfAnterior);

int main(){
    srand(time(NULL));
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
            printf("%d (%d)  ",aux->prox->iNdice+1,aux->prox->iTempo);
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

void grafo_dijkstra(plan ** grafo, int gfInicio, int * iCusto, int * gfAnterior){

    int * gfVisitados = malloc(sizeof*gfVisitados * QPLANETAS); // Lista de indices que ja tiveram todos vertices adjacentes visitados
    int gfVisitadosTam = 0;
    int * gfMenorCaminho = malloc(sizeof*gfVisitados * QPLANETAS); // Lista de indices que estao para ser testadas mas ja foram vistas por outro vertice
    int gfMenorCaminhoTam = 0;


    gfMenorCaminho[gfMenorCaminhoTam] = gfInicio;
    gfMenorCaminhoTam += 1;
    gfAnterior[gfInicio] = gfInicio;
    iCusto[gfInicio] = 0; // Nao há distancia entre o primeiro e ele mesmo
    int gfAtual = gfInicio;


    while (gfMenorCaminhoTam != 0){
        int i;
        int minAux = 0;
        // Escolher o que ta na lista com o menor custo >> ** em relação ao atual  ** << 
        for (i = 1; i < gfMenorCaminhoTam; i += 1){
            if (iCusto[gfMenorCaminho[minAux]] > iCusto[gfMenorCaminho[i]] ){ // Se o custo de tempo do atual for maior do que o de outro
                minAux = i;                                                  // Guarda o com menor custo
            }
        }
        gfAtual = gfMenorCaminho[minAux];
        // Tira o Atual da lista
        gfMenorCaminho[minAux] = gfMenorCaminho[gfMenorCaminhoTam -1];
        gfMenorCaminhoTam -= 1;
        // COloca ele na lista dos ja visitados
        gfVisitados[gfVisitadosTam] = gfAtual;
        gfVisitadosTam += 1;


        plan * aux = grafo[gfAtual];
        aux = aux->prox; // Coloca no primeiro próximo gráfico de uma vez, talvez tenha que mudar isso pra fazer contar pode esperar
        int bJaVisitou; // Booleana se uma vertice adjacente ja foi vistada
        int bEstaLista; // Booleana se um vertice já está na lista
        while (aux != NULL){ // Enquanto tiver vertices adjacentes
            bJaVisitou = 0;
            for (i = 0; i < gfVisitadosTam; i += 1){ // Procura nos vertices ja visitados pelo atual
                if (aux->iNdice == gfVisitados[i]){
                    bJaVisitou = 1; // Se achar só passa pro próximo vertice
                }
            }
            if (bJaVisitou != 1){
                bEstaLista = 0;
                for (i = 0; i < gfMenorCaminhoTam; i += 1){ // Se for um dos grafos que esta na lista
                    if (aux->iNdice == gfMenorCaminho[i]){ // Se sim existe outro caminho e testamos qual o menor
                        bEstaLista = 1;
                        if (iCusto[gfAtual] + aux->iTempo < iCusto[gfMenorCaminho[i]]){ // Se sim o que acabamos de descobrir eh menor
                            iCusto[gfMenorCaminho[i]] = iCusto[gfAtual] + aux->iTempo; // O novo menor eh esse
                            gfAnterior[gfMenorCaminho[i]] = gfAtual; // O anterior ao desse outro caminho eh o atual
                        }
                    break;
                    }

                }
                if (bEstaLista != 1){ // Se nao estiver na lista a gente coloca na lista(menorcaminho) e nas outras coisas
                    gfMenorCaminho[gfMenorCaminhoTam] = aux->iNdice;
                    gfMenorCaminhoTam += 1;
                    iCusto[aux->iNdice] = aux->iTempo + iCusto[gfAtual]; // O custo do atual eh o custo do atual (o mais curto ate agr) e o caminho
                    gfAnterior[aux->iNdice] = gfAtual;
                }

            }

            aux = aux->prox;
        }


    }
}




