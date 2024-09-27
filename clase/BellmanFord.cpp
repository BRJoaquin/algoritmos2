#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
#include "../ADTs/Queue.h"
#include "../ADTs/QueueImp.cpp"
using namespace std;

void caminoRec(int v, int *path)
{
    if (path[v] == -1)
    {
        cout << v;
    }
    else
    {
        caminoRec(path[v], path);
        cout << "->" << v;
    }
}

void bellmanFord(Graph *g, int origen)
{
    int *costos = new int[g->getV() + 1]();
    int *vengo = new int[g->getV() + 1]();
    bool *enCola = new bool[g->getV() + 1]();
    int *vecesEncolado = new int[g->getV() + 1]();

    for (int v = 1; v <= g->getV(); v++)
    {
        costos[v] = INT_MAX;
        vengo[v] = -1;
        enCola[v] = false;
        vecesEncolado[v] = 0;
    }

    Queue<int> *toProcess = new QueueImp<int>();
    toProcess->enqueue(origen);
    enCola[origen] = true;
    costos[origen] = 0;

    while (!toProcess->isEmpty())
    {
        int v = toProcess->dequeue();
        enCola[v] = false;
        if (vecesEncolado[v] > g->getV())
        {
            cout << "ciclo negativo detectado!";
            return;
        }
        Iterator<Edge> *ady = g->adjacents(v);
        while (ady->hasNext())
        {
            Edge arista = ady->next();
            int w = arista.to;
            if (costos[w] > costos[v] + arista.weight)
            {
                costos[w] = costos[v] + arista.weight;
                vengo[w] = v;
                if (!enCola[w])
                {
                    toProcess->enqueue(w);
                    enCola[w] = true;
                    vecesEncolado[w]++;
                }
            }
        }
    }

    for (int v = 1; v <= g->getV(); v++)
    {
        if (v == origen)
        {
            continue;
        }
        if (costos[v] < INT_MAX)
        {
            cout << "el costo de ir hasta " << v << " es " << costos[v] << endl;
            caminoRec(v, vengo);
            cout << endl;
        }
        else
        {
            cout << "no hay un camino hasta " << v << endl;
        }
    }
}

int main()
{
    Graph *grafito = new GraphListImp(6, true, true);
    grafito->addEdge(1, 5, 5);
    grafito->addEdge(1, 3, 2);
    grafito->addEdge(3, 2, 4);
    grafito->addEdge(5, 6, 2);
    grafito->addEdge(6, 3, -8);
    grafito->addEdge(6, 2, 3);
    grafito->addEdge(2, 4, 5);
    // grafito->addEdge(3, 1, 0);

    bellmanFord(grafito, 6);
}