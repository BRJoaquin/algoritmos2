#include <string>
#include <iostream>
#include <limits>
#include "../ADTs/Queue.h"
#include "../ADTs/QueueImp.cpp"

using namespace std;

template <class T>
class NodoLista {
    public:
        T dato;
        NodoLista * sig;
        NodoLista(T _dato, NodoLista * _sig) : dato(_dato), sig(_sig) {};
        NodoLista(T _dato) : dato(_dato), sig(NULL) {};
};

class Arista {
    public:
        // int origen; queda en ustedes usarlo
        int destino;
        int peso;
        Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}
};

class Grafo_LA {
    private:
        NodoLista<Arista> ** grafo;
        int V;
        bool esDirigido;
    
    public:
        Grafo_LA(int _V, bool _esDirigido) {
            this->V =  _V;
            this->esDirigido = _esDirigido;
            grafo = new NodoLista<Arista>*[_V];
            for (int i = 0; i < _V; i++)
            {
                grafo[i] = NULL;
            }
        }

        int getV() {
            return this->V;
        }

        void agregarArista(int origen, int destino, int peso = 1) {
            Arista a(destino, peso);
            grafo[origen] = new NodoLista<Arista>(a, grafo[origen]);
            if(!this->esDirigido) {
                Arista a(origen, peso);
                grafo[destino] = new NodoLista<Arista>(a, grafo[destino]);
            }
        }

        NodoLista<Arista> * adyacentesA(int origen) {
            NodoLista<Arista> * ret = NULL;
            NodoLista<Arista> * ptr =  grafo[origen];
            while(ptr != NULL) {
                Arista a(ptr->dato.destino, ptr->dato.peso);
                ret = new NodoLista<Arista>(a, ret);
                ptr = ptr->sig;
            }
            return ret;
        }
};


bool* bfs(int nodo, Grafo_LA * g, bool* encolados) {
    int V = g->getV();
    Queue<int> *cola =  new QueueImp<int>();
    cola->enqueue(nodo);
    encolados[nodo] = true;

    while(!cola->isEmpty()){
        int v = cola->dequeue();

        NodoLista<Arista>* ady = g->adyacentesA(v);
        while(ady != NULL) {
            int u = ady->dato.destino;
            if(!encolados[u]){
                cola->enqueue(u);
                encolados[u] = true;
            }
            ady = ady->sig;
        }
    }
    return encolados;
}


int main()
{
    Grafo_LA * miGrafito = new Grafo_LA(5, false);
    miGrafito->agregarArista(0, 1);
    miGrafito->agregarArista(1, 2);
    miGrafito->agregarArista(3, 4);
    miGrafito->agregarArista(2, 4);


    int cantComponentesConexas = 0;
    bool* visitados = new bool[miGrafito->getV()]();
    for (int i = 0; i < miGrafito->getV(); i++){
        visitados[i] = false;
    }
    for (int i = 0; i < miGrafito->getV(); i++)
    {
        if(!visitados[i]) {
            cantComponentesConexas++;
            bfs(i, miGrafito, visitados);
        }
    }

    cout << "La cantidad de componentes conexas es " << cantComponentesConexas << endl;
}