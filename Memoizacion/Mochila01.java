import java.util.*;
import java.lang.Math;

class Mochila01 {

    static int max(int a, int b) {
        return (a > b) ? a : b;
    }

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

    static int mochila01Memo(int capacidad, int fin, int[] valores, int[] pesos, int[][] memo) {
        // si no tengo capacidad o no tengo objetos
        if (capacidad == 0 || fin < 0) {
            // no tengo valor
            return 0;
        }

        // si ya esta calculado, devuelvo el valor
        if(memo[fin][capacidad] != -1) {
            System.out.println("Memoizacion: " + fin + " " + capacidad);
            return memo[fin][capacidad];
        }

        // si no entra el objeto fin, no lo considero
        if (pesos[fin] > capacidad) {
            return mochila01Memo(capacidad, fin - 1, valores, pesos, memo);
        }

        int valorDeLaMochilaUsandoElObjeto = valores[fin] + mochila01Memo(capacidad - pesos[fin], fin - 1, valores, pesos, memo);
        int valorDeLaMochilaDeNOusarElObjeto = mochila01Memo(capacidad, fin - 1, valores, pesos, memo);            
        memo[fin][capacidad] = max(valorDeLaMochilaUsandoElObjeto, valorDeLaMochilaDeNOusarElObjeto);

        return memo[fin][capacidad];
    }

    static int mochila01v2(int capacidad, int fin, int[] valores, int[] pesos) {
        int[][] memo = new int[fin + 1][capacidad + 1];
        for (int i = 0; i <= fin; i++) {
            for (int j = 0; j <= capacidad; j++) {
                memo[i][j] = -1;
            }
        }
        return mochila01Memo(capacidad, fin, valores, pesos, memo);
    }

    // TODO

    public static int generarRandom(int max, int min) {
        return (int) (Math.random() * (max - min + 1)) + min;
    }

    public static void main(String args[]) {
        System.out.println("Ingrese cantidad de elementos");
        Scanner in = new Scanner(System.in);
        int cantElementos = in.nextInt();

        int[] valores = new int[cantElementos];
        int[] pesos = new int[cantElementos];
        int capacidadMochila = 50;

        for (int i = 0; i < cantElementos; i++) {
            valores[i] = generarRandom(1, 10);
            pesos[i] = generarRandom(1, 100);
        }

        System.out.println("Valor de la mochila: " + mochila01v2(capacidadMochila, cantElementos - 1, valores, pesos));
    }
}