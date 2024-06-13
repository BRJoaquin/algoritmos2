#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

struct Posicion
{
    int fila;
    int columna;
};

void imprimirSolucion(int tablero[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (tablero[i][j] > 0)
            {
                cout << "[" << tablero[i][j] << "] ";
            }
            else
            {
                cout << "[ ] ";
            }
        }
        cout << endl;
    }
}

bool puedoAplicarMovimiento(Posicion celdaAIntentar, int nro, int tablero[9][9])
{
    // chequeo vertical
    for (int i = 0; i < 9; i++)
    {
        if (tablero[i][celdaAIntentar.columna] == nro)
            return false;
    }

    // chequeo horizontal
    for (int j = 0; j < 9; j++)
    {
        if (tablero[celdaAIntentar.fila][j] == nro)
            return false;
    }

    // chequeo cuadrante
    int cuandranteFilaInicio = (celdaAIntentar.fila / 3) * 3;
    int cuandranteColuInicio = (celdaAIntentar.columna / 3) * 3;

    for (int i = cuandranteFilaInicio; i < cuandranteFilaInicio + 3; i++)
    {
        for (int j = cuandranteColuInicio; j < cuandranteColuInicio + 3; j++)
        {
            if (tablero[i][j] == nro)
            {
                return false;
            }
        }
    }

    return true;
}

Posicion proximaCelda(int tablero[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (tablero[i][j] == 0)
            {
                Posicion toRet = {i, j};
                return toRet;
            }
        }
    }
    assert(false);
}

bool esSolucion(int celdasRestantes)
{
    return celdasRestantes == 0;
}

void aplicarMovimiento(Posicion celdaAIntentar, int num, int tablero[9][9])
{
    tablero[celdaAIntentar.fila][celdaAIntentar.columna] = num;
}

void deshacerMovimiento(Posicion celdaAIntentar, int tablero[9][9])
{
    tablero[celdaAIntentar.fila][celdaAIntentar.columna] = 0;
}

void sudoku(int celdasRestantes, int tablero[9][9], bool &exito)
{
    if (!exito)
    {
        if (esSolucion(celdasRestantes))
        {
            imprimirSolucion(tablero);
            exito = true;
        }
        else
        {
            Posicion celdaAIntentar = proximaCelda(tablero);
            // movimientos posibles
            for (int i = 1; i <= 9; i++)
            {
                // if puedo aplicar movimiento
                if (puedoAplicarMovimiento(celdaAIntentar, i, tablero))
                {
                    aplicarMovimiento(celdaAIntentar, i, tablero);
                    sudoku(celdasRestantes - 1, tablero, exito);
                    deshacerMovimiento(celdaAIntentar, tablero);
                }
            }
        }
    }
}

void sudokuContadorDeSoluciones(int celdasRestantes, int tablero[9][9], int &contador)
{
    if (esSolucion(celdasRestantes))
    {
        contador++;
    }
    else
    {
        Posicion celdaAIntentar = proximaCelda(tablero);
        // movimientos posibles
        for (int i = 1; i <= 9; i++)
        {
            // if puedo aplicar movimiento
            if (puedoAplicarMovimiento(celdaAIntentar, i, tablero))
            {
                aplicarMovimiento(celdaAIntentar, i, tablero);
                sudokuContadorDeSoluciones(celdasRestantes - 1, tablero, contador);
                deshacerMovimiento(celdaAIntentar, tablero);
            }
        }
    }
}

int calcularCeldasRestantes(int tablero[9][9])
{
    int toRet = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (tablero[i][j] == 0)
            {
                toRet++;
            }
        }
    }
    return toRet;
}

int main()
{
    int tablero[9][9] = {
        {5, 0, 0, 0, 0, 6, 0, 0, 0},
        {0, 0, 8, 5, 9, 4, 0, 0, 0},
        {2, 6, 0, 0, 3, 7, 9, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 4},
        {9, 0, 5, 0, 6, 1, 0, 2, 3},
        {8, 0, 3, 4, 0, 9, 0, 1, 6},
        {7, 3, 0, 0, 1, 8, 6, 0, 0},
        {4, 5, 1, 6, 0, 2, 3, 8, 9},
        {0, 0, 9, 3, 4, 5, 1, 7, 2}};

    int celdasRestantes = calcularCeldasRestantes(tablero);
    // bool exito = false;
    // sudoku(celdasRestantes, tablero, exito);

    int cantSoluciones = 0;
    sudokuContadorDeSoluciones(celdasRestantes, tablero, cantSoluciones);

    cout << "La cantidad de soluciones que existen son: " << cantSoluciones << endl;
}