import java.util.*;

class MaxSec {

    static int maxCrossingSum(int arr[], int inicio, int medio, int fin) {
        int sum = arr[medio];
        int maxSum = arr[medio];
        // sumamos desde el medio hacia la izquierda <-
        for (int i = medio-1; i >= inicio; i--) {
            sum = sum + arr[i];
            if (sum > maxSum)
                maxSum = sum;
        }

        // sumamos desde el medio hacia la derecha ->
        sum = maxSum;
        for (int i = medio + 1; i <= fin; i++) {
            sum = sum + arr[i];
            if (sum > maxSum)
                maxSum = sum;
        }

        return maxSum;
    }

    static int maxSubArraySum(int arr[], int inicio, int fin) {
        if (inicio == fin)
            return arr[inicio];

        int medio = (inicio + fin) / 2;

        return Math.max(Math.max(maxSubArraySum(arr, inicio, medio), maxSubArraySum(arr, medio + 1, fin)),
                maxCrossingSum(arr, inicio, medio, fin));
    }

    public static void main(String[] args) {
        int arr[] = { -2, -5, 4, -2, -3, 1, -5, -6 };
        int n = arr.length;
        int max_sum = maxSubArraySum(arr, 0, n - 1);

        System.out.println("La sumatoria maxima de un subarray es " + max_sum);
    }
}