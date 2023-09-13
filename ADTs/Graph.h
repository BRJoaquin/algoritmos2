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
    void DFS(int from, int step, std::function<void(int, int)> each, bool *visited)
    {
        visited[from] = true;
        each(from, step);
        Edge edge;
        Iterator<Edge> *it = this->adjacents(from);
        while (it->hasNext())
        {
            edge = it->next();
            int w = edge.to;
            if (!visited[w])
            {
                DFS(w, step + 1, each, visited);
            }
        }
    }

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

    void BFS(int from, std::function<void(int, int)> each)
    {
        bool *queued = new bool[V + 1]();
        for (int i = 0; i <= V; i++)
        {
            queued[i] = false;
        }
        Queue<Tuple<int, int>> *queue = new QueueImp<Tuple<int, int>>();
        queue->enqueue(Tuple<int, int>(from, 0));
        queued[from] = true;
        while (!queue->isEmpty())
        {
            Tuple<int, int> node = queue->dequeue();
            int v = node.getFirst();
            int step = node.getSecond();
            each(v, step);
            Edge edge;
            Iterator<Edge> *it = adjacents(v);
            while (it->hasNext())
            {
                edge = it->next();
                int w = edge.to;
                if (!queued[w])
                {
                    queued[w] = true;
                    queue->enqueue(Tuple<int, int>(w, step + 1));
                }
            }
        }
        delete[] queued;
    }

    void DFS(int from, std::function<void(int, int)> each)
    {
        bool *visited = new bool[V + 1]();
        for (int i = 0; i <= V; i++)
        {
            visited[i] = false;
        }
        DFS(from, 0, each, visited);
        delete[] visited;
    }
};
#endif