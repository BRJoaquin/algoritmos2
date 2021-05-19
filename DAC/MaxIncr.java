// import java.util.*;

// class MaxIncr {

//     static int maxCrossingSum(int arr[], int inicio, int medio, int fin) {
//         boolean sigo = true;
//         int ultimo = arr[medio];
//         int maxIncr = 1;
//         for (int i = medio - 1; (i >= inicio) && sigo; i--) {
//             if (arr[i] < ultimo) {
//                 maxIncr++;
//                 ultimo = arr[i];
//             } else {
//                 sigo = false;
//             }
//         }

//         sigo = true;
//         ultimo = arr[medio];
//         for (int i = medio + 1; (i <= fin) && sigo; i++) {
//             if (arr[i] > ultimo) {
//                 maxIncr++;
//                 ultimo = arr[i];
//             } else {
//                 sigo = false;
//             }
//         }

//         return maxIncr;
//     }

//     static int maxSubArrayIncr(int arr[], int inicio, int fin) {
//         if (inicio == fin)
//             return 1;

//         int medio = (inicio + fin) / 2;

//         return Math.max(Math.max(maxSubArrayIncr(arr, inicio, medio), maxSubArrayIncr(arr, medio + 1, fin)),
//                 maxCrossingSum(arr, inicio, medio, fin));
//     }

//     public static void main(String[] args) {
//         int arr[] = { -2, -5, 4, 10, -3, 1, -5, -6 };
//         int n = arr.length;
//         int max_sum = maxSubArrayIncr(arr, 0, n - 1);

//         System.out.println(max_sum);
//     }
// }