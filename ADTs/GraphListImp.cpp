#ifndef GRAPH_LIST_IMP
#define GRAPH_LIST_IMP

#include "./Graph.h"
#include "./List.h"
#include "./ListImp.cpp"

class GraphListImp : public Graph
{
private:
    typedef List<Edge> *AdjacentsList;
    AdjacentsList *listOfAdjacents;

public:
    GraphListImp(unsigned int V, bool directed, bool weighted) : Graph(V, directed, weighted)
    {
        listOfAdjacents = new AdjacentsList[V + 1]();
        for (int i = 1; i <= V; i++)
        {
            listOfAdjacents[i] = new ListImp<Edge>();
        }
    }
    void addEdge(int from, int to, int weight = 1)
    {
        Edge edge(from, to, this->isWeighted() ? weight : 1);
        listOfAdjacents[from]->insert(edge);
        if (!directed)
        {
            Edge twingEdge(to, from, this->isWeighted() ? weight : 1);
            listOfAdjacents[to]->insert(twingEdge);
        }
        A++;
    }
    Iterator<Edge> *adjacents(int from)
    {
        return listOfAdjacents[from]->getIterator();
    }
};

#endif