#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
using namespace std;

int nextToProcess(bool *visitado, int *costo, int V)
{
    int menor = -1;
    for (int v = 1; v <= V; v++)
    {
        if (!visitado[v] && costo[v] < INT_MAX)
        {
            if (menor == -1)
            {
                menor = v;
            }
            else if (costo[menor] > costo[v])
            {
                menor = v;
            }
        }
    }
    return menor;
}

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

void dijkstra(Graph *g, int from)
{
    bool *visitado = new bool[g->getV() + 1]();
    int *costo = new int[g->getV() + 1]();
    int *vengo = new int[g->getV() + 1]();

    for (int v = 1; v <= g->getV(); v++)
    {
        visitado[v] = false;
        costo[v] = INT_MAX;
        vengo[v] = -1;
    }

    costo[from] = 0;
    for (int i = 1; i <= g->getV(); i++)
    {
        int v = nextToProcess(visitado, costo, g->getV());
        if (v == -1)
        {
            break;
        }
        visitado[v] = true;
        Iterator<Edge> *ady = g->adjacents(v);
        while (ady->hasNext())
        {
            Edge arista = ady->next();
            int w = arista.to;
            if (costo[w] > costo[v] + arista.weight)
            {
                costo[w] = costo[v] + arista.weight;
                vengo[w] = v;
            }
        }
    }

    for (int i = 1; i <= g->getV(); i++)
    {
        if (!visitado[i])
        {
            cout << "No existe camino de " << from << " a " << i << endl;
        }
        else
        {
            cout << "voy de " << from << " a " << i << " con costo: " << costo[i] << endl;
            cout << "camino: " << endl;
            caminoRec(i, vengo);
        }

        cout << endl
             << "----- barra espaciadora de bajo presupuesto ----" << endl;
    }
}

int main()
{
    Graph *grafito = new GraphListImp(9, true, true);
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