#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

bool** construirMatrizDeAdyacencia(Grafo *g, int V) {
    bool** matriz = new bool*[V+1]()
    for(int i=1; i <=V; i++) {
        matriz[i] = new bool[V+1]();
    }
    for(int i=1; i <=V; i++) {
        ListaArista ady = g->adyacentesA(i);
        while(ady!=NULL){
            int w = ady->dato.destino;
            matriz[i][w] = true;
            ady= ady->sig;
        }
    }
}


bool **warshall(Grafo *g, int verticeAEvaluar, int V) {
    bool** m = construirMatrizDeAdyacencia(g, v);
    for(int k=1; k <=V; k++) {
        for(int i=1; i <=V; i++) {
            for(int j=1; j <=V; j++) {
                if(i != verticeAEvaluar && j != verticeAEvaluar && k != verticeAEvaluar) {
                    m[i][j] = m[i][j] || m[i][k] && m[k][j];
                }
            }
        }
    }
    return m;
}

bool todosTrue(bool **warshall, int verticeAEvaluar, int V) {
    for(int i=1; i <=V; i++) {
        for(int j=1; j <=V; j++) {
            if(i != verticeAEvaluar && j != verticeAEvaluar) {
                if(!warshall[i][j]) return false;
            }
        }
    }
    return true;
}


bool esPuntoDeArticulacion(Grafo *g, int verticeAEvaluar, int V) {
    bool **warshall = warshall(g, verticeAEvaluar, V);
    return !todosTrue( warshall, verticeAEvaluar, V);
}


bool esBiconexo(Grafo *g, int V) {
    for(int v=1; v <= V; v++) {
        if(esPuntoDeArticulacion(g,v,V)) return false;
    }
    return true;
}

int main()
{
    
    return 0;
}