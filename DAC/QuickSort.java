import java.util.Scanner;

public class QuickSort {

  static void intercambiar(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  static int partition(int[] arr, int inicio, int fin) {
    int pivote = arr[fin]; // se usa el final pero en realidad puede ser cualquiera
    int i = inicio;

    // para cada elemento se compara con el pivote, de ser menor lo mueve hacia la
    // "izquierda"
    for (int j = inicio; j <= fin - 1; j++) {
      if (arr[j] < pivote) {
        intercambiar(arr, i, j);
        i++;
      }
    }
    intercambiar(arr, i, fin); // dejamos el pivote en su lugar
    return i;
  }

  static void quickSort(int[] arr, int inicio, int fin) {
    if (inicio < fin) {
      int pi = partition(arr, inicio, fin); //

      quickSort(arr, inicio, pi - 1);
      quickSort(arr, pi + 1, fin);
    }
  }

  public static void main(String[] args) {
    int[] prueba = { 2, 45, 34, 8, 67, 41, 32, 54, 234, 444, 25 };
    quickSort(prueba, 0, prueba.length - 1);
    for (int i = 0; i < prueba.length; i++) {
      System.out.println(prueba[i]);
    }
  }
}