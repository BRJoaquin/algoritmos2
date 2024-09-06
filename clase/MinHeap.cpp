#ifndef MIN_HEAP
#define MIN_HEAP

template <class T>
class MinHeap
{
    private:
        int capacidad;
        int primerLibre;
        T* arr;
        int (*comparacion)(T, T);

        void swap(int pos1, int pos2) {
            T aux = arr[pos1];
            arr[pos1] = arr[pos2];
            arr[pos2] = aux;
        }

        int padre(int i) {
            return i / 2;
        }

        int izq(int i) {
            return 2 * i;
        }

        int der(int i) {
            return (2 * i) + 1;
        }

        void flotar(int pos) {
            if(pos == 1) return;
            int posPadre = padre(pos);
            if(comparacion(arr[pos], arr[posPadre]) > 0) {
                swap(pos, posPadre);
                flotar(posPadre);
            }
        }

        void hundir(int pos) {
            int posIzq = izq(pos);
            int posDer = der(pos);
            if(posIzq < primerLibre) { //  si tengo hijo izquierdo
                int posMenor = posIzq;
                // si tengo hijo derecho y mi hijo derecho es menor que mi hijo izquierdo
                if(posDer < primerLibre && comparacion(arr[posIzq], arr[posDer]) < 0) { 
                    posMenor = posDer;
                }

                // si el mejor de mis hijos es menor que yo, intercambio
                if(comparacion(arr[pos], arr[posMenor]) < 0) { 
                    swap(pos, posMenor);
                    hundir(posMenor);
                }
            }
        }
    public:

        MinHeap(int _capacidad, int (*_comparacion)(T, T)) {
            capacidad = _capacidad;
            primerLibre = 1;
            arr = new T[capacidad + 1]();
            comparacion = _comparacion;
        }

        void insertar(T el) {
            assert(!estaLleno());
            arr[primerLibre] = el;
            primerLibre++;
            flotar(primerLibre - 1);
        }

        T tope() {
            assert(!estaVacio());
            return arr[1];
        }

        void eliminar() {
            assert(!estaVacio());
            swap(1, primerLibre - 1);
            primerLibre--;
            hundir(1);
        }

        bool estaLleno() {
            return primerLibre > capacidad;
        }

        bool estaVacio() {
            return primerLibre == 1;
        }
};
#endif