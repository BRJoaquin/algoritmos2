#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

bool sePuedePodar(int candidataMetrica, int mejorSolucionMetrica)
{
    return candidataMetrica >= mejorSolucionMetrica;
}

bool esSolucion(int resto)
{
    return resto == 0;
}

bool esMejorSolucion(int candidataMetrica, int mejorSolucionMetrica)
{
    return candidataMetrica < mejorSolucionMetrica;
}

void clonarSolucion(int *origen, int *destino, int N)
{
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}

bool puedoUsarNumero(int resto, int numero)
{
    return numero <= resto;
}

void usarNumero(int numero, int index, int &resto, int *candidata, int &candidataMetrica)
{
    resto -= numero;
    candidata[index]++;
    candidataMetrica++;
}

void desusarNumero(int numero, int index, int &resto, int *candidata, int &candidataMetrica)
{
    resto += numero;
    candidata[index]--;
    candidataMetrica--;
}

void sumatoria_bt(int resto, int *C, int N, int *candidata, int candidataMetrica, int *mejorSolucion, int &mejorSolucionMetrica)
{
    if (!sePuedePodar(candidataMetrica, mejorSolucionMetrica))
    {
        if (esSolucion(resto) && esMejorSolucion(candidataMetrica, mejorSolucionMetrica))
        {
            clonarSolucion(candidata, mejorSolucion, N);
            mejorSolucionMetrica = candidataMetrica;
        }
        else
        {
            for (int i = 0; i < N; i++)
            {
                int numero = C[i];
                if (puedoUsarNumero(resto, numero))
                {
                    usarNumero(numero, i, resto, candidata, candidataMetrica);
                    sumatoria_bt(resto, C, N, candidata, candidataMetrica, mejorSolucion, mejorSolucionMetrica);
                    desusarNumero(numero, i, resto, candidata, candidataMetrica);
                }
            }
        }
    }
}

void sumatoria(int *C, int N, int M)
{
    int *sandbox = new int[N + 1]();
    int *solucion = new int[N + 1]();
    int mejorSolucionMetrica = INT_MAX;
    sumatoria_bt(M, C, N, sandbox, 0, solucion, mejorSolucionMetrica);
    if (mejorSolucionMetrica < INT_MAX)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < solucion[i]; j++)
            {
                cout << C[i] << endl;
            }
        }
    }
    else
    {
        cout << "No existe" << endl;
    }
}

int main()
{
    int N = 6;
    int C[6] = {4, 34, 3, 12, 5, 2};
    int M = 9;

    sumatoria(C, N, M);

    return 0;
}