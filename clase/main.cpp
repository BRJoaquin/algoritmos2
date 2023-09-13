#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
using namespace std;

int main()
{
    Graph *graph = new GraphListImp(5, false, false);
    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 4);
    graph->addEdge(3, 4);
    graph->addEdge(4, 5);

    int *distance = new int[graph->getV() + 1];
    graph->BFS(1, [&distance](int vertex, int step) {
        distance[vertex] = step;
    });

    for (int i = 1; i <= graph->getV(); i++)
    {
        cout << "Distance from 1 to " << i << ": " << distance[i] << endl;
    }
    return 0;
}