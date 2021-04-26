#include <cassert>
#include <climits>
#include <string>
#include <iostream>
using namespace std;

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

    // Extras
    virtual void prim(int origen) = 0;
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

    bool *initVisitados()
    {
        bool *ret = new bool[V + 1];
        for (int i = 1; i <= V; i++)
        {
            ret[i] = false;
        }
        return ret;
    }

    int *initCostos(int origen)
    {
        int *ret = new int[V + 1];
        for (int i = 1; i <= V; i++)
        {
            ret[i] = i == origen ? 0 : INF;
        }
        return ret;
    }

    int *initVengo()
    {
        int *ret = new int[V + 1];
        for (int i = 1; i <= V; i++)
        {
            ret[i] = -1;
        }
        return ret;
    }

    int verticesDesconocidoDeMenorCosto(bool *vistados, int *costos)
    {
        int menorVerticeNoConocido = -1;
        int menorCosto = INF;
        for (int i = 1; i <= V; i++)
        {
            if (!vistados[i] && costos[i] < menorCosto)
            {
                menorVerticeNoConocido = i;
                menorCosto = costos[i];
            }
        }
        return menorVerticeNoConocido;
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

    void prim(int origen)
    {
        bool *visitados = initVisitados();
        int *costos = initCostos(origen);
        int *vengo = initVengo();

        for (int i = 1; i <= V; i++)
        {
            int v = verticesDesconocidoDeMenorCosto(visitados, costos);
            if (v != -1)
            {
                visitados[v] = true;
                ListaAristas ady = adyacentesA(v);
                while (ady != NULL)
                {
                    int w = ady->dato.destino;
                    if (!visitados[w] && costos[w] > ady->dato.peso)
                    {
                        costos[w] = ady->dato.peso;
                        vengo[w] = v;
                    }
                    ady = ady->sig;
                }
            }
        }

        int pesoTotal = 0;
        for (int i = 1; i <= V; i++)
        {
            if (vengo[i] != -1)
            {
                pesoTotal += costos[i];
                cout << i << " <-" << costos[i] << "-> " << vengo[i] << endl;
            }
        }
        cout << endl
             << "Costo total: " << pesoTotal << endl;
    }
};

int main()
{

    Grafo *g = new GrafoListaAdyImp(7, false, true);

    g->aniadirArista(3, 1, 4);
    g->aniadirArista(3, 4, 2);
    g->aniadirArista(3, 6, 5);
    g->aniadirArista(1, 4, 1);
    g->aniadirArista(6, 4, 8);
    g->aniadirArista(1, 2, 2);
    g->aniadirArista(6, 7, 1);
    g->aniadirArista(4, 2, 3);
    g->aniadirArista(4, 5, 2);
    g->aniadirArista(4, 7, 4);
    g->aniadirArista(2, 5, 10);
    g->aniadirArista(7, 5, 6);

    g->prim(1);
    return 0;
}