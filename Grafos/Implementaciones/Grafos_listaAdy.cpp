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
        if (!esDirigido)                                      // en caso de no ser dirigido podemos duplicar la arista hacia el otro sentido w->v
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
};

int main()
{
    cout << "Prueba de grafo dirigido y no ponderado:" << endl;
    Grafo *gDirNoPon = new GrafoListaAdyImp(10, true, false);
    gDirNoPon->aniadirArista(1, 3);
    gDirNoPon->aniadirArista(1, 2);
    gDirNoPon->aniadirArista(4, 1);

    gDirNoPon->imprimir();

    cout << endl
         << "Prueba de grafo dirigido y ponderado:" << endl;

    Grafo *gDirPon = new GrafoListaAdyImp(10, true, true);
    gDirPon->aniadirArista(1, 3, 4);
    gDirPon->aniadirArista(3, 1, 8);
    gDirPon->aniadirArista(1, 2, -5);
    gDirPon->aniadirArista(4, 1, 10);

    gDirPon->imprimir();

    cout << endl
         << "Prueba de grafo no dirigido y no ponderado:" << endl;
    Grafo *gNoDirNoPon = new GrafoListaAdyImp(10, false, false);
    gNoDirNoPon->aniadirArista(1, 3);
    gNoDirNoPon->aniadirArista(1, 2);
    gNoDirNoPon->aniadirArista(4, 1);
    gNoDirNoPon->aniadirArista(5, 2);
    gNoDirNoPon->aniadirArista(8, 4);
    gNoDirNoPon->aniadirArista(4, 9);

    gNoDirNoPon->imprimir();

    return 0;
}