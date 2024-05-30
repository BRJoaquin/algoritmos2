#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int FILAS = 300;
int COLUMNAS = 400;

int **initMatriz()
{
    int **tab = new int *[FILAS]();
    for (int f = 0; f < FILAS; f++)
    {
        tab[f] = new int[COLUMNAS]();
        for (int c = 0; c < COLUMNAS; c++)
        {
            tab[f][c] = -1;
        }
        
    }
    return tab;
}

bool **initMatrizCalculado()
{
    bool **calc = new bool *[FILAS]();
    for (int f = 0; f < FILAS; f++)
    {
        calc[f] = new bool[COLUMNAS]();
        for (int c = 0; c < COLUMNAS; c++)
        {
            calc[f][c] = false;
        }
        
    }
    return calc;
}

int cantCaminosTab()
{
    int **matriz = initMatriz();
    // casos base
    for (int c = 0; c < COLUMNAS; c++)
    {
        matriz[0][c] = 1;
    }
    for (int f = 0; f < FILAS; f++)
    {
        matriz[f][0] = 1;
    }
    // "paso recursivo"
    for (int f = 1; f < FILAS; f++)
    {
        for (int c = 1; c < COLUMNAS; c++)
        {
            matriz[f][c] = matriz[f - 1][c] + matriz[f][c - 1];
        }
    }
    return matriz[FILAS - 1][COLUMNAS - 1];
}

int cantCaminosRec(int f, int c)
{
    if (f == 0)
    {
        return 1;
    }
    if (c == 0)
    {
        return 1;
    }
    return cantCaminosRec(f - 1, c) + cantCaminosRec(f, c - 1);
}

int cantCaminosMemo(int f, int c, int ** memo, bool** calculado)
{
    if (f == 0)
    {
        return 1;
    }
    if (c == 0)
    {
        return 1;
    }
    if(calculado[f][c]) { 
        return memo[f][c];
    }
    memo[f][c] = cantCaminosMemo(f - 1, c, memo, calculado) + cantCaminosMemo(f, c - 1, memo, calculado);
    calculado[f][c] = true;
    return memo[f][c];
}

int main()
{

    // cout << cantCaminosRec(FILAS - 1, COLUMNAS - 1) << endl;
    cout << cantCaminosTab() << endl;
    int** memo  = initMatriz();
    bool** calculado  = initMatrizCalculado();
    cout << cantCaminosMemo(FILAS - 1, COLUMNAS - 1, memo, calculado) << endl;
}