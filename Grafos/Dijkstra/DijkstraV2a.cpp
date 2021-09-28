#include <climits>
#include <string>
#include <iostream>
using namespace std;

class Heap
{
private:
    int **elementos;
    int *pos;
    int largo;
    int ultimoLibre;

    // navegar hacia la izquierda
    int izq(int posNodo)
    {
        return posNodo * 2;
    }

    // navegar hacia la derecha
    int der(int posNodo)
    {
        return posNodo * 2 + 1;
    }

    // navego hacia mi padre
    int padre(int posNodo)
    {
        return posNodo / 2;
    }

    void intercambiar(int x, int y)
    {
        int eleAux = elementos[0][x];
        int prioridadAux = elementos[1][x];
        // intercambio los elementos
        elementos[0][x] = elementos[0][y];
        elementos[0][y] = eleAux;
        // intercambio las prioridades
        elementos[1][x] = elementos[1][y];
        elementos[1][y] = prioridadAux;

        int posAux = pos[x];
        pos[x] = pos[y];
        pos[y] = posAux;
    }

    void flotar(int posNodo)
    {
        // si no llegue a la raiz
        if (posNodo != 1)
        {
            int posNodoPadre = padre(posNodo);
            // en el caso de que no sea mi posicion: intercambio y sigo flotando
            if (elementos[1][posNodo] < elementos[1][posNodoPadre])
            {
                intercambiar(posNodo, posNodoPadre);
                flotar(posNodoPadre);
            }
        }
    }

    void hundir(int posNodo)
    {
        // si tiene hijos (al menos 1)
        if (izq(posNodo) < ultimoLibre)
        {
            int posIzq = izq(posNodo);
            int posDer = der(posNodo);
            int hijoMenor = posIzq;

            // si tengo hijo derecho && el hijo derecho es menor que el hijo izquierdo
            if (posDer < ultimoLibre && elementos[1][posDer] < elementos[1][posIzq])
            {
                hijoMenor = posDer;
            }

            if (elementos[1][hijoMenor] < elementos[1][posNodo])
            {
                intercambiar(hijoMenor, posNodo);
                hundir(hijoMenor);
            }
        }
    }

public:
    Heap(int tamanio)
    {
        elementos = new int *[2];
        elementos[0] = new int[tamanio + 1];
        elementos[1] = new int[tamanio + 1];
        pos = new int[tamanio + 1];
        for (int i = 0; i < tamanio + 1; i++)
        {
            pos[i] = -1;
        }
        largo = tamanio;
        ultimoLibre = 1;
    }

    void insertar(int nuevoElemento, int prioridad)
    {
        if (!estaLleno())
        {
            // inserto en la ultima posicion libre
            elementos[0][ultimoLibre] = nuevoElemento;
            elementos[1][ultimoLibre] = prioridad;
            pos[nuevoElemento] = ultimoLibre;
            // floto la ultima posicion libre
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

    void cambiarPrioridad(int elemento, int nuevaPrioridad) {
        if(existe(elemento)) {
            int posDelElemento = pos[elemento];
            elementos[1][posDelElemento] = nuevaPrioridad;
            flotar(posDelElemento);
            hundir(posDelElemento);
        }
    }

    bool existe(int elemento) {
        return pos[elemento] != -1;
    }

    int obtenerMinimo()
    {
        if (!esVacio())
        {
            return elementos[0][1];
        }
        return -1;
    }

    void borrarMinimo()
    {
        if (!esVacio())
        {
            // pongo en la raiz el ultimo elemento
            pos[elementos[0][1]] = -1;
            elementos[0][1] = elementos[0][ultimoLibre - 1];
            elementos[1][1] = elementos[1][ultimoLibre - 1];
            ultimoLibre--;
            // hundo la raiz
            hundir(1);
        }
    }

    bool esVacio()
    {
        return ultimoLibre == 1;
    }

    bool estaLleno()
    {
        return ultimoLibre > largo;
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


void imprimirCamino(int destino, int *vengo)
{
    while (destino != -1)
    {
        cout << destino;
        if (vengo[destino] != -1)
        {
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
    Heap* heap = new Heap(V);
	heap->insertar(origen, 0);
	while(!heap->esVacio()) {
		int v = heap->obtenerMinimo(); // extrae el vértice de menor costo no visitado
        heap->borrarMinimo();
		visitados[v] = true;
        ListaAristas arista = g->adyacentesA(v);
        while(arista != NULL) {
            int w =  arista->dato.destino;
            int peso =  arista->dato.peso;
            // pregunto si mejoro el costo tentativo
            if(costos[w] > costos[v] + peso) {
                costos[w] = costos[v] + peso;
                vengo[w] = v;
                if(heap->existe(w)) {
                    heap->cambiarPrioridad(w, costos[w]);
                }else {
                    heap->insertar(w, costos[w]);
                }
            }
            arista = arista->sig;
        }
    } 

    for (int i = 1; i <= V; i++)
    {
        int inf = INF;
        if (i != origen)
        {
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
    Grafo *g = new GrafoListaAdyImp(7, true, true);

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