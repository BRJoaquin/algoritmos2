#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int N = 8;

bool esSolucion(int colActual)
{
    return colActual == N;
}

void imprimirSolucion(bool **tablero)
{

    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < N; j++)
        {
            cout << "|";
            if (tablero[i][j])
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl
         << endl;
}

void aplicarMovimiento(bool **tablero, int col, int fila)
{
    tablero[fila][col] = true;
}

void deshacerMovimiento(bool **tablero, int col, int fila)
{
    tablero[fila][col] = false;
}

bool cooEsValida(int col, int fila)
{
    return col >= 0 && col < N && fila >= 0 && fila < N;
}

bool puedoAplicarMovimiento(bool **tablero, int col, int fila)
{

    // chequeo la fila
    for (int f = fila, c = col; cooEsValida(c, f); c--)
    {
        if (tablero[f][c])
        {
            return false;
        }
    }

    // chequeo la diagonal hacia arriba
    for (int f = fila, c = col; cooEsValida(c, f); c--, f--)
    {
        if (tablero[f][c])
        {
            return false;
        }
    }

    // chequeo la diagonal hacia arriba
    for (int f = fila, c = col; cooEsValida(c, f); c--, f++)
    {
        if (tablero[f][c])
        {
            return false;
        }
    }

    return true;
}

void nreinasEnum(bool **tablero, int colActual, int &cantSoluciones)
{
    if (esSolucion(colActual))
    {
        cantSoluciones++;
        imprimirSolucion(tablero);
    }
    else
    {
        // para cada movimiento posible
        for (int filaCand = 0; filaCand < N; filaCand++)
        {
            if (puedoAplicarMovimiento(tablero, colActual, filaCand))
            {
                aplicarMovimiento(tablero, colActual, filaCand);
                nreinasEnum(tablero, colActual + 1, cantSoluciones);
                deshacerMovimiento(tablero, colActual, filaCand);
            }
        }
    }
}

void nreinasDec(bool **tablero, int colActual, bool &exito)
{
    if (!exito)
    {
        if (esSolucion(colActual))
        {
            exito = true;
            imprimirSolucion(tablero);
        }
        else
        {
            // para cada movimiento posible
            for (int filaCand = 0; filaCand < N; filaCand++)
            {
                if (puedoAplicarMovimiento(tablero, colActual, filaCand))
                {
                    aplicarMovimiento(tablero, colActual, filaCand);
                    nreinasDec(tablero, colActual + 1, exito);
                    deshacerMovimiento(tablero, colActual, filaCand);
                }
            }
        }
    }
}

int main()
{
    bool **tablero = new bool *[N]();
    for (int i = 0; i < N; i++)
    {
        tablero[i] = new bool[N]();
    }
    // int cantSoluciones = 0;
    // nreinasEnum(tablero, 0, cantSoluciones);
    // cout << "Encontró " << cantSoluciones << " soluciones" << endl;
    bool exito = false;
    nreinasDec(tablero, 0, exito);
}