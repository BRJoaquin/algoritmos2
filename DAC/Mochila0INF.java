import java.util.*;

class Mochila0INF {

    static int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // { obj1, obj2, obj3, .., objN-1, objN}
    //
    static int mochila0INF(int capacidad, int fin, int[] valores, int[] pesos) {
        // si no tengo capacidad o no tengo objetos
        if (capacidad == 0 || fin < 0) {
            // no tengo valor
            return 0;
        }

        // si no entra el objeto fin, no lo considero
        if (pesos[fin] > capacidad) {
            return mochila0INF(capacidad, fin - 1, valores, pesos);
        }

        int valorDeLaMochilaUsandoElObjeto = valores[fin] + mochila0INF(capacidad - pesos[fin], fin, valores, pesos);

        int valorDeLaMochilaDeNOusarElObjeto = mochila0INF(capacidad, fin - 1, valores, pesos);
        return max(valorDeLaMochilaUsandoElObjeto, valorDeLaMochilaDeNOusarElObjeto);
    }

    public static void main(String args[]) {
        int valores[] = new int[] { 60, 100, 120 };
        int pesos[] = new int[] { 15, 20, 30 };
        int capacidadMochila = 75;
        int cantidadDeObjetos = valores.length;

        System.out.println(mochila0INF(capacidadMochila, cantidadDeObjetos - 1, valores, pesos));
    }
}
// fuente: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/