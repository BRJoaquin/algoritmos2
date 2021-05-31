#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int calcularDigitos(int n)
{
    int ret = 1;
    int div = 10;
    while (n % div != n)
    {
        div *= 10;
        ret++;
    }
    return ret;
}

void colocarTentativamenteElNumero(int numeros[], int objeto, int &cifrasSignificativas, long &solucionActual)
{
    int d = calcularDigitos(numeros[objeto]);
    cifrasSignificativas -= d;
    solucionActual += numeros[objeto] * pow(10, cifrasSignificativas);
}
void retirarElNumero(int numeros[], int objeto, int &cifrasSignificativas, long &solucionActual)
{
    int d = calcularDigitos(numeros[objeto]);
    solucionActual -= numeros[objeto] * pow(10, cifrasSignificativas);
    cifrasSignificativas += d;
}

bool esMejorSolucion(long solucionActual, long mejorSolucion)
{
    return solucionActual > mejorSolucion;
}

long todosNueve(int cifrasSignificativas)
{
    long aux = 0;
    for (int i = 1; i <= cifrasSignificativas; i++)
    {
        aux += 9 * pow(10, i);
    }
    return aux;
}
bool puedeMejorar(long solucionActual, long mejorSolucion, int cifrasSignificativas)
{
    long aux = solucionActual + todosNueve(cifrasSignificativas);
    return aux > mejorSolucion;
}

void mejorSuma(int numeros[], int cifrasSignificativas, int N, bool usados[], long solucionActual, long &mejorSolucion)
{
    for (int i = 0; i < N; i++)
    {
        if (!usados[i])
        {
            colocarTentativamenteElNumero(numeros, i, cifrasSignificativas, solucionActual);
            usados[i] = true;
            if (esMejorSolucion(solucionActual, mejorSolucion))
            {
                mejorSolucion = solucionActual;
            }
            if (cifrasSignificativas > 0 && puedeMejorar(solucionActual, mejorSolucion, cifrasSignificativas))
            {
                mejorSuma(numeros, cifrasSignificativas, N, usados, solucionActual, mejorSolucion);
            }
            retirarElNumero(numeros, i, cifrasSignificativas, solucionActual);
            usados[i] = false;
        }
    }
}

int main()
{
    long solucion = 0;
    int valorMaximo = 0;
    int N = 8;
    bool usuados[N];
    int numeros[N] = {909, 11, 221, 9, 95, 4, 12, 1};
    int digitos = 0;
    for (int i = 0; i < N; i++)
    {
        digitos += calcularDigitos(numeros[i]);
        usuados[i] = false;
    }
    mejorSuma(numeros, digitos, N, usuados, 0, solucion);
    // cout.precision(100);
    cout << solucion << endl;

    return 0;
}