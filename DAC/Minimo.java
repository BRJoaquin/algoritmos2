import java.util.Scanner;

public class Minimo {

  static int[] copiarArr(int[] original, int desde, int hasta) {
    int[] ret = new int[hasta - desde];
    int index = 0;
    for (int i = desde; i < hasta; i++) {
      ret[index++] = original[i];
    }
    return ret;
  }

  static int minimo(int[] valores) {
    int largoArr = valores.length;
    if (largoArr == 1) {
      return valores[0];
    }

    int mitad = largoArr / 2;

    int[] valoresIzq = copiarArr(valores, 0, mitad);
    int[] valoresDer = copiarArr(valores, mitad, largoArr);

    int min1 = minimo(valoresIzq);
    int min2 = minimo(valoresDer);

    return min1 < min2 ? min1 : min2;
  }

  static int minimoV2(int[] valores, int inicio, int fin) {
    if (inicio == fin) {
      return valores[inicio];
    }

    int mitad = inicio + (fin - inicio) / 2;

    int min1 = minimoV2(valores, inicio, mitad);
    int min2 = minimoV2(valores, mitad + 1, fin);

    return min1 < min2 ? min1 : min2;
  }

  public static void main(String[] args) {
    int[] prueba = { 2, 3, 5, 8, 12, 23, 89, 15, 10 };

    System.out.println("V1:");
    System.out.println(minimo(prueba));
    System.out.println("V2:");
    System.out.println(minimoV2(prueba, 0, prueba.length - 1));
  }
}
