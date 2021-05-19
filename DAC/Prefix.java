import java.util.Scanner;

public class Prefix {

  static String prefixStr(String str1, String str2) {
    String ret = "";
    int l1 = str1.length();
    int l2 = str2.length();
    for (int i = 0; i < l1 && i < l2; i++) {
      if (str1.charAt(i) == str2.charAt(i)) {
        ret += str1.charAt(i);
      }
    }
    return ret;
  }

  static String prefix(String[] valores, int inicio, int fin) {
    if (inicio == fin) {
      return valores[inicio];
    }

    int mitad = inicio + (fin - inicio) / 2;

    String prefix1 = prefix(valores, inicio, mitad);
    String prefix2 = prefix(valores, mitad + 1, fin);

    return prefixStr(prefix1, prefix2);
  }

  public static void main(String[] args) {
    String[] prueba = { "ABC", "AB", "ABB", "ABE" };
    String prefixComun = prefix(prueba, 0, prueba.length - 1);
    System.out.println(prefixComun);
  }
}
