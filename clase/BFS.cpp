#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Graph.h"
#include "../ADTs/GraphListImp.cpp"
#include "../ADTs/Queue.h"
#include "../ADTs/QueueImp.cpp"
using namespace std;


void BFS(Graph *g, int from) {
    bool* inqueue = new bool[g->getV() + 1]();
    Queue<int> * toProcess = new QueueImp<int>();
    toProcess->enqueue(from);
    inqueue[from] = true;

    while(!toProcess->isEmpty()) {
        int v = toProcess->dequeue();
        // procesar
        cout << v << endl;
        Iterator<Edge> *ady = g->adjacents(v);
        while(ady->hasNext()){
            Edge arista = ady->next();
            int w = arista.to;
            if(!inqueue[w]) {
                toProcess->enqueue(w);
                inqueue[w] = true;
            }
        }
    }
}

bool esConexo(Graph *g) {
    int from = 1;
    bool* inqueue = new bool[g->getV() + 1]();
    Queue<int> * toProcess = new QueueImp<int>();
    toProcess->enqueue(from);
    inqueue[from] = true;

    while(!toProcess->isEmpty()) {
        int v = toProcess->dequeue();
        // procesar
        // cout << v << endl;
        Iterator<Edge> *ady = g->adjacents(v);
        while(ady->hasNext()){
            Edge arista = ady->next();
            int w = arista.to;
            if(!inqueue[w]) {
                toProcess->enqueue(w);
                inqueue[w] = true;
            }
        }
    }

    for(int i = 1; i <= g->getV(); i++){
        if(!inqueue[i]) {
            return false;
        }
    }
    return true;
}

void caminoRec(int v, int* path) {
    if(path[v] == 0) {
        cout << v ;
    }else {
        caminoRec(path[v], path);
        cout << "->" << v;
    }
}

void costo(Graph *g, int from) {
    bool* inqueue = new bool[g->getV() + 1]();
    int * cost = new int[g->getV() + 1]();
    int * path = new int[g->getV() + 1]();
    Queue<int> * toProcess = new QueueImp<int>();
    toProcess->enqueue(from);
    inqueue[from] = true;

    while(!toProcess->isEmpty()) {
        int v = toProcess->dequeue();
        Iterator<Edge> *ady = g->adjacents(v);
        while(ady->hasNext()){
            Edge arista = ady->next();
            int w = arista.to;
            if(!inqueue[w]) {
                cost[w] = cost[v] + 1;
                path[w] = v;
                toProcess->enqueue(w);
                inqueue[w] = true;
            }
        }
    }

    for(int i = 1; i <= g->getV(); i++) {
        cout << "voy de " << from << " a " << i << " con costo: " << cost[i] << endl;
        cout << "camino: " << endl;
        caminoRec(i, path);
        cout << endl <<"----- barra espaciadora de bajo presupuesto ----" << endl;
    }
}


bool esBiparito(Graph *g) {
    int from = 1;
    int* color = new int[g->getV() + 1]();
    bool* inqueue = new bool[g->getV() + 1]();
    Queue<int> * toProcess = new QueueImp<int>();
    toProcess->enqueue(from);
    inqueue[from] = true;
    color[from] = 1;

    while(!toProcess->isEmpty()) {
        int v = toProcess->dequeue();
        Iterator<Edge> *ady = g->adjacents(v);
        while(ady->hasNext()){
            Edge arista = ady->next();
            int w = arista.to;
            if(color[w] == 0) {
                color[w] = color[v] * -1;
            }else if(color[w] == color[v]) {
                return false;
            }
            if(!inqueue[w]) {
                toProcess->enqueue(w);
                inqueue[w] = true;
            }
        }
    }
    return true;
}

int main()
{
    Graph * grafito = new GraphListImp(8, false, false);
    grafito->addEdge(1,4);
    grafito->addEdge(2,4);
    grafito->addEdge(2,3);
    grafito->addEdge(3,4);
    grafito->addEdge(4,7);
    grafito->addEdge(3,5);
    grafito->addEdge(5,6);
    grafito->addEdge(8,7);
    grafito->addEdge(3,8);
    grafito->addEdge(5,7);



    // BFS(grafito, 2);

    // if(esConexo(grafito)) {
    //     cout << "es conexo" << endl;
    // } else {
    //     cout << "no es conexo" << endl;
    // }

    // costo(grafito, 4);

    if(esBiparito(grafito)) {
        cout << "es bipartito" << endl;
    } else {
        cout << "no es bipartito" << endl;
    }
}