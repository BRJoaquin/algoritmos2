#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
using namespace std;

void DFS(Graph *g, int v, bool *visitado)
{
    visitado[v] = true;
    Iterator<Edge> *aristas = g->adjacents(v);
    while (aristas->hasNext())
    {
        Edge e = aristas->next();
        int w = e.to;
        if (!visitado[w])
        {
            DFS(g, w, visitado);
        }
    }
}

bool esConexo(Graph *g, int verticeAIgnorar)
{
    bool *visitado = new bool[g->getV() + 1]();
    int start = verticeAIgnorar == 1 ? 2 : 1;
    visitado[verticeAIgnorar] = true;
    DFS(g, start, visitado);
    for (int v = 1; v <= g->getV(); v++)
    {
        if (!visitado[v])
        {
            return false;
        }
    }
    return true;
}

bool esBiconexo(Graph *g)
{

    for (int v = 1; v <= g->getV(); v++)
    {
        if (!esConexo(g, v))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    Graph *grafito = new GraphListImp(5, false, false);
    grafito->addEdge(1, 2);
    grafito->addEdge(1, 3);
    grafito->addEdge(1, 4);
    grafito->addEdge(2, 3);
    grafito->addEdge(3, 5);
    grafito->addEdge(4, 5);

    // Graph *grafito = new GraphListImp(3, false, false);
    // grafito->addEdge(1, 2);
    // grafito->addEdge(2, 3);

    if (esBiconexo(grafito))
    {
        cout << "es biconexo " << endl;
    }
    else
    {
        cout << "no lo es  :(" << endl;
    }
}