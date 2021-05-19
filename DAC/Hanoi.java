class Hanoi {

  static void hanoi(int n, char origen, char destino, char intermediario) {
    if (n == 1) {
      System.out.println("Muevo el disco 1 desde " + origen + " a " + destino);
      return;
    }
    hanoi(n - 1, origen, intermediario, destino);
    System.out.println(
      "Muevo el disco " + n + " desde " + origen + " hacia " + destino
    );
    hanoi(n - 1, intermediario, destino, origen);
  }

  public static void main(String args[]) {
    int n = 5; // numero de discos
    hanoi(n, 'A', 'C', 'B');
  }
}
