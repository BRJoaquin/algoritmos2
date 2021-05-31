import java.util.Scanner;

public class Fibo {

    static double fibovigna(int n, int m, double[][] calculados) {
        if (calculados[n][m] != -1) {
            return calculados[n][m];
        }
        if (n == 0) {
            return 2;
        }
        if (m == 0) {
            return 0;
        }
        calculados[n][m] = fibovigna(n - 1, m, calculados) + fibovigna(n - 1, m - 1, calculados);
        return calculados[n][m];
    }

    static int fibonacci(int n, int[] calculados) {
        if (calculados[n] != -1) {
            return calculados[n];
        }
        if (n == 0 || n == 1) {
            return n;
        }
        calculados[n] = fibonacci(n - 1, calculados) + fibonacci(n - 2, calculados);
        return calculados[n];
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        double[][] calculados = new double[n + 1][m + 1];
        for (int i = 0; i < calculados.length; i++) {
            for (int j = 0; j < calculados[0].length; j++) {
                calculados[i][j] = -1;
            }
        }
        // System.out.println(fibonacci(n, calculados));
        System.out.println(fibovigna(n, m, calculados));
    }
}