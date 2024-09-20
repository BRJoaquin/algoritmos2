#ifndef GRAPH_H
#define GRAPH_H

#include "Queue.h"
#include "QueueImp.cpp"
#include "../Helpers/Iterator.h"
#include "../Helpers/Tuple.cpp"
using namespace std;

struct Edge
{
    int from;
    int to;
    int weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    Edge(int from, int to) : from(from), to(to), weight(1) {}
    Edge() {}
    ~Edge() {}
    bool operator==(const Edge &other) const
    {
        return (from == other.from && to == other.to);
    }
};

class Graph
{
private:
    

protected:
    int V;
    int A;
    bool directed;
    bool weighted;

public:
    virtual void addEdge(int from, int to, int weight = 1) = 0;
    virtual Iterator<Edge> *adjacents(int from) = 0;

    Graph(unsigned int V, bool directed, bool weighted)
    {
        this->V = V;
        this->A = 0;
        this->directed = directed;
        this->weighted = weighted;
    }

    // virtual ~Graph() {}

    int getV() { return V; }
    int getA() { return A; }
    bool isDirected() { return directed; }
    bool isWeighted() { return weighted; }
};
#endif