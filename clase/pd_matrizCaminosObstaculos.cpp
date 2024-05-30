#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int FILAS = 3;
int COLUMNAS = 4;

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

bool **initMatrizObs()
{
    bool **obs = new bool *[FILAS]();
    for (int f = 0; f < FILAS; f++)
    {
        obs[f] = new bool[COLUMNAS]();
        for (int c = 0; c < COLUMNAS; c++)
        {
            obs[f][c] = false;
        }
        
    }
    return obs;
}


int cantCaminosTab(bool ** obstaculos)
{
    int **matriz = initMatriz();
    // casos base
    for (int c = 0; c < COLUMNAS; c++)
    {
        matriz[0][c] = obstaculos[0][c] ? 0 : 1;
    }
    for (int f = 0; f < FILAS; f++)
    {
        matriz[f][0] = obstaculos[f][0] ? 0 : 1;
    }
    // "paso recursivo"
    for (int f = 1; f < FILAS; f++)
    {
        for (int c = 1; c < COLUMNAS; c++)
        {
            matriz[f][c] = obstaculos[f][c] ? 0 : matriz[f - 1][c] + matriz[f][c - 1];
        }
    }
    return matriz[FILAS - 1][COLUMNAS - 1];
}

int main()
{
    bool ** obstaculos = initMatrizObs();
    obstaculos[1][2] = true;
    obstaculos[1][3] = true;
    cout << cantCaminosTab(obstaculos) << endl;
}