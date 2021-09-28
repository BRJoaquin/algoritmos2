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
};

// defino mi Infinito como el maximo inf posible
#define INF INT_MAX;

class GrafoMatrizImp : public Grafo
{
private:
    int **matriz;
    int V;
    int A;

    bool esDirigido;
    bool esPonderado;

public:
    // Crea un grafo con V vertices (del 1 al V)
    // O(V^2)
    GrafoMatrizImp(int cantidadDeVertices, bool esDirigido = true, bool esPonderado = true)
    {
        this->V = cantidadDeVertices;
        this->A = 0;
        this->esDirigido = esDirigido;
        this->esPonderado = esPonderado;

        matriz = new int *[V + 1];
        for (int i = 1; i <= V; i++)
        {
            matriz[i] = new int[V + 1];
            for (int j = 1; j <= V; j++)
            {
                matriz[i][j] = INF; // podemos hacer una matriz de ceros, siempre y cuando no se existan aristas con peso 0
            }
        }
    }
    // O(1)
    void aniadirArista(int v, int w, int peso = 1)
    {
        matriz[v][w] = esPonderado ? peso : 1;
        if (!esDirigido)
        {
            matriz[w][v] = esPonderado ? peso : 1;
        }
        this->A++;
    }
    // O(V)
    ListaAristas adyacentesA(int origen)
    {
        int inf = INF;
        ListaAristas listaRetorno = NULL;
        for (int i = 1; i <= V; i++)
        {
            if (matriz[origen][i] != inf) // en el caso de que exista una arista origen->i
            {
                Arista aux(origen, i, matriz[origen][i]);
                listaRetorno = new NodoLista<Arista>(aux, listaRetorno);
            }
        }
        return listaRetorno;
    }
};

int *initGradoDeEntrada(Grafo *g, int V)
{
    int *gradoEntradas = new int[V + 1]();
    for (int i = 1; i <= V; i++)
    {
        ListaAristas adyacentes = g->adyacentesA(i);
        while (adyacentes != NULL)
        {
            Arista a = adyacentes->dato;
            gradoEntradas[a.destino]++;
            adyacentes = adyacentes->sig;
        }
    }
    return gradoEntradas;
}

bool *initVisitados(int V)
{
    bool *visitados = new bool[V + 1];
    for (int i = 1; i <= V; i++)
    {
        visitados[i] = false;
    }
    return visitados;
}

int verticeGradoEntranteCeroNoVisitado(int *gradoEntrada, bool *visitados, int V)
{

    for (int i = 1; i <= V; i++)
    {
        if (gradoEntrada[i] == 0 && !visitados[i])
        {
            return i;
        }
    }
    return -1;
}

void ordenacionTopologica(Grafo *g, int V)
{
    int *gradoEntrada = initGradoDeEntrada(g, V);
    Cola<int> cola;
    int vertice, cont = 0;
    for (int v = 1; v <= V; v++)
        if (gradoEntrada[v] == 0)
            cola.encolar(v);

    while (!cola.estaVacia())
    {
        vertice = cola.desencolar();
        cont++;
        cout << vertice << endl;
        ListaAristas adyacentesAV = g->adyacentesA(vertice);
        while (adyacentesAV != NULL)
        {
            int w = adyacentesAV->dato.destino;
            gradoEntrada[w]--;
            if (gradoEntrada[w] == 0)
                cola.encolar(w);
            adyacentesAV = adyacentesAV->sig;
        }
    }

    if(cont < V) {
        cout << "Hay ciclo!" << endl;
    }
}

int main()
{
    Grafo *gDirNoPon = new GrafoMatrizImp(4, true, false);

    gDirNoPon->aniadirArista(1, 3);
    gDirNoPon->aniadirArista(3, 4);
    gDirNoPon->aniadirArista(2, 4);
    gDirNoPon->aniadirArista(2, 3);
    gDirNoPon->aniadirArista(1, 2);

    ordenacionTopologica(gDirNoPon, 4);

    return 0;
}