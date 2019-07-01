#include<stdio.h>
#include<stdlib.h>
#include"staren.h"

void grafo_insere(plan * aInserir, int gfIndice, int iTempo, int bEmGuerra){
    plan * aux = aInserir;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    plan * novo = malloc(sizeof*novo);
    aux->prox = novo;
    novo->iTempo = iTempo;
    novo->bEmGuerra = bEmGuerra;
    novo->gfIndice = gfIndice;
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
    novo->gfIndice = sec; // Conexão do primário pro segundário
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
    novoSec->gfIndice = prim; // Conexão do secundario pro primário
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
                if (aux->gfIndice == gfVisitados[i]){
                    bJaVisitou = 1; // Se achar só passa pro próximo vertice
                }
            }
            if (bJaVisitou != 1){
                bEstaLista = 0;
                for (i = 0; i < gfMenorCaminhoTam; i += 1){ // Se for um dos grafos que esta na lista
                    if (aux->gfIndice == gfMenorCaminho[i]){ // Se sim existe outro caminho e testamos qual o menor
                        bEstaLista = 1;
                        if (iCusto[gfAtual] + aux->iTempo < iCusto[gfMenorCaminho[i]]){ // Se sim o que acabamos de descobrir eh menor
                            iCusto[gfMenorCaminho[i]] = iCusto[gfAtual] + aux->iTempo; // O novo menor eh esse
                            gfAnterior[gfMenorCaminho[i]] = gfAtual; // O anterior ao desse outro caminho eh o atual
                        }
                        break; // so precisa percorrer ate achar, achou, sai
                    }

                }
                if (bEstaLista != 1){ // Se nao estiver na lista a gente coloca na lista(menorcaminho) e nas outras coisas
                    gfMenorCaminho[gfMenorCaminhoTam] = aux->gfIndice;
                    gfMenorCaminhoTam += 1;
                    iCusto[aux->gfIndice] = aux->iTempo + iCusto[gfAtual]; // O custo do atual eh o custo do atual (o mais curto ate agr) e o caminho
                    gfAnterior[aux->gfIndice] = gfAtual;
                }

            }

            aux = aux->prox;
        }


    }
    free(gfVisitados);
    free(gfMenorCaminho);
}

int dijkstra_pesototal(plan ** grafo, int origem, int destino){
    int * iCusto = malloc(sizeof*iCusto * QPLANETAS);
    int * gfAnterior = malloc(sizeof*gfAnterior * QPLANETAS);
    grafo_dijkstra(grafo, origem, iCusto, gfAnterior);
    int x = iCusto[destino];
    free(iCusto);
    free(gfAnterior);
    return x;

}

int dijkstra_proximo(plan ** grafo, int origem, int destino){
    int * iCusto = malloc(sizeof*iCusto * QPLANETAS);
    int * gfAnterior = malloc(sizeof*gfAnterior * QPLANETAS);
    grafo_dijkstra(grafo, origem, iCusto, gfAnterior);
    int x = destino;
    while (gfAnterior[x] != origem){
        x = gfAnterior[x];
    }
    free(iCusto);
    free(gfAnterior);
    return x;

}




