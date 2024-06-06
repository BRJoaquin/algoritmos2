#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int N = 8;

struct Posicion
{
    int fila;
    int columna;
};

bool esSolucion(Posicion actual, Posicion destino)
{
    return actual.fila == destino.fila && actual.columna == destino.columna;
}

void imprimirTablero(int **pasos)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (pasos[i][j] > 0)
            {
                cout << "[" << pasos[i][j] << "] ";
            }
            else
            {
                cout << "[ ] ";
            }
        }
        cout << endl;
    }
}

void aplicarMovimiento(int **pasos, Posicion nueva, int nroPaso)
{
    pasos[nueva.fila][nueva.columna] = nroPaso;
}

void removerMovimiento(int **pasos, Posicion nueva)
{
    pasos[nueva.fila][nueva.columna] = 0;
}

bool puedoAplicarMovimiento(Posicion nueva, int **pasos)
{
    // es posicion valida
    return nueva.fila >= 0 && nueva.fila < N && nueva.columna >= 0 && nueva.columna < N && pasos[nueva.fila][nueva.columna] == 0;
}

void caballoEnum(Posicion actual, Posicion destino, int pasoActual, int **pasos)
{
    if (esSolucion(actual, destino))
    {
        cout << "encontre solucion!" << endl;
        imprimirTablero(pasos);
    }
    else
    {
        // veo los movimientos posibles
        int dFila[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        int dColu[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
        for (int i = 0; i < 8; i++)
        {
            Posicion nueva = {actual.fila + dFila[i], actual.columna + dColu[i]};
            // if puedo hacer movimiento
            if (puedoAplicarMovimiento(nueva, pasos))
            {
                aplicarMovimiento(pasos, nueva, pasoActual);
                caballoEnum(nueva, destino, pasoActual + 1, pasos);
                removerMovimiento(pasos, nueva);
            }
        }
    }
}

void caballoDec(Posicion actual, Posicion destino, int pasoActual, int **pasos, bool &exito)
{
    if (!exito)
    {
        if (esSolucion(actual, destino))
        {
            cout << "encontre solucion!" << endl;
            imprimirTablero(pasos);
            exito = true;
        }
        else
        {
            // veo los movimientos posibles
            int dFila[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
            int dColu[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
            for (int i = 0; i < 8; i++)
            {
                Posicion nueva = {actual.fila + dFila[i], actual.columna + dColu[i]};
                // if puedo hacer movimiento
                if (puedoAplicarMovimiento(nueva, pasos))
                {
                    aplicarMovimiento(pasos, nueva, pasoActual);
                    caballoDec(nueva, destino, pasoActual + 1, pasos, exito);
                    removerMovimiento(pasos, nueva);
                }
            }
        }
    }
}

bool esMejorSolucion(int actual, int mejorHastaElMomento)
{
    return actual < mejorHastaElMomento;
}

void clonarSolucion(int **origen, int **destino)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            destino[i][j] = origen[i][j];
        }
    }
}

bool tengoQuePodar(int actual, int mejorHastaElMomento) {
    return actual > mejorHastaElMomento;
}

void caballoOpt(Posicion actual, Posicion destino, int pasoActual, int **pasos, int &pasoMejor, int **pasosMejor)
{
    if (!tengoQuePodar(pasoActual, pasoMejor))
    {
        if (esSolucion(actual, destino) && esMejorSolucion(pasoActual, pasoMejor))
        {
            pasoMejor = pasoActual;
            clonarSolucion(pasos, pasosMejor);
        }
        else
        {
            // veo los movimientos posibles
            int dFila[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
            int dColu[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
            for (int i = 0; i < 8; i++)
            {
                Posicion nueva = {actual.fila + dFila[i], actual.columna + dColu[i]};
                // if puedo hacer movimiento
                if (puedoAplicarMovimiento(nueva, pasos))
                {
                    aplicarMovimiento(pasos, nueva, pasoActual);
                    caballoOpt(nueva, destino, pasoActual + 1, pasos, pasoMejor, pasosMejor);
                    removerMovimiento(pasos, nueva);
                }
            }
        }
    }
}

int main()
{
    Posicion inicial = {0, 0};
    Posicion destino = {N - 1, N - 1};

    int **pasos = new int *[N];
    for (int i = 0; i < N; i++)
    {
        pasos[i] = new int[N]();
    }
    pasos[inicial.fila][inicial.columna] = 1;
    // caballoEnum(inicial, destino, 2, pasos);
    bool exito = false;
    // caballoDec(inicial, destino, 2, pasos, exito);

    int mejoresPasos = INT_MAX;
    int **mejor = new int *[N];
    for (int i = 0; i < N; i++)
    {
        mejor[i] = new int[N]();
    }
    caballoOpt(inicial, destino, 2, pasos, mejoresPasos, mejor);
    if(mejoresPasos != INT_MAX) {
        imprimirTablero(mejor);
    } else {
        cout << "No hay solucion!" << endl;
    }
}