import java.util.Scanner;

public class MergeSort {

  static int[] intercalar(int[] izq, int[] der) {
    int[] ret = new int[izq.length + der.length];
    int indexIzq = 0;
    int indexDer = 0;
    int i = 0;
    while (indexIzq < izq.length && indexDer < der.length) {
      if (izq[indexIzq] < der[indexDer]) {
        ret[i++] = izq[indexIzq++];
      } else {
        ret[i++] = der[indexDer++];
      }
    }
    while (indexIzq < izq.length) {
      ret[i++] = izq[indexIzq++];
    }
    while (indexDer < der.length) {
      ret[i++] = der[indexDer++];
    }
    return ret;
  }

  static int[] mergeSort(int[] valores, int inicio, int fin) {
    if (inicio == fin) {
      int[] ret = new int[1];
      ret[0] = valores[inicio];
      return ret;
    }

    int mitad = inicio + (fin - inicio) / 2;

    int[] izq = mergeSort(valores, inicio, mitad);
    int[] der = mergeSort(valores, mitad + 1, fin);

    return intercalar(izq, der);
  }

  public static void main(String[] args) {
    int[] prueba = { 2, 45, 34, 8, 67, 41, 32, 54, 234, 444 };
    int[] ordenado = mergeSort(prueba, 0, prueba.length - 1);
    for (int i = 0; i < ordenado.length; i++) {
      System.out.println(ordenado[i]);
    }
  }
}
