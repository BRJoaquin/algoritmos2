#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int N = 5;
int monedas[5] = {1, 2, 5, 10, 50};
// int monedas[5] = {50, 10, 5, 2, 1};
int cambioADevolver = 5000;

int cantMonedasUsadas(int *usadas)
{
    int cant = 0;
    for (int i = 0; i < N; i++)
    {
        cant += usadas[i];
    }
    return cant;
}

int cambioDevuelto(int *usadas)
{
    int devuelto = 0;
    for (int i = 0; i < N; i++)
    {
        devuelto += usadas[i] * monedas[i];
    }
    return devuelto;
}

bool puedoPodar(int *monedasUsadas, int mejorCantMonedas)
{
    return cantMonedasUsadas(monedasUsadas) > mejorCantMonedas;
}

bool esSolucion(int *monedasUsadas)
{
    return cambioDevuelto(monedasUsadas) == cambioADevolver;
}

bool esMejorSolucion(int *monedasUsadas, int mejorCantMonedas)
{
    return cantMonedasUsadas(monedasUsadas) < mejorCantMonedas;
}

void clonarSolucion(int *monedasUsadas, int *mejorMonedas)
{
    for (int i = 0; i < N; i++)
    {
        mejorMonedas[i] = monedasUsadas[i];
    }
}

bool puedoHacerMovimiento(int *monedasUsadas, int monedaActual)
{
    return cambioDevuelto(monedasUsadas) + monedas[monedaActual] <= cambioADevolver;
}

void hacerMovimiento(int *monedasUsadas, int monedaActual)
{
    monedasUsadas[monedaActual]++;
}

void deshacerMovimiento(int *monedasUsadas, int monedaActual)
{
    monedasUsadas[monedaActual]--;
}

void cambio(int monedaActual, int *monedasUsadas, int *mejorMonedas, int &mejorCantMonedas)
{
    if (!puedoPodar(monedasUsadas, mejorCantMonedas))
    {
        if (esSolucion(monedasUsadas))
        {
            if (esMejorSolucion(monedasUsadas, mejorCantMonedas))
            {
                clonarSolucion(monedasUsadas, mejorMonedas);
                mejorCantMonedas = cantMonedasUsadas(monedasUsadas);
            }
        }
        else if (monedaActual < N)
        {
            // pongo moneda
            if (puedoHacerMovimiento(monedasUsadas, monedaActual))
            {
                hacerMovimiento(monedasUsadas, monedaActual);
                cambio(monedaActual, monedasUsadas, mejorMonedas, mejorCantMonedas);
                deshacerMovimiento(monedasUsadas, monedaActual);
            }

            // no poner moneda
            cambio(monedaActual + 1, monedasUsadas, mejorMonedas, mejorCantMonedas);
        }
    }
}

int main()
{
    int *monedasSandbox = new int[N]();
    int *mejorMonedas = new int[N]();
    int mejorCantMonedas = INT_MAX;
    cambio(0, monedasSandbox, mejorMonedas, mejorCantMonedas);
    for (int i = 0; i < N; i++)
    {
        if(mejorMonedas[i] > 0) {
            cout << "Use " << mejorMonedas[i] << " monedas de " << monedas[i] << endl;
        }
    }
}