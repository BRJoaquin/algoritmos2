#include <climits>
#include <string>
#include <iostream>
#include <cassert>
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

// uso un NodoLista generico
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
    int peso; // puede que sea 1, en el caso de que no sea ponderado.
    Arista(int unOrigen, int unDestino, int unPeso = 1) : origen(unOrigen), destino(unDestino), peso(unPeso) {}
};

// para trabajar mas comodo defino mi Lista de Aristas como un puntero a un NodoLista de Arista
typedef NodoLista<Arista> *ListaAristas;

// definicion minima de un grafo
class Grafo
{
public:
    // pre:
    //  - v y w son vertices validos del grafo
    //  - no existe la arista v w
    // pos: agrega la arista v w con su respectivo peso al grafo
    virtual void aniadirArista(int v, int w, int peso = 1) = 0;
    // pre: el vertice origen es un vertice valido del grafo
    // pos: retorna una lista de Arsitas las cuales tienen como origen al vertice parametro
    virtual ListaAristas adyacentesA(int origen) = 0;
    // pre:
    // pos: retorna la cantidad de vertices del grafo
    virtual int cantidadDeVertices() = 0;
    // pre:
    // pos: imprime el grafo
    virtual void imprimir() = 0;
};

class GrafoListaAdyImp : public Grafo
{
private:
    ListaAristas *listaAdy; // represetnacion del grafo con listas
    int V;                  // cantidad de vertices
    int A;                  // cantidad de arsitas

    bool esDirigido;  // indica si el grafo es dirigido
    bool esPonderado; // indica si el grafo es ponderado

public:
    // Crea un grafo con V vertices (del 1 al V)
    // O(V)
    GrafoListaAdyImp(int cantidadDeVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->V = cantidadDeVertices;
        this->A = 0;
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;

        listaAdy = new ListaAristas[V + 1];
        for (int i = 1; i <= V; i++)
        {
            listaAdy[i] = NULL; // inicializa todas las listas como vacias
        }
    }
    // O(1)
    void aniadirArista(int v, int w, int peso = 1)
    {
        int pesoArista = this->esPonderado ? peso : 1; // en el caso de ser ponderado se toma en cuenta el parametro
        Arista a1(v, w, pesoArista);
        listaAdy[v] = new NodoLista<Arista>(a1, listaAdy[v]); // se agrega al ppio de la lista de los adyacentes al veritce v
        this->A++;
        if (!esDirigido) // en caso de no ser dirigido podemos duplicar la arista hacia el otro sentido w->v
        {
            Arista a2(w, v, pesoArista);
            listaAdy[w] = new NodoLista<Arista>(a2, listaAdy[w]);
        }
    }
    // O(V) pc
    // si bien esta funcion podria ser O(1) si retornamos la lista original, es peligroso si la manipulan => corrompiendo el grafo
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
    // O(V + A)
    void imprimir()
    {
        // por cada vertice del 1 al V, imprimo sus adyacentes
        for (int i = 1; i <= V; i++)
        {
            cout << "Adyacentes al vertice " << i << endl;
            int cantidadDeVertices();
            ListaAristas adyacentes = this->adyacentesA(i);
            while (adyacentes != NULL)
            {
                Arista arista = adyacentes->dato;
                cout << i << "-";
                if (this->esPonderado) // en caso de ser ponderado, imprimo el peso
                {
                    cout << arista.peso;
                }
                cout << "->" << arista.destino << endl;
                adyacentes = adyacentes->sig;
            }
        }
    }
    int cantidadDeVertices()
    {
        return this->V;
    }
};

// array de V casilleros, todos con valor “INF” a excepción de origen (con 0)
int *initCosto(int V, int origen)
{
    int *ret = new int[V + 1]();
    for (int i = 0; i <= V; i++)
    {
        ret[i] = i == origen ? 0 : (V + 1);
    }
    return ret;
}
int *initVengo(int V)
{
    int *ret = new int[V + 1]();
    for (int i = 0; i <= V; i++)
    {
        ret[i] = -1;
    }
    return ret;
}

void reconstruirCamino(int actual, int *vengo)
{
    if (vengo[actual] != -1)
    {
        reconstruirCamino(vengo[actual], vengo);
    }
    cout << " " << actual;
}

void caminoMasCortoNoPonderado(Grafo *g, int origen)
{
    int V = g->cantidadDeVertices();
    int *costo = initCosto(V, origen); // array de V casilleros, todos con valor “INF” a excepción de origen (con 0)
    int *vengo = initVengo(V);         // array de V casilleros, todos con valor -1

    Cola<int> cola;
    cola.encolar(origen);

    while (!cola.estaVacia())
    {
        int vertice = cola.desencolar();
        ListaAristas ady = g->adyacentesA(vertice);
        while (ady != NULL)
        {
            int verticeAdyacente = ady->dato.destino;
            if (costo[verticeAdyacente] > costo[vertice] + 1)
            {
                cola.encolar(verticeAdyacente);
                costo[verticeAdyacente] = costo[vertice] + 1;
                vengo[verticeAdyacente] = vertice;
            }
            ady = ady->sig;
        }
    }

    for (int i = 1; i <= V; i++)
    {
        if (costo[i] <= V)
        {
            cout << "hasta el vertice " << i << " tiene costo: " << costo[i] << endl;
            reconstruirCamino(i, vengo);
            cout << endl;
        }
        else
        {
            cout << "hasta el vertice " << i << " no tiene llegada" << endl;
        }
    }
}

int main()
{
    Grafo *g = new GrafoListaAdyImp(8, true, false);
    g->aniadirArista(1, 4);
    g->aniadirArista(1, 2);
    g->aniadirArista(2, 4);
    g->aniadirArista(2, 5);
    g->aniadirArista(3, 1);
    g->aniadirArista(3, 6);
    g->aniadirArista(4, 3);
    g->aniadirArista(4, 6);
    g->aniadirArista(4, 7);
    g->aniadirArista(4, 5);
    g->aniadirArista(5, 7);
    g->aniadirArista(7, 6);

    caminoMasCortoNoPonderado(g, 3);
    return 0;
}