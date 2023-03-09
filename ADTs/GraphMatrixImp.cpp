#include "./Graph.h"

class GraphMatrixImp : public Graph
{
private:
    int **matriz;

public:
    GraphMatrixImp(unsigned int V, bool directed, bool weighted) : Graph(V, directed, weighted)
    {
        matriz = new int *[V + 1];
        for (int i = 0; i <= V; i++)
        {
            matriz[i] = new int[V + 1]();
            for (int j = 0; j <= V; j++)
            {
                matriz[i][j] = 0;
            }
        }
    }
    void addEdge(int from, int to, int weight = 1);
    Iterator<Edge> *adjacents(int from);
};