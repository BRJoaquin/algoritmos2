#include <string>
#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

// 2 34 4 -8 3

int calcConMedio(int *arr, int i, int m, int f)
{
    int maxIzq = INT_MIN;
    int sumaIzq = 0;

    for (int index = m; index >= i; index--)
    {
        sumaIzq += arr[index];
        if (sumaIzq > maxIzq)
        {
            maxIzq = sumaIzq;
        }
    }

    int maxDer = 0;
    int sumaDer = 0;

    for (int index = m + 1; index <= f; index++)
    {
        sumaDer += arr[index];
        if (sumaDer > maxDer)
        {
            maxDer = sumaDer;
        }
    }

    return maxIzq + maxDer;
}

int max(int a, int b, int c)
{
    int maxab = a > b ? a : b;
    return maxab > c ? maxab : c;
}

int secuenciaMaxima(int *arr, int i, int f)
{
    if (i == f)
    {
        return arr[i];
    }

    int mitad = (i + f) / 2;

    int maxIzq = secuenciaMaxima(arr, i, mitad);
    int maxDer = secuenciaMaxima(arr, mitad + 1, f);

    int maxConMedio = calcConMedio(arr, i, mitad, f);

    return max(maxIzq, maxDer, maxConMedio);
}

int main()
{
    int sec[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << secuenciaMaxima(sec, 0, 8) << endl;
}