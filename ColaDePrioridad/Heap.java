class MinHeap {
    private int[] elementos;
    private int largo;
    private int ultimoLibre;

    public MinHeap(int tamanio) {
        elementos = new int[tamanio + 1];
        largo = tamanio;
        ultimoLibre = 1;
    }

    private int izq(int nodo) {
        return nodo * 2;
    }

    private int der(int nodo) {
        return nodo * 2 + 1;
    }

    private int padre(int nodo) {
        return nodo/2;
    }

    private void intercambiar(int x, int y) {
        int aux = elementos[x];
        elementos[x] = elementos[y];
        elementos[y] = aux;
    }

    public void insertar(int nuevoElemento) {
        if(!estaLleno()) {
            elementos[ultimoLibre] = nuevoElemento;
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

    private void flotar(int nodo) {
        if(nodo != 1) {
            int nodoPadre = padre(nodo);
            if(elementos[nodo] < elementos[nodoPadre]) {
                intercambiar(nodo, nodoPadre);
                flotar(nodoPadre);
            }
        }
    }

    public int obtenerMinimo() {
        if(!esVacio()) {
            return elementos[1];
        }
        return -1;
    }

    public void borrarMinimo() {
        if(!esVacio()) {
            elementos[1] = elementos[ultimoLibre - 1];
            ultimoLibre--;
            hundir(1);
        }
    }

    private void hundir(int nodo) {
        // si tiene hijos (al menos 1)
        if(izq(nodo) < ultimoLibre) {
            int izq = izq(nodo);
            int der = der(nodo);
            int hijoMenor = izq;

            if(der < ultimoLibre && elementos[der] < elementos[izq]) {
                hijoMenor = der;
            }

            if(elementos[hijoMenor] < elementos[nodo]) {
                intercambiar(hijoMenor, nodo);
                hundir(hijoMenor);
            }
        }
    }

    public boolean esVacio() {
        return ultimoLibre == 1;
    }

    public boolean estaLleno() {
        return ultimoLibre == largo;
    }

    public void imprimirHeap() {
        System.out.println("Array: ");
        for(int i=1; i < ultimoLibre; i++) {
            System.out.print(elementos[i] + " ");
        }
        System.out.println("");
        System.out.println("Arbol:");
        int cantidadPorNivel = 1;
        int impresosDelNivel = 0;
        for(int i=1; i < ultimoLibre; i++) {
            System.out.print(elementos[i] + " ");
            impresosDelNivel++;
            if(cantidadPorNivel == impresosDelNivel) {
                System.out.println("");
                cantidadPorNivel *= 2;
                impresosDelNivel = 0;
            }
        }
		System.out.println("\n");
    }
}

public class Heap {
    public static void main(String[] args) {
        MinHeap heap = new MinHeap(20);
        heap.insertar(5);
        heap.insertar(2);
        heap.insertar(3);
        heap.insertar(64);
        heap.insertar(34);
        heap.insertar(100);
        heap.insertar(23);
        heap.insertar(21);

        heap.imprimirHeap();

        System.out.println("Vacio el heap:");
        while(!heap.esVacio()) {
            System.out.println(heap.obtenerMinimo());
			heap.borrarMinimo();
        }
    }
}