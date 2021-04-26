import java.util.Scanner;

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

    public void aniadirArista(int origen, int destino, int peso) {
        grafo[origen][destino] = peso;
    }

    private void icRec(int origen, int destino, int[] vengo) {
        if(origen == destino) {
            System.out.print(origen + "->");
        }else {
            icRec(origen, vengo[destino], vengo);
            System.out.print(destino + "->");
        }
    }

    private void imprimirCamino(int origen, int destino, int[] costos, int[] vengo) {
        if(costos[destino] == INF) {
            System.out.println("No existe camino desde " + origen + " a " + destino);
        }else {
            System.out.println("El camino + corto desde " + origen + " a " + destino + " tiene peso " + costos[destino]);
            icRec(origen, destino, vengo);
            System.out.println("");
            System.out.println("");
        }
    }

   private int[][] generarMatrizAdy() {
        int[][] ret = new int[V+1][V+1];
        for(int i=1; i<=V; i++) {
            for(int j=1; j<=V; j++) {
                // retiro las aristas a uno mismo
                ret[i][j] = i==j ? INF : grafo[i][j];
            }
        }
        return ret;
    }

    private int[][] initMatrizVengo() {
        int[][] ret = new int[V+1][V+1];
        for(int i=1; i<=V; i++) {
            for(int j=1; j<=V; j++) {
                ret[i][j] = grafo[i][j] != INF ? i : -1;
            }
        }
        return ret;
    }

    public void floyd() {
        int[][] matriz = generarMatrizAdy();
        int[][] vengo =  initMatrizVengo();

        for(int k=1; k<=V; k++) {
            for(int i=1; i<=V; i++) {
                for(int j=1; j<=V; j++) {
                    if(matriz[i][k]!=INF && matriz[k][j]!= INF && matriz[i][j] > matriz[i][k] + matriz[k][j]) {
                        matriz[i][j] = matriz[i][k] + matriz[k][j];
                        vengo[i][j] = k;
                    }
                }
            }
        }

        for(int i=1; i<=V; i++) {
            System.out.println("Desde origen " + i + "\n");
            for(int j=1; j<=V; j++) {
                if(i != j) {
                    imprimirCamino(i, j, matriz[i], vengo[i]);
                }
            }
            System.out.println("+_+_+_+_+_+_+_+_+_+_+_+_+_\n");
        }
    }
}

public class Floyd {
    public static void main(String[] args) {
        Grafo g= new Grafo(7);
        g.aniadirArista(1, 2, 2);
        g.aniadirArista(1, 4, 1);
        g.aniadirArista(2, 4, 3);
        g.aniadirArista(2, 5, 10);
        g.aniadirArista(3, 1, 4);
        g.aniadirArista(3, 6, 5);
        g.aniadirArista(4, 3, 2);
        g.aniadirArista(4, 5, 2);
        g.aniadirArista(4, 6, 8);
        g.aniadirArista(4, 7, 4);
        g.aniadirArista(5, 7, 6);
        g.aniadirArista(7, 6, 1);
        g.floyd();
    }
}