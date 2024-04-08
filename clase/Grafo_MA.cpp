#include <string>
#include <iostream>
#include <limits>
using namespace std;

template <class T>
class NodoLista {
    public:
        T dato;
        NodoLista * sig;
        NodoLista(T _dato, NodoLista * _sig) : dato(_dato), sig(_sig) {};
        NodoLista(T _dato) : dato(_dato), sig(NULL) {};
};

class Arista {
    public:
        // int origen; queda en ustedes usarlo
        int destino;
        int peso;
        Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}
};


#define inf INT_MAX;

class Grafo_MA {
    private:
        int** grafo;
        int V;
        bool esDirigido;
    
    public:
        Grafo_MA(int _V, bool _esDirigido) {
            this->V =  _V;
            this->esDirigido = _esDirigido;
            grafo = new int*[_V];
            for (int i = 0; i < _V; i++)
            {
                grafo[i] = new int[_V];
                for (int j = 0; j < _V; j++)
                {
                    grafo[i][j] = inf;
                }
            }
        }

        void agregarArista(int origen, int destino, int peso = 1) {
            grafo[origen][destino] = peso;
            if(!esDirigido) {
                grafo[destino][origen] = peso;
            }
        }

        NodoLista<Arista> * adyacentesA(int origen) {
            NodoLista<Arista> * ret = NULL;
            int internalInf =  inf;
            for (int destino = 0; destino < V; destino++)
            {
                if(grafo[origen][destino] != internalInf) {
                    Arista a(destino, grafo[origen][destino]);
                    ret = new NodoLista<Arista>(a, ret);
                }
            } 
            return ret;
        }
};


int main()
{
    Grafo_MA * miGrafito = new Grafo_MA(4, true);
    miGrafito->agregarArista(0, 1, 5);
    miGrafito->agregarArista(1, 2, 10);
    miGrafito->agregarArista(1, 3, 1);
    miGrafito->agregarArista(2, 3, 2);
    miGrafito->agregarArista(3, 2, 4);

    // O(V^2)
    for (int v = 0; v < 4; v++)
    {
        cout << "Los adyacentes de " << v << ":" << endl;
        NodoLista<Arista> * adyacentesAUno = miGrafito->adyacentesA(v);
        while(adyacentesAUno != NULL) {
            Arista a = adyacentesAUno->dato;
            cout << a.destino << " p(" << a.peso << ")" << endl;
            adyacentesAUno = adyacentesAUno->sig;
        }
    }
}