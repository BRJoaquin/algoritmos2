#include <cassert>
#include <string>
#include <iostream>
#include <climits>
using namespace std;

int min(int a, int b)
{
    return a < b ? a : b;
}

// ASUME que se pueden dar todos los cambios (por la moneda de 1)
int problemaDelCambio(int resto)
{
    int *res = new int[resto + 1];
    int monedas[] = {1, 2, 5, 10, 50};
    res[0] = 0;
    for (int i = 1; i <= resto; i++)
    {
        int menor;
        menor = res[i - 1]; // uso la moneda de 1
        if (i >= 2)
        {
            menor = min(menor, res[i - 2]); // trato de usar la moneda de 2
        }
        if (i >= 5)
        {
            menor = min(menor, res[i - 5]); // trato de usar la moneda de 5
        }
        if (i >= 10)
        {
            menor = min(menor, res[i - 10]); // trato de usar la moneda de 10
        }
        if (i >= 50)
        {
            menor = min(menor, res[i - 50]); // trato de usar la moneda de 50
        }
        res[i] = 1 + menor;
    }
    return res[resto];
}

// Puede decirnos si no es posible el cambio
int problemaDelCambioV2(int resto)
{
    int *res = new int[resto + 1];
    int monedas[] = {1, 2, 5, 10, 50};
    int cantMonedas = 5;
    res[0] = 0;
    for (int i = 1; i < resto + 1; i++)
    {
        int menor = INT_MAX;
        for (int j = 0; j < cantMonedas; j++)
        {
            if (i >= monedas[j])
            {
                menor = min(menor, res[i - monedas[j]]);
            }
        }
        if (menor != INT_MAX)
        {
            res[i] = 1 + menor;
        }
        else
        {
            res[i] = INT_MAX;
        }
    }
    return res[resto];
}

void problemaDelCambioCamino(int resto)
{
    int *res = new int[resto + 1];
    int *use = new int[resto + 1];
    int monedas[] = {1, 2, 5, 10, 50};
    int cantMonedas = 5;
    res[0] = 0;
    for (int i = 1; i < resto + 1; i++)
    {
        int menor = INT_MAX;
        for (int j = 0; j < cantMonedas; j++)
        {
            if (i >= monedas[j])
            {
                if (res[i - monedas[j]] < menor)
                {
                    menor = res[i - monedas[j]];
                    use[i] = monedas[j];
                }
            }
        }
        if (menor != INT_MAX)
        {
            res[i] = 1 + menor;
        }
        else
        {
            res[i] = INT_MAX;
        }
    }
    cout << "Cantidad de monedas " << res[resto] << endl;
    int aux = resto;

    cout << "Use: ";
    while (aux != 0)
    {
        cout << use[aux] << " ";
        aux -= use[aux];
    }
    cout << endl;
}

// Con una matriz
int problemaDelCambioV3(int resto)
{
    int INF = INT_MAX;
    int monedas[] = {1, 2, 5, 10, 50};
    int cantMonedas = 5;
    int **m = new int *[cantMonedas];
    for (int i = 0; i < cantMonedas; i++)
    {
        m[i] = new int[resto + 1]();
    }

    // procesamos la primera moneda
    for (int restoIndex = 1; restoIndex < resto + 1; restoIndex++)
    {

        if (restoIndex < monedas[0] || m[0][restoIndex - monedas[0]] == INF)
        {
            m[0][restoIndex] = INF;
        }
        else
        {
            m[0][restoIndex] = 1 + m[0][restoIndex - monedas[0]];
        }
    }

    // empezamos por la segunda moneda
    for (int monedaIndex = 1; monedaIndex < cantMonedas; monedaIndex++)
    {
        for (int restoIndex = 0; restoIndex < resto + 1; restoIndex++)
        {
            if (restoIndex < monedas[monedaIndex] || m[monedaIndex][restoIndex - monedas[i]] == INF)
            {
                m[monedaIndex][restoIndex] = m[monedaIndex - 1][restoIndex];
            }
            else
            {
                m[monedaIndex][restoIndex] = min(m[monedaIndex - 1][restoIndex], 1 + m[monedaIndex][restoIndex - monedas[monedaIndex]]);
            }
        }
    }

    return m[cantMonedas - 1][resto];
}

int main()
{
    int cambio;
    cin >> cambio;
    // cout << problemaDelCambio(cambio) << endl;
    // cout << problemaDelCambioV2(cambio) << endl;
    // problemaDelCambioCamino(cambio);
    // cout << problemaDelCambioV3(cambio) << endl;
    return 0;
}