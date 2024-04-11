#include <string>
#include <iostream>
#include <climits>
#include "../ADTs/Queue.h"
#include "../ADTs/QueueImp.cpp"

#define INF INT_MAX;

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


void recostruirCamino(int destino, int * vengo) {
    if(destino != -1) {
        recostruirCamino(vengo[destino], vengo);
        cout << destino << " ";
    }
}

void dijsktra(int origen, Grafo_LA *g) {
    int* costo = new int[g->getV()]();
    int* vengo = new int[g->getV()]();
    bool* visitado = new bool[g->getV()]();

    for (int i = 0; i < g->getV(); i++)
    {
        costo[i] = INF;
        vengo[i] = -1;
        visitado[i] = false;
    }

    costo[origen] = 0;
    
    for (int i = 0; i < g->getV(); i++)
    {
        // vertice a procesar: el de menor costo NO visitado
        int v = -1;
        int menorCosto = INF;
        for (int j = 0; j < g->getV(); j++)
        {
            if(costo[j] < menorCosto && !visitado[j]) {
                v = j;
                menorCosto = costo[j];
            }
        }
        
        // nos cubrimos por si el menor nodo no visitado no lo puedo alcanzar me voy
        if(v == -1)
            break;
        
        visitado[v] = true;

        NodoLista<Arista> * ady = g->adyacentesA(v);
        while(ady != NULL) {
            Arista a = ady->dato;
            int u = a.destino;
            int w = a.peso;
            if(!visitado[u] && costo[u] > costo[v] + w) {
                costo[u] = costo[v] + w;
                vengo[u] = v;
            }
            ady = ady->sig;
        }
    }

    std::cout << "Desde el origen " << origen << std::endl;
    for (int i = 0; i < g->getV(); i++)
    {
        if(!visitado[i]) {
            std::cout << "No puedo llegar a " << i << std::endl;
        }else {
            std::cout << "El costo de llegar a " << i << " es: " << costo[i] << std::endl;
            recostruirCamino(i, vengo);
            std::cout  << std::endl;
        }
    }
}


int main()
{
    Grafo_LA * miGrafito = new Grafo_LA(5, true);
    miGrafito->agregarArista(0, 4, 2);
    miGrafito->agregarArista(1, 0, 2);
    miGrafito->agregarArista(1, 3, 4);
    miGrafito->agregarArista(1, 2, 1);
    miGrafito->agregarArista(2, 3, 2);
    miGrafito->agregarArista(3, 4, 8);
    miGrafito->agregarArista(3, 2, 0);


    dijsktra(1, miGrafito);


    // int cantComponentesConexas = 0;
    // bool* visitados = new bool[miGrafito->getV()]();
    // for (int i = 0; i < miGrafito->getV(); i++){
    //     visitados[i] = false;
    // }
    // for (int i = 0; i < miGrafito->getV(); i++)
    // {
    //     if(!visitados[i]) {
    //         cantComponentesConexas++;
    //         bfs(i, miGrafito, visitados);
    //     }
    // }

    // cout << "La cantidad de componentes conexas es " << cantComponentesConexas << endl;
}