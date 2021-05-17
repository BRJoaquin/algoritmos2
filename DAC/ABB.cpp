#ifndef ARBOL_ABB
#define ARBOL_ABB
#include <iostream>
#include <cassert>
using namespace std;

template <class T>
struct NodoAB
{
    T dato;
    NodoAB *izq;
    NodoAB *der;

    NodoAB(T &dt) : dato(dt), izq(0), der(0) {}
    NodoAB(T &dt, NodoAB *i, NodoAB *d) : dato(dt), izq(i), der(d) {}
};

template <class T>
class ArbolABB
{
private:
    typedef NodoAB<T> *ABB;
    ABB raiz;
    void insertAux(T dato, ABB &nodo)
    {
        if (nodo == 0)
        {
            nodo = new NodoAB<T>(dato);
        }
        else
        {
            if (nodo->dato > dato)
            {
                insertAux(dato, nodo->izq);
            }
            else if (nodo->dato < dato)
            {
                insertAux(dato, nodo->der);
            }
        }
    }
    void recInOrderAux(ABB nodo)
    {
        if (nodo != 0)
        {
            recInOrderAux(nodo->izq);
            cout << nodo->dato << endl;
            recInOrderAux(nodo->der);
        }
    }
    int cantidadElementosAux(ABB nodo)
    {
        if (nodo != 0)
        {
            return 1 + cantidadElementosAux(nodo->izq) + cantidadElementosAux(nodo->der);
        }
        return 0;
    }
    int alturaAux(ABB nodo)
    {
        if (nodo != 0)
        {
            int alturaIzq = alturaAux(nodo->izq);
            int alturaDer = alturaAux(nodo->der);

            int maxAltura = alturaIzq > alturaDer ? alturaIzq : alturaDer;
            return 1 + maxAltura;
        }
        return 0;
    }

    int maximoRecorridoAux(ABB nodo)
    {
        if (nodo != 0)
        {
            int maxIzq = maximoRecorridoAux(nodo->izq);
            int maxDer = maximoRecorridoAux(nodo->der);

            int maxRec = maxIzq > maxDer ? maxIzq : maxDer;
            return nodo->dato + maxRec;
        }
        return 0;
    }

public:
    ArbolABB()
    {
        raiz = 0;
    }
    void insert(T dato)
    {
        this->insertAux(dato, raiz);
    }
    void recInOrder()
    {
        this->recInOrderAux(raiz);
    }
    
    int cantidadElementos()
    {
        return this->cantidadElementosAux(raiz);
    }
    int altura()
    {
        return this->alturaAux(raiz);
    }
    int maximoRecorrido()
    {
        return this->maximoRecorridoAux(raiz);
    }
};

int main()
{

    ArbolABB<int> *miArbol = new ArbolABB<int>();

    miArbol->insert(5);
    miArbol->insert(6);
    miArbol->insert(1);
    miArbol->insert(2);
    miArbol->insert(3);
    miArbol->insert(33);
    miArbol->insert(23);
    miArbol->insert(123);
    miArbol->insert(99);
    miArbol->insert(12);
    miArbol->insert(24);
    miArbol->insert(55);

    
    // miArbol->recInOrder();
    // cout << "Cantidad de elemntos: " << miArbol->cantidadElementos() << endl;
    // cout << "Altura del arbol: " << miArbol->altura() << endl;
    cout << "Maximo recorrido: " << miArbol->maximoRecorrido() << endl;

    return 0;
}
#endif
