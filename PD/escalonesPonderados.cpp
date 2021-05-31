#include <cassert>
#include <string>
#include <iostream>
using namespace std;

/*
f(n) = p(n) + min(f(n-1),f(n-2))
*/
int min(int a, int b)
{
    return a < b ? a : b;
}

void escalerasPonderado(int n, int pesos[])
{
    int *res = new int[n + 1];
    res[0] = 0;
    res[1] = pesos[1];
    for (int i = 2; i <= n; i++)
    {
        res[i] = pesos[i] + min(res[i - 1], res[i - 2]);
    }
    cout << res[n] << endl;
}

void escalerasPonderadoCamino(int n, int pesos[])
{
    int *res = new int[n + 1];
    res[0] = 0;
    res[1] = pesos[1];
    for (int i = 2; i <= n; i++)
    {
        res[i] = pesos[i] + min(res[i - 1], res[i - 2]);
    }
    cout << res[n] << endl;

    int acumulado = res[n];
    int index = n;
    while (acumulado > 0)
    {
        cout << "vengo de " << index << endl;
        acumulado -= pesos[index];
        if (res[index - 1] == acumulado)
        {
            index -= 1;
        }
        else
        {
            index -= 2;
        }
    }
}

void escalerasPonderadoCaminoV2(int n, int pesos[])
{
    int *res = new int[n + 1];
    int *vengo = new int[n + 1];
    res[0] = 0;
    vengo[0] = 0;
    res[1] = pesos[1];
    vengo[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        int min;
        if (res[i - 1] < res[i - 2])
        {
            min = res[i - 1];
            vengo[i] = i - 1;
        }
        else
        {
            min = res[i - 2];
            vengo[i] = i - 2;
        }
        res[i] = pesos[i] + min;
    }
    cout << res[n] << endl;

    int index = vengo[n];
    cout << "vengo de " << n << endl;
    while (index > 0)
    {
        cout << "vengo de " << index << endl;
        index = vengo[index];
    }
}

int main()
{
    int n = 8;
    //              0  1  2  3  4  5  6  7  8
    int pesos[9] = {0, 3, 2, 4, 6, 1, 1, 5, 3};
    // escalerasPonderado(n, pesos);
    // escalerasPonderadoCamino(n, pesos);
    escalerasPonderadoCaminoV2(n, pesos);
    return 0;
}