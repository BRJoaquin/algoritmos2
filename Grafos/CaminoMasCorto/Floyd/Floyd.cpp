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
// defino mi Infinito como el maximo inf posible
#define INF INT_MAX;

int **matrizAdy(Grafo *g)
{
    int V = g->cantidadDeVertices();
    int **ret = new int *[V + 1];
    for (int i = 1; i <= V; i++)
    {
        ret[i] = new int[V + 1]();
        for (int j = 1; j <= V; j++)
        {
            ret[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 1; i <= V; i++)
    {
        int origen = i;
        ListaAristas ady = g->adyacentesA(origen);
        while (ady != NULL)
        {
            int destino = ady->dato.destino;
            int peso = ady->dato.peso;
            ret[origen][destino] = peso;
            ady = ady->sig;
        }
    }
    return ret;
}
int **initCaminos(Grafo *g)
{
    int V = g->cantidadDeVertices();
    int **ret = new int *[V + 1];
    for (int i = 1; i <= V; i++)
    {
        ret[i] = new int[V + 1]();
        for (int j = 1; j <= V; j++)
        {
            ret[i][j] = -1;
        }
    }
    for (int i = 1; i <= V; i++)
    {
        int origen = i;
        ListaAristas ady = g->adyacentesA(origen);
        while (ady != NULL)
        {
            int destino = ady->dato.destino;
            ret[origen][destino] = origen;
            ady = ady->sig;
        }
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

void floyd(Grafo *g)
{
    int V = g->cantidadDeVertices();
    int **matrizCosto = matrizAdy(g);
    int **matrizCamino = initCaminos(g);

    int inf = INF;
    for (int k = 1; k <= V; k++)
    {
        for (int i = 1; i <= V; i++)
        {
            for (int j = 1; j <= V; j++)
            {
                if (matrizCosto[i][k] < inf && matrizCosto[k][j] < inf)
                {
                    if (matrizCosto[i][j] > matrizCosto[i][k] + matrizCosto[k][j])
                    {
                        matrizCosto[i][j] = matrizCosto[i][k] + matrizCosto[k][j];
                        matrizCamino[i][j] = k;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= V; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            if (matrizCosto[i][j] == inf)
            {
                cout << "No se puede ir desde " << i << "  hasta " << j << endl;
            }
            else
            {
                cout << "El costo de ir desde " << i << "  hasta " << j << " es " << matrizCosto[i][j] <<endl;
                cout << "Camino:" << endl;
                reconstruirCamino(j, matrizCamino[i]);
                cout << endl;
            }
                cout << endl;
        }
    }
}

// int** matriz = grafoMatriz(); // devuelve una copia de la matriz de adyacencia
// int** matrizCamino = initCaminos();
// for(int i=1; i<=V; i++)
//     matriz[i][i]=0; // “borramos” la diagonal

// for(int k=1; k<=V; k++) // el nodo “intermedio”
//     for(int i=1; i<=V; i++)
//         for(int j=1; j<=V; j++)
//             if(matriz[i][j] > matriz[i][k] + matriz[k][j])
//                 matriz[i][j] = matriz[i][k] + matriz[k][j]
//                 matrizCamino[i][j] = k;

int main()
{
    Grafo *g = new GrafoListaAdyImp(8, true, true);

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

    floyd(g);
    return 0;
}