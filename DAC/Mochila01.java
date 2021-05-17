import java.util.*;

class Mochila01 {

    static int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // post: retorna el mayor valor que puede entrar dentro de la mochila
    static int mochila(int capacidadMochila, int pesos[], int valores[], int objetoHasta) {
        // caso base
        if (objetoHasta < 0 || capacidadMochila == 0)
            return 0;

        // En caso de que el objeto no entre lo descartamos (objetoHasta - 1)
        if (pesos[objetoHasta] > capacidadMochila) {
            return mochila(capacidadMochila, pesos, valores, objetoHasta - 1);
        }

        // retornar el maximo de:
        // usar el objeto (sumo valor, resto peso)
        // no usar el objeto (llamo recursivo ignorando el objeto)
        int valorDeUsarlo = valores[objetoHasta]
                + mochila(capacidadMochila - pesos[objetoHasta], pesos, valores, objetoHasta - 1);
        int valorNoDeUsarlo = mochila(capacidadMochila, pesos, valores, objetoHasta - 1);
        return max(valorDeUsarlo, valorNoDeUsarlo);
    }

    // Driver program to test
    // above function
    public static void main(String args[]) {
        int valores[] = new int[] { 60, 100, 120 };
        int pesos[] = new int[] { 10, 20, 30 };
        int capacidadMochila = 50;
        int cantidadDeObjetos = valores.length;
        System.out.println(mochila(capacidadMochila, pesos, valores, cantidadDeObjetos - 1));
    }
}
// fuente: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/