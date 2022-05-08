#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int * initVisitados(int V) {
    int * ret = new int[V+1]();
    for(int v=1; v <= V; v++) {
        ret[v] = false;
    }
    return ret;
}

void DFS(Grafo *g, int origen, int prohibido, int * visitados) {
    if(origen == prohibido) return;
    visitados[origen] = true;
    // recorro los adyacentes
    ListaArsita ady = g->aydyacentes(origen);
    while(ady!=NULL){
        int w = ady->dato.destino;
        // si ya no lo visite previamente, lo llamo recursivamente
        if(!visitados[w]) {
            DFS(g,w,prohibodo,visitados);
        }
        ady = ady->sig;
    }
}

bool todosTrue(int *visitados,int verticeAEvaluar, int V) {
    for(int v=1; v <= V; v++) {
        if(!visitados[v] && v!=verticeAEvaluar) return false;
    }
    return true;
}

bool esPuntoDeArticulacion(Grafo *g, int verticeAEvaluar, int V) {
    int * visitados =  initVisitados(V);
    ListaArsita ady = g->adyacentesA(verticeAEvaluar);
    int dfsNodoSalida = ady->dato.destino; 
    DFS(g, dfsNodoSalida, verticeAEvaluar, visitados);
    return !todosTrue(visitados, verticeAEvaluar, V);
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