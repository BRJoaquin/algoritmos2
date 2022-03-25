#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Min_Heap
{
private:
    int *arr;
    int primerPosLibre;
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
        int aux = this->arr[pos1];
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
        if (posHijoDer < primerPosLibre)
        {
            int posHijoMenor = arr[posHijoIzq] < arr[posHijoDer] ? posHijoIzq : posHijoDer;
            if (arr[pos] > arr[posHijoMenor])
            {
                intercambiar(pos, posHijoMenor);
                hundir(posHijoMenor);
            }
            // si tengo solo hijo izquierdo
        }
        else if (posHijoIzq < primerPosLibre)
        {
            if (arr[pos] > arr[posHijoIzq])
            {
                intercambiar(pos, posHijoIzq);
                hundir(posHijoIzq);
            }
        }
    }

public:
    Min_Heap(int unaCapacidad)
    {
        this->arr = new int[unaCapacidad + 1]();
        this->primerPosLibre = 1;
        this->capacidad = unaCapacidad;
    }

    int tope()
    {
        assert(!estaVacio());
        return this->arr[1];
    }

    void eliminarTope()
    {
        assert(!estaVacio());
        // sutituimos la raiz con el ultimo elemento
        this->arr[1] = this->arr[primerPosLibre - 1];
        this->primerPosLibre--;
        hundir(1);
    }

    void insertar(int el)
    {
        assert(!estaLleno());
        this->arr[primerPosLibre++] = el;
        flotar(primerPosLibre - 1);
    }

    bool estaLleno()
    {
        return this->primerPosLibre > this->capacidad;
    }

    bool estaVacio()
    {
        return this->primerPosLibre == 1;
    }
};

int main()
{
    Min_Heap *heap = new Min_Heap(100);
    
    heap->insertar(22);
    heap->insertar(10);
    heap->insertar(100);
    heap->insertar(77);
    heap->insertar(18);
    heap->insertar(101);
    heap->insertar(99);
    heap->insertar(200);
    heap->insertar(1000);
    heap->insertar(2);
    heap->insertar(23);

    while(!heap->estaVacio()) {
        cout << heap->tope() << endl;
        heap->eliminarTope();
    }

    return 0;
}