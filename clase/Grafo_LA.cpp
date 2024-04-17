#include <string>
#include <iostream>
#include <climits>
#include "../ADTs/Queue.h"
#include "../ADTs/QueueImp.cpp"

#define INF INT_MAX;

using namespace std;

template <class T>
class NodoLista
{
public:
    T dato;
    NodoLista *sig;
    NodoLista(T _dato, NodoLista *_sig) : dato(_dato), sig(_sig){};
    NodoLista(T _dato) : dato(_dato), sig(NULL){};
};

class Arista
{
public:
    // int origen; queda en ustedes usarlo
    int destino;
    int peso;
    Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}
};

class Grafo_LA
{
private:
    NodoLista<Arista> **grafo;
    int V;
    bool esDirigido;

public:
    Grafo_LA(int _V, bool _esDirigido)
    {
        this->V = _V;
        this->esDirigido = _esDirigido;
        grafo = new NodoLista<Arista> *[_V];
        for (int i = 0; i < _V; i++)
        {
            grafo[i] = NULL;
        }
    }

    int getV()
    {
        return this->V;
    }

    void agregarArista(int origen, int destino, int peso = 1)
    {
        Arista a(destino, peso);
        grafo[origen] = new NodoLista<Arista>(a, grafo[origen]);
        if (!this->esDirigido)
        {
            Arista a(origen, peso);
            grafo[destino] = new NodoLista<Arista>(a, grafo[destino]);
        }
    }

    NodoLista<Arista> *adyacentesA(int origen)
    {
        NodoLista<Arista> *ret = NULL;
        NodoLista<Arista> *ptr = grafo[origen];
        while (ptr != NULL)
        {
            Arista a(ptr->dato.destino, ptr->dato.peso);
            ret = new NodoLista<Arista>(a, ret);
            ptr = ptr->sig;
        }
        return ret;
    }
};

bool *bfs(int nodo, Grafo_LA *g, bool *encolados)
{
    int V = g->getV();
    Queue<int> *cola = new QueueImp<int>();
    cola->enqueue(nodo);
    encolados[nodo] = true;

    while (!cola->isEmpty())
    {
        int v = cola->dequeue();

        NodoLista<Arista> *ady = g->adyacentesA(v);
        while (ady != NULL)
        {
            int u = ady->dato.destino;
            if (!encolados[u])
            {
                cola->enqueue(u);
                encolados[u] = true;
            }
            ady = ady->sig;
        }
    }
    return encolados;
}

void recostruirCamino(int destino, int *vengo)
{
    if (destino != -1)
    {
        recostruirCamino(vengo[destino], vengo);
        cout << destino << " ";
    }
}

void dijsktra(int origen, Grafo_LA *g)
{
    int *costo = new int[g->getV()]();
    int *vengo = new int[g->getV()]();
    bool *visitado = new bool[g->getV()]();

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
            if (costo[j] < menorCosto && !visitado[j])
            {
                v = j;
                menorCosto = costo[j];
            }
        }

        // nos cubrimos por si el menor nodo no visitado no lo puedo alcanzar me voy
        if (v == -1)
            break;

        visitado[v] = true;

        NodoLista<Arista> *ady = g->adyacentesA(v);
        while (ady != NULL)
        {
            Arista a = ady->dato;
            int u = a.destino;
            int w = a.peso;
            if (!visitado[u] && costo[u] > costo[v] + w)
            {
                costo[u] = costo[v] + w;
                vengo[u] = v;
            }
            ady = ady->sig;
        }
    }

    std::cout << "Desde el origen " << origen << std::endl;
    for (int i = 0; i < g->getV(); i++)
    {
        if (!visitado[i])
        {
            std::cout << "No puedo llegar a " << i << std::endl;
        }
        else
        {
            std::cout << "El costo de llegar a " << i << " es: " << costo[i] << std::endl;
            recostruirCamino(i, vengo);
            std::cout << std::endl;
        }
    }
}

