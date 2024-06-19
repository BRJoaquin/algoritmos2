#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"

using namespace std;

// Ejericicio 2

int lucas(int n, int a, int b)
{
    int *tab = new int[n + 1]();
    tab[0] = a;
    tab[1] = b;
    for (int i = 2; i <= n; i++)
    {
        tab[i] = tab[i - 1] + tab[i - 2];
    }
    return tab[n];
}

// Ejercicio 3

// dimesiones del tablero
int N = 8;

struct Pos
{
    int fila;
    int col;
};

bool hayQuePodar(int cantPasos, int mejorPasos)
{
    return cantPasos > mejorPasos;
}

bool esSolucion(Pos actual, Pos destino)
{
    return actual.fila == destino.fila && actual.col == destino.col;
}

bool esMejorSolucion(int cantPasos, int mejorPasos)
{
    return cantPasos < mejorPasos;
}

void clonarSolucion(List<Pos> *solActual, List<Pos> *&mejorSolucion)
{
    if (mejorSolucion != NULL)
    {
        delete mejorSolucion;
    }
    mejorSolucion = solActual->clone();
}

bool posValida(Pos nuevaPos)
{
    return nuevaPos.fila >= 0 && nuevaPos.fila < N && nuevaPos.col >= 0 && nuevaPos.col < N;
}

bool pase(Pos nuevaPos, List<Pos> *solActual)
{
    return solActual->contains(nuevaPos);
}

bool esMuro(Pos nuevaPos, bool **muro)
{
    return muro[nuevaPos.fila][nuevaPos.col];
}

bool puedoAplicarMovimiento(Pos nuevaPos, List<Pos> *solActual, bool **muro)
{
    return posValida(nuevaPos) && !pase(nuevaPos, solActual) && !esMuro(nuevaPos, muro);
}

void aplicarMovimiento(Pos nuevaPos, List<Pos> *solActual)
{
    solActual->insert(nuevaPos);
}

void quitarMovimiento(Pos nuevaPos, List<Pos> *solActual)
{
    solActual->remove(nuevaPos);
}

void camino(Pos actual, Pos destino, bool **muro, List<Pos> *solActual, int cantPasos, List<Pos> *&mejorSolucion, int &mejorPasos)
{
    if (!hayQuePodar(cantPasos, mejorPasos))
    {
        if (esSolucion(actual, destino) && esMejorSolucion(cantPasos, mejorPasos))
        {
            clonarSolucion(solActual, mejorSolucion);
            mejorPasos = cantPasos;
        }
        else
        {
            // movimientos posibles
            int dFila[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dColu[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
            bool esMovDiagonal[8] = {true, false, true, false, false, true, false, true};
            for (int mov = 0; mov < 8; mov++)
            {
                Pos nuevaPos = {actual.fila + dFila[mov], actual.col + dColu[mov]};
                int sumaACantPasos = esMovDiagonal[mov] ? 2 : 1;
                if (puedoAplicarMovimiento(nuevaPos, solActual, muro))
                {
                    aplicarMovimiento(nuevaPos, solActual);
                    camino(nuevaPos, destino, muro, solActual, cantPasos + sumaACantPasos, mejorSolucion, mejorPasos);
                    quitarMovimiento(nuevaPos, solActual);
                }
            }
        }
    }
}

List<Pos> *camino(int fO, int cO, int fD, int cD, bool **muros)
{
    Pos actual = {fO, cO};
    Pos destino = {fD, cD};
    List<Pos> *sandbox = new ListImp<Pos>();
    sandbox->insert(actual);
    List<Pos> *solucion = NULL;
    int mejorPasos = INT_MAX;

    camino(actual, destino, muros, sandbox, 0, solucion, mejorPasos);

    return solucion;
}

int main()
{
}