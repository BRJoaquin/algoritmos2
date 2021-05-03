#include <cassert>
#include <climits>
#include <string>
#include <iostream>
using namespace std;

template <class T>
class Cola
{
private:
    struct NodoColaFIFO
    {
        T dato;                                                                                // guarda el dato en si dentro del nodo
        NodoColaFIFO *sig;                                                                     // guarda la referencia al siguiente nodo
        NodoColaFIFO(T &unDato, NodoColaFIFO *unSiguiente) : dato(unDato), sig(unSiguiente) {} // Constructor con ambos datos
        NodoColaFIFO(T &unDato) : dato(unDato), sig(0) {}                                      // Constructor con solo el dato, por defecto el sig es null
    };

    NodoColaFIFO *ppio;
    NodoColaFIFO *fin;

public:
    Cola()
    {
        ppio = fin = 0;
    }
    void encolar(T nuevoDato)
    {
        NodoColaFIFO *nuevoNodo = new NodoColaFIFO(nuevoDato);
        if (ppio == NULL)
        {
            ppio = nuevoNodo;
        }
        else
        {
            fin->sig = nuevoNodo;
        }
        fin = nuevoNodo;
    }
    // pre: no esta vacia
    T desencolar()
    {
        assert(!estaVacia()); // validacion
        T ret = ppio->dato;
        ppio = ppio->sig;
        if (ppio == NULL)
        {
            fin = NULL;
        }
        return ret;
    }
    bool estaVacia()
    {
        return ppio == NULL;
    }
    T tope()
    {
        assert(!estaVacia()); // validacion
        return ppio->dato;
    }
};


template <class T>
struct NodoLista
{
    T dato;
    NodoLista *sig;
    NodoLista(T &unDato) : dato(unDato), sig(0){};
    NodoLista(T &unDato, NodoLista *unSig) : dato(unDato), sig(unSig){};
};

struct Arista
{
    int origen;
    int destino;
    int peso;
    Arista(int unOrigen, int unDestino, int unPeso = 1) : origen(unOrigen), destino(unDestino), peso(unPeso) {}
};

typedef NodoLista<Arista> *ListaAristas;

class Grafo
{
public:
    virtual void aniadirArista(int v, int w, int peso = 1) = 0;
    virtual ListaAristas adyacentesA(int origen) = 0;

    virtual void DFS(int origen) = 0;
    virtual void BFS(int origen) = 0;
};

// defino mi Infinito como el maximo inf posible
#define INF INT_MAX;

class GrafoListaAdyImp : public Grafo
{
private:
    ListaAristas *listaAdy;
    int V;
    int A;

    bool esDirigido;
    bool esPonderado;

    bool * initEncolados() {
        return new bool[V+1](); // todos los valores en false
    }

    void DFS_rec(int origen,bool* visitados){
        visitados[origen] = true;
        // proceso el vertice
        cout << origen << endl;
        ListaAristas adyacentesAOrigen = this->adyacentesA(origen);
        while (adyacentesAOrigen != NULL)
        {
            int w = adyacentesAOrigen->dato.destino;
            if(!visitados[w]) {
                DFS_rec(w, visitados);
            }
            adyacentesAOrigen = adyacentesAOrigen->sig; 
        }
    }
public:
    // Crea un grafo con V vertices (del 1 al V)
    // O(v)
    GrafoListaAdyImp(int cantidadDeVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->V = cantidadDeVertices;
        this->A = 0;
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;

        listaAdy = new ListaAristas[V + 1];
        for (int i = 1; i <= V; i++)
        {
            listaAdy[i] = NULL;
        }
    }
    // O(1)
    void aniadirArista(int v, int w, int peso = 1)
    {
        int pesoArista = this->esPonderado ? peso : 1;
        Arista a1(v, w, pesoArista);
        listaAdy[v] = new NodoLista<Arista>(a1, listaAdy[v]);
        if (!esDirigido)
        {
            Arista a2(w, v, pesoArista);
            listaAdy[w] = new NodoLista<Arista>(a2, listaAdy[w]);
        }
    }
    // O(V) pc
    ListaAristas adyacentesA(int origen)
    {
        // copio la lista
        ListaAristas listaRetorno = NULL;
        ListaAristas listaAuxiliar = listaAdy[origen];

        while (listaAuxiliar != NULL)
        {
            Arista aristaAuxiliar = listaAuxiliar->dato;
            listaRetorno = new NodoLista<Arista>(aristaAuxiliar, listaRetorno);
            listaAuxiliar = listaAuxiliar->sig;
        }

        return listaRetorno;
    }

    void BFS(int origen) {
        bool * encolados = initEncolados(); // array de V+1 pos, todos en false
        Cola<int> * cola = new Cola<int>(); // FIFO
        cola->encolar(origen);
        encolados[origen] = true;
        while(!cola->estaVacia()) {
            int ver = cola->desencolar();
            cout << ver << endl;
            ListaAristas adyacentesAV = this->adyacentesA(ver);
            while ( adyacentesAV != NULL)
            {
                int w = adyacentesAV->dato.destino;
                adyacentesAV =  adyacentesAV->sig; 
                if(!encolados[w]) {
                    encolados[w] = true;
                    cola->encolar(w);
                }
            }
        }
    }

    void DFS(int origen) {
        bool * visitados = new bool[V+1]();
        DFS_rec(origen, visitados);
    }
};

int main()
{

    Grafo *g = new GrafoListaAdyImp(7, false, true);

    g->aniadirArista(1, 2, 2);
    g->aniadirArista(1, 4, 1);
    g->aniadirArista(3, 1, 4);
    g->aniadirArista(3, 4, 2);
    g->aniadirArista(3, 6, 5);
    g->aniadirArista(6, 4, 8);
    g->aniadirArista(6, 7, 1);
    g->aniadirArista(4, 2, 3);
    g->aniadirArista(4, 5, 7);
    g->aniadirArista(4, 7, 4);
    g->aniadirArista(2, 5, 10);
    g->aniadirArista(7, 5, 6);

    cout << "BFS" << endl;
    g->BFS(2);
    cout << endl << "DFS" << endl;
    g->DFS(2);
    return 0;
}