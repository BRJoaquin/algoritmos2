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
    // pre:
    // pos: imprime el grafo
    virtual void imprimir() = 0;
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
    // O(V^2)
    void imprimir()
    {
        for (int i = 1; i <= V; i++)
        {
            cout << "Adyacentes al vertice " << i << endl;
            ListaAristas adyacentes = this->adyacentesA(i);
            while (adyacentes != NULL)
            {
                Arista arista = adyacentes->dato;
                cout << i << "-";
                if (this->esPonderado)
                {
                    cout << arista.peso;
                }
                cout << "->" << arista.destino << endl;
                adyacentes = adyacentes->sig;
            }
        }
    }
};

int main()
{
    cout << "Prueba de grafo dirigido y no ponderado:" << endl;
    Grafo *gDirNoPon = new GrafoMatrizImp(10, true, false);
    gDirNoPon->aniadirArista(1, 3);
    gDirNoPon->aniadirArista(1, 2);
    gDirNoPon->aniadirArista(4, 1);

    gDirNoPon->imprimir();

    cout << endl
         << "Prueba de grafo dirigido y ponderado:" << endl;

    Grafo *gDirPon = new GrafoMatrizImp(10, true, true);
    gDirPon->aniadirArista(1, 3, 4);
    gDirPon->aniadirArista(3, 1, 8);
    gDirPon->aniadirArista(1, 2, -5);
    gDirPon->aniadirArista(4, 1, 10);

    gDirPon->imprimir();

    cout << endl
         << "Prueba de grafo no dirigido y no ponderado:" << endl;
    Grafo *gNoDirNoPon = new GrafoMatrizImp(10, false, false);
    gNoDirNoPon->aniadirArista(1, 3);
    gNoDirNoPon->aniadirArista(1, 2);
    gNoDirNoPon->aniadirArista(4, 1);
    gNoDirNoPon->aniadirArista(5, 2);
    gNoDirNoPon->aniadirArista(8, 4);
    gNoDirNoPon->aniadirArista(4, 9);

    gNoDirNoPon->imprimir();

    return 0;
}