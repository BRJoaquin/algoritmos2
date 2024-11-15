#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../../ADTs/List.h"
#include "../../ADTs/ListImp.cpp"

using namespace std;

int N = 8;

bool esSolucion(int fAc, int cAc, int fD, int cD)
{
    return fAc == fD && cAc == cD;
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

bool puedoAplicarMovimiento(int **camino, int fila, int col)
{
    return cooEsValida(fila, col) && !pase(camino, fila, col);
}

void aplicarMovimiento(int **camino, int fila, int col, int paso)
{
    camino[fila][col] = paso;
}

void deshacerMovimiento(int **camino, int fila, int col, int paso)
{
    camino[fila][col] = 0;
}

void caballoDec(int **camino, int paso, int fAc, int cAc, int fD, int cD, bool &exito)
{
    if (!exito)
    {
        if (esSolucion(fAc, cAc, fD, cD))
        {
            exito = true;
            imprimirSolucion(camino);
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
                if (puedoAplicarMovimiento(camino, fCan, cCan))
                {
                    aplicarMovimiento(camino, fCan, cCan, paso);
                    caballoDec(camino, paso + 1, fCan, cCan, fD, cD, exito);
                    deshacerMovimiento(camino, fCan, cCan, paso);
                }
            }
        }
    }
}

void caballoEnum(int **camino, int paso, int fAc, int cAc, int fD, int cD)
{

    if (esSolucion(fAc, cAc, fD, cD))
    {
        imprimirSolucion(camino);
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
            if (puedoAplicarMovimiento(camino, fCan, cCan))
            {
                aplicarMovimiento(camino, fCan, cCan, paso);
                caballoEnum(camino, paso + 1, fCan, cCan, fD, cD);
                deshacerMovimiento(camino, fCan, cCan, paso);
            }
        }
    }
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

void caballoOpt(int **camino, int paso, int fAc, int cAc, int fD, int cD, int &mejoresPasos, int **&mejorCamino)
{
    if (!hayQuePodar(paso, mejoresPasos))
    {
        if (esSolucion(fAc, cAc, fD, cD) && esMejorSolucion(paso, mejoresPasos))
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
                if (puedoAplicarMovimiento(camino, fCan, cCan))
                {
                    aplicarMovimiento(camino, fCan, cCan, paso);
                    caballoOpt(camino, paso + 1, fCan, cCan, fD, cD, mejoresPasos, mejorCamino);
                    deshacerMovimiento(camino, fCan, cCan, paso);
                }
            }
        }
    }
}

bool esMejorIgualSolucion(int actual, int mejor)
{
    return actual <= mejor;
}

void caballoOptEnum(int **camino, int paso, int fAc, int cAc, int fD, int cD, int &mejoresPasos, List<int **> *mejoresCaminos)
{
    if (!hayQuePodar(paso, mejoresPasos))
    {
        if (esSolucion(fAc, cAc, fD, cD) && esMejorIgualSolucion(paso, mejoresPasos))
        {
            if (esMejorSolucion(paso, mejoresPasos))
            {
                mejoresCaminos->empty();
                mejoresPasos = paso;
            }
            int **caminoClone;
            clonarSolucion(camino, caminoClone);
            mejoresCaminos->insert(caminoClone);
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
                if (puedoAplicarMovimiento(camino, fCan, cCan))
                {
                    aplicarMovimiento(camino, fCan, cCan, paso);
                    caballoOptEnum(camino, paso + 1, fCan, cCan, fD, cD, mejoresPasos, mejoresCaminos);
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
    for (int i = 0; i < N; i++)
    {
        camino[i] = new int[N]();
    }
    camino[fI][cI] = 1;

    // Decisión
    // bool exito = false;
    // caballoDec(camino, 2, fI, cI, fD, cD, exito);

    // Enumeración
    // caballoEnum(camino, 2, fI, cI, fD, cD);

    // Optimación
    // int mejoresPasos =  INT_MAX;
    // int **mejorCamino = NULL;
    // caballoOpt(camino, 2, fI, cI, fD, cD, mejoresPasos, mejorCamino);
    // imprimirSolucion(mejorCamino);

    // Optimación Enumeración
    int mejoresPasos = INT_MAX;
    List<int **> *mejoresSoluciones = new ListImp<int **>();
    caballoOptEnum(camino, 2, fI, cI, fD, cD, mejoresPasos, mejoresSoluciones);
    Iterator<int **> *it = mejoresSoluciones->getIterator();
    while (it->hasNext())
    {
        int **solAux = it->next();
        imprimirSolucion(solAux);
    }
    cout << "Encontramos " << mejoresSoluciones->getSize() << " soluciones " << endl;
}