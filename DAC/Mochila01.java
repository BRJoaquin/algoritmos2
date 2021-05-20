import java.util.*;

class Mochila01 {

    static int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // { obj1, obj2, obj3, .., objN-1, objN}
    //                              
    static int mochila01(int capacidad, int fin, int[] valores, int[] pesos) {
        // si no tengo capacidad o no tengo objetos
        if (capacidad == 0 || fin < 0) {
            // no tengo valor
            return 0;
        }

        // si no entra el objeto fin, no lo considero
        if (pesos[fin] > capacidad) {
            return mochila01(capacidad, fin - 1, valores, pesos);
        }

        int valorDeLaMochilaUsandoElObjeto = valores[fin] + mochila01(capacidad - pesos[fin], fin - 1, valores, pesos);

        int valorDeLaMochilaDeNOusarElObjeto = mochila01(capacidad, fin - 1, valores, pesos);            
        return max(valorDeLaMochilaUsandoElObjeto, valorDeLaMochilaDeNOusarElObjeto);
    }

    /*
        int valores[] = new int[] { 120, 200};
        int pesos[] = new int[] { 20, 10 };
        int capacidadMochila = 50;
    */
    // m (50, 1) = max(200+m(40,0), m(50,0)) = max(200+120, 120) = 320
        // m(40, 0) = max(120+m(20,-1), m(50,-1)) = 120
            // m(20,-1) = 0
            // m(50,-1) = 0
        // m(50, 0) = max(120+m(30,-1), m(50, -1)) = 120
            // 

            // 2^n
            // 0 1
            // 00 01 10 11
            // 000 001 010 011 100 101 110 111


    // Driver program to test
    // above function
    public static void main(String args[]) {
        int valores[] = new int[] { 60, 100, 120 };
        int pesos[] = new int[] { 10, 20, 30 };
        int capacidadMochila = 50;
        int cantidadDeObjetos = valores.length;

        System.out.println(mochila01(capacidadMochila, cantidadDeObjetos - 1, valores, pesos));
    }
}
// fuente: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/