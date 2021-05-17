import java.util.*; 

class MaxSec { 
  
    static int maxCrossingSum(int arr[], int inicio, int medio, int fin) 
    { 
        int sum = 0; 
        int sumatoriaIzq = Integer.MIN_VALUE; 
        // sumamos desde el medio hacia la izquierda <-
        for (int i = medio; i >= inicio; i--) 
        { 
            sum = sum + arr[i]; 
            if (sum > sumatoriaIzq)
                sumatoriaIzq = sum;
        } 
  
        // sumamos desde la derecha (no incluimos al medio)
        sum = 0; 
        int sumatoriaDer = Integer.MIN_VALUE; 
        for (int i = medio + 1; i <= fin; i++) 
        { 
            sum = sum + arr[i]; 
            if (sum > sumatoriaDer)
                sumatoriaDer = sum;
        } 
  
        // elegimos entre usar solo mid->izq, solo mid->derecha (no incluye mid), o incluyendo el medio (izq<-mid->der)
        // casos
        // -10 9 4 2 -23 3 85  -> usamos solo mid->izq (9<-4<-2)
        // -10 1 1 -5 6 3 -8  -> usamos solo mid->der (6->3)
        // -10 1 4 2 6 3 4  -> usamos incluido medio (1<-4<-2->6->3->4)
        return Math.max(sumatoriaIzq + sumatoriaDer, Math.max(sumatoriaIzq, sumatoriaDer)); 
    } 
  
    static int maxSubArraySum(int arr[], int inicio, int fin) 
    { 
        if (inicio == fin) 
            return arr[inicio]; 
    
        int medio = (inicio + fin)/2; 

        return Math.max(Math.max(maxSubArraySum(arr, inicio, medio), 
                        maxSubArraySum(arr, medio+1, fin)), 
                        maxCrossingSum(arr, inicio, medio, fin)); 
    } 
  
    public static void main(String[] args) 
    { 
        int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6}; 
        int n = arr.length; 
        int max_sum = maxSubArraySum(arr, 0, n-1); 
        
        System.out.println("La sumatoria maxima de un subarray es " + max_sum); 
    } 
}
// Fuente: https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/