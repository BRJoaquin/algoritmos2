
#include <iostream>
using namespace std;

// los dos metodos mas importantes de todo iterador son termino() y siguiente()
template <class T>
class Iterador
{
public:
    // pre:
    // pos: indica si termino de recorrer la estructura
    virtual bool termino() = 0;
    // pre: que no haya terminado
    // pos: avanza el indice y retorna el elemento actual
    virtual T siguiente() = 0;
};

// para ser practicos se define una lista minimalista
// lo importante es el metodo getIterador donde retorna un iterador
template <class T>
class Lista
{
public:
    virtual void insertar(T &el) = 0;
    virtual void insertarFin(T &el) = 0;
    /* 
        ...
        Resto de metodos de lista
        ...
    */
    virtual Iterador<T> *getIterador() = 0;
};

template <class T>
struct NodoLista
{
    T dato;
    NodoLista *sig;
    NodoLista(T &unDato) : dato(unDato), sig(0){};
    NodoLista(T &unDato, NodoLista *unSig) : dato(unDato), sig(unSig){};
};

// implementacion 1 de iterador de lista
// basicamente se copia la lista con NodoListas en el caso que se modifique la lista
template <class T>
class IteradorListaImp : public Iterador<T>
{
private:
    NodoLista<T> *ppio;
    NodoLista<T> *aux;

public:
    IteradorListaImp(NodoLista<T> *unPpio)
    {
        if (unPpio != 0)
        {
            this->ppio = new NodoLista<T>(unPpio->dato);
            NodoLista<T> *miAux = this->ppio;
            NodoLista<T> *listAux = unPpio;
            while (listAux->sig != 0)
            {
                listAux = listAux->sig;
                miAux->sig = new NodoLista<T>(listAux->dato);
                miAux = miAux->sig;
            }
            this->aux = this->ppio;
        }
        else
        {
            this->ppio = 0;
            this->aux = 0;
        }
    }
    bool termino()
    {
        return aux == 0;
    }
    T siguiente()
    {
        T toRet = aux->dato;
        aux = aux->sig;
        return toRet;
    }
};

// implementacion 2 de lista: en vez de utilizar NodoLista guarda un array para luego recorrer
template <class T>
class IteradorListaImp2 : public Iterador<T>
{
private:
    T *arr;
    int largo;
    int index;

public:
    IteradorListaImp2(NodoLista<T> *unPpio)
    {
        this->largo = 0;
        if (unPpio != 0)
        {
            // calculo el largo de la lista
            NodoLista<T> *listAux = unPpio;
            while (listAux != 0)
            {
                this->largo++;
                listAux = listAux->sig;
            }
            this->arr = new T[this->largo];

            // recorro la lista y copio los elementos en un array
            listAux = unPpio;
            int i = 0;
            while (listAux != 0)
            {
                this->arr[i] = listAux->dato;
                listAux = listAux->sig;
                i++;
            }
        }
    }
    bool termino()
    {
        return this->index == this->largo;
    }
    T siguiente()
    {
        return this->arr[index++];
    }
};

template <class T>
class ListaImp : public Lista<T>
{
private:
    NodoLista<T> *ppio;
    NodoLista<T> *fin;

public:
    ListaImp()
    {
        ppio = 0;
        fin = 0;
    }
    void insertar(T &el)
    {
        this->ppio = new NodoLista<T>(el, this->ppio);
        if (this->ppio->sig == NULL)
        {
            this->fin = this->ppio;
        }
    }
    void insertarFin(T &el)
    {
        if (this->ppio == NULL)
        {
            this->insertar(el);
        }
        else
        {
            this->fin->sig = new NodoLista<T>(el);
            this->fin = this->fin->sig;
        }
    }
    /* 
        ...
        Resto de metodos de lista
        ...
    */
    Iterador<T> *getIterador()
    {
        // version 1: con NodoLista
        // return new IteradorListaImp<T>(this->ppio);
        // version 2: con array
        return new IteradorListaImp2<T>(this->ppio);
    }
};


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
class ArbolBinarioDeBusqueda
{
private:
    typedef NodoAB<T> *ABB;
    ABB raiz;
    void insertAux(T &dato, ABB &nodo)
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

    Lista<T> *aplanarArbol(ABB nodo)
    {
        if (nodo == 0)
        {
            return new ListaImp<T>();
        }
        Lista<T> *listaIzq = aplanarArbol(nodo->izq);
        T datoNodo = nodo->dato;
        Lista<T> *listaDer = aplanarArbol(nodo->der);

        listaIzq->insertarFin(datoNodo);
        Iterador<T> *it = listaDer->getIterador();
        while (!it->termino())
        {
            T aux = it->siguiente();
            listaIzq->insertarFin(aux);
        }

        delete listaDer;
        delete it;

        return listaIzq;
    }

public:
    ArbolBinarioDeBusqueda()
    {
        raiz = 0;
    }
    void insert(T &dato)
    {
        this->insertAux(dato, raiz);
    }
    // en muchos casos de estructuras no lineales como los arboles, se puede optar por "aplanar" el arbol
    Iterador<T> *getIterador()
    {
        Lista<T> *lista = this->aplanarArbol(this->raiz);
        Iterador<T> *it = lista->getIterador();
        delete lista;
        return it;
    }
};

// Probar iterador arbol
int main()
{
    int n;
    int aux;
    cout << "Ingrese la cantidad de datos a ingresar: " << endl;
    cin >> n;
    ArbolBinarioDeBusqueda<int> *miArbol = new ArbolBinarioDeBusqueda<int>();

    cout << "Ingrese los datos" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> aux;
        miArbol->insert(aux);
    }

    cout << "Recorro el arbol" << endl;
    Iterador<int> *it = miArbol->getIterador();
    // por lo general, utilizar un iterador tiene la siguiente estructura, un while e ir avanzando el indice
    // notar que en el ejemplo de abajo (el segundo main), se recorre exactamten igual.
    // a quien utiliza el iterador NO le interesa como lo hace
    while (!it->termino())
    {
        int aux = it->siguiente();
        cout << aux << endl;
    }

    return 0;
}

// Probar iterador lista
// int main()
// {
//     int n;
//     int aux;
//     cout << "Ingrese la cantidad de datos a ingresar: " << endl;
//     cin >> n;
//     Lista<int> *miLista = new ListaImp<int>();

//     cout << "Ingrese los datos" << endl;
//     for (int i = 0; i < n; i++)
//     {
//         cin >> aux;
//         miLista->insertarFin(aux);
//     }

//     cout << "Recorro la lista" << endl;
//     Iterador<int> *it = miLista->getIterador();
//     while (!it->termino())
//     {
//         int aux = it->siguiente();
//         cout << aux << endl;
//     }

//     return 0;
// }
