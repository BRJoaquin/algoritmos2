#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"
using namespace std;

// Ejercicio 1

// f(x) = 1 si x<=3
// f(x) = f(x-1) + f(x-2) * f(x-3) si x>3

int fMemoRec(unsigned int x, int *memo)
{
    if (x <= 3)
    {
        return 1;
    }
    if (memo[x] == 0)
    {
        memo[x] = fMemoRec(x - 1, memo) + fMemoRec(x - 2, memo) * fMemoRec(x - 3, memo);
    }
    return memo[x];
}

int fMemo(unsigned int x)
{
    int *memo = new int[x + 1]();
    return fMemoRec(x, memo);
}

int fTab(unsigned int x)
{
    if (x <= 3)
    {
        return 1;
    }
    int ant = 1;
    int antAnt = 1;
    int antAntAnt = 1;
    int sig;
    for (int i = 4; i <= x; i++)
    {
        sig = ant + antAnt * antAntAnt;
        antAntAnt = antAnt;
        antAnt = ant;
        ant = sig;
    }
    return sig;
}

// Ejercicio 2

struct Pos
{
    int fila;
    int col;
    bool operator==(const Pos &otro) const
    {
        return fila == otro.fila && col == otro.col;
    }
};


bool tengoQuePodar (List<Pos> *solActual, List<Pos> *&mejorSolucion) {
    return mejorSolucion != NULL && solActual->getSize() > mejorSolucion->getSize();
}

bool llegoAlDestino(Pos actual, Pos destino) {
    return actual.fila = destino.fila && actual.col == destino.col;
}

bool hizoMinPasos(int  minPasos, List<Pos> *solActual) {
    return solActual->getSize() >= minPasos;
}

bool esSolucion(Pos actual, Pos destino, int  minPasos, List<Pos> *solActual) {
    return llegoAlDestino(actual, destino) && hizoMinPasos(minPasos, solActual);
}

bool esMejorSolucion (List<Pos> *solActual, List<Pos> *&mejorSolucion) {
    return mejorSolucion == NULL || (mejorSolucion != NULL && solActual->getSize() < mejorSolucion->getSize());
}

void clonarSolucion(List<Pos> *solActual, List<Pos> *&mejorSolucion) {
    mejorSolucion = solActual->clone();
}


bool esCoordenadaValida(Pos nuevaPos, int f, int c) {
    return nuevaPos.fila >= 0 && nuevaPos.fila < f && nuevaPos.col >= 0 && nuevaPos.col < c;
}

bool puedoPasarSiEsMuro(bool useMuro, bool esMuro) {
    return !esMuro || !useMuro;
}

bool noSuperoMaxPasos(int max, int actual) {
    return actual <= max;
}

bool esProhibido(Pos Actual, List<Pos> * posProhibidas) {
    return posProhibidas->contains(Actual);
}

bool puedoAplicarMovimiento(Pos nuevaPos, bool useMuro, bool esMuro, int ** tablero,int filas,int columnas,int  maxPasos, List<Pos> * posProhibidas, int cantPasosActual) {
    // aca validaria si la coordenada e valida, si no pase por ahi y no supere la max pasos
    return esCoordenadaValida(nuevaPos, filas, columnas) && puedoPasarSiEsMuro(useMuro, esMuro) && noSuperoMaxPasos(maxPasos, cantPasosActual) && !esProhibido(nuevaPos, posProhibidas); 
}


void aplicarMovimiento(Pos nuevaPos, List<Pos> *solActual) {
    solActual->insert(nuevaPos);
} 

void deshacerMovimiento(Pos nuevaPos, List<Pos> *solActual) {
    solActual->remove(nuevaPos);
} 

void caminoBT(Pos actual, Pos destino, bool useMuro, int **tablero, int filas, int columnas, int minPasos, int maxPasos, List<Pos> *posProhibidas, List<Pos> *solActual, List<Pos> *&mejorSolucion)
{
    if(!tengoQuePodar(solActual, mejorSolucion)) {
        if(esSolucion(actual, destino, minPasos, solActual) && esMejorSolucion(solActual, mejorSolucion)) {
            clonarSolucion(solActual, mejorSolucion);
        } else {
            // movimientos posibles
            int dFila[4] = { -1, 1, 0,  0};
            int dColu[4] = {  0, 0, 1, -1};
            for (int i = 0; i < 4; i++)
            {
                Pos nuevaPos = {actual.fila + dFila[i], actual.col + dColu[i] };
                bool esMuro = tablero[nuevaPos.fila][nuevaPos.col];
                if(puedoAplicarMovimiento(nuevaPos, useMuro, esMuro, tablero, filas, columnas, maxPasos, posProhibidas,solActual->getSize())) {
                    aplicarMovimiento(actual, solActual);
                    caminoBT(nuevaPos, destino, esMuro, tablero, filas, columnas, minPasos, maxPasos, posProhibidas, solActual, mejorSolucion);
                    deshacerMovimiento(actual, solActual);
                }
            }
        }
    }
}

List<Pos> *camino(int **tablero, int filas, int columnas, Pos inicial, Pos destino, int minPasos, int maxPasos, List<Pos> *posProhibidas)
{
    List<Pos> * sandbox = new ListImp<Pos>();
    sandbox->insert(inicial);
    List<Pos> * solucion;
    caminoBT(inicial, destino, false, tablero, filas, columnas, minPasos, maxPasos, posProhibidas, sandbox, solucion);
    return solucion;
}

int main()
{
}