#ifndef STAREN_H
#define STAREN_H

#define QPLANETAS 13

typedef struct planeta{
    int gfIndice;
    int iTempo;
    int bEmGuerra;
    struct planeta * prox;
}plan;

plan * grafo_inicia(int gfIndice);
void grafo_insere(plan * aInserir, int gfIndice, int iTempo, int bEmGuerra);
void grafo_libera(plan * grafo);
void grafo_insere_duplo(plan ** grafo, int prim, int sec, int iTempo, int bEmGuerra);
void grafo_dijkstra(plan ** grafo, int gfInicio, int * iCusto, int * gfAnterior);
int dijkstra_pesototal(plan ** grafo, int origem, int destino);
int dijkstra_proximo(plan ** grafo, int origem, int destino);

#endif
