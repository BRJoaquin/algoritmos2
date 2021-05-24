import java.util.*; 

class Cambio_desordenado { 

    static public int monedaNoUsadaDeMayorValor(int[] monedas, boolean[] usadas) {
        int mayorValor = Integer.MIN_VALUE;
        int mayorIndex = -1;
        for(int i = 0; i < monedas.length; i++) {
            if(mayorValor < monedas[i] && !usadas[i]) {
                mayorIndex = i;
                mayorValor = monedas[i];
            }
        }
        return mayorIndex;
    }

    // pre: las monedas estan ordenadas de forma creciente
    public static int[] problemaDelCambio(int[] monedas,int cambio) {
        int cantidadDeTiposDeMoneda = monedas.length;
        int[] cambioADevolver = new int[cantidadDeTiposDeMoneda];
        boolean[] usadas = new boolean[cantidadDeTiposDeMoneda];
        for(int i = 0; i < usadas.length; i++) {
            usadas[i] = false;
        }

        int monedaUsandoIndex = monedaNoUsadaDeMayorValor(monedas, usadas);

        while(monedaUsandoIndex >= 0 && cambio>0) {
            usadas[monedaUsandoIndex] = true;
            int monedaUsandoValor = monedas[monedaUsandoIndex];
            if(cambio >= monedaUsandoValor) {
                cambioADevolver[monedaUsandoIndex]++;
                cambio-=monedaUsandoValor;
            }else{
                monedaUsandoIndex = monedaNoUsadaDeMayorValor(monedas, usadas);
            }
        }
        if(cambio>0) {
            throw new Error("No existe cambio posible");
        }
        return cambioADevolver;
    }
  
    public static void main(String[] args) 
    { 
        int[] monedas = {10, 50, 5, 1, 2};
        Scanner in = new Scanner(System.in);
        int cambio = in.nextInt();

        int[] cantMonedasDevolver = problemaDelCambio(monedas, cambio);

        int cantidadDeMonedasUsadas = 0;
        for(int i=0; i< monedas.length; i++) {
            cantidadDeMonedasUsadas+= cantMonedasDevolver[i];
            System.out.println("Se usaron " + cantMonedasDevolver[i] + " de valor " + monedas[i]);
        }
        System.out.println("\nTotal de monedas usadas: " + cantidadDeMonedasUsadas);
    } 
}
