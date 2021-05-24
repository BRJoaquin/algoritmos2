#include <iostream>
#include <limits.h>
#include <cassert>
using namespace std;

enum enfoque
{
    mayorValorPrimero,
    menorPesoPrimero,
    mejorRatioPrimero
};

int seleccionarProximoCandidato(int *valores, int *pesos, bool *procesados, enfoque e, int n)
{
    int mejorIndice = -1;
    float mejorValor = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        float valorActual;
        if (e == mayorValorPrimero)
        {
            valorActual = valores[i];
        }
        else if (e == menorPesoPrimero)
        {
            valorActual = (float)1 / pesos[i];
        }
        else if (e == mejorRatioPrimero)
        {
            valorActual = (float)valores[i] / pesos[i];
        }

        if (!procesados[i] && mejorValor < valorActual)
        {
            mejorIndice = i;
            mejorValor = valorActual;
        }
    }

    return mejorIndice;
}

int mochila01(int *valores, int *pesos, int capacidad, enfoque e, int n)
{
    bool *procesados = new bool[n]();
    int valor = 0;
    for (int i = 0; i < n; i++)
    {
        int candidatoIndex = seleccionarProximoCandidato(valores, pesos, procesados, e, n);
        procesados[candidatoIndex] = true;
        if (capacidad >= pesos[candidatoIndex])
        {
            valor += valores[candidatoIndex];
            capacidad -= pesos[candidatoIndex];
        }
    }
    return valor;
}

int main()
{

    int valores[] = {10, 20, 25, 8};
    int pesos[] = {5, 3, 8, 4};
    int capacidad = 13;
    int n = 4;

    cout << "Valor de la mochila bajo enfoque 1 (mayor valor primero): " << mochila01(valores, pesos, capacidad, mayorValorPrimero, n) << endl;
    cout << "Valor de la mochila bajo enfoque 2 (menor peso primero): " << mochila01(valores, pesos, capacidad, menorPesoPrimero, n) << endl;
    cout << "Valor de la mochila bajo enfoque 3 (mejor ratio primero): " << mochila01(valores, pesos, capacidad, mejorRatioPrimero, n) << endl;
    
    
    // int valores[] = {
    //     360, 83, 59, 130, 431, 67, 230, 52, 93, 125, 670, 892, 600,
    //     38, 48, 147, 78, 256, 63, 17, 120, 164, 432, 35, 92, 110,
    //     22, 42, 50, 323, 514, 28, 87, 73, 78, 15, 26, 78, 210,
    //     36, 85, 189, 274, 43, 33, 10, 19, 389, 276, 312};
    // int pesos[] = {7, 0, 30, 22, 80, 94, 11, 81, 70, 64, 59, 18, 0, 36, 3, 8, 15,
    //                42, 9, 0, 42, 47, 52, 32, 26, 48, 55, 6, 29, 84, 2, 4, 18, 56,
    //                7, 29, 93, 44, 71, 3, 86, 66, 31, 65, 0, 79, 20, 65, 52, 13};
    // int capacidad = 850;
    // int n = 50;

    // cout << "Valor de la mochila bajo enfoque 1 (mayor valor primero): " << mochila01(valores, pesos, capacidad, mayorValorPrimero, n) << endl;
    // cout << "Valor de la mochila bajo enfoque 2 (menor peso primero): " << mochila01(valores, pesos, capacidad, menorPesoPrimero, n) << endl;
    // cout << "Valor de la mochila bajo enfoque 3 (mejor ratio primero): " << mochila01(valores, pesos, capacidad, mejorRatioPrimero, n) << endl;

    return 0;
}