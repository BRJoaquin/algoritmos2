import java.util.*;
import java.lang.Math;

class Mochila01 {

    static int max(int a, int b) {
        return (a > b) ? a : b;
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
    }
}