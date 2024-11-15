#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int N = 9;

struct Celda
{
    int fila;
    int columna;
    Celda(int unaFila, int unaColumna)
    {
        fila = unaFila;
        columna = unaColumna;
    }
    Celda siguiente()
    {
        if (this->columna == N - 1)
        {
            return Celda(this->fila + 1, 0);
        }
        return Celda(this->fila, this->columna + 1);
    }
};

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

bool esSolucion(Celda act)
{
    return act.fila == N;
}

bool puedoAplicarMovimiento(bool *puedo, int n)
{
    return puedo[n];
}

void aplicarMovimiento(int **tablero, Celda act, int n)
{
    tablero[act.fila][act.columna] = n;
}

void deshacerMovimiento(int **tablero, Celda act)
{
    tablero[act.fila][act.columna] = 0;
}

bool * calcularMovimientosPosibles(int **tablero, Celda act) {
    bool* puedo = new bool[N+1]();
    for (int i = 1; i <= N; i++)
    {
        puedo[i] = true;
    }

    for (int i = 0; i < N; i++)
    {
        puedo[tablero[act.fila][i]] = false;
        puedo[tablero[i][act.columna]] = false;
    }

    int fCuadrante = (act.fila / 3) * 3;
    int cCuadrante = (act.columna / 3) * 3;

    for (int i = fCuadrante; i < fCuadrante + 3; i++)
    {
        for (int j = cCuadrante; j < cCuadrante + 3; j++)
        {
            puedo[tablero[i][j]] = false;
        }
    }
    return puedo;
}

void sudoku(int **tablero, Celda act, bool &exito)
{
    if (!exito)
    {
        if (esSolucion(act))
        {
            imprimirSolucion(tablero);
            exito = true;
        }
        else if (tablero[act.fila][act.columna] > 0)
        {
            sudoku(tablero, act.siguiente(), exito);
        }
        else
        {
            bool* puedo = calcularMovimientosPosibles(tablero, act);
            for (int n = 1; n <= N; n++)
            {
                if (puedoAplicarMovimiento(puedo, n))
                {
                    aplicarMovimiento(tablero, act, n);
                    sudoku(tablero, act.siguiente(), exito);
                    deshacerMovimiento(tablero, act);
                }
            }
        }
    }
}

int main()
{
    int **tablero = new int *[N]();
    for (int i = 0; i < N; i++)
    {
        tablero[i] = new int[N]();
    }
    tablero[0][1] = 1;
    tablero[0][3] = 6;
    tablero[0][4] = 5;
    tablero[0][7] = 4;

    tablero[1][0] = 8;
    tablero[1][8] = 9;

    tablero[2][7] = 3;

    tablero[3][0] = 1;
    tablero[3][1] = 5;

    tablero[4][1] = 7;
    tablero[4][2] = 6;

    tablero[5][4] = 2;
    tablero[5][5] = 8;

    tablero[6][3] = 7;
    tablero[6][6] = 5;

    tablero[7][0] = 3;
    tablero[7][3] = 4;

    tablero[8][6] = 2;
    bool exito = false;

    sudoku(tablero, Celda(0, 0), exito);
}