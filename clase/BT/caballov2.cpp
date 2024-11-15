#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../../ADTs/List.h"
#include "../../ADTs/ListImp.cpp"

using namespace std;

int N = 8;

bool pasePorDondeTeniaQuePasar(int **camino, bool **debemos) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(debemos[i][j] && camino[i][j] == 0) {
                return false;
            }
        }
    }
    return true;    
}

bool esSolucion(int fAc, int cAc, int fD, int cD,int **camino, bool **debemos)
{
    return fAc == fD && cAc == cD && pasePorDondeTeniaQuePasar(camino, debemos);
}

void imprimirSolucion(int **tablero)
{

    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < N; j++)
        {
            cout << "|";
            if (tablero[i][j] > 0 && tablero[i][j] < 10)
            {
                cout << " " << tablero[i][j];
            }
            else if (tablero[i][j] > 0)
            {
                cout << tablero[i][j];
            }
            else
            {
                cout << "  ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl
         << endl;
}

bool cooEsValida(int fila, int col)
{
    return col >= 0 && col < N && fila >= 0 && fila < N;
}

bool pase(int **camino, int fila, int col)
{
    return camino[fila][col] > 0;
}

bool puedoAplicarMovimiento(int **camino, int fila, int col, bool **prohibido)
{
    return cooEsValida(fila, col) && !pase(camino, fila, col) && !prohibido[fila][col];
}

void aplicarMovimiento(int **camino, int fila, int col, int paso)
{
    camino[fila][col] = paso;
}

void deshacerMovimiento(int **camino, int fila, int col, int paso)
{
    camino[fila][col] = 0;
}

bool esMejorSolucion(int actual, int mejor)
{
    return actual < mejor;
}

bool hayQuePodar(int actual, int mejor)
{
    return actual > mejor;
}

void clonarSolucion(int **origen, int **&destino)
{
    destino = new int *[N]();
    for (int i = 0; i < N; i++)
    {
        destino[i] = new int[N]();
        for (int j = 0; j < N; j++)
        {
            destino[i][j] = origen[i][j];
        }
    }
}

void caballoOpt(int **camino, int paso, int fAc, int cAc, int fD, int cD, bool **debemos, bool **prohibido, int &mejoresPasos, int **&mejorCamino)
{
    if (!hayQuePodar(paso, mejoresPasos))
    {
        if (esSolucion(fAc, cAc, fD, cD, camino, debemos) && esMejorSolucion(paso, mejoresPasos))
        {
            clonarSolucion(camino, mejorCamino);
            mejoresPasos = paso;
        }
        else
        {
            int dF[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
            int dC[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
            for (int i = 0; i < 8; i++) // movimientos posibles del caballo, son siempre 8 no importa el tamaño del tablero, presta atencion!
            {
                int fCan = fAc + dF[i];
                int cCan = cAc + dC[i];
                // movimientos posibles
                if (puedoAplicarMovimiento(camino, fCan, cCan, prohibido))
                {
                    aplicarMovimiento(camino, fCan, cCan, paso);
                    caballoOpt(camino, paso + 1, fCan, cCan, fD, cD, debemos, prohibido, mejoresPasos, mejorCamino);
                    deshacerMovimiento(camino, fCan, cCan, paso);
                }
            }
        }
    }
}

int main()
{
    int fI = 0;
    int cI = 0;
    int fD = 7;
    int cD = 7;

    int **camino = new int *[N]();
    bool **debemos = new bool *[N]();
    bool **prohibido = new bool *[N]();
    for (int i = 0; i < N; i++)
    {
        camino[i] = new int[N]();
        debemos[i] = new bool[N]();
        prohibido[i] = new bool[N]();
    }
    camino[fI][cI] = 1;
    debemos[3][5] = true;
    debemos[4][4] = true;
    debemos[4][5] = true;

    prohibido[1][4] = true;

    // Optimación
    int mejoresPasos = INT_MAX;
    int **mejorCamino = NULL;
    caballoOpt(camino, 2, fI, cI, fD, cD, debemos, prohibido, mejoresPasos, mejorCamino);
    imprimirSolucion(mejorCamino);
}