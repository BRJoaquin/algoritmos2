#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
using namespace std;


void warshall(Graph *g)
{
    int V = g->getV();
    bool **mct = new bool *[V + 1]();
    for (int i = 1; i <= V; i++)
    {
        mct[i] = new bool[V + 1]();
        for (int j = 1; j <= V; j++)
        {
            mct[i][j] = false;
        }
    }

    for (int v = 1; v <= V; v++)
    {
        Iterator<Edge> *ady = g->adjacents(v);
        while (ady->hasNext())
        {
            Edge arista = ady->next();
            int w = arista.to;
            mct[v][w] = true;
        }
    }

    for (int i = 1; i <= V; i++)
    {
        for (int o = 1; o <= V; o++)
        {
            for (int d = 1; d <= V; d++)
            {
                // mct[o][d] = mct[o][d] || mct[o][i] && mct[i][d];
                if(mct[o][i] && mct[i][d]) {
                    mct[o][d] = true;
                }
            }
        }
    }

    for (int o = 1; o <= V; o++)
    {
        cout << "desde " << o << " puedo ir a: ";
        for (int d = 1; d <= V; d++)
        {
            if (o == d)
                continue;
            if (mct[o][d])
            {
                cout << d << " ";
            }
        }
        cout << endl;
    }
}


void floyd(Graph *g)
{
    int V = g->getV();
    int **costo = new int *[V + 1]();
    int **vengo = new int *[V + 1]();
    for (int i = 1; i <= V; i++)
    {
        costo[i] = new int[V + 1]();
        vengo[i] = new int[V + 1]();
        for (int j = 1; j <= V; j++)
        {
            costo[i][j] = INT_MAX;
            vengo[i][j] = -1;
        }
    }

    for (int v = 1; v <= V; v++)
    {
        Iterator<Edge> *ady = g->adjacents(v);
        while (ady->hasNext())
        {
            Edge arista = ady->next();
            int w = arista.to;
            costo[v][w] = arista.weight;
            vengo[v][w] = v;
        }
    }

    for (int i = 1; i <= V; i++)
    {
        for (int o = 1; o <= V; o++)
        {
            for (int d = 1; d <= V; d++)
            {
                // chequeamos que al menos haya un camino de origen a intermedio
                // y de intermedio a destino
                if (costo[o][i] == INT_MAX || costo[i][d] == INT_MAX)
                    continue;
                if (costo[o][i] + costo[i][d] < costo[o][d])
                {
                    costo[o][d] = costo[o][i] + costo[i][d];
                    vengo[o][d] = i;
                }
            }
        }
    }

    for (int o = 1; o <= V; o++)
    {
        cout << endl
             << endl
             << "----- barra espaciadora de bajo presupuesto -----" << endl
             << endl;
        cout << "Caminos mas cortos empezando deeeee " << o << endl;
        for (int d = 1; d <= V; d++)
        {
            if (o == d)
                continue;
            if (costo[o][d] == INT_MAX)
            {
                cout << " no hay camino a " << d << endl;
            }
            else
            {
                cout << "costo hasta " << d << " es de " << costo[o][d] << endl;
            }
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
    grafito->addEdge(6, 3, -7);
    grafito->addEdge(6, 2, 3);
    grafito->addEdge(2, 4, 5);

    // floyd(grafito);
    warshall(grafito);
}