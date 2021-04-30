#include <cassert>
#include <climits>
#include <string>
#include <iostream>
using namespace std;

class MFSet
{
    int *altura, *parent, n;

public:
    MFSet(int n)
    {
        parent = new int[n];
        altura = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            // aplanamos el arbol
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);

        // si estan dentro del mismo set terminamos
        if (xset == yset)
            return;

        // evitamos aumentar la altura del arbol
        if (altura[xset] < altura[yset])
        {
            parent[xset] = yset;
        }
        else if (altura[xset] > altura[yset])
        {
            parent[yset] = xset;
        }

        // si ambas alturas con la misma usamos cualquiera y actualizamos la altura
        else
        {
            parent[yset] = xset;
            altura[xset] = altura[xset] + 1;
        }
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
    Arista(){};
    Arista(int unOrigen, int unDestino, int unPeso = 1) : origen(unOrigen), destino(unDestino), peso(unPeso) {}
};

typedef NodoLista<Arista> *ListaAristas;

class Grafo
{
public:
    virtual void aniadirArista(int v, int w, int peso = 1) = 0;
    virtual ListaAristas adyacentesA(int origen) = 0;

    // Extras
    virtual void kruskal() = 0;
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

    void cargarAristas(Arista *aristas)
    {
        int index = 0;
        for (int i = 1; i <= V; i++)
        {
            ListaAristas adyacentes = this->adyacentesA(i);
            while (adyacentes != NULL)
            {
                Arista arista = adyacentes->dato;
                // para evistar la doble arista
                if(i < arista.destino) {
                    aristas[index++] = arista;
                }
                adyacentes = adyacentes->sig;
            }
        }
    }

    int menorAristaNoProcesada(Arista *aristas, bool *procesadas)
    {
        int menor = -1;
        int menorValor;
        for (int i = 0; i < A; i++)
        {
            if (!procesadas[i])
            {
                if (menor == -1 || menorValor > aristas[i].peso)
                {
                    menor = i;
                    menorValor = aristas[i].peso;
                }
            }
        }
        return menor;
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
        this->A++;
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

    void kruskal()
    {
        Arista *aristas = new Arista[A];
        bool *procesadas = new bool[A]();
        bool *utilizadas = new bool[A]();
        MFSet sets(V + 1);

        cargarAristas(aristas);

        for (int i = 0; i < A; i++) // // O(A^2) <- a mejorar con heap
        {
            int menorAristaIndex = menorAristaNoProcesada(aristas, procesadas); // O(A)
            Arista menorArista = aristas[menorAristaIndex];
            procesadas[menorAristaIndex] = true;
            if (sets.find(menorArista.origen) != sets.find(menorArista.destino))
            {
                utilizadas[menorAristaIndex] = true;
                sets.merge(menorArista.origen, menorArista.destino);
            }
        }

        // Leemos los datos
        int pesoTotal = 0;
        for (int i = 0; i < A; i++)
        {
            if (utilizadas[i])
            {
                Arista arista = aristas[i];
                pesoTotal += arista.peso;
                cout << arista.origen << " <-" << arista.peso << "-> " << arista.destino << endl;
            }
        }
        cout << endl << "Costo total: " << pesoTotal << endl;
    }
};

int main()
{

    Grafo *g = new GrafoListaAdyImp(7, false, true);

    g->aniadirArista(3,1,4);
    g->aniadirArista(3,4,2);
    g->aniadirArista(3,6,5);
    g->aniadirArista(1,4,1);
    g->aniadirArista(6,4,8);
    g->aniadirArista(1,2,2);
    g->aniadirArista(6,7,1);
    g->aniadirArista(4,2,3);
    g->aniadirArista(4,5,2);
    g->aniadirArista(4,7,4);
    g->aniadirArista(2,5,10);
    g->aniadirArista(7,5,6);

    g->kruskal();
    return 0;
}