void floyd(Grafo_LA *g)
{
    int **costos = new int *[g->getV()]();
    int **vengo = new int *[g->getV()]();
    for (int i = 0; i < g->getV(); i++)
    {
        costos[i] = new int[g->getV()]();
        vengo[i] = new int[g->getV()]();
        for (int j = 0; j < g->getV(); j++)
        {
            costos[i][j] = INF;
            vengo[i][j] = -1;
        }
        costos[i][i] = 0; // representa que puedo llegar a mi mismo con costo 0.
    }
    for (int i = 0; i < g->getV(); i++)
    {
        NodoLista<Arista> *ady = g->adyacentesA(i);
        while (ady != NULL)
        {
            Arista a = ady->dato;
            if (i != a.destino)
            {
                costos[i][a.destino] = a.peso;
                vengo[i][a.destino] = i;
            }
            ady = ady->sig;
        }
    }

    int inf = INF;

    for (int k = 0; k < g->getV(); k++)
    {
        for (int o = 0; o < g->getV(); o++)
        {
            for (int d = 0; d < g->getV(); d++)
            {
                if (costos[o][k] != inf && costos[k][d] != inf)
                { // pregunta si hay camino de o-...->k y de k-...->d
                    if (costos[o][k] + costos[k][d] < costos[o][d])
                    { // pregunta si mejora el coste
                        costos[o][d] = costos[o][k] + costos[k][d];
                        vengo[o][d] = k;
                    }
                }
            }
        }
    }
    
    for (int o = 0; o < g->getV(); o++)
    {
        for (int d = 0; d < g->getV(); d++)
        {
            if (o != d)
            {
                if (costos[o][d] == inf)
                {
                    cout << "No existe camino entre el origen " << o << " y el destino " << d << endl;
                }
                else
                {
                    std::cout << "El menor costo entre el origen " << o << " y el destino " << d << " es " << costos[o][d] << std::endl;
                    std::cout << "El Camino: ";
                    recostruirCamino(d, vengo[o]);
                    std::cout << std::endl;
                }
            }
        }
    }
}

void warshall(Grafo_LA *g)
{
    bool **clausura = new bool *[g->getV()]();
    for (int i = 0; i < g->getV(); i++)
    {
        clausura[i] = new bool[g->getV()]();
        for (int j = 0; j < g->getV(); j++)
        {
            clausura[i][j] = false;
        }
        clausura[i][i] = true; // representa que puedo llegar a mi mismo con costo 0.
    }
    for (int i = 0; i < g->getV(); i++)
    {
        NodoLista<Arista> *ady = g->adyacentesA(i);
        while (ady != NULL)
        {
            Arista a = ady->dato;
            if (i != a.destino)
            {
                clausura[i][a.destino] = true;
            }
            ady = ady->sig;
        }
    }

    int inf = INF;

    for (int k = 0; k < g->getV(); k++)
    {
        for (int o = 0; o < g->getV(); o++)
        {
            for (int d = 0; d < g->getV(); d++)
            {
                clausura[o][d] = clausura[o][d] || clausura[o][k] && clausura[k][d];
            }
        }
    }

    for (int o = 0; o < g->getV(); o++)
    {
        for (int d = 0; d < g->getV(); d++)
        {
            if (o != d)
            {
                if (!clausura[o][d])
                {
                    cout << "No existe camino entre el origen " << o << " y el destino " << d << endl;
                }
                else
                {
                    cout << "Existe camino entre el origen " << o << " y el destino " << d << endl;
                }
            }
        }
    }
}

void prim(int origen, Grafo_LA *g)
{
    int *costo = new int[g->getV()]();
    int *vengo = new int[g->getV()]();
    bool *visitado = new bool[g->getV()]();

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
            if (costo[j] < menorCosto && !visitado[j])
            {
                v = j;
                menorCosto = costo[j];
            }
        }

        // nos cubrimos por si el menor nodo no visitado no lo puedo alcanzar me voy
        if (v == -1)
            break;

        visitado[v] = true;

        NodoLista<Arista> *ady = g->adyacentesA(v);
        while (ady != NULL)
        {
            Arista a = ady->dato;
            int u = a.destino;
            int w = a.peso;
            if (!visitado[u] && costo[u] > w)
            {
                costo[u] = w;
                vengo[u] = v;
            }
            ady = ady->sig;
        }
    }

    int sum = 0;

    for (int i = 0; i < g->getV(); i++)
    {
        if (visitado[i] && vengo[i] != -1)
        {
            cout << i << "--" << vengo[i] << " " << costo[i] << endl;
            sum += costo[i];
        }
    }
    std::cout << "Con un costo total de " << sum << std::endl;
}

int main()
{
    Grafo_LA *miGrafito = new Grafo_LA(7, false);
    miGrafito->agregarArista(0, 1, 2);
    miGrafito->agregarArista(1, 4, -1);
    miGrafito->agregarArista(1, 3, 10);
    miGrafito->agregarArista(1, 2, 2);
    miGrafito->agregarArista(0, 2, 5);
    miGrafito->agregarArista(4, 2, 3);
    miGrafito->agregarArista(2, 3, 4);
    miGrafito->agregarArista(3, 5, 2);
    miGrafito->agregarArista(6, 3, 15);
    miGrafito->agregarArista(6, 5, 1);
    miGrafito->agregarArista(2, 5, 1);

    // dijsktra(1, miGrafito);

    // floyd(miGrafito);

    // warshall(miGrafito);

    prim(0, miGrafito);

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