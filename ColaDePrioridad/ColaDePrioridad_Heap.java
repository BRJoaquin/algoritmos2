// import java.util.Scanner;

abstract class ColaDePrioridad {
    abstract void insertar(int elemento);
    abstract void desencolar();
    abstract int tope();
    abstract boolean esVacia();
    abstract boolean estaLlena();
};

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

}

class ColaDePrioridadImpHeap extends ColaDePrioridad {
    private MinHeap miHeap;

    public ColaDePrioridadImpHeap(int tamanio) {
        miHeap = new MinHeap(tamanio);
    }
    public void insertar(int el) {
        miHeap.insertar(el);
    }
    public void desencolar() {
        miHeap.borrarMinimo();
    }
    public int tope() {
		return miHeap.obtenerMinimo();
	}
    public boolean esVacia() {
        return miHeap.esVacio();
    }
    public boolean estaLlena() {
        return miHeap.estaLleno();
    }
};



public class ColaDePrioridad_Heap {
    public static void main(String[] args) {
        ColaDePrioridad cp = new ColaDePrioridadImpHeap(100);
		
        cp.insertar(12);
        cp.insertar(1);
        cp.insertar(44);
        cp.insertar(100);
        cp.insertar(56);
        cp.insertar(122);

        while(!cp.esVacia()) {
            System.out.println(cp.tope());
			cp.desencolar();
        }
    }
}