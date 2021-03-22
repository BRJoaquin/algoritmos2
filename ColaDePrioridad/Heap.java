class MinHeap {
    private int[] elementos;
    private int largo;
    private int ultimoLibre;

    public MinHeap(int tamanio) {
        elementos = new int[tamanio + 1];
        largo = tamanio;
        ultimoLibre = 1;
    }

    // navegar hacia la izquierda
    private int izq(int posNodo) {
        return posNodo * 2;
    }
    
    // navegar hacia la derecha
    private int der(int posNodo) {
        return posNodo * 2 + 1;
    }

    // navego hacia mi padre
    private int padre(int posNodo) {
        return posNodo/2;
    }

    private void intercambiar(int x, int y) {
        int aux = elementos[x];
        elementos[x] = elementos[y];
        elementos[y] = aux;
    }

    public void insertar(int nuevoElemento) {
        if(!estaLleno()) {
            // inserto en la ultima posicion libre
            elementos[ultimoLibre] = nuevoElemento;
            // floto la ultima posicion libre
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

    private void flotar(int posNodo) {
        // si no llegue a la raiz
        if(posNodo != 1) {
            int posNodoPadre = padre(posNodo);
            // en el caso de que no sea mi posicion: intercambio y sigo flotando
            if(elementos[posNodo] < elementos[posNodoPadre]) {
                intercambiar(posNodo, posNodoPadre);
                flotar(posNodoPadre);
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
            // pongo en la raiz el ultimo elemento
            elementos[1] = elementos[ultimoLibre - 1];
            ultimoLibre--;
            // hundo la raiz
            hundir(1);
        }
    }

    private void hundir(int posNodo) {
        // si tiene hijos (al menos 1)
        if(izq(posNodo) < ultimoLibre) {
            int posIzq = izq(posNodo);
            int posDer = der(posNodo);
            int hijoMenor = posIzq;

            // si tengo hijo derecho && el hijo derecho es menor que el hijo izquierdo
            if(posDer < ultimoLibre && elementos[posDer] < elementos[posIzq]) {
                hijoMenor = posDer;
            }

            if(elementos[hijoMenor] < elementos[posNodo]) {
                intercambiar(hijoMenor, posNodo);
                hundir(hijoMenor);
            }
        }
    }

    public boolean esVacio() {
        return ultimoLibre == 1;
    }

    public boolean estaLleno() {
        return ultimoLibre > largo;
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