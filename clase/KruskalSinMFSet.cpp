#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
#include "MinHeap.cpp"

using namespace std;

int comparacionAristas(Edge a, Edge b)
{
    return a.weight - b.weight;
}

void llenarHeap(Graph *g, MinHeap<Edge> *aristas)
{
    for (int v = 1; v <= g->getV(); v++)
    {
        Iterator<Edge> *it = g->adjacents(v);
        while (it->hasNext())
        {
            Edge e = it->next();
            aristas->insertar(e);
        }
    }
}

bool estanConectados(Graph *g, int from, int to)
{
    bool *inqueue = new bool[g->getV() + 1]();
    Queue<int> *toProcess = new QueueImp<int>();
    toProcess->enqueue(from);
    inqueue[from] = true;

    while (!toProcess->isEmpty())
    {
        int v = toProcess->dequeue();
        Iterator<Edge> *ady = g->adjacents(v);
        while (ady->hasNext())
        {
            Edge arista = ady->next();
            int w = arista.to;
            if (!inqueue[w])
            {
                toProcess->enqueue(w);
                inqueue[w] = true;
            }
        }
    }

    return inqueue[to];
}

Graph *kruskal(Graph *g)
{
    int A = g->getA();
    MinHeap<Edge> *aristas = new MinHeap<Edge>(A + A, comparacionAristas);
    llenarHeap(g, aristas);
    int count = 0;
    Graph *ACM = new GraphListImp(g->getV(), false, true);
    while (!aristas->estaVacio() && count < g->getV() - 1)
    {
        Edge e = aristas->tope();
        aristas->eliminar();
        if (estanConectados(g, e.from, e.to))
        {
            count++;
            ACM->addEdge(e.from, e.to, e.weight);
        }
    }
    return ACM;
}

int main()
{
    Graph *grafito = new GraphListImp(9, false, true);
    grafito->addEdge(1, 2, 2);
    grafito->addEdge(1, 3, 4);
    grafito->addEdge(2, 5, 22);
    grafito->addEdge(2, 6, 12);
    grafito->addEdge(3, 2, 1);
    grafito->addEdge(3, 6, 3);
    grafito->addEdge(3, 5, 4);
    grafito->addEdge(3, 7, 5);
    grafito->addEdge(4, 3, 2);
    grafito->addEdge(4, 1, 10);
    grafito->addEdge(6, 3, 8);
    grafito->addEdge(7, 4, 3);
    grafito->addEdge(7, 5, 1);
    grafito->addEdge(5, 8, 10);
    grafito->addEdge(8, 9, 2);
    grafito->addEdge(9, 5, 3);

    dijkstra(grafito, 5);
}