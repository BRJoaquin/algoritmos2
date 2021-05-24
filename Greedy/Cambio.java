import java.util.*; 

class Cambio { 

    // pre: las monedas estan ordenadas de forma creciente
    public static int[] problemaDelCambio(int[] monedas,int cambio) {
        int cantidadDeTiposDeMoneda = monedas.length;
        int[] cambioADevolver = new int[cantidadDeTiposDeMoneda];
        int monedaUsandoIndex = cantidadDeTiposDeMoneda - 1;

        while(monedaUsandoIndex >= 0 && cambio>0) {
            int monedaUsandoValor = monedas[monedaUsandoIndex];
            if(cambio >= monedaUsandoValor) {
                cambioADevolver[monedaUsandoIndex]++;
                cambio-=monedaUsandoValor;
            }else{
                monedaUsandoIndex--;
            }
        }
        if(cambio>0) {
            throw new Error("No existe cambio posible");
        }
        return cambioADevolver;
    }
  
    public static void main(String[] args) 
    { 
        int[] monedas = {1, 2, 5, 10, 50};
        // int[] monedas = {1, 2, 5, 10, 12, 50}; <- no funciona para cambio de 15
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
