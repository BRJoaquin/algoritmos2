#ifndef MINHEAP
#define MINHEAP
#include <cassert>
template <class T>
class MinHeap
{
private:
    T *arr;
    int posTope;
    int capacidad;

    int izq(int pos)
    {
        return pos * 2;
    }

    int der(int pos)
    {
        return (pos * 2) + 1;
    }

    int padre(int pos)
    {
        return pos / 2;
    }

    void intercambiar(int pos1, int pos2)
    {
        T aux = this->arr[pos1];
        this->arr[pos1] = this->arr[pos2];
        this->arr[pos2] = aux;
    }

    void flotar(int pos)
    {
        // trato de flotar si no soy la raiz
        if (pos > 1)
        {
            int posPadre = padre(pos);
            if (this->arr[posPadre] > this->arr[pos])
            {
                intercambiar(posPadre, pos);
                flotar(posPadre);
            }
        }
    }

    void hundir(int pos)
    {
        int posHijoIzq = izq(pos);
        int posHijoDer = der(pos);

        // si tengo mis dos hijos
        if (posHijoIzq < posTope && posHijoDer < posTope)
        {
            int posHijoMenor = arr[posHijoIzq] < arr[posHijoDer] ? posHijoIzq : posHijoDer;
            if (arr[pos] > arr[posHijoMenor])
            {
                intercambiar(pos, posHijoMenor);
                hundir(posHijoMenor);
            }
            // si tengo solo hijo izquierdo
        }
        else if (posHijoIzq < posTope)
        {
            if (arr[pos] > arr[posHijoIzq])
            {
                intercambiar(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
        }
    }

public:
    MinHeap(int unaCapacidad)
    {
        this->arr = new T[unaCapacidad + 1]();
        this->posTope = 1;
        this->capacidad = unaCapacidad;
    }

    T tope()
    {
        assert(!estaVacio());
        return this->arr[1];
    }

    void eliminarTope()
    {
        assert(!estaVacio());
        this->arr[1] = this->arr[posTope - 1];
        this->posTope--;
        hundir(1);
    }

    void insertar(T el)
    {
        assert(!estaLleno());
        this->arr[posTope++] = el;
        flotar(posTope - 1);
    }

    bool estaLleno()
    {
        return this->posTope > this->capacidad;
    }

    bool estaVacio()
    {
        return this->posTope == 1;
    }
};
#endif