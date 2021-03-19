// import java.util.Scanner;

abstract class ColaDePrioridad {
    abstract void insertar(int elemento);
    abstract void desencolar();
    abstract int tope();
    abstract boolean esVacia();
    abstract boolean estaLlena();
};

class NodoLista {
    public NodoLista sig;
    public NodoLista ant;
    public int dato;
    public NodoLista() {};
    public NodoLista(int unDato, NodoLista unSig, NodoLista unAnt) {
        dato = unDato;
        sig = unSig;
        ant = unAnt;
    };
    public NodoLista(int unDato) {
        dato = unDato;
        sig = null;
        ant = null;
    };
};

class Lista {
    private NodoLista ppio;

    public Lista() { ppio = null; }

    public void insertar(int dato) {
        NodoLista nuevoNodo =  new NodoLista(dato, this.ppio, null);
        if(this.ppio != null) {
            this.ppio.ant = nuevoNodo;
        }
        ppio = nuevoNodo;
    }
    public int obtenerMenor() {
		if(esVacia())
			throw new Error("La lista esta vacia");
        NodoLista menor = this.ppio;
        NodoLista aux = this.ppio;
        while(aux != null) {
            if(menor.dato > aux.dato) {
                menor = aux;
            }
            aux = aux.sig;
        }
        return menor.dato;
    }

    public void eliminarMenor() {
		if(esVacia())
			throw new Error("La lista esta vacia");
        NodoLista menor = this.ppio;
        NodoLista aux = this.ppio;
        while(aux != null) {
            if(menor.dato > aux.dato) {
                menor = aux;
            }
            aux = aux.sig;
        }

        // elimino el nodo que contiene el menor dato
        if(menor.ant != null) {
            menor.ant.sig = menor.sig;
        }else {
            ppio = menor.sig;
        }
        if(menor.sig != null) {
            menor.sig.ant = menor.ant;
        }
    }

    public boolean esVacia() {
        return ppio == null;
    }
};

class ColaDePrioridadImpLista extends ColaDePrioridad {
    private Lista miLista;

    public ColaDePrioridadImpLista() {
        miLista = new Lista();
    }
    public void insertar(int el) {
        miLista.insertar(el);
    }
    public void desencolar() {
        miLista.eliminarMenor();
    }
    public int tope() {
		return miLista.obtenerMenor();
	}
    public boolean esVacia() {
        return miLista.esVacia();
    }
    public boolean estaLlena() {
        return false;
    }
};



public class ColaDePrioridad_Lista {
    public static void main(String[] args) {
        ColaDePrioridad cp = new ColaDePrioridadImpLista();
		
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