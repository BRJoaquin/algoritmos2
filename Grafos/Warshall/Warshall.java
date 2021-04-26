import java.util.Scanner;

// grafo dirigido y no ponderado
class Grafo {
    int INF = Integer.MAX_VALUE;
    int V;
    int[][] grafo;

    Grafo(int cantidadDeVertices) {
        V =  cantidadDeVertices;
        grafo = new int[V+1][V+1];
        for(int i=1; i<=V; i++) {
            for(int j=1; j<=V; j++) {
                grafo[i][j] = INF;
            }
        }
    }

    void aniadirArista(int origen, int destino) {
        grafo[origen][destino] = 1;
    }

    private boolean[][] initMatriz(boolean tratarComoDirigido) {
        boolean[][] ret = new boolean[V+1][V+1];
        for(int i=1; i<=V; i++) {
            for(int j=1; j<=V; j++) {
                if(tratarComoDirigido) {
                    ret[i][j] = grafo[i][j] != INF;
                }else {
                    ret[i][j] = grafo[i][j] != INF || grafo[j][i] != INF;
                }
            }
        }
        return ret;
    }

    private void warshall(boolean[][] matriz) {
        // imprimirMatriz(matriz);
        for(int k=1; k<=V; k++) {
            for(int i=1; i<=V; i++) {
                for(int j=1; j<=V; j++) {
                    matriz[i][j] = matriz[i][j] || matriz[i][k] && matriz[k][j];
                }
            }
        }
        // imprimirMatriz(matriz);
    }

    private void imprimirMatriz(boolean[][] matriz) {
        System.out.println("");
        for(int i=1; i<=V; i++) {
            for(int j=1; j<=V; j++) {
                System.out.print((matriz[i][j] ? "1": "0") + " ");
            }
            System.out.println("");
        }
        System.out.println("");
    }

    private boolean matrizCompleta(boolean[][] matriz) {
        boolean esCompleta = true;
        for(int i=1; i<=V; i++) {
            for(int j=1; j<=V; j++) {
                esCompleta = esCompleta && matriz[i][j];
            }
        }
        return esCompleta;
    }

    void conexidad() {
        boolean[][] matriz = initMatriz(true);
        boolean[][] matrizNoDirigida = initMatriz(false);

        warshall(matriz);
        if(matrizCompleta(matriz)) {
            System.out.println("Fuertemente conexo");
        }else{
            warshall(matrizNoDirigida);
            if(matrizCompleta(matrizNoDirigida)) {
                System.out.println("Debilmente conexo");
            }else {
                System.out.println("No conexo");
            }
        }
    }
}


public class Warshall {

    public static void main(String[] args) {
        Grafo g = new Grafo(7);
        g.aniadirArista(1, 2);
        g.aniadirArista(1, 4);
        g.aniadirArista(2, 4);
        g.aniadirArista(2, 5);
        g.aniadirArista(3, 1);
        g.aniadirArista(3, 6);
        g.aniadirArista(4, 3);
        g.aniadirArista(4, 5);
        g.aniadirArista(4, 6);
        g.aniadirArista(4, 7);
        g.aniadirArista(5, 7);
        g.aniadirArista(7, 6);
        g.conexidad();
    }
}