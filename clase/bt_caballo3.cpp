#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"
#include "../Helpers/Iterator.h"

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

bool esMejorOIgualSolucion(int actual, int mejorHastaElMomento)
{
    return actual <= mejorHastaElMomento;
}


bool esMejorSolucion(int actual, int mejorHastaElMomento)
{
    return actual < mejorHastaElMomento;
}

int ** clonarSolucion(int **origen)
{
    int **destino = new int *[N];
    for (int i = 0; i < N; i++)
    {
        destino[i] = new int[N]();
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            destino[i][j] = origen[i][j];
        }
    }
    return destino;
}

bool tengoQuePodar(int actual, int mejorHastaElMomento) {
    return actual > mejorHastaElMomento;
}

void caballoOptEnum(Posicion actual, Posicion destino, int pasoActual, int **pasos, int &pasoMejor, List<int**> *mejoresSoluciones)
{
    if (!tengoQuePodar(pasoActual, pasoMejor))
    {
        if (esSolucion(actual, destino) && esMejorOIgualSolucion(pasoActual, pasoMejor))
        {
            if(esMejorSolucion(pasoActual, pasoMejor)){
                mejoresSoluciones->empty();
            }
            int** clonado = clonarSolucion(pasos);
            mejoresSoluciones->insert(clonado);
            pasoMejor = pasoActual;
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
                    caballoOptEnum(nueva, destino, pasoActual + 1, pasos, pasoMejor, mejoresSoluciones);
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

    int mejoresPasos = INT_MAX;
    List<int**> *mejoresSoluciones = new ListImp<int**>();
    caballoOptEnum(inicial, destino, 2, pasos, mejoresPasos, mejoresSoluciones);
    if(mejoresPasos != INT_MAX) {
        cout << "Se encontraron " << mejoresSoluciones->getSize() << " solucion/es" << endl;
        Iterator<int**>* it = mejoresSoluciones->getIterator();
        while(it->hasNext()) {
            int** solAux = it->next();
            cout << "Solucion:" << endl;
            imprimirTablero(solAux);
        }
    } else {
        cout << "No hay solucion!" << endl;
    }
}