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

bool puedoPodar(int actual, int mejor)
{
    return actual > mejor;   
}

bool esSolucion(Posicion actual, Posicion destino)
{
    return actual.columna == destino.columna && actual.fila == destino.fila;
}

bool esMejorSolucion(int pasoActual, int pasoMejor) 
{
    return pasoActual < pasoMejor;
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

bool posicionValida(Posicion nueva)
{
    return nueva.fila < N && nueva.fila >= 0 && nueva.columna < N && nueva.columna >= 0;
}

bool pasePorAhi(Posicion nueva, int **pasos) {
    return pasos[nueva.fila][nueva.columna] > 0;
}

bool esPared(Posicion nueva, int laberinto[8][8]) {
    return laberinto[nueva.fila][nueva.columna] == 1;
}

bool puedoAplicarMovimiento(Posicion nueva, int **pasos, int laberinto[8][8]) {
    return posicionValida(nueva) && !pasePorAhi(nueva, pasos) && !esPared(nueva, laberinto);
}

void aplicarMovimiento(Posicion nueva, int **pasos, int pasoActual) {
    pasos[nueva.fila][nueva.columna] = pasoActual;
}

void deshacerMovimiento(Posicion nueva, int** pasos)
{
    pasos[nueva.fila][nueva.columna] = 0;
}


void resolverLaberinto(Posicion actual, Posicion destino, int laberinto[8][8], int pasoActual, int **pasos,int &pasoMejor, int **& pasosMejor) {
    if(!puedoPodar(pasoActual, pasoMejor)){
        if(esSolucion(actual, destino) && esMejorSolucion(pasoActual, pasoMejor)) {
            clonarSolucion(pasos, pasosMejor);
            pasoMejor = pasoActual;
        }else {
            // movimientosPosibles
            int dFila[4] = {-1, 1, 0, 0};
            int dColu[4] = { 0, 0,-1, 1};
            for (int i = 0; i < 4; i++)
            {
                Posicion nueva = {actual.fila + dFila[i], actual.columna + dColu[i] };
                if (puedoAplicarMovimiento(nueva, pasos, laberinto)) {
                    aplicarMovimiento(nueva, pasos, pasoActual);
                    resolverLaberinto(nueva, destino, laberinto, pasoActual + 1, pasos, pasoMejor, pasosMejor);
                    deshacerMovimiento(nueva, pasos);
                }
            }
        }
    }
}

void imprimirTablero(int **pasos, int laberinto[8][8])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(laberinto[i][j]) {
                cout << "[**] ";
            }else{
                if (pasos[i][j] > 0)
                {
                    if(pasos[i][j] >= 10){
                        cout << "[" << pasos[i][j] << "] ";
                    }else{
                        cout << "[ " << pasos[i][j] << "] ";
                    }
                    
                }
                else
                {
                    cout << "[  ] ";
                }
            }
            
        }
        cout << endl;
    }
}

int main()
{
    
    int laberinto[8][8] = {
        {0,0,0,0,0,0,0,1},
        {0,1,1,0,1,1,0,0},
        {0,0,0,0,0,1,1,0},
        {0,1,1,1,0,0,0,1},
        {0,0,1,1,0,1,0,0},
        {0,0,0,1,0,1,0,1},
        {0,1,0,0,0,1,0,0},
        {1,1,1,0,0,1,0,0}
    };

    Posicion inicial = {0, 0};
    Posicion destino = {N - 1, N - 1};

    int **pasos = new int *[N];
    int **mejorCamino = new int *[N];

    for (int i = 0; i < N; i++)
    {
        pasos[i] = new int[N]();
        mejorCamino[i] = new int[N]();
    }
    pasos[inicial.fila][inicial.columna] = 1;

    int mejoresPasosValor = INT_MAX;

    resolverLaberinto(inicial, destino, laberinto, 2, pasos, mejoresPasosValor, mejorCamino);

    imprimirTablero(mejorCamino, laberinto);

}