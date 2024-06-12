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

bool pasoPorDondeTeniaQuePasar(int **pasos, bool ** tieneQuePasar) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(tieneQuePasar[i][j] && pasos[i][j] == 0){
                return false;
            }
        }
    }
    return true;    
}

bool esSolucion(Posicion actual, Posicion destino, int **pasos, bool ** tieneQuePasar, int minPasos,int  maxPasos) 
{
    int cantPasos = pasos[actual.fila][actual.columna];
    return actual.fila == destino.fila && actual.columna == destino.columna && cantPasos >= minPasos && cantPasos <= maxPasos && pasoPorDondeTeniaQuePasar(pasos, tieneQuePasar);
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

bool puedoAplicarMovimiento(Posicion nueva, int **pasos, bool ** noTieneQuePasar,int pasoActual, int maxPasos)
{
    // es posicion valida
    return nueva.fila >= 0 && nueva.fila < N && nueva.columna >= 0 && nueva.columna < N && pasos[nueva.fila][nueva.columna] == 0 && !noTieneQuePasar[nueva.fila][nueva.columna] && pasoActual <= maxPasos;
}

void caballoDec(Posicion actual, Posicion destino, int pasoActual, int **pasos, bool &exito, bool ** tieneQuePasar, bool ** noTieneQuePasar, int minPasos, int maxPasos)
{
    if (!exito)
    {
        if (esSolucion(actual, destino, pasos, tieneQuePasar, minPasos, maxPasos))
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
                if (puedoAplicarMovimiento(nueva, pasos, noTieneQuePasar, pasoActual, maxPasos))
                {
                    aplicarMovimiento(pasos, nueva, pasoActual);
                    caballoDec(nueva, destino, pasoActual + 1, pasos, exito, tieneQuePasar, noTieneQuePasar,minPasos, maxPasos);
                    removerMovimiento(pasos, nueva);
                }
            }
        }
    }
}

// bool esMejorSolucion(int actual, int mejorHastaElMomento)
// {
//     return actual < mejorHastaElMomento;
// }

// void clonarSolucion(int **origen, int **destino)
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             destino[i][j] = origen[i][j];
//         }
//     }
// }

// bool tengoQuePodar(int actual, int mejorHastaElMomento) {
//     return actual > mejorHastaElMomento;
// }

// void caballoOpt(Posicion actual, Posicion destino, int pasoActual, int **pasos, int &pasoMejor, int **pasosMejor, bool ** tieneQuePasar, bool ** noTieneQuePasar, int minPasos, int maxPasos)
// {
//     if (!tengoQuePodar(pasoActual, pasoMejor))
//     {
//         if (esSolucion(actual, destino, pasos, tieneQuePasar) && esMejorSolucion(pasoActual, pasoMejor))
//         {
//             pasoMejor = pasoActual;
//             clonarSolucion(pasos, pasosMejor);
//         }
//         else
//         {
//             // veo los movimientos posibles
//             int dFila[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
//             int dColu[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
//             for (int i = 0; i < 8; i++)
//             {
//                 Posicion nueva = {actual.fila + dFila[i], actual.columna + dColu[i]};
//                 // if puedo hacer movimiento
//                 if (puedoAplicarMovimiento(nueva, pasos, noTieneQuePasar))
//                 {
//                     aplicarMovimiento(pasos, nueva, pasoActual);
//                     caballoOpt(nueva, destino, pasoActual + 1, pasos, pasoMejor, pasosMejor, tieneQuePasar, noTieneQuePasar, minPasos, maxPasos);
//                     removerMovimiento(pasos, nueva);
//                 }
//             }
//         }
//     }
// }

int main()
{
    Posicion inicial = {0, 0};
    Posicion destino = {N - 1, N - 1};

    int **pasos = new int *[N];
    bool **tieneQuePasar = new bool *[N];
    bool **noTieneQuePasar = new bool *[N];

    for (int i = 0; i < N; i++)
    {
        pasos[i] = new int[N]();
        tieneQuePasar[i] = new bool[N]();
        noTieneQuePasar[i] = new bool[N]();
    }
    pasos[inicial.fila][inicial.columna] = 1;

    tieneQuePasar[4][0] = true;
    tieneQuePasar[6][1] = true;
    tieneQuePasar[2][4] = true;
    tieneQuePasar[0][7] = true;
    tieneQuePasar[7][0] = true;

    noTieneQuePasar[3][3] = true;
    noTieneQuePasar[3][4] = true;
    noTieneQuePasar[3][5] = true;

    int minPasos = 10;
    int maxPasos = 15;

    bool exito = false;
    caballoDec(inicial, destino, 2, pasos, exito, tieneQuePasar, noTieneQuePasar, minPasos, maxPasos);
    if(!exito) {
        cout << "no hay solucion" << endl;
    }


    // int mejoresPasos = INT_MAX;
    // int **mejor = new int *[N];
    // for (int i = 0; i < N; i++)
    // {
    //     mejor[i] = new int[N]();
    // }

    // caballoOpt(inicial, destino, 2, pasos, mejoresPasos, mejor, tieneQuePasar, noTieneQuePasar);
    // if(mejoresPasos != INT_MAX) {
    //     imprimirTablero(mejor);
    // } else {
    //     cout << "No hay solucion!" << endl;
    // }
}