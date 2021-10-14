import java.util.Scanner;

public class BusquedaPorBiparticion {

    // busqueda por biparticion
    static int DAC(int[] arr, int buscado, int inicio, int fin) {
        if(inicio == fin) {
            return arr[fin] == buscado ? fin : -1;
        }

        int mitad =  (inicio + fin) / 2;

        if(arr[mitad] == buscado) {
            return mitad;
        }
        if(arr[mitad] > buscado) {
            return DAC(arr, buscado, inicio, mitad);
        }
        return DAC(arr, buscado, mitad + 1, fin);
    }

    public static void main(String[] args) {
        int[] prueba = { 2, 4, 6, 8, 10, 13, 15, 22, 100, 102, 1000, 2000, 3500 };
        int pos = DAC(prueba, 15, 0, prueba.length -1);
        if(pos >= 0) {
            System.out.println("El elemento esta en la pos " + pos);
        }else {
            System.out.println("No esta el elemento");
        }
    }
}