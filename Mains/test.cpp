#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
#include "../DataStructures/MinHeap.cpp"
#include "../DataStructures/DisjointSet.cpp"
using namespace std;

int **initMatrizCosto(Graph *g)
{
    int **m = new int *[g->getV() + 1]();
    for (int i = 1; i <= g->getV(); i++)
    {
        m[i] = new int[g->getV() + 1]();
        for (int j = 0; j <= g->getV(); j++)
        {
            m[i][j] = INT_MAX;
        }
    }

    for (int origen = 1; origen <= g->getV(); origen++)
    {
        Iterator<Edge> *it = g->adjacents(origen);
        while (it->hasNext())
        {
            Edge e = it->next();
            int destino = e.to;
            int peso = e.weight;
            if (origen != destino)
            {
                m[origen][destino] = peso;
            }
        }
    }

    return m;
}

void floyd(Graph *g)
{
    int V = g->getV();
    int **matrizCosto = initMatrizCosto(g);

    for (int k = 1; k <= V; k++)
    {
        for (int i = 1; i <= V; i++)
        {
            for (int j = 1; j <= V; j++)
            {
                if (matrizCosto[i][k] != INT_MAX && matrizCosto[k][j] != INT_MAX  
                    && matrizCosto[i][j] > matrizCosto[i][k] + matrizCosto[k][j] ) {
                    matrizCosto[i][j] = matrizCosto[i][k] + matrizCosto[k][j];
                }
            }
        }
    }

    cout << "Costo del 3 al 1:" << matrizCosto[3][1] << endl;
}

int compararEdge(Edge e1, Edge e2)
{
    return e1.weight - e2.weight;
}

void cargarAristas(Graph *g, MinHeap<Edge> *heap)
{
    for (int origen = 1; origen <= g->getV(); origen++)
    {
        Iterator<Edge> *it = g->adjacents(origen);
        while (it->hasNext())
        {
            Edge e = it->next();
            int destino = e.to;
            int peso = e.weight;
            if (origen != destino)
            {
                heap->insertar(e);
            }
        }
    }
}

void kruskal(Graph *g) {
    int V = g->getV();
    int aristasAceptadas = 0;
    MinHeap<Edge> *heap = new MinHeap<Edge>(V*V, compararEdge);
    cargarAristas(g, heap);

    DisjointSet *disjointSet = new DisjointSet(V);
    int total = 0;
    while (!heap->estaVacio() || aristasAceptadas < V - 1) {
        Edge e = heap->tope();
        heap->eliminarTope();
        int origen = e.from;
        int destino = e.to;
        int peso = e.weight;
        if (disjointSet->find(origen) != disjointSet->find(destino)) {
            disjointSet->merge(origen, destino);
            aristasAceptadas++;
            total += peso;
            cout << "arista aceptada: " << origen << " " << destino << " " << peso << endl;
        }
    }

    cout << "Costo total: " << total << endl;
}

int main()
{
    Graph *graph = new GraphListImp(5, false, true);
    graph->addEdge(1, 2, 10);
    graph->addEdge(1, 4, 1);
    graph->addEdge(2, 4, 5);
    graph->addEdge(2, 3, 2);
    graph->addEdge(4, 3, 12);
    graph->addEdge(3, 5, 1);
    graph->addEdge(4, 5, -4);

    // floyd(graph);
    kruskal(graph);
    return 0;
}