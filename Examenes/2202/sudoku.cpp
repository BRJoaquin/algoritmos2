#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

#define N 9
struct Coordenada
{
    int fila;
    int columna;
};
bool esSolucion(int cantidadRestantes)
{
    return cantidadRestantes == 0;
}
void imprimir(int tablero[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}
Coordenada proximaCoordenadaAProbar(int tablero[N][N])
{
    Coordenada coordenada;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (tablero[i][j] == 0)
            {
                coordenada.fila = i;
                coordenada.columna = j;
                return coordenada;
            }
        }
    }
    return coordenada;
}
bool coordenadaValida(int fila, int columna)
{
    return fila >= 0 && fila < N && columna >= 0 && columna < N;
}
bool *calcularValoresAProbar(int tablero[N][N], Coordenada coordenada)
{
    bool *valoresAProbar = new bool[N + 1]();
    for (int i = 1; i <= N; i++)
    {
        valoresAProbar[i] = true;
    }
    // Revisar fila
    for (int fila = 0; fila < N; fila++)
    {
        valoresAProbar[tablero[fila][coordenada.columna]] = false;
    }
    // Revisar columna
    for (int columna = 0; columna < N; columna++)
    {
        valoresAProbar[tablero[coordenada.fila][columna]] = false;
    }
    // Revisar cuadrante
    int filaInicio = 3* (coordenada.fila / 3);
    int columnaInicio = 3* (coordenada.columna / 3);
    for (int i = filaInicio; i < filaInicio + 3; i++)
    {
        for (int j = columnaInicio; j < columnaInicio + 3; j++)
        {
            valoresAProbar[tablero[i][j]] = false;
        }
    }
    return valoresAProbar;
}

void ponerNumero(int nroAProbar, Coordenada coordenada, int tablero[N][N])
{
    tablero[coordenada.fila][coordenada.columna] = nroAProbar;
}
void sacarNumero(Coordenada coordenada, int tablero[N][N])
{
    tablero[coordenada.fila][coordenada.columna] = 0;
}
void sudoku(int tablero[N][N], int cantidadRestantes, bool &exito)
{
    if (!exito)
    {
        if (esSolucion(cantidadRestantes))
        {
            imprimir(tablero);
            exito = true;
        }
        else
        {
            // calcular proximos movimientos
            Coordenada coordenada = proximaCoordenadaAProbar(tablero);
            bool *aProbar = calcularValoresAProbar(tablero, coordenada);
            for (int i = 1; i <= N; i++)
            {
                if (aProbar[i])
                {
                    ponerNumero(i, coordenada, tablero);
                    sudoku(tablero, cantidadRestantes - 1, exito);
                    sacarNumero(coordenada, tablero);
                }
            }
        }
    }
}
int calcularCantidadDeNumerosRestantes(int tablero[N][N])
{
    int cantidadRestantes = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (tablero[i][j] == 0)
            {
                cantidadRestantes++;
            }
        }
    }
    return cantidadRestantes;
}
int main()
{
    int tablero[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                         {5, 2, 0, 0, 0, 0, 0, 0, 0},
                         {0, 8, 7, 0, 0, 0, 0, 3, 1},
                         {0, 0, 3, 0, 1, 0, 0, 8, 0},
                         {9, 0, 0, 8, 6, 3, 0, 0, 5},
                         {0, 5, 0, 0, 9, 0, 6, 0, 0},
                         {1, 3, 0, 0, 0, 0, 2, 5, 0},
                         {0, 0, 0, 0, 0, 0, 0, 7, 4},
                         {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    bool exito = false;
    int cantidadDeNumeros = calcularCantidadDeNumerosRestantes(tablero);
    sudoku(tablero, cantidadDeNumeros, exito);
    if (!exito)
    {
        cout << "No hay solucion" << endl;
    }
    return 0;
}