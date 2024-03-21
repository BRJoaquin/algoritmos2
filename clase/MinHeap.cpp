#include <string>
#include <iostream>
#include <limits>
#include <cassert>

using namespace std;

template <class T>
class MinHeap
{
    private:
        T* heap;
        int next;
        int capacity;
        int (*compereTo)(T,T);

        int father(int pos) {
            return pos / 2;
        }

        int left(int pos) {
            return pos * 2;
        }

        int right(int pos) {
            return (pos * 2) + 1;
        }

        void swap(int a, int b) {
            T aux =  heap[a];
            heap[a] = heap[b];
            heap[b] = aux;
        }

        void heapFloat(int pos) {
            if(pos == 1) return; // si estoy en la raiz termino
            int fatherPos = father(pos);
            if(this->compereTo(heap[fatherPos], heap[pos]) > 0) { // tengo que flotar
                swap(fatherPos, pos);
                heapFloat(fatherPos);
            }
        }

        void sink(int pos) {
            int leftPos = left(pos);
            int rightPos = right(pos);
            bool hasLeftChild = leftPos < this->next;
            bool hasRightChild = rightPos < this->next;
            if(!hasLeftChild) return; // no tengo ningun hijo
            if(!hasRightChild) { // solo tiene hijo izquierdo
                if(this->compereTo(heap[pos], heap[leftPos]) > 0) {
                    swap(pos, leftPos);
                    sink(leftPos);
                }
            } else { // tengo mis dos hijos
                int posToCompare = this->compereTo(heap[leftPos], heap[rightPos]) < 0 ? leftPos : rightPos;
                if(this->compereTo(heap[pos], heap[posToCompare]) > 0) {
                    swap(pos, posToCompare);
                    sink(posToCompare);
                }
            }
        }

    public:
        MinHeap(int _capacity, int (*_compereTo)(T,T)) : capacity(_capacity) {
            this->next = 1;
            this->heap = new T[_capacity + 1]();
            this->compereTo=_compereTo;
        }

        void insert(T el) {
            assert(!isFull()); // chequeamos que no este lleno el heap
            heap[next] = el;
            next++;
            heapFloat(next-1); //flotamos la posicion del elemento que ingresamos
        }

        T peek() {
            assert(!isEmpty());
            return this->heap[1];
        }

        void removePeek() {
            assert(!isEmpty());
            this->heap[1] = this->heap[next-1];
            this->next--;
            sink(1);
        }

        bool isFull() {
            return next > capacity;
        }

        bool isEmpty() {
            return next == 1;
        }
};

//  0  1  2  3  4  5
// [/][3][5][ ][ ][ ]

class Persona{
    public: 
        int edad;
        string nombre;
        Persona() {}
        Persona(int _edad, string _nombre) : edad(_edad), nombre(_nombre) {}
};

int compararInts(int a, int b) {
    return a - b;
}


int main()
{
    MinHeap<int> * myMinHeap = new MinHeap<int>(10, compararInts);
    for (int i = 0; i < 5; i++)
    {
        cout << "ingrese elemento" << endl;
        int aux;
        cin >> aux;
        myMinHeap->insert(aux);
    }
    std::cout << "Imprimir todos los elementos" << std::endl;
    while(!myMinHeap->isEmpty()){
        std::cout << myMinHeap->peek() << std::endl;
        myMinHeap->removePeek();
    }
    
}