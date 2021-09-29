#include <climits>
#include <string>
#include <iostream>
using namespace std;

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

bool *initVisitados(int V)
{
    bool *ret = new bool[V + 1]();
    for (int i = 1; i <= V; i++)
    {
        ret[i] = false;
    }
    return ret;
}

int *initCostos(int origen, int V)
{
    int *ret = new int[V + 1]();
    for (int i = 1; i <= V; i++)
    {
        ret[i] = INF;
    }
    ret[origen] = 0;
    return ret;
}

int *initVengo(int V)
{
    int *ret = new int[V + 1]();
    for (int i = 1; i <= V; i++)
    {
        ret[i] = -1;
    }
    return ret;
}

int verticeDesconocidoDeMenorCosto(bool *visitados, int *costos, int V)
{
    int menor = -1;
    int costoMenorHastaElMomento = INF;
    for (int i = 1; i <= V; i++)
    {
        if (!visitados[i] && costos[i] < costoMenorHastaElMomento)
        {
            menor = i;
            costoMenorHastaElMomento = costos[i];
        }
    }
    return menor;
}

void imprimirCamino(int destino, int * vengo) {
    while(destino != -1) {
        cout << destino;
        if(vengo[destino] != -1) {
            cout << "<-";
        }
        destino = vengo[destino];
    }
    cout << endl;
}

void dijkstra(Grafo *g, int origen, int V)
{
    bool *visitados = initVisitados(V);  // array V casilleros, todos en false
    int *costos = initCostos(origen, V); // array V casillero, todos en INF menos origen con 0
    int *vengo = initVengo(V);           // array V casilleros, todos en -1
    for (int i = 0; i < V; i++)
    {
        int v = verticeDesconocidoDeMenorCosto(visitados, costos, V); // vértice a procesar
        if (v == -1)
        {
            // ya termine
            break;
        }
        else
        {
            visitados[v] = true;
            ListaAristas aristas = g->adyacentesA(v);
            while (aristas != NULL)
            {
                int w = aristas->dato.destino;
                int costoHaciaW = aristas->dato.peso;
                if (costos[w] > costos[v] + costoHaciaW)
                {
                    costos[w] = costos[v] + costoHaciaW;
                    vengo[w] = v;
                }
                aristas = aristas->sig;
            }
        }
    }

    for (int i = 1; i <= V; i++)
    {
        int inf = INF;
        if(i != origen) {
            if (costos[i] == inf)
            {
                cout << "No puedo ir al vertice " << i << endl;
            }
            else
            {
                cout << "El costo de ir de " << origen << " a " << i << " es de " << costos[i] << endl;
                imprimirCamino(i, vengo);
            }
        }
    }
}
int main()
{
    Grafo *g = new GrafoMatrizImp(7, true, true);

    g->aniadirArista(1, 2, 2);
    g->aniadirArista(1, 4, 1);
    g->aniadirArista(2, 4, 3);
    g->aniadirArista(2, 5, 10);
    g->aniadirArista(3, 1, 4);
    g->aniadirArista(3, 6, 5);
    g->aniadirArista(4, 3, 2);
    g->aniadirArista(4, 5, 2);
    g->aniadirArista(4, 6, 8);
    g->aniadirArista(4, 7, 4);
    g->aniadirArista(5, 7, 6);
    g->aniadirArista(7, 6, 1);

    dijkstra(g, 3, 7);

    return 0;
